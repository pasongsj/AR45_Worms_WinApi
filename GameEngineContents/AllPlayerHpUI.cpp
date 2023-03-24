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

    for (size_t i = 0; i < 6; i++)
    {
        vecPlayerCurHp[i] = dynamic_cast<Player*>(PlayerList[i])->GetPlayerHP();
    }

    bSetHP = true;
}

void AllPlayerHpUI::Start()
{
    AllHpUI = this;

    std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

    for (size_t i = 0; i < 6; i++)
    {
        vecPlayerHpBar.push_back(CreateRender(WormsRenderOrder::UI));
        vecPlayerCurHp.push_back(dynamic_cast<Player*>(PlayerList[i])->GetPlayerHP());
    }
    float4 rStartPos = StartPos;
    vecPlayerHpBar[0]->SetImageToScaleToImage("BottomHPbarB.bmp");
    vecPlayerHpBar[0]->EffectCameraOff();
    vecPlayerHpBar[0]->SetPosition(rStartPos);
    rStartPos.y += 17.f;

    vecPlayerHpBar[1]->SetImageToScaleToImage("BottomHPbarG.bmp");
    vecPlayerHpBar[1]->EffectCameraOff();
    vecPlayerHpBar[1]->SetPosition(rStartPos);
    rStartPos.y += 17.f;

    vecPlayerHpBar[2]->SetImageToScaleToImage("BottomHPbarP.bmp");
    vecPlayerHpBar[2]->EffectCameraOff();
    vecPlayerHpBar[2]->SetPosition(rStartPos);
    rStartPos.y += 17.f;

    vecPlayerHpBar[3]->SetImageToScaleToImage("BottomHPbarR.bmp");
    vecPlayerHpBar[3]->EffectCameraOff();
    vecPlayerHpBar[3]->SetPosition(rStartPos);
    rStartPos.y += 17.f;

    vecPlayerHpBar[4]->SetImageToScaleToImage("BottomHPbarS.bmp");
    vecPlayerHpBar[4]->EffectCameraOff();
    vecPlayerHpBar[4]->SetPosition(rStartPos);
    rStartPos.y += 17.f;

    vecPlayerHpBar[5]->SetImageToScaleToImage("BottomHPbarY.bmp");
    vecPlayerHpBar[5]->EffectCameraOff();
    vecPlayerHpBar[5]->SetPosition(rStartPos);

}

void AllPlayerHpUI::Update(float _DeltaTime)
{

    if (true == bSetHP)
    {
        //for (size_t i = 0; i < vecPlayerCurHp.size(); i++)
        //{
        //    vecPlayerCurHp[vecPlayerCurHp.size() - i-1] = 100 - i;
        //}
        for (size_t i = 0; i < vecPlayerCurHp.size(); i++)
        {
            for (size_t j = 1; j < vecPlayerCurHp.size() - i; j++)
            {
                if (vecPlayerCurHp[j] > vecPlayerCurHp[j - 1])
                {
                    int iTemp = vecPlayerCurHp[j];
                    vecPlayerCurHp[j] = vecPlayerCurHp[j - 1];
                    vecPlayerCurHp[j - 1] = iTemp;


                    GameEngineRender* pTemp = vecPlayerHpBar[j];
                    vecPlayerHpBar[j] = vecPlayerHpBar[j - 1];
                    vecPlayerHpBar[j - 1] = pTemp;
                }
            }
        }
        bSetHP = false;
        bSort = true;
    }
    if (true==bSort)
    {
        float4 rStartPos = StartPos;        
    
        for (size_t i = 0; i < vecPlayerHpBar.size(); i++)
        {
            float fHpRatio = vecPlayerCurHp[i] / 100.f;
            vecPlayerHpBar[i]->SetPosition(rStartPos);
            vecPlayerHpBar[i]->SetScale({ 200 * fHpRatio ,17 });
            rStartPos.y += 17.f;
        }

        bSort = false;
    }

    
}

