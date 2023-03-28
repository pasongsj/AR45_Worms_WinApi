#include "WeaponClusterBomb.h"
#include "Player.h"
#include "MapModifier.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>

WeaponClusterBomb::WeaponClusterBomb()
{
}

WeaponClusterBomb::~WeaponClusterBomb()
{
}

void WeaponClusterBomb::Start()
{
    // 수류탄 기본 설정 -- 상수값 조정 필요
    MoveSpeed = 1000.0f; // 임시값
    Gravity = 1.0f;// 임시값
    //Dmg = 0.0f;
    Timer = 2.0f;// 임시값
    Dir = float4::Right;
    BombScale = 120;
    WeaponName = "ClusterBomb";

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 이미지 이름 변수or 함수화 필요

    for (int i = 0;i < 6;i++)
    {
        GameEngineRender* NewClusterRender = CreateRender("cluster.bmp",WormsRenderOrder::Weapon);
        NewClusterRender->SetScale({ 24,24 });
        NewClusterRender->SetRotFilter("clusterRot.bmp");

        GameEngineCollision* NewClusterCollision = CreateCollision(WormsCollisionOrder::Weapon);
        NewClusterCollision->SetScale(NewClusterRender->GetScale());

        ClusterRender.push_back(NewClusterRender);
        ClusterCollision.push_back(NewClusterCollision);
        ClusterDir.push_back(float4::Zero);

    }
    ClusterOff();
    AllWeapons[WeaponName] = this;
    WeaponNumber = static_cast<int>(WeaponNum::ClusterBomb);

    // 터지는 애니메이션 랜더
    ExplosionCircle = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
    ExplosionCircle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End = 8, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->SetScale({ 240, 240 });

    ExplosionCircle->ChangeAnimation("Idle");
    ExplosionCircle->Off();

    ExplosionElipse = CreateRender("Elipse50.bmp", WormsRenderOrder::Weapon);
    ExplosionElipse->CreateAnimation({ .AnimationName = "ExplosionElipse", .ImageName = "Elipse50.bmp", .Start = 0, .End = 19, .InterTime = 0.03f , .Loop = false });
    ExplosionElipse->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Elipse50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionElipse->SetScale({ 360, 360 });

    ExplosionElipse->ChangeAnimation("Idle");
    ExplosionElipse->Off();

    BiffTextAnimation = CreateRender("Biff.bmp", WormsRenderOrder::Weapon);
    BiffTextAnimation->CreateAnimation({ .AnimationName = "Biff", .ImageName = "Biff.bmp", .Start = 0, .End = 11, .InterTime = 0.02f , .Loop = false });
    BiffTextAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Biff.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    BiffTextAnimation->SetScale({ 170, 170 });

    BiffTextAnimation->ChangeAnimation("Idle");
    BiffTextAnimation->Off();

    
    PootTextAnimation = CreateRender("Poot.bmp", WormsRenderOrder::Weapon);
    PootTextAnimation->CreateAnimation({ .AnimationName = "Poot", .ImageName = "Poot.bmp", .Start = 0, .End = 16, .InterTime = 0.02f , .Loop = false });
    PootTextAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Poot.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    PootTextAnimation->SetScale({ 170, 170 });

    PootTextAnimation->ChangeAnimation("Idle");
    PootTextAnimation->Off();


    // 차지 애니메이션
    ChargeAnimation = CreateRender(WormsRenderOrder::Weapon);
    ChargeAnimation->CreateAnimation({ .AnimationName = "Charge", .ImageName = "ChargeAni.bmp",.FilterName = "ChargeAniRot.bmp", .Start = 0, .End = 15, .InterTime = 0.1f , .Loop = false });
    ChargeAnimation->ChangeAnimation("Charge");
    ChargeAnimation->SetScale({64,192});
    ChargeAnimation->Off();
    ChargeAnimation->SetPosition({ 0,-10 });


    // 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
    AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
    AimingLine->SetScale({ 20,20 });

}

void WeaponClusterBomb::Update(float _DeltaTime)
{
    if (nullptr == WeaponRender) // 무기 랜더가 존재하지 않는 경우
    {
        WeaponClusterBombInit();
    }

    if (false == isFire)
    {
        SetCurPlayer(); // 플레이어 전환버튼 때문에 추가
        SetAimFrameIndex();
        if (false == isFire && AimIndex != NextAimIndex && CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON)
        {
            float Ratio = 6 * _DeltaTime;
            AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);
            CurPlayer->ChangePlayerAnimation("ClusterBombAim", static_cast<int>(AimIndex));
            AimingLine->On();
            AimingLine->SetPosition(Dir * 200); // 조준선 이동
            if (Dir.x > 0)
            {
                AimingLine->SetAngle(Dir.GetAnagleDeg());
            }
            else
            {
                AimingLine->SetAngle(-Dir.GetAnagleDeg());
            }
        }
        else
        {
            AimingLine->Off();
        }
    }

    Firing(_DeltaTime);
    ClusterFiring(_DeltaTime);

    if (true == isDone())
    {
        isWeaponDone = true;
        GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half()); //다음 턴 Player로 카메라 이동- 삭제필요
    }
}

void WeaponClusterBomb::SetAimFrameIndex()
{
    float Angle = Dir.GetAnagleDeg();


    int NewIndex = 0;
    if (Dir.x > 0 && Angle > 270)
    {
        Angle = Angle - 360;
    }

    else if (Dir.x < 0)
    {
        Angle = 180 - Angle;
    }

    NewIndex = Angle / 5 + 15;

    if (NewIndex < 0)
    {
        NewIndex = 0;
    }
    NextAimIndex = NewIndex;

}

void WeaponClusterBomb::ClusterFiring(float _DeltaTime)
{
    if (true == isExplosion)
    {
        if (true == ExplosionCircle->IsAnimationEnd())
        {
            ExplosionCircle->Off();
            ExplosionCircle->ChangeAnimation("Idle");
        }
        if (true == ExplosionElipse->IsAnimationEnd())
        {
            ExplosionElipse->Off();
            ExplosionElipse->ChangeAnimation("Idle");
        }
        if (true == BiffTextAnimation->IsAnimationEnd())
        {
            BiffTextAnimation->Off();
            BiffTextAnimation->ChangeAnimation("Idle");
        }
        if (true == PootTextAnimation->IsAnimationEnd())
        {
            PootTextAnimation->Off();
            PootTextAnimation->ChangeAnimation("Idle");
        }

        // 클러스터 카메라 이동 
        GetLevel()->SetCameraPos(ClusterRender[0]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());
        for (int i = 0;i < ClusterRender.size();i++)
        {
            if (false == ClusterCollision[i]->IsUpdate())
            {
                continue;
            }
            ClusterDir[i].y = ClusterDir[i].y + Gravity * 10 * _DeltaTime;

            ClusterRender[i]->SetAngle(ClusterDir[i].GetAnagleDeg());
            ClusterRender[i]->SetMove(ClusterDir[i] * _DeltaTime * ClusterSpeed);
            ClusterCollision[i]->SetMove(ClusterDir[i] * _DeltaTime * ClusterSpeed);

            if (true == CheckCollision(ClusterCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
            {

                ExplosionCircle->SetPosition(ClusterCollision[i]->GetPosition());
                ExplosionCircle->On();
                ExplosionCircle->ChangeAnimation("Explosion", 0);

                ExplosionElipse->SetPosition(ClusterCollision[i]->GetPosition());
                ExplosionElipse->On();
                ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);

                PootTextAnimation->SetPosition(ClusterCollision[i]->GetPosition());
                PootTextAnimation->On();
                PootTextAnimation->ChangeAnimation("Poot", 0);


                GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();
                BombCollision->SetPosition(ClusterCollision[i]->GetActorPlusPos());

                //AttackPlayer(BombCollision);

                MapModifier::MainModifier->CreateHole(ClusterCollision[i]->GetActorPlusPos(), 60);
                ClusterRender[i]->Off();
                ClusterCollision[i]->Off();
            }

        }
    }
}

void WeaponClusterBomb::Firing(float _DeltaTime)
{
    if (false == isFire) // 발사하기 전
    {
        float4 PlayerPos = CurPlayer->GetPos();
        Dir = GetShootDir();
        SetPos(PlayerPos);
        if (true == PressShoot())
        {
            if (false == ChargeAnimation->IsUpdate())
            {
                ChargeAnimation->On();
                ChargeAnimation->ChangeAnimation("Charge", 0);
                if (Dir.x > 0)
                {
                    ChargeAnimation->SetAngle((-Dir).GetAnagleDeg());
                }
                else
                {
                    ChargeAnimation->SetAngle(Dir.GetAnagleDeg());
                }
            }
            SetCharge();// 차징포인트 계산
        }
        if (isEndCharging() == true) // 발사체크
        {
            ChargeAnimation->Off();
            Dir *= Charge;
            isFire = true;
            WeaponRender->On();
        }

    }

    else // 발사 중
    {
        // 카메라 이동
        GetLevel()->SetCameraPos(WeaponRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());

        Timer -= _DeltaTime;
        if (false == isExplosion)// && true == isFire)
        {
            Dir.y = Dir.y + Gravity * _DeltaTime; // dt동안 중력의 영향

            WeaponRender->SetMove(Dir * MoveSpeed  * _DeltaTime);
            WeaponCollision->SetMove(Dir * MoveSpeed  * _DeltaTime);

            if (Timer > 2.0f - 0.1f)
            {
                return;
            }
            float4 CheckedCol = CheckCollisionSide(WeaponCollision);
            if (Dir.x * CheckedCol.x > 0) // 방향이 달라
            {
                WeaponRender->SetMove(-Dir * MoveSpeed  * _DeltaTime);
                WeaponCollision->SetMove(-Dir * MoveSpeed  * _DeltaTime);

                Dir.x = -Dir.x * 0.5f;										  //  x값은 마찰고려값
                Dir.y = -Dir.y * 0.25f;
            }

            else if (Dir.x * CheckedCol.x < 0 || CheckedCol.x == 0 && CheckedCol.y > 0)// 방향이 같아 or 좌우 이동x
            {
                WeaponRender->SetMove({ 0, -Dir.y * MoveSpeed  * _DeltaTime });
                WeaponCollision->SetMove({ 0, -Dir.y * MoveSpeed  * _DeltaTime });
                Dir.x = Dir.x * 0.5f;
                Dir.y = -Dir.y * 0.25f;
            }
        }

        //타이머 체크 -> 큰 폭발 체크
        if (Timer < 0 && isExplosion == false)
        {
            GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();
            BombCollision->SetPosition(GetPos() + WeaponCollision->GetPosition());

            AttackPlayer(BombCollision);

            ExplosionCircle->SetPosition(WeaponRender->GetPosition());
            ExplosionCircle->On();
            ExplosionCircle->ChangeAnimation("Explosion", 0);

            ExplosionElipse->SetPosition(WeaponRender->GetPosition());
            ExplosionElipse->On();
            ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);

            BiffTextAnimation->SetPosition(WeaponRender->GetPosition());
            BiffTextAnimation->On();
            BiffTextAnimation->ChangeAnimation("Biff", 0);

            MapModifier::MainModifier->CreateHole(GetPos() + WeaponCollision->GetPosition(), 120);
            isExplosion = true;
            WeaponRender->Off();
            WeaponCollision->Off();
            ClusterOn(WeaponRender->GetPosition());
        }
    }
}

void WeaponClusterBomb::SetCharge() // Charging으로 함수이름 통일
{
    if (Charge > GetChargeTime())
    {
        return;
    }
    if (GetChargeTime() > 1.5f) // 최대 2배 차징
    {
        Charge = 1.5f;
    }
    else if (GetChargeTime() < 0.5f)
    {
        Charge = 0.5f;
    }
    else {
        Charge = GetChargeTime();
    }
}

void WeaponClusterBomb::ResetWeapon()
{

    isFire = false;
    isExplosion = false;
    Timer = 2.0f;
    if (nullptr == WeaponRender)
    {
        return;
    }
    WeaponRender->On();
    WeaponRender->SetPosition(float4::Zero);

    WeaponCollision->On();
    WeaponCollision->SetPosition(float4::Zero);

}

void WeaponClusterBomb::WeaponClusterBombInit()
{
    WeaponRender = CreateRender(WormsRenderOrder::Weapon);		//렌더
    WeaponRender->SetImage("Clusterbomb.bmp");
    WeaponRender->SetRotFilter("ClusterbombRot.bmp");
    WeaponRender->SetScale({ 30,30 }); // 임시 설정 값 

    WeaponCollision = CreateCollision(WormsCollisionOrder::Weapon);	//콜리전
    WeaponCollision->SetScale(WeaponRender->GetScale());
    isFire = false;
    WeaponRender->Off();
}


void WeaponClusterBomb::ClusterOn(float4 _Pos)
{
    for (int i = 0;i < ClusterRender.size();i++)
    {
        ClusterRender[i]->On();
        ClusterCollision[i]->On();
        float Randx = GameEngineRandom::MainRandom.RandomFloat(-BombScale *0.5f, BombScale * 0.5f);
        float Randy = GameEngineRandom::MainRandom.RandomFloat(-BombScale * 0.5f, BombScale * 0.5f);
        float4 RandomPos = float4{ Randx, Randy };

        ClusterDir[i] = RandomPos.NormalizeReturn();
        ClusterRender[i]->SetPosition(_Pos/*+ RandomPos*/);
        ClusterCollision[i]->SetPosition(_Pos/*+ RandomPos*/);
    }
}
void WeaponClusterBomb::ClusterOff()
{
    for (int i = 0;i < ClusterRender.size();i++)
    {
        ClusterRender[i]->Off();
        ClusterCollision[i]->Off();
    }
}

bool WeaponClusterBomb::isDone()
{
    if (true == isFire && true == isExplosion)
    {
        for (int i = 0;i < ClusterCollision.size();i++)
        {
            if (true == ClusterCollision[i]->IsUpdate())
            {
                return false;
            }
        }
        return true;
    }
    return false;
}