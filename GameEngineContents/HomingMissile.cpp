#include "HomingMissile.h"
#include "ContentsEnums.h"
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
    if (GameEngineInput::IsPress("Shoot"))
    {
        Firing(_DeltaTime);
    }
}

void HomingMissile::Render(float _DeltaTime)
{

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

    MoveSpeed = 0.0f; //임시 설정값

    SetCurPlayer();
}

void HomingMissile::Firing(float _DeltaTime)
{
    if (Dir == float4{0, 0})
    {
        WeaponRender->SetPosition(CurPlayer->GetPos());
        WeaponCollision->SetPosition(CurPlayer->GetPos());
        Dir = { 1, -10 };
    }
    Gravity += 0.1f * _DeltaTime;
    Dir += {Dir.x, Dir.y + Gravity};
    Dir.Normalize();

    WeaponRender->SetMove({Dir.x * 500.0f * _DeltaTime, (Dir.y + Gravity) * 500.0f * _DeltaTime });
    WeaponCollision->SetMove({ Dir.x * 500.0f * _DeltaTime, (Dir.y + Gravity) * 500.0f * _DeltaTime });

}