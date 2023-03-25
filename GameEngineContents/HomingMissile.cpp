#include "HomingMissile.h"
#include "ContentsEnums.h"
#include "MapModifier.h"
#include "Player.h"

#include <ctime>

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
}

void HomingMissile::Update(float _DeltaTime)
{
    if (CurPlayer->GetPlayerState() == PlayerState::IDLE || CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON)
    {
        if (isAiming == false)
        {
            CurPlayer->ChangePlayerAnimation("HomingOn");

            if (CurPlayer->IsPlayerAnimationEnd() == true)
            {
                isAiming = true;
            }
        }
        else
        {
            if (isFire == false)
            {
                Aiming();
            }
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
        isFire = false;
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

    BombScale = 50;
    Dmg = 50;

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

    WeaponRender->SetScaleToImage(); //임시 설정값
    WeaponRender->Off();

    WeaponCollision->SetScale({ 30,30 });
    WeaponCollision->Off();

    ScreenSize = GameEngineWindow::GetScreenSize();
    WeaponNumber = static_cast<int>(WeaponNum::HomingMissile);

    WeaponName = "HomingMissile";

    Gravity = 0.0f; //임시 설정값

    MoveSpeed = 900.0f; //임시 설정값

    SetCurPlayer();
}

void HomingMissile::Firing(float _DeltaTime)
{
    if (isFire == false)
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

        Marker->Off();

        TimeCount = 0;
        isTimeSet = false;

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
            CurPlayer->SetPlayerAnimationFrame(AngleIndex);
        }

        else if (AngleIndex > CurIndex)
        {
            TimeCounting(&TimeCount);

            if (TimeCount >= 0.01f)
            {
                ++CurIndex;
                CurPlayer->SetPlayerAnimationFrame(CurIndex);
                TimeCount = 0;
            }
        }
        else if (AngleIndex < CurIndex)
        {
            TimeCounting(&TimeCount);

            if (TimeCount >= 0.01f)
            {
                --CurIndex;
                CurPlayer->SetPlayerAnimationFrame(CurIndex);
                TimeCount = 0;
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
    }

    WeaponRender->Off();
    WeaponCollision->Off();

    DamageToPlayer();

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

        TimeCounting(&CameraTimeCount);

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

void HomingMissile::TimeCounting(float* TimeCount)
{
    if (TimeCount == nullptr)
    {
        return;
    }

    if (*TimeCount == 0)
    {
        PrevTime = clock() - 1;
    }

    CurTime = clock();

    *TimeCount += (CurTime - PrevTime) / (float)1000.0f;

    PrevTime = CurTime;
}

void HomingMissile::DamageToPlayer()
{
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

    TimeCounting(&ChargingTimeCount);
    
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