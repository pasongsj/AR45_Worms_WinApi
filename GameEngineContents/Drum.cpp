#include "Drum.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"

Drum::Drum() 
{
}

Drum::~Drum() 
{
}

void Drum::Start()
{
    //Render
    MapObjRender = CreateRender(WormsRenderOrder::MapObject);
    MapObjRender->SetImage("oildrum1.bmp");
    MapObjRender->SetScale(ObjScale);
    MapObjRender->SetPosition(GetPos());

    //Animation
    MapObjRender->CreateAnimation({ .AnimationName = "OilDrum_1", .ImageName = "oildrum1.bmp", .Start = 0, .End = 19 });
    MapObjRender->CreateAnimation({ .AnimationName = "OilDrum_2", .ImageName = "oildrum2.bmp", .Start = 0, .End = 19 });
    MapObjRender->CreateAnimation({ .AnimationName = "OilDrum_3", .ImageName = "oildrum3.bmp", .Start = 0, .End = 19 });
    MapObjRender->CreateAnimation({ .AnimationName = "OilDrum_4", .ImageName = "oildrum4.bmp", .Start = 0, .End = 19 });


    MapObjRender->ChangeAnimation("OilDrum_1");

    //Collision
    MapObjCol = CreateCollision(static_cast<int>(WormsCollisionOrder::MapObject));
    MapObjCol->SetScale({ 20.0f, 27.0f });
    MapObjCol->SetPosition(GetPos());
    MapObjCol->SetDebugRenderType(CT_CirCle);

    SetColImage();
}

void Drum::Update(float _DeltaTime)
{
    if (GameEngineInput::IsDown("DebugCollision"))
    {
        GetLevel()->DebugRenderSwitch();
    }

    HitCheck();
    AnimCheck();




    //이동 관련
    GravityApplied(_DeltaTime);                                     //중력 적용
    float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
    NextPos = PullUp(NextPos, _DeltaTime);                          //중력에 의해 하강한 위치값을 다시 땅위로 끌어올림

    SetMove(MoveDir * _DeltaTime);                                  //이동 적용



}


void Drum::HitCheck()
{
    if (nullptr != MapObjCol)
    {
        if (true == MapObjCol->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Weapon), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }))
        {
            --Count;

            if (0 == Count)
            {
                int a = 9;
            }
        }
    }
}

void Drum::AnimCheck()
{
    switch (Count)
    {
    case 3:
    {
        MapObjRender->ChangeAnimation("OilDrum_2");
        break;
    }
    case 2:
    {
        MapObjRender->ChangeAnimation("OilDrum_3");
        break;
    }
    case 1:
    {
        MapObjRender->ChangeAnimation("OilDrum_4");
        break;
    }
    default:
        break;
    }
}

