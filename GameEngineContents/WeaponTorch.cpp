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
        StartPos = CurPlayer->GetPos();
    }

    if(isAttack == true && isFireEnd == false)
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

    BombScale = 12;

    WeaponName = "Torch";
}

void WeaponTorch::TorchOn()
{
    if (TorchTime <= 0.0f)
    {
        isFireEnd = true;
        return;
    }

    CurPlayer->ChangePlayerAnimation("Torchfire");

    TorchTimerOn();

    float4 HolePos = { CurPlayer->GetPos().x, StartPos.y - BombScale};
    MapModifier::MainModifier->CreateHole(HolePos, BombScale);
  
}

void WeaponTorch::TorchTimerOn()
{
    if (TorchTimeSet == false)
    {
        TorchPrevTime = clock();
        TorchTimeSet = true;
    }
    
    TorchCurTime = clock();

    float TorchTimeCount = (TorchCurTime - TorchPrevTime) / 1000;

    TorchTime -= TorchTimeCount;

    TorchPrevTime = TorchCurTime;
}