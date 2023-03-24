#include "WeaponTorch.h"
#include "MapModifier.h"
#include "ContentsEnums.h"
#include "Player.h"

#include <ctime>

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>

WeaponTorch::WeaponTorch()
{
}

WeaponTorch::~WeaponTorch()
{
}

void WeaponTorch::Start()
{
    TorchInit();
}
void WeaponTorch::Update(float _DeltaTime)
{
    if (GameEngineInput::IsDown("Shoot"))
    {
        isAttack = true;
    }

    if(isAttack == true)
    {
        TorchOn();
    }
}

void WeaponTorch::Render(float _DeltaTime)
{

}

void WeaponTorch::TorchInit()
{
    SetCurPlayer();

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

    ScreenSize = GameEngineWindow::GetScreenSize();

    WeaponNumber = static_cast<int>(WeaponNum::AirStrike);

    BombScale = 10;
}

void WeaponTorch::TorchOn()
{
    TimeCounting();

    if (TimeCount >= 0.1f)
    {
        TimeCount = 0;
        MapModifier::MainModifier->CreateHole(CurPlayer->GetPos() + float4{ 10 , -10 }, 10);
        MapModifier::MainModifier->CreateHole(CurPlayer->GetPos() + float4{ 10 , -10 }, 10);
        MapModifier::MainModifier->CreateHole(CurPlayer->GetPos() + float4{ 20 , -10 }, 10);
    }
}

void WeaponTorch::TimeCounting()
{
    if (isTimeSet = false)
    {
        PrevTime = clock();
        isTimeSet = true;
    }

    CurTime = clock();

    TimeCount += (CurTime - PrevTime) / 1000;
    TimeCount_2 += (CurTime - PrevTime) / 1000;

    PrevTime = CurTime;
}