#include "HomingMissile.h"
#include "ContentsEnums.h"
#include "MapModifier.h"
#include "Player.h"

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
}

void HomingMissile::Update(float _DeltaTime)
{
    if (GameEngineInput::IsDown("Shoot"))
    {
        isAttack = true;
    }

    if (isAttack == true)
    {
        Firing(_DeltaTime);
    }

    if(isFire == false)
    {
        Aiming();
    }
}

void HomingMissile::Render(float _DeltaTime)
{
    //HDC _hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

    //Rectangle(_hdc, TargetPos.x - GetLevel()->GetCameraPos().x - 20,
    //    TargetPos.y - GetLevel()->GetCameraPos().y - 20,
    //    TargetPos.x - GetLevel()->GetCameraPos().x + 20,
    //    TargetPos.y - GetLevel()->GetCameraPos().y + 20);
       
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
    WeaponRender->On();

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
        WeaponRender->SetPosition(CurPlayer->GetPos());
        WeaponCollision->SetPosition(CurPlayer->GetPos());
        isFire = true;
    }

    //Gravity += 0.1f * _DeltaTime;
    //Dir += {Dir.x, Dir.y + Gravity};
    //Dir.Normalize();

    //WeaponRender->SetMove({Dir.x * 500.0f * _DeltaTime, (Dir.y + Gravity) * 500.0f * _DeltaTime });
    //WeaponCollision->SetMove({ Dir.x * 500.0f * _DeltaTime, (Dir.y + Gravity) * 500.0f * _DeltaTime });

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
    }

    else if (isHoming == false && isHomingSet == true)
    {
        int PrevNum = PrevAngle / 360 ;
        int TargetNum = TargetAngle / 360;
        float PrevAngleRM = PrevAngle - PrevNum * 360;
        float TargetAngleRM = TargetAngle - TargetNum * 360;

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
        Accel += 10.0f * _DeltaTime;

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
    }

    if(GameEngineInput::IsPress("WeaponUp") == true)
    {
        Dir = GetShootDir();
        PrevAngle = Dir.GetAnagleDeg();
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
}