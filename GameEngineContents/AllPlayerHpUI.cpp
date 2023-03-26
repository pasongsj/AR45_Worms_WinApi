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
    std::vector<Player*> PlayerList = GlobalValue::gValue.GetAllPlayer();

    for (size_t i = 0; i < PlayerList.size(); i++)
    {
        for (size_t j = 0; j < PlayerList.size(); j++)
        {
            if (vecMixNum[j]==static_cast<int>(i))
            {
                vecPlayerCurHp[j] =PlayerList[i]->GetPlayerHP();
                continue;
            }
        }
    }
    bSetHP = true;
}

void AllPlayerHpUI::Start()
{
    AllHpUI = this;

    std::vector<Player*> PlayerList = GlobalValue::gValue.GetAllPlayer();

    for (size_t i = 0; i < PlayerList.size(); i++)
    {
        vecPlayerHpBar.push_back(CreateRender(WormsRenderOrder::UI));
        vecPlayerCurHp.push_back(PlayerList[i]->GetPlayerHP());
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

    rStartPos = StartPos;

    for (size_t i = 0; i < vecPlayerHpBar.size(); i++)
    {
        vecMixNum.push_back(static_cast<int>(i));
        vecLastPos.push_back(rStartPos);
        rStartPos.y += 17.f;
    }

}

void AllPlayerHpUI::Update(float _DeltaTime)
{

    if (true == bSetHP)
    {
        
        for (size_t i = 0; i < vecPlayerCurHp.size(); i++)
        {
            for (size_t j = 1; j < vecPlayerCurHp.size() - i; j++)
            {
                if (vecPlayerCurHp[j] > vecPlayerCurHp[j - 1])
                {
                    int iTemp = vecPlayerCurHp[j];
                    vecPlayerCurHp[j] = vecPlayerCurHp[j - 1];
                    vecPlayerCurHp[j - 1] = iTemp;

                    iTemp = vecMixNum[j];
                    vecMixNum[j] = vecMixNum[j - 1];
                    vecMixNum[j - 1] = iTemp;


                    float4 f4Temp = vecLastPos[j];
                    vecLastPos[j] = vecLastPos[j - 1];
                    vecLastPos[j - 1] = f4Temp;


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
       
        fLerpRatio += _DeltaTime;


        for (size_t i = 0; i < vecPlayerHpBar.size(); i++)
        {
            float4 LerpCamPos = float4::Zero;

            
            float fHpRatio = vecPlayerCurHp[i] / 100.f;
            float4 end = LerpCamPos.LerpClamp(vecLastPos[i], float4{ rStartPos.x,rStartPos.y + (i * 17.f) }, fLerpRatio);
            vecPlayerHpBar[i]->SetPosition(LerpCamPos.LerpClamp(vecLastPos[i], float4{ rStartPos.x,rStartPos.y + (i * 17.f) }, fLerpRatio));
            vecPlayerHpBar[i]->SetScale({ 200 -(200*(1-fHpRatio)* fLerpRatio) ,17 });
        }

        if (fLerpRatio>=1.f)
        {
            bSort = false;

            for (size_t i = 0; i < vecPlayerHpBar.size(); i++)
            {
                vecLastPos[i] = vecPlayerHpBar[i]->GetPosition();
                if (vecPlayerCurHp[i] <=0)
                {
                    vecPlayerHpBar[i]->Off();
                }

            }

            fLerpRatio = 0.f;
        }
    }

    
}

