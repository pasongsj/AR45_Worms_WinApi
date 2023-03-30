#include "HomingMissile.h"
#include "ContentsEnums.h"
#include "MapModifier.h"
#include "Player.h"

#include <ctime>

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>


HomingMissile::HomingMissile()
{

}

HomingMissile::~HomingMissile()
{

}

void HomingMissile::Start()
{
    HomingMissileInit();
    ChargingRenderInit();
    MarkerInit();
    DebrisInit();

    PrevTime = clock();

}

void HomingMissile::Update(float _DeltaTime)
{
    Timer();

    if (CurPlayer->GetPlayerState() == PlayerState::IDLE || CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON)
    {
        if (isShoot == false)
        {
            Aiming();
        }
    }
    else
    {
        CurIndex = 16;
        isAiming = false;
        isAimSet = false;
    }

    Charging();

    if (isAttack == true)
    {
        Firing(_DeltaTime);
    }
    
    if (isExplosion == true)
    {
        DebrisAnimation(_DeltaTime);
    }
    
    ExplosionAnimationOff();

    CameraUpdate(_DeltaTime);
}

void HomingMissile::Render(float _DeltaTime)
{
    if (true == GameEngineInput::IsDown("ChangePlayer"))
    {
        CurPlayer->ChangePlayerAnimation("HomingOff");
        SetCurPlayer();

        MoveSpeed = 900.0f;
        Accel = 0;
        isTimeSet = false;
        isHoming = false;
        isHomingSet = false;
        isAttack = false;
        isShoot = false;
        isExplosion = false;
        isAiming = false;
        isAimSet = false;
    }
}

void HomingMissile::HomingMissileInit()
{
    WeaponRender = CreateRender("HomingRed.bmp", static_cast<int>(WormsRenderOrder::Weapon));
    WeaponCollision = CreateCollision(static_cast<int>(WormsCollisionOrder::Weapon));

    WeaponRender->SetRotFilter("HomingRot.bmp");

    BombScale = 208;
    MinDmg = 35;
    MaxDmg = 75;

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

    WeaponRender->SetScaleToImage(); //임시 설정값
    WeaponRender->Off();

    WeaponCollision->SetScale({ 30,30 });
    WeaponCollision->Off();

    ScreenSize = GameEngineWindow::GetScreenSize();
    WeaponNumber = static_cast<int>(WeaponNum::HomingMissile);

    WeaponName = "Homing";

    Gravity = 0.0f; //임시 설정값

    MoveSpeed = 900.0f; //임시 설정값

    ExplosionEffectInit(BombScale);
    SetCurPlayer();
}

void HomingMissile::Firing(float _DeltaTime)
{
    if (isShoot == false)
    {
        WeaponRender->On();
        WeaponCollision->On();

        if(CurPlayer->GetPlayerDir() == float4::Right)
        {
            WeaponRender->SetPosition(CurPlayer->GetPos() + float4{ 15, -15 });
            WeaponCollision->SetPosition(CurPlayer->GetPos() + float4{ 15, -15 });
        }
        else if (CurPlayer->GetPlayerDir() == float4::Left)
        {
            WeaponRender->SetPosition(CurPlayer->GetPos() + float4{ -15, -15 });
            WeaponCollision->SetPosition(CurPlayer->GetPos() + float4{ -15, -15 });
        }

        isTimeSet = false;

        isShoot = true;
        isFire = true;
    }

    if(isHoming == false && isHomingSet == false)
    {
        MoveSpeed -= Accel;
        Accel += 10.0f * _DeltaTime;

        WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);
        WeaponCollision->SetMove(Dir * MoveSpeed * _DeltaTime);
      
        PrevAngle += 1080.0f * _DeltaTime;

        WeaponRender->SetAngle(PrevAngle);

        if (MoveSpeed < 0)
        {
            PrevDir = Dir;

            Dir = TargetPos - WeaponRender->GetPosition();
            Dir.Normalize();

            Accel = 0;

            TargetAngle = Dir.GetAnagleDeg();

            isHomingSet = true;
        }

        if (CheckCollision(WeaponCollision) == true)
        {
            Explosion();
        }
    }

    else if (isHoming == false && isHomingSet == true)
    {
        int PrevNum = PrevAngle / 360 ;
        int TargetNum = TargetAngle / 360;
        float PrevAngleRM = abs(PrevAngle) - abs(PrevNum) * 360;
        float TargetAngleRM = abs(TargetAngle) - abs(TargetNum) * 360;

        if (PrevAngleRM < TargetAngleRM)
        {
            PrevAngle -= 1080.0f * _DeltaTime;
        }
        else
        {
            PrevAngle = TargetAngle;

            WeaponRender->SetImage("HomingBlue.bmp");
            WeaponRender->SetRotFilter("HomingRot.bmp");

            isHoming = true;
        }

        WeaponRender->SetAngle(-PrevAngle);
    }

    else if(isHoming == true && isHomingSet == true)
    {
        MakeSmoke();

        MoveSpeed += Accel;
        Accel += 50.0f * _DeltaTime;

        WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);
        WeaponCollision->SetMove(Dir * MoveSpeed * _DeltaTime);

        TargetAngle = -Dir.GetAnagleDeg();

        if (CheckCollision(WeaponCollision) == true)
        {
            Explosion();
        }

        WeaponRender->SetAngle(TargetAngle);
    }
}

void HomingMissile::Aiming()
{

    if (GameEngineInput::IsKey("LeftMouseClick") == false)
    {
        GameEngineInput::CreateKey("LeftMouseClick", VK_LBUTTON);
    }

    if (GameEngineInput::IsDown("LeftMouseClick"))
    {
        TargetPos = GetLevel()->GetMousePosToCamera();
        Marker->On();
        Marker->SetPosition(TargetPos);
        Marker->ChangeAnimation("MarkerOn");
    }

    if(isAimSet == true)
    {
        Dir = GetShootDir();

        float Angle = Dir.GetAnagleDeg();

        if (Dir.x > 0 && Angle > 270)
        {
            Angle = Angle - 360;
        }

        else if (Dir.x < 0)
        {
            Angle = 180 - Angle;
        }

        AngleIndex = Angle / 5 + 15;

        if (AngleIndex < 0)
        {
            AngleIndex = 0;
        }

        if (AngleIndex == CurIndex)
        {
            CurPlayer->ChangePlayerAnimation("HomingAim", AngleIndex);
        }

        else if (AngleIndex > CurIndex)
        {
            AngleTimeCount += TimeCount;

            if (AngleTimeCount >= 0.01f)
            {
                ++CurIndex;
                CurPlayer->ChangePlayerAnimation("HomingAim", CurIndex);
                AngleTimeCount = 0;
            }
        }
        else if (AngleIndex < CurIndex)
        {
            AngleTimeCount += TimeCount;

            if (AngleTimeCount >= 0.01f)
            {
                --CurIndex;
                CurPlayer->ChangePlayerAnimation("HomingAim", CurIndex);
                AngleTimeCount = 0;
            }
        }
    }

    if (isAimSet == false)
    {
        AngleIndex = 16;
        CurPlayer->ChangePlayerAnimation("HomingAim", AngleIndex);
        isAimSet = true;
    }
}

void HomingMissile::Explosion()
{
    if (WeaponRender->IsUpdate() == true)
    {
        MapModifier::MainModifier->CreateHole(WeaponRender->GetActorPlusPos(), BombScale);

        ExplosionCircle->SetPosition(WeaponRender->GetPosition());
        ExplosionCircle->On();
        ExplosionCircle->ChangeAnimation("Explosion", 0);

        ExplosionElipse->SetPosition(WeaponRender->GetPosition());
        ExplosionElipse->On();
        ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);

        PootTextAnimation->SetPosition(WeaponRender->GetPosition());
        PootTextAnimation->On();
        PootTextAnimation->ChangeAnimation("Poot", 0);

        DamageToPlayer();
    }

    WeaponRender->Off();
    WeaponCollision->Off();

    Marker->Off();

    isExplosion = true;
}

void HomingMissile::CameraUpdate(float _DeltaTime)
{
    if (isAttack == false)
    {
        return;
    }

    if (isExplosion == false)
    {
        GetLevel()->SetCameraPos(WeaponRender->GetActorPlusPos() - ScreenSize.half());
    }
    else
    {
        float a = CameraTimeCount;

        CameraTimeCount += TimeCount;
        
        if (CameraTimeCount >= 2.0f && fLerpRatio < 1)
        {
            CurPlayerPos = CurPlayer->GetPos();
            PrevCamPos = GetLevel()->GetCameraPos();
            fLerpRatio += _DeltaTime * fLerpSpeed;
            GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
        }
        else if (fLerpRatio >= 1)
        {
            isWeaponDone = true;
        }
    }
}



void HomingMissile::DamageToPlayer()
{
 
    std::vector<GameEngineCollision*> CollisionPlayer;

    MapModifier::MainModifier->SetModifierColScale({BombScale, BombScale});
    GameEngineCollision* HoleCollision = MapModifier::MainModifier->GetModifierCollision();

    AttackPlayer(HoleCollision);
}

void HomingMissile::ChargingRenderInit()
{
    ChargingRender.resize(16);
    size_t Size = ChargingRender.size();

    for (int i = 0; i < Size; i++)
    {
        ChargingRender[i] = CreateRender("Charging.bmp", WormsRenderOrder::Weapon);
        ChargingRender[i]->SetFrame(i);
        ChargingRender[i]->SetScale({ 64, 64 });
        ChargingRender[i]->Off();
    }
}

void HomingMissile::ChargingRenderOn()
{
    if (CountingIndex >= ChargingRender.size())
    {
        return;
    }

    size_t Size = ChargingRender.size();
    float4 PlayerPos = CurPlayer->GetPos();

    float4 StartPos = PlayerPos + float4{ Dir.x * 5, Dir.y * 5 } + float4{ 0, -8 };

    ChargingTimeCount += TimeCount;

    if (ChargingTimeCount > 0.05)
    {
        ChargingRender[CountingIndex]->SetPosition(StartPos + float4{ Dir.x * 4 * (CountingIndex + 1), Dir.y * 4 * (CountingIndex + 1) });
        ChargingRender[CountingIndex]->On();

        ChargingTimeCount = 0;

        CountingIndex++;
    }


}

void HomingMissile::ChargingRenderOff()
{
    CountingIndex = 0;
    ChargingTimeCount = 0;
    size_t Size = ChargingRender.size();

    for (int i = 0; i < Size; i++)
    {
        ChargingRender[i]->Off();
    }
}


void HomingMissile::MarkerInit()
{
    Marker = CreateRender("Marker.bmp", WormsRenderOrder::Weapon);
    Marker->SetScale({ 60, 60 });

    Marker->CreateAnimation({ .AnimationName = "MarkerOn",.ImageName = "Marker.bmp",.Start = 0,.End = 9,.InterTime = 0.05 ,. Loop = true });
    Marker->Off();
}

void HomingMissile::Charging()
{
    if (GameEngineInput::IsPress("Shoot"))
    {
        ChargingRenderOn();
        MoveSpeed = GetChargeTime() * 900.0f;

        if (MoveSpeed > 1500.0f)
        {
            MoveSpeed = 1500.0f;
        }
    }
    else if (GameEngineInput::IsUp("Shoot"))
    {
        ChargingRenderOff();
        isAttack = true;
    }
}



void HomingMissile::DebrisAnimation(float _DeltaTime)
{
    if (isDebrisSet == false)
    {
        for (int i = 0; i < Sparks.size(); i++)
        {
            float X = GameEngineRandom::MainRandom.RandomFloat(-20, 20);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-20, 20);

            Sparks[i]->SetPosition(WeaponRender->GetPosition() + float4{ X,Y });
            Sparks[i]->ChangeAnimation("Spark");
            Sparks[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SparksDir.push_back(Dir);
        }

        for (int i = 0; i < Smokes.size(); i++)
        {
            float X = GameEngineRandom::MainRandom.RandomFloat(-40, 40);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-40, 40);

            Smokes[i]->SetPosition(WeaponRender->GetPosition() + float4{ X,Y });
            Smokes[i]->ChangeAnimation("Smoke");
            Smokes[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SmokesDir.push_back(Dir);
        }

        isDebrisSet = true;

    }
    else
    {
        for (int i = 0; i < Sparks.size(); i++)
        {
            Sparks[i]->SetMove(SparksDir[i] * 150.0f * _DeltaTime + float4{ 0, DebrisGravity } *_DeltaTime);
        }

        DebrisGravity += 250.0f * _DeltaTime;

        for (int i = 0; i < Smokes.size(); i++)
        {
            //Smokes[i]->SetMove(SmokesDir[i] * 25.0f * _DeltaTime);
            if (Smokes[i]->IsAnimationEnd() == true)
            {
                Smokes[i]->Off();
            }
        }
    }
}

void HomingMissile::DebrisInit()
{
    for (int i = 0; i < 9; i++)
    {
        GameEngineRender* Smoke = CreateRender("Smoke100.bmp", WormsRenderOrder::Weapon);
        Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "Smoke100.bmp", .Start = 0, .End = 27, .InterTime = 0.03f , .Loop = false });
        Smoke->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Smoke100.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Smoke->SetScale({ 134, 134 });
        Smoke->Off();

        Smokes.push_back(Smoke);
    }

    for (int i = 0; i < 10; i++)
    {
        GameEngineRender* Spark = CreateRender("Spark1.bmp", WormsRenderOrder::Weapon);
        Spark->CreateAnimation({ .AnimationName = "Spark", .ImageName = "Spark1.bmp", .Start = 0, .End = 31, .InterTime = 0.05f , .Loop = false });
        Spark->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Spark1.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Spark->SetScale({ 60, 60 });
        Spark->Off();

        Sparks.push_back(Spark);
    }
}


void HomingMissile::MakeSmoke()
{
    if (WeaponRender->IsUpdate() == false)
    {
        return;
    }

    SmokeTimeCount += TimeCount;

    if (SmokeTimeCount > 0.03)
    {
        float4 Homing = WeaponRender->GetActorPlusPos();

        GameEngineRender* Smoke = CreateRender("BazSmoke.bmp", static_cast<int>(WormsRenderOrder::Weapon));
        Smoke->SetPosition(Homing + float4{ 0, -15 });
        Smoke->SetScale({ 60, 60 });
        Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "BazSmoke.bmp", .Start = 0, .End = 63, .InterTime = 0.0001f , .Loop = false });
        Smoke->ChangeAnimation("Smoke");

        SmokeTimeCount = 0;
    }
}

void HomingMissile::Timer()
{
    CurTime = clock();

    TimeCount = (CurTime - PrevTime) / 1000.0f;

    PrevTime = CurTime;
}

void HomingMissile::ExplosionAnimationOff()
{
    if (isExplosion == true)
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
}