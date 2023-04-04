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
    PetrolRender->SetScale({ 30, 30 });

    PetrolRender->CreateAnimation({ .AnimationName = "Petrol_30", .ImageName = "petrol30.bmp", .Start = 0, .End = 19, .InterTime = 0.05f });
    PetrolRender->ChangeAnimation("Petrol_30");

    PetrolCol = CreateCollision(static_cast<int>(WormsCollisionOrder::Petrol));
    PetrolCol->SetScale({ 5, 5 });
    PetrolCol->SetPosition(GetPos());
}

void PetrolEffect::Update(float _DeltaTime)
{
    if (false == IsJump)
    {
        MoveDir.y -= 100.0f;                 //JumpPower
        IsJump = true;
    }

    if (false == IsWindEffectEnd)
    {
        int WindDir = GlobalValue::gValue.GetWindPhase();                           //WindPhase(-10 ~ 10)
        MoveDir.x += WindDir*0.1f;
    }

    GravityApplied(_DeltaTime);
    
    SetMove(MoveDir * _DeltaTime);


    float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
    NextPos = PullUp(NextPos, _DeltaTime);                          //중력에 의해 하강한 위치값을 다시 땅위로 끌어올림

    //IsWallCheck(GetPos());

    LiveTime -= _DeltaTime;

    if (true == IsGroundCheck(GetPos()))
    {
        IsWindEffectEnd = true;
        WaitTime -= _DeltaTime;

        if (0.0f >= WaitTime)
        {
            CreateFireEffect(_DeltaTime);
           
            if (false == IsDamageToDrum)
            {
                IsDamageToDrum = true;
                //HitDrumCheck();
            }
            WaitTime = 0.3f;
        }
        MoveDir.y = 0.0f;
    }
    

    if (0.0f >= LiveTime)
    {
        Death();
    }
}


//보류
void PetrolEffect::HitDrumCheck()
{
    std::vector<GameEngineCollision*> CollisionDrum;


    if (true == PetrolCol->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Drum), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionDrum))
    {
        for (int i = 0; i < CollisionDrum.size(); i++)
        {
            dynamic_cast<Drum*>(CollisionDrum[i]->GetActor())->DamageDrum(1);
        }
    }

}


void PetrolEffect::CreateFireEffect(float _DeltaTime)
{
    float RandX = GameEngineRandom::MainRandom.RandomFloat(-20, 20);
    Dir.x = RandX;
    MoveDir.x += Dir.x * _DeltaTime * 10;

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

void PetrolEffect::IsWallCheck(float4 _Pos)
{
    float4 CheckRPos = _Pos + float4::Right;
    float4 checkLPos = _Pos + float4::Left;

    if (Blue == ColImage->GetPixelColor(CheckRPos, RGB(0, 0, 0)))
    {
        SetPos({ GetPos().x + 1, GetPos().y });
    }
    
    if (Blue == ColImage->GetPixelColor(checkLPos, RGB(0, 0, 0)))
    {
        SetPos({ GetPos().x - 1, GetPos().y });
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
