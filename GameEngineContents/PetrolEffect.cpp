#include "PetrolEffect.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "GlobalValue.h"
#include "MapModifier.h"
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
}

void PetrolEffect::Update(float _DeltaTime)
{
    int WindDir = GlobalValue::gValue.GetWindPhase();                           //WindPhase(-10 ~ 10)
  /*  float RandomX = 0.0f;

    if (0 > WindDir)
    {
        GameEngineRandom::MainRandom.RandomFloat(0, 15);
    }

    else if (0 < WindDir)
    {
        GameEngineRandom::MainRandom.RandomFloat(-15, 0);
    }
    else if (0 == WindDir)
    {
        GameEngineRandom::MainRandom.RandomFloat(-10, 10);
    }

    MoveDir.x += RandomX;*/

    MoveDir.x += WindDir;

    if (false == IsJump)
    {
        MoveDir.y -= 120.0f;                 //JumpPower
        IsJump = true;
    }


    for (int i = 0; i < NumOfPetrol; ++i)
    {
        GravityApplied(_DeltaTime);                                             //중력 적용


        if (true == IsGroundCheck(AllPetrolPos[i]))
        {
            MoveDir = float4::Zero;
            LiveTime -= _DeltaTime;
            WaitTime -= _DeltaTime;

            if (0.0f >= WaitTime)
            {
                CreateFireEffect(_DeltaTime);
                WaitTime = 1.5f;
            }

            if (0.0f >= LiveTime)
            {
                Death();
            }
        }
        else
        {
            float4 NextPos = AllPetrolPos[i] + (MoveDir * _DeltaTime);
            float4 CurPos = AllPetrolPos[i];
            NextPos = PullUp(NextPos, CurPos, _DeltaTime);                          //중력에 의해 하강한 위치값을 다시 땅위로 끌어올림

            AllPetrolPos[i] = float4::Zero;
            AllPetrolPos[i].x += (MoveDir.x * MoveSpeed);
            AllPetrolPos[i].y += (MoveDir.y * MoveSpeed);
            AllPetrol[i]->SetMove(AllPetrolPos[i] * _DeltaTime);

            AllPetrolPos[i] = AllPetrol[i]->GetPosition();
        }
    }

   

  
}



void PetrolEffect::CreatePetrolEffect(int _NumOfPetrol, float4 _StartPos)
{

    NumOfPetrol = _NumOfPetrol;

    AllPetrol.clear();
    AllPetrolPos.clear();

    AllPetrol.reserve(NumOfPetrol);
    AllPetrolPos.reserve(NumOfPetrol);

    for (int i = 0; i < NumOfPetrol; i++)
    {
        float4 Pos = _StartPos;
        Pos.x += GameEngineRandom::MainRandom.RandomFloat(-Scale, Scale);

        GameEngineRender* NewPetrol = CreateRender(WormsRenderOrder::MapObject);
        NewPetrol->SetPosition(Pos);

        NewPetrol->SetScale({ 30, 30 });

        NewPetrol->CreateAnimation({ .AnimationName = "Petrol_30", .ImageName = "petrol30.bmp", .Start = 0, .End = 19, .InterTime = 0.05f });
        NewPetrol->ChangeAnimation("Petrol_30");
        AllPetrol.push_back(NewPetrol);
        AllPetrolPos.push_back(Pos);
    }
}

void PetrolEffect::CreateFireEffect(float _DeltaTime)
{
    float RandX = GameEngineRandom::MainRandom.RandomFloat(-20, 20);
    Dir.x = RandX;
    for (int i = 0; i < NumOfPetrol; ++i)
    {

        AllPetrolPos[i].x += Dir.x * _DeltaTime*10;
        AllPetrolPos[i].y += Dir.y * _DeltaTime*10;
        MapModifier::MainModifier->CreateHole(AllPetrolPos[i], 6);
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


float4 PetrolEffect::PullUp(float4 _NextPos, float4 _CurPos, float _DeltaTime)
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

        _NextPos = _CurPos + MoveDir * _DeltaTime;

        if (Blue == ColImage->GetPixelColor(_NextPos, RGB(0, 0, 0)))
        {
            continue;
        }

        return _NextPos;
    }
}
