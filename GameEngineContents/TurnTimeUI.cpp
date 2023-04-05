#include "TurnTimeUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnums.h"
#include "PlayLevel.h"
#include "GlobalValue.h"
#include "Player.h"
#include "Weapon.h"

TurnTimeUI::TurnTimeUI() 
{
}

TurnTimeUI::~TurnTimeUI() 
{
}

void TurnTimeUI::Start()
{
    fTurnTime = GlobalValue::gValue.GetPlayLevel()->GetLevelSetting().fTime;
    pTimeEdgeRender = CreateRender(WormsRenderOrder::UI);
    pTimeEdgeRender->SetImageToScaleToImage("TimerWindowB.bmp");
    pTimeEdgeRender->EffectCameraOff();
    pTimeEdgeRender->SetPosition({ 50,910 });

    pTimeRender.SetOwner(this);
    pTimeRender.SetImage("TimerNum.bmp",{16,34}, static_cast<int>(WormsRenderOrder::UI),RGB(255,0,255));
    pTimeRender.SetRenderPos({ 50,910 });
    pTimeRender.SetCameraEffect(false);
    pTimeRender.SetAlign(Align::Center);
    pTimeRender.SetValue(static_cast<int>(fTurnTime));

    pCurPlayer = GlobalValue::gValue.GetPlayer();
}

void TurnTimeUI::Update(float _DeltaTime)
{
    if (pCurPlayer != GlobalValue::gValue.GetPlayer())
    {
        pCurPlayer = GlobalValue::gValue.GetPlayer();
        fTurnTime = GlobalValue::gValue.GetPlayLevel()->GetLevelSetting().fTime;
        IsFire = false;
        return;
    }

    if (true == GameEngineCore::GetInst()->IsDebug())
    {
        return;
    }

    CheckFire();
    
    if (IsFire)
    {
        return;
    }
   

    fTurnTime -= _DeltaTime;

    if (fTurnTime <= 0.f)
    {
        GlobalValue::gValue.GetPlayer()->SetIsMyTurn(false);
        fTurnTime = GlobalValue::gValue.GetPlayLevel()->GetLevelSetting().fTime;
        return;
    }

    pTimeRender.SetValue(static_cast<int>(fTurnTime));
}

void TurnTimeUI::CheckFire()
{
    if (nullptr!=pCurPlayer->GetCurWeapon()&& GameEngineInput::IsDown("Shoot"))
    {
        IsFire = true;
    }
}
