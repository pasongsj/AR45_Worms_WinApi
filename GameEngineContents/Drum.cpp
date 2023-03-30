#include "Drum.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "GlobalValue.h"
#include "MapModifier.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "Weapon.h"

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
    ExplosionEffectInit();
}

void Drum::Update(float _DeltaTime)
{
    if (GameEngineInput::IsDown("DebugCollision"))
    {
        GetLevel()->DebugRenderSwitch();
    }

    HitWeaponCheck();
    AnimCheck();

    if (0 >= Gauge && false == IsExplosion)
    {
       MapObjRender->Off();
       Explosion();

       //Death();
    }




    //이동 관련
    GravityApplied(_DeltaTime);                                     //중력 적용
    float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
    NextPos = PullUp(NextPos, _DeltaTime);                          //중력에 의해 하강한 위치값을 다시 땅위로 끌어올림

    SetMove(MoveDir * _DeltaTime);                                  //이동 적용
}


void Drum::HitWeaponCheck()
{
    if (nullptr != MapObjCol)
    {
        if (true == MapObjCol->Collision({.TargetGroup = static_cast<int>(WormsCollisionOrder::Weapon), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }))
        {
            //현재 턴에서 무기 충돌체와 충돌했을때 드릴이면 데미지 받지 않음
            //Air Strike의 사정권 내에서 충돌하면 바로 터져야 함
         /*   Player* CurPlayer = GlobalValue::gValue.GetPlayer();
            std::string WeaponName = CurPlayer->GetCurWeapon()->GetWeaponName();

            if ("Drill" != WeaponName)
            {
            }*/
                Gauge -= 50;
        }
    }
}

void Drum::HitPlayerCheck()
{
    float4 Pos = GetPos();
    MapModifier::MainModifier->SetModifierColScale({ 50, 50 });                                              //Modifier 충돌체의 크기를 먼저 세팅
    MapModifier::MainModifier->CreateHole(Pos, BombScale);

    GameEngineCollision* ModifierCollision = MapModifier::MainModifier->GetModifierCollision();

    std::vector<GameEngineCollision*> CollisionPlayer;
    if (true == ModifierCollision->Collision({.TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle}, CollisionPlayer))
    {
        for (int i = 0; i < CollisionPlayer.size(); i++)
        {
            Player* ColPlayer = dynamic_cast<Player*>(CollisionPlayer[i]->GetActor());
            float4 Dir = ColPlayer->GetPos() - MapModifier::MainModifier->GetModifierCollision()->GetActorPlusPos();
            Dir.Normalize();

            ColPlayer->Damaged(Dmg, Dir, 300);


        }
    }
}

void Drum::AnimCheck()
{

    if (100 >= Gauge && 50 < Gauge)
    {
        MapObjRender->ChangeAnimation("OilDrum_2");
    }
    else if (50 >= Gauge && 0 < Gauge)
    {
        MapObjRender->ChangeAnimation("OilDrum_3");
    }
    else if (0 >= Gauge)
    {
        MapObjRender->ChangeAnimation("OilDrum_4");
    }
}

void Drum::Explosion() //폭발
{
    if (CheckCollision(MapObjCol) == true)
    {
        return;
    }
    else
    {
        ExplosionCircle->SetPosition(MapObjRender->GetPosition());
        ExplosionCircle->On();
        ExplosionCircle->ChangeAnimation("Explosion", 0);

        ExplosionElipse->SetPosition(MapObjRender->GetPosition());
        ExplosionElipse->On();
        ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);




        if (true == ExplosionCircle->GameEngineRender::IsAnimationEnd())
        {
            ExplosionAnimationOff();
        }

      
        HitPlayerCheck();                                                                       //플레이어에게 데미지 적용(폭발 반경에 있다면)


        IsExplosion = true;
    }
   


}

bool Drum::CheckCollision(GameEngineCollision* _Col)
{
    if (nullptr == _Col)
    {
        MsgAssert("체크할 콜리전이 없습니다.");
    }

    //맵체크
    if (Blue == ColImage->GetPixelColor(_Col->GetActorPlusPos(), Blue) && _Col->GetActorPlusPos().y > 0)               //맵에 닿으면 사라짐
    {
        return true;
    }

    //맵 밖으로 나갔는지 체크
    float4 _Pos = _Col->GetPosition();
    if (!(-640 <= _Pos.x && _Pos.x < 4480 && -743 <= _Pos.y && _Pos.y < 1310))
    {
        return true;
    }

    return false;
}

void Drum::ExplosionEffectInit()
{
    ExplosionCircle = CreateRender("circle50.bmp", WormsRenderOrder::MapObject);
    ExplosionCircle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End = 8, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->SetScale({ 100, 100 });

    ExplosionCircle->ChangeAnimation("Idle");
    ExplosionCircle->Off();

    ExplosionElipse = CreateRender("Elipse50.bmp", WormsRenderOrder::MapObject);
    ExplosionElipse->CreateAnimation({ .AnimationName = "ExplosionElipse", .ImageName = "Elipse50.bmp", .Start = 0, .End = 19, .InterTime = 0.03f , .Loop = false });
    ExplosionElipse->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Elipse50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionElipse->SetScale({ 150, 150 });

    ExplosionElipse->ChangeAnimation("Idle");
    ExplosionElipse->Off();

    PootTextAnimation = CreateRender("Poot.bmp", WormsRenderOrder::Weapon);
    PootTextAnimation->CreateAnimation({ .AnimationName = "Poot", .ImageName = "Poot.bmp", .Start = 0, .End = 17, .InterTime = 0.02f , .Loop = false });
    PootTextAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Poot.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    PootTextAnimation->SetScale({ 70, 70 });

    PootTextAnimation->ChangeAnimation("Idle");
    PootTextAnimation->Off();
}

void Drum::CreateSpark()
{
    int NumOfSpark = GameEngineRandom::MainRandom.RandomInt(3, 5);
    //방향은 한 번은 오른쪽 한 번은 왼쪽으로 가도록 반전을 주어야 함
    // 포물선 그림
    // 충돌맵에 닿으면 particle생성
    //GameEngineRender* Spark = GameEngineActor::CreateRender()
}

void Drum::ExplosionAnimationOff()
{
    if (ExplosionCircle->IsAnimationEnd() == true)
    {
        ExplosionCircle->ChangeAnimation("Idle");
        ExplosionCircle->Off();
    }
    if (ExplosionElipse->IsAnimationEnd() == true)
    {
        ExplosionElipse->ChangeAnimation("Idle");
        ExplosionElipse->Off();
    }

    if (PootTextAnimation->IsAnimationEnd() == true)
    {
        PootTextAnimation->ChangeAnimation("Idle");
        PootTextAnimation->Off();
    }
}