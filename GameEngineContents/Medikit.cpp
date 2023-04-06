#include "Medikit.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "GlobalValue.h"
#include "Map.h"
#include "Player.h"
#include "ContentsEnums.h"

Medikit::Medikit() 
{
}

Medikit::~Medikit() 
{
}


void Medikit::Start()
{
    //Render
    MapObjRender = CreateRender(WormsRenderOrder::MapObject);
    MapObjRender->SetImage("mcrate1.bmp");
    MapObjRender->SetScale(ObjScale);
    MapObjRender->SetPosition(GetPos());

    //Animation
    MapObjRender->CreateAnimation({ .AnimationName = "Medikit_Idle", .ImageName = "mcrate1.bmp", .Start = 0, .End = 11 });
    MapObjRender->CreateAnimation({ .AnimationName = "Medikit_Flying", .ImageName = "mcrate2.bmp", .Start = 9, .End = 9 });
    MapObjRender->CreateAnimation({ .AnimationName = "Right_Medikit_Flying", .ImageName = "mcrate2.bmp", .Start = 0, .End = 8 });
    MapObjRender->CreateAnimation({ .AnimationName = "Left_Medikit_Flying", .ImageName = "mcrate2.bmp", .Start = 10, .End = 18 });


    MapObjRender->ChangeAnimation("Right_Medikit_Flying");

    //Collision
    MapObjCol = CreateCollision(static_cast<int>(WormsCollisionOrder::Medikit));
    MapObjCol->SetScale({ 20.0f, 27.0f });
    MapObjCol->SetPosition(GetPos());
    MapObjCol->SetDebugRenderType(CT_CirCle);

    SetColImage();

}

void Medikit::Update(float _DeltaTime)
{
    if (true == IsWindApplied() && false == IsChangedAnim)             //처음 공중에서 낙하할 때, 낙하산 애니메이션 적용(1회)
    {
        //공중에 있는 동안은 바람의 영향을 받아야 함
        MoveDir.x += static_cast<float>(GlobalValue::gValue.GetWindPhase());

        DirCheck("Medikit_Flying");                                   //wind의 방향에 맞게 애니메이션 교체해야 함
    }

    if (false == IsWindApplied() && false == IsChangedAnim)           //땅에서 일정 거리이상 떨어져 있다면 기본 낙하 애니메이션으로 변경(더이상 바람의 영향은 받지 않음)
    {
        MapObjRender->ChangeAnimation("Medikit_Flying");
    }

    if (false == IsChangedAnim && true == IsGroundCheck())            //땅에 닿으면 기본 이미지로 교체
    {
        MoveDir = float4::Zero;
        IsChangedAnim = true;
        MapObjRender->ChangeAnimation("Medikit_Idle");
    }

    if (true == IsUnderWaterCheck())                                   //바다에 빠지면 액터 제거
    {
        Death();
    }

    RecoveryCheck();


    //이동 관련 함수
    GravityApplied(_DeltaTime);                                     //중력 적용
    float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
    NextPos = PullUp(NextPos, _DeltaTime);                          //중력에 의해 하강한 위치값을 다시 땅위로 끌어올림

    SetMove(MoveDir * _DeltaTime);                                  //이동 적용
}



void Medikit::DirCheck(const std::string_view& _AnimationName)
{
    std::string PrevDirString = DirString;

    int WindDir = GlobalValue::gValue.GetWindPhase();                           //WindPhase(-10 ~ 10)

    if (0 > WindDir)
    {
        DirString = "Left_";
    }

    if (0 < WindDir)
    {
        DirString = "Right_";
    }

    if (0 == WindDir)
    {
        MapObjRender->ChangeAnimation(_AnimationName.data());
        return;
    }

    if (PrevDirString != DirString)
    {
        MapObjRender->ChangeAnimation(DirString + _AnimationName.data());
    }
}


void Medikit::RecoveryCheck()
{
    std::vector<GameEngineCollision*> CollisionPlayer;

    if (true == MapObjCol->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionPlayer))
    {
        for (int i = 0; i < CollisionPlayer.size(); i++)
        {
            dynamic_cast<Player*>(CollisionPlayer[i]->GetActor())->UsingHealkit(Recovery);
        }
        Death();
    }
}

bool Medikit::IsWindApplied()
{
    float4 CheckPos = GetPos();                                                  //검사 대상 위치: 액터의 위치에서 오브젝트 스케일만큼 내려간 지점
    CheckPos.y += (ObjScale.y * 1.5f);

    if (Blue == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0)))
    {
        return false;
    }
    else
    {
        return true;
    }
}