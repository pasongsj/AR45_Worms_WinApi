#include "WeaponDrill.h"
#include "MapModifier.h"
#include "ContentsEnums.h"
#include "Player.h"

#include <ctime>

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

WeaponDrill::WeaponDrill()
{
}

WeaponDrill::~WeaponDrill()
{
}

void WeaponDrill::Start()
{
    DrillInit();
    PrevTime = static_cast<float>(clock());
}

void WeaponDrill::Update(float _DeltaTime)
{
    Timer();

    if (GameEngineInput::IsDown("Shoot") == true)
    {
        isAttack = true;
        StartPos = CurPlayer->GetPos();
        CurPlayer->ChangePlayerAnimation("Drillfire");
    }

    if (isAttack == true)
    {
        Drilling(_DeltaTime);
    }

    if (isDrillEnd == true)
    {
        TurnChangeCount += TimeCount;

        if (TurnChangeCount >= 1.0f)
        {
            isWeaponDone = true;
        }
    }

}

void WeaponDrill::Render(float _DeltaTime)
{

}

void WeaponDrill::DrillInit()
{
    SetCurPlayer();

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

    ScreenSize = GameEngineWindow::GetScreenSize();

    WeaponNumber = static_cast<int>(WeaponNum::Drill);

    BombScale = 30;
    
    MinDmg = 10;
    MaxDmg = 10;

    HoleCollision = CreateCollision(WormsCollisionOrder::Weapon);
    HoleCollision->SetScale({ 30, 30 });

    WeaponName = "Drill";
}

void WeaponDrill::Timer()
{
    CurTime = static_cast<float>(clock());

    TimeCount = (CurTime - PrevTime) / 1000.0f;

    PrevTime = CurTime;
}

void WeaponDrill::Drilling(float _DeltaTime)
{
    isFire = true;

    DrillOnTime += TimeCount;

    GetLevel()->SetCameraPos(CurPlayer->GetPos() - GameEngineWindow::GetScreenSize().half());

    if (DrillOnTime >= 4.0f)
    {
        isAttack = false;
        isDrillEnd = true;
        CurPlayer->ChangePlayerAnimation("DrillOff");
        return;
    }

    DrillCycleTime += TimeCount;

    if (DrillCycleTime >= 0.2f)
    {
        DrillCycleTime = 0.0f;
        float4 HolePos = { StartPos.x, CurPlayer->GetPos().y};
        MapModifier::MainModifier->CreateHole(HolePos, static_cast<int>(BombScale));
        HoleCollision->SetPosition(HolePos);

        AttackPlayer(HoleCollision, false);
    }
}