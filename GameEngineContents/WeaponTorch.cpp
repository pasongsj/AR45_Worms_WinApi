#include "WeaponTorch.h"
#include "MapModifier.h"
#include "ContentsEnums.h"
#include "Player.h"

#include <ctime>

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

WeaponTorch::WeaponTorch()
{
}

WeaponTorch::~WeaponTorch()
{
}

void WeaponTorch::Start()
{
    TorchInit();
    PrevTime = clock();
}
void WeaponTorch::Update(float _DeltaTime)
{

    Timer();

    if (GameEngineInput::IsDown("Shoot") == true)
    {
        isAttack = true;
        StartPos = CurPlayer->GetPos();
        CurPlayer->ChangePlayerAnimation("Torchfire");
    }

    if(isAttack == true && isFireEnd == false)
    {
        TorchOn(_DeltaTime);
    }

    if (isFireEnd == true)
    {
        TurnChangeCount += TimeCount;

        if (TurnChangeCount >= 2.0f)
        {
            isWeaponDone = true;
        }
    }

    GetLevel()->SetCameraPos(CurPlayer->GetPos() - GameEngineWindow::GetScreenSize().half());
}

void WeaponTorch::Render(float _DeltaTime)
{

}

void WeaponTorch::TorchInit()
{
    SetCurPlayer();

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

    ScreenSize = GameEngineWindow::GetScreenSize();

    WeaponNumber = static_cast<int>(WeaponNum::Torch);

    BombScale = 20.0f;

    MinDmg = 10.0f;
    MaxDmg = 10.0f;

    MinKnockBackPower = 100.0f;
    MaxKnockBackPower = 100.0f;

    WeaponName = "Torch";
}

void WeaponTorch::TorchOn(float _DeltaTime)
{
    float4 PlayerPos = CurPlayer->GetPos();

    if (StartPos.y != PlayerPos.y)
    {
        CurPlayer->ChangePlayerAnimation("TorchOn", 7);

        TorchTime = 5.0f;
        isFireEnd = true;
        return;
    }

    isFire = true;

    if (TorchTime >= 5.0f)
    {
        CurPlayer->ChangePlayerAnimation("TorchOn", 7);
        isFireEnd = true;
        return;
    }

    TorchTime += TimeCount;

    float4 Dir = CurPlayer->GetPlayerDir();

    float4 HolePos = { PlayerPos.x + Dir.x * 10.0f , StartPos.y - BombScale * 0.5f};

    MapModifier::MainModifier->CreateHole(HolePos, BombScale);

    GameEngineCollision* HoleCollision = MapModifier::MainModifier->GetModifierCollision();
    HoleCollision->SetMove({ Dir.x * 10.0f , 0 });

    attackTimeCount += TimeCount;

    if(attackTimeCount >= 0.5f)
    {
        AttackPlayer(HoleCollision);
        attackTimeCount = 0;
    }

    CurPlayer->SetMove(Dir * 25.0f * _DeltaTime);
  
}

void WeaponTorch::Timer()
{
    CurTime = clock();

    TimeCount = (CurTime - PrevTime) / 1000.0f;

    PrevTime = CurTime;
}