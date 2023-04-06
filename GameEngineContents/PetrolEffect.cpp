#include "PetrolEffect.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "GlobalValue.h"
#include "MapModifier.h"
#include "Drum.h"
#include "ContentsEnums.h"

PetrolEffect::PetrolEffect() 
{
}

PetrolEffect::~PetrolEffect() 
{
}

void PetrolEffect::Start()
{
    SetColImage();

    PetrolRender = CreateRender(static_cast<int>(WormsRenderOrder::MapObject));
    PetrolRender->SetPosition(GetPos());
    PetrolRender->SetScale({ 45, 45 });

    PetrolRender->CreateAnimation({ .AnimationName = "petrol_40", .ImageName = "petrol40.bmp", .Start = 0, .End = 19, .InterTime = 0.05f });
    PetrolRender->ChangeAnimation("petrol_40");

    PetrolCol = CreateCollision(static_cast<int>(WormsCollisionOrder::Petrol));
    PetrolCol->SetScale({ 10, 10 });
    PetrolCol->SetPosition(GetPos());
}

void PetrolEffect::Update(float _DeltaTime)
{
    if (false == IsJump)
    {
        float RandDir = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(-1, 1));
        float RandSpeed = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(20, 80));
        MoveDir.x += RandDir * RandSpeed;
        MoveDir.y += JumpPower;
        IsJump = true;
    }


    if (false == IsGroundCheck(GetPos()) && false == IsGravityOff)
    {
        GravityApplied(_DeltaTime);
    
        SetMove(MoveDir * _DeltaTime);


        float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
        NextPos = PullUp(NextPos, _DeltaTime);                          //중력에 의해 하강한 위치값을 다시 땅위로 끌어올림
    }
    else
    {
        IsGravityOff = true;
    }

    LiveTime -= _DeltaTime;


    if (true == IsGroundCheck(GetPos()))
    {
        WaitTime -= _DeltaTime;

        if (0.0f >= WaitTime)
        {
            CreateFireEffect(_DeltaTime);
            HitDrumCheck();

            WaitTime = 0.2f;
        }
        MoveDir.y = 0.0f;
    }

    if (0.0f >= LiveTime)
    {
        Death();
    }
}


void PetrolEffect::HitDrumCheck()
{
    std::vector<GameEngineCollision*> CollisionDrum;

    if (true == PetrolCol->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Drum), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionDrum))
    {
        for (int i = 0; i < CollisionDrum.size(); i++)
        {
            dynamic_cast<Drum*>(CollisionDrum[i]->GetActor())->DamageDrum(20);
        }
    }

}


void PetrolEffect::CreateFireEffect(float _DeltaTime)
{
    float RandX = 0.0f;
    float WindDir = static_cast<float>(GlobalValue::gValue.GetWindPhase());                           //WindPhase(-10 ~ 10)

    if (0 > WindDir)
    {
       RandX = GameEngineRandom::MainRandom.RandomFloat(-50, -1);
    }
    else
    {
       RandX = GameEngineRandom::MainRandom.RandomFloat(1, 50);
    }


    MoveDir.x += RandX* _DeltaTime * MoveSpeed;
    MoveDir.y += 10*_DeltaTime * MoveSpeed;
   
    SetPos(GetPos() + MoveDir * _DeltaTime);

    MapModifier::MainModifier->CreateHole(GetPos(), 8, false);
}



float4 PetrolEffect::PullUp(float4 _NextPos, float _DeltaTime)
{
    if (nullptr == ColImage)
    {
        MsgAssert("ColImage가 nullptr입니다.");
    }

    if (Blue != ColImage->GetPixelColor(_NextPos, Blue))
    {
        return _NextPos;
    }

    while (true)
    {
         MoveDir.y -= 1;

        _NextPos = GetPos() + MoveDir * _DeltaTime;

        if (Blue == ColImage->GetPixelColor(_NextPos, RGB(0, 0, 0)))
        {
            continue;
        }

        return _NextPos;
    }
}

bool PetrolEffect::IsGroundCheck(float4 _Pos)
{
    float4 GroundCheckPos = _Pos + float4::Down;                                    //검사 대상 위치: 이미지의 중앙 하단부에서 한 칸 아랫 지점

    if (Blue == ColImage->GetPixelColor(GroundCheckPos, RGB(0, 0, 0)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PetrolEffect::GravityApplied(float _DeltaTime)
{
    MoveDir += (float4::Down * Gravity * _DeltaTime);
}
