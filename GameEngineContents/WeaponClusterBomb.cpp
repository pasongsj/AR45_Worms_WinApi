#include "WeaponClusterBomb.h"
#include "Player.h"
#include "MapModifier.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GlobalValue.h"

WeaponClusterBomb::WeaponClusterBomb()
{
}

WeaponClusterBomb::~WeaponClusterBomb()
{
}

void WeaponClusterBomb::Start()
{
    // 수류탄 기본 설정 -- 상수값 조정 필요
    MoveSpeed = 1200.0f; // 임시값
    Gravity = 1.0f;// 임시값
    Timer = 1.5;// 임시값
    //Dir = float4::Right;
    BombScale = 61;

    MaxDmg = 30;
    MinDmg = 14;
    MaxKnockBackPower = 122;
    MinKnockBackPower = 70;
    WeaponName = "ClusterBomb";

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 이미지 이름 변수or 함수화 필요
    WeaponNumber = static_cast<int>(WeaponNum::ClusterBomb);

    // 터지는 애니메이션 랜더
    ExplosionCircle = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
    ExplosionCircle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End = 8, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->SetScale({ 104, 104 });

    ExplosionCircle->ChangeAnimation("Idle");
    ExplosionCircle->Off();

    ExplosionElipse = CreateRender("Elipse50.bmp", WormsRenderOrder::Weapon);
    ExplosionElipse->CreateAnimation({ .AnimationName = "ExplosionElipse", .ImageName = "Elipse50.bmp", .Start = 0, .End = 19, .InterTime = 0.03f , .Loop = false });
    ExplosionElipse->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Elipse50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionElipse->SetScale({ 104 * 1.5f, 104 * 1.5f });

    ExplosionElipse->ChangeAnimation("Idle");
    ExplosionElipse->Off();

    BiffTextAnimation = CreateRender("Biff.bmp", WormsRenderOrder::Weapon);
    BiffTextAnimation->CreateAnimation({ .AnimationName = "Biff", .ImageName = "Biff.bmp", .Start = 0, .End = 11, .InterTime = 0.02f , .Loop = false });
    BiffTextAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Biff.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    BiffTextAnimation->SetScale({ 104, 104 });

    BiffTextAnimation->ChangeAnimation("Idle");
    BiffTextAnimation->Off();

    
    PowTextAnimation = CreateRender("Pow.bmp", WormsRenderOrder::Weapon);
    PowTextAnimation->CreateAnimation({ .AnimationName = "Pow", .ImageName = "Pow.bmp", .Start = 0, .End = 11, .InterTime = 0.02f , .Loop = false });
    PowTextAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Pow.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    PowTextAnimation->SetScale({ BombScale, BombScale });

    PowTextAnimation->ChangeAnimation("Idle");
    PowTextAnimation->Off();


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

    // 타이머
    TimerRenderBack = CreateRender("TimerBack.bmp", WormsRenderOrder::UI);
    TimerRenderBack->SetScaleToImage();
    TimerRenderBack->Off();

    TimerRender.SetOwner(this);
    TimerRender.SetCameraEffect(true);
    TimerRender.SetImage("RedNumberRender.bmp", { 15, 15 }, 10, RGB(255, 0, 255));
    TimerRender.SetAlign(Align::Center);
    TimerRender.SetValue(static_cast<int>(Timer));
    TimerRender.Off();

}

void WeaponClusterBomb::Update(float _DeltaTime)
{
    if (nullptr == WeaponRender) // 무기 랜더가 존재하지 않는 경우
    {
        WeaponClusterBombInit();
        SetCurPlayer();
    }

    if (false == isFire) //발사가 안되었다면
    {
        Aiming(_DeltaTime);
    }
    else // true == isFire
    {
        if (false == isExplosion) // 발사되고 아직 터지기 전
        {
            Firing(_DeltaTime);
        }
        else   
        {
            CheckAnimationDone();
        }
    }

    if (true == isClusterFire)
    {

        ClusterFiring(_DeltaTime);

        if (true == isClusterExplosion)
        {
            if (0.0f == WaitTime)
            {
                WaitTime = GetLiveTime() + 1.5f;
            }
            else if (GetLiveTime() > WaitTime && true == isDone())
            {
                isWeaponDone = true;
                GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half()); //다음 턴 Player로 카메라 이동- 삭제필요

            }
        }
    }


}
void WeaponClusterBomb::CheckAnimationDone()
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
    if (true == PowTextAnimation->IsAnimationEnd())
    {
        PowTextAnimation->Off();
        PowTextAnimation->ChangeAnimation("Idle");
    }
}

void WeaponClusterBomb::Aiming(float _DeltaTime)
{
    if (CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON) // 현재 플레이어가 무기 State
    {
        // 위치
        float4 PlayerPos = CurPlayer->GetPos() + float4{ 0,-15 };
        Dir = GetShootDir();
        SetPos(PlayerPos);

        // 조준선
        SetAimFrameIndex();
        AimingLine->On();

        // lerf한 프레임 변경
        float Ratio = (3 * _DeltaTime > 1 ? 1 : 3 * _DeltaTime);
        AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);

        // FrameIndex 설정
        CurPlayer->ChangePlayerAnimation("ClusterBombAim", static_cast<int>(AimIndex));
        AimingLine->SetPosition(Dir * 150 + float4{ 0,15 }); // 조준선 이동
        AimingLine->SetAngle(-Dir.GetAnagleDeg());

        // 발사 체크
        if (true == PressShoot())
        {
            if (false == isPress)
            {
                ChargeAnimation->On();
                ChargeAnimation->ChangeAnimation("Charge", 0);
                ChargeAnimation->SetAngle(270 - Dir.GetAnagleDeg());
                isPress = true;
            }
            SetCharge();// 차징포인트 계산
        }

        if (isEndCharging() == true) // 발사체크2
        {
            ChargeAnimation->Off();
            AimingLine->Off();

            WeaponRender->On();
            WeaponCollision->On();

            MoveSpeed *= Charge;
            isFire = true;
            // 타이머랜더
            TimerRenderBack->On();
            TimerRender.On();
        }

    }
    else
    {
        AimingLine->Off();
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

    NewIndex = static_cast<int>(Angle / 5 + 15);

    if (NewIndex < 0)
    {
        NewIndex = 0;
    }
    NextAimIndex = NewIndex;

}

void WeaponClusterBomb::ClusterFiring(float _DeltaTime)
{

    // 클러스터 카메라 이동 
    float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), ClusterRender[0]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 10);
    GetLevel()->SetCameraPos(CamPos);
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
        MakeSmoke();

        float4 CheckedCol = CheckCollisionSide(ClusterCollision[i]);
        if (CheckedCol.Size() > 0) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
        //if (true == CheckCollision(ClusterCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
        {
            isClusterExplosion = true;
            GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();
            BombCollision->SetPosition(GetPos() + WeaponCollision->GetPosition());
            BombCollision->SetScale(float4{ static_cast<float>(BombScale) });

            AttackPlayer(BombCollision); // 임시값

            // 약간의 수정이 필요함
            ExplosionCircle->SetPosition(ClusterCollision[i]->GetPosition());
            ExplosionCircle->On();
            ExplosionCircle->ChangeAnimation("Explosion", 0);

            ExplosionElipse->SetPosition(ClusterCollision[i]->GetPosition());
            ExplosionElipse->On();
            ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);

            PowTextAnimation->SetPosition(ClusterCollision[i]->GetPosition());
            PowTextAnimation->On();
            PowTextAnimation->ChangeAnimation("Pow", 0);

            MapModifier::MainModifier->CreateHole(ClusterCollision[i]->GetActorPlusPos(), static_cast<int>(BombScale));
            ClusterRender[i]->Off();
            ClusterCollision[i]->Off();
        }

    }
    
}


void WeaponClusterBomb::Firing(float _DeltaTime)
{
    // 발사중 true == isFire 

    // 카메라 이동
    float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), WeaponRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 10);
    GetLevel()->SetCameraPos(CamPos);

    Timer -= _DeltaTime;
    if (false == isExplosion)// && true == isFire)
    {
        Dir.y = Dir.y + Gravity * _DeltaTime; // dt동안 중력의 영향

        float4 MoveVec = CulWindMoveVec(_DeltaTime);

        WeaponRender->SetMove(MoveVec);
        WeaponCollision->SetMove(MoveVec);

        if (Timer > 1.5f - 0.08f)// 보정값 ( 땅에 박히는 오류 )
        {
            return;
        }
        float4 CheckedCol = CheckCollisionSide(WeaponCollision);
        if (Dir.x * CheckedCol.x > 0) // 방향이 달라
        {
            WeaponRender->SetMove(-MoveVec);
            WeaponCollision->SetMove(-MoveVec);

            Dir.x = -Dir.x * 0.5f;										  //  x값은 마찰고려값
            Dir.y = -Dir.y * 0.25f;
        }
        else if (Dir.x * CheckedCol.x < 0 || CheckedCol.x == 0 && CheckedCol.y > 0)// 방향이 같아 or 좌우 이동x
        {
            WeaponRender->SetMove({ 0, -MoveVec.y });
            WeaponCollision->SetMove({ 0, -MoveVec.y });
            Dir.x = Dir.x * 0.5f;
            Dir.y = -Dir.y * 0.25f;
        }
        else if (CheckedCol == float4::Up)
        {
            WeaponRender->SetMove(-MoveVec);
            WeaponCollision->SetMove(-MoveVec);
            Dir *= 0.1f;
        }
        TimerRenderBack->SetPosition(WeaponRender->GetPosition() - float4{ 30,30 });
        TimerRender.SetRenderPos(WeaponRender->GetPosition() - float4{ 30,30 });
        TimerRender.SetValue(static_cast<int>(Timer) + 1);
    }


    //타이머 체크 -> 큰 폭발 체크
    if (Timer < 0 && isExplosion == false)
    {
        TimerRenderBack->Off();
        TimerRender.Off();
        GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();
        BombCollision->SetPosition(GetPos() + WeaponCollision->GetPosition());
        BombCollision->SetScale(float4{ static_cast<float>(MainBombScale) });

        AttackPlayer(BombCollision);// 임시값

        ExplosionCircle->SetPosition(WeaponRender->GetPosition());
        ExplosionCircle->On();
        ExplosionCircle->ChangeAnimation("Explosion", 0);
        ExplosionCircle->SetScale({ BombScale,BombScale });

        ExplosionElipse->SetPosition(WeaponRender->GetPosition());
        ExplosionElipse->On();
        ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);
        ExplosionElipse->SetScale({ BombScale,BombScale });

        BiffTextAnimation->SetPosition(WeaponRender->GetPosition());
        BiffTextAnimation->On();
        BiffTextAnimation->ChangeAnimation("Biff", 0);

        MapModifier::MainModifier->CreateHole(GetPos() + WeaponCollision->GetPosition(), MainBombScale);
        isExplosion = true;
        WeaponRender->Off();
        WeaponCollision->Off();

        ClusterOn(WeaponRender->GetPosition());
        isClusterFire = true;
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


void WeaponClusterBomb::WeaponClusterBombInit()
{
    WeaponRender = CreateRender(WormsRenderOrder::Weapon);		//렌더
    WeaponRender->SetImage("Clusterbomb.bmp");
    WeaponRender->SetRotFilter("ClusterbombRot.bmp");
    WeaponRender->SetScale({ 30,30 }); // 임시 설정 값 

    WeaponCollision = CreateCollision(WormsCollisionOrder::Weapon);	//콜리전
    WeaponCollision->SetScale({15,25});
    isFire = false;
    WeaponRender->Off();
    WeaponCollision->Off();

    for (int i = 0;i < 6;i++)
    {
        GameEngineRender* NewClusterRender = CreateRender("cluster.bmp", WormsRenderOrder::Weapon);
        NewClusterRender->SetScale({ 24,24 });
        NewClusterRender->SetRotFilter("clusterRot.bmp");

        GameEngineCollision* NewClusterCollision = CreateCollision(WormsCollisionOrder::Weapon);
        NewClusterCollision->SetScale(NewClusterRender->GetScale());

        ClusterRender.push_back(NewClusterRender);
        ClusterCollision.push_back(NewClusterCollision);
        ClusterDir.push_back(float4::Zero);
        ClusterSmokeInterval.push_back(float4::Zero);

    }
    ClusterOff();
}

void WeaponClusterBomb::MakeSmoke()
{
    for (int i = 0;i < ClusterRender.size();i++)
    {
        float4 ClusterPos = ClusterRender[i]->GetPosition();
        if ((ClusterPos - ClusterSmokeInterval[i]).Size() > 70)
        {
            ClusterSmokeInterval[i] = ClusterPos;
            GameEngineRender* Smoke = CreateRender("BazSmoke.bmp", static_cast<int>(WormsRenderOrder::Weapon));
            Smoke->SetPosition(ClusterPos);
            Smoke->SetScale({ 60, 60 });
            Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "BazSmoke.bmp", .Start = 0, .End = 63, .InterTime = 0.00001f , .Loop = false });
            Smoke->SetAlpha(GameEngineRandom::MainRandom.RandomInt(100, 160));
            Smoke->ChangeAnimation("Smoke");
        }
    }
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
        ClusterSmokeInterval[i] = _Pos;
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
    if (true == isFire && true == isExplosion && true == isClusterFire)
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


float4 WeaponClusterBomb::CulWindMoveVec(float _DeltaTime)
{
    //if (abs(Dir.x * MoveSpeed) > 2000)
    //{
    //    return Dir * MoveSpeed * _DeltaTime;
    //}
    //Dir.x += GlobalValue::gValue.GetWindPhase() * 0.1f * _DeltaTime; 가속
    float4 ReturnVec = Dir * MoveSpeed * _DeltaTime;
    ReturnVec.x += (GlobalValue::gValue.GetWindPhase() / 7) * (MoveSpeed / 2) * _DeltaTime; // 등속
    return ReturnVec;
}