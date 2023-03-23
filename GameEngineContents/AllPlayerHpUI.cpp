#include "AllPlayerHpUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "GlobalValue.h"

AllPlayerHpUI* AllPlayerHpUI::AllHpUI = nullptr;
AllPlayerHpUI::AllPlayerHpUI() 
{
}

AllPlayerHpUI::~AllPlayerHpUI() 
{
}

void AllPlayerHpUI::SetAllPlayerHP()
{
    std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

    iPlayer0HP = dynamic_cast<Player*>(PlayerList[0])->GetPlayerHP();
    iPlayer1HP = dynamic_cast<Player*>(PlayerList[1])->GetPlayerHP();
    iPlayer2HP = dynamic_cast<Player*>(PlayerList[2])->GetPlayerHP();
    iPlayer3HP = dynamic_cast<Player*>(PlayerList[3])->GetPlayerHP();
    iPlayer4HP = dynamic_cast<Player*>(PlayerList[4])->GetPlayerHP();
    iPlayer5HP = dynamic_cast<Player*>(PlayerList[5])->GetPlayerHP();

    bSetHP = true;
}

void AllPlayerHpUI::Start()
{
    AllHpUI = this;
    float4 ScreenSize = GameEngineWindow::GetScreenSize();

    std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

    iPlayer0HP = dynamic_cast<Player*>(PlayerList[0])->GetPlayerHP();
    iPlayer1HP = dynamic_cast<Player*>(PlayerList[1])->GetPlayerHP();
    iPlayer2HP = dynamic_cast<Player*>(PlayerList[2])->GetPlayerHP();
    iPlayer3HP = dynamic_cast<Player*>(PlayerList[3])->GetPlayerHP();
    iPlayer4HP = dynamic_cast<Player*>(PlayerList[4])->GetPlayerHP();
    iPlayer5HP = dynamic_cast<Player*>(PlayerList[5])->GetPlayerHP();

    pPlayer0 = CreateRender(WormsRenderOrder::UI);
    pPlayer0->SetImageToScaleToImage("BottomHPbarB.bmp");
    pPlayer0->EffectCameraOff();
    pPlayer0->SetPosition({ ScreenSize.hx(),850.f });

    pPlayer1 = CreateRender(WormsRenderOrder::UI);
    pPlayer1->SetImageToScaleToImage("BottomHPbarG.bmp");
    pPlayer1->EffectCameraOff();
    pPlayer1->SetPosition({ ScreenSize.hx(),867.f });

    pPlayer2 = CreateRender(WormsRenderOrder::UI);
    pPlayer2->SetImageToScaleToImage("BottomHPbarP.bmp");
    pPlayer2->EffectCameraOff();
    pPlayer2->SetPosition({ ScreenSize.hx(),884.f });

    pPlayer3 = CreateRender(WormsRenderOrder::UI);
    pPlayer3->SetImageToScaleToImage("BottomHPbarR.bmp");
    pPlayer3->EffectCameraOff();
    pPlayer3->SetPosition({ ScreenSize.hx(),901.f });

    pPlayer4 = CreateRender(WormsRenderOrder::UI);
    pPlayer4->SetImageToScaleToImage("BottomHPbarS.bmp");
    pPlayer4->EffectCameraOff();
    pPlayer4->SetPosition({ ScreenSize.hx(),918.f });

    pPlayer5 = CreateRender(WormsRenderOrder::UI);
    pPlayer5->SetImageToScaleToImage("BottomHPbarY.bmp");
    pPlayer5->EffectCameraOff();
    pPlayer5->SetPosition({ ScreenSize.hx(),935.f });

}

void AllPlayerHpUI::Update(float _DeltaTime)
{

    if (true == bSetHP)
    {
        float fHpRatio0 = static_cast<float>(iPlayer0HP)  /100.f;
        float fHpRatio1 = static_cast<float>(iPlayer1HP)  /100.f;
        float fHpRatio2 = static_cast<float>(iPlayer2HP)  /100.f;
        float fHpRatio3 = static_cast<float>(iPlayer3HP)  /100.f;
        float fHpRatio4 = static_cast<float>(iPlayer4HP)  /100.f;
        float fHpRatio5 = static_cast<float>(iPlayer5HP)  /100.f;

        pPlayer0->SetScale({ 200 * fHpRatio0,17 });
        pPlayer1->SetScale({ 200 * fHpRatio1,17 });
        pPlayer2->SetScale({ 200 * fHpRatio2,17 });
        pPlayer3->SetScale({ 200 * fHpRatio3,17 });
        pPlayer4->SetScale({ 200 * fHpRatio4,17 });
        pPlayer5->SetScale({ 200 * fHpRatio5,17 });

        bSetHP = false;
    }
}

