#include "AllPlayerHpUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "GlobalValue.h"
#include "PlayLevel.h"
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
    HPScaleRatio = GlobalValue::gValue.GetPlayLevel()->GetLevelSetting().iPlayerHp;
    std::vector<Player*> PlayerList = GlobalValue::gValue.GetAllPlayer();
        
    vecPlayerHpBar.reserve(PlayerList.size());
    vecPlayerName.reserve(PlayerList.size());
    vecPlayerCurHp.reserve(PlayerList.size());
    vecLastPos.reserve(PlayerList.size());
    vecMixNum.reserve(PlayerList.size());
    vecLastScale.reserve(PlayerList.size());

    float4 rStartPos = StartPos;
    for (size_t i = 0; i < PlayerList.size(); i++)
    {
        vecLastScale.push_back(0.f);
        vecPlayerHpBar.push_back(CreateRender(WormsRenderOrder::UI));
        vecPlayerName.push_back(CreateRender(WormsRenderOrder::UI));
        vecPlayerCurHp.push_back(PlayerList[i]->GetPlayerHP());

        vecPlayerHpBar[i]->EffectCameraOff();
        vecPlayerHpBar[i]->SetPosition(rStartPos);

        vecPlayerName[i]->EffectCameraOff();
        vecPlayerName[i]->SetPosition(rStartPos + float4{ -38,0 });
        rStartPos.y += 17.f;
        switch (i)
        {
        case 0:
            vecPlayerHpBar[i]->SetImageToScaleToImage("BottomHPbarR.bmp");
            vecPlayerName[i]->SetImageToScaleToImage("RedNameTag.bmp");
            break;
        case 1:
            vecPlayerHpBar[i]->SetImageToScaleToImage("BottomHPbarB.bmp");
            vecPlayerName[i]->SetImageToScaleToImage("BlueNameTag.bmp");
            break;
        case 2:
            vecPlayerHpBar[i]->SetImageToScaleToImage("BottomHPbarG.bmp");
            vecPlayerName[i]->SetImageToScaleToImage("GreenNameTag.bmp");
            break;
        case 3:
            vecPlayerHpBar[i]->SetImageToScaleToImage("BottomHPbarY.bmp");
            vecPlayerName[i]->SetImageToScaleToImage("YellowNameTag.bmp");
            break;
        case 4:
            vecPlayerHpBar[i]->SetImageToScaleToImage("BottomHPbarP.bmp");
            vecPlayerName[i]->SetImageToScaleToImage("PinkNameTag.bmp");
            break;
        case 5:
            vecPlayerHpBar[i]->SetImageToScaleToImage("BottomHPbarS.bmp");
            vecPlayerName[i]->SetImageToScaleToImage("MintNameTag.bmp");
            break;
        default:
            break;
        }
        
    }
    rStartPos = StartPos;

    for (size_t i = 0; i < vecPlayerHpBar.size(); i++)
    {
        vecMixNum.push_back(static_cast<int>(i));
        vecLastPos.push_back(rStartPos);
        rStartPos.y += 17.f;
    }

    fMaxHP = static_cast<float>(GlobalValue::gValue.GetPlayLevel()->GetLevelSetting().iPlayerHp);
    pPlayLevel = GlobalValue::gValue.GetPlayLevel();
}

void AllPlayerHpUI::Update(float _DeltaTime)
{
    if (0!= pPlayLevel->GetGameSet())
    {
        Death();
    }
    

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
                    

                    pTemp = vecPlayerName[j];
                    vecPlayerName[j] = vecPlayerName[j - 1];
                    vecPlayerName[j - 1] = pTemp;

                }
            }
        }
        bSetHP = false;
        bSort = true;

        for (size_t i = 0; i < vecPlayerHpBar.size(); i++)
        {
            vecLastScale[i] = vecPlayerHpBar[i]->GetScale().x;
        }
    }
    if (true==bSort)
    {
        float4 rStartPos = StartPos;
       
        fLerpRatio += _DeltaTime;
        

        for (size_t i = 0; i < vecPlayerHpBar.size(); i++)
        {
            float4 LerpCamPos = float4::Zero;
            float4 LerpNamePos = float4::Zero;

            
            float fHpRatio = (fMaxHP -vecPlayerCurHp[i]) / HPScaleRatio;
            float4 end = LerpCamPos.LerpClamp(vecLastPos[i], float4{ rStartPos.x,rStartPos.y + (i * 17.f) }, fLerpRatio);
            float4 NameEnd = LerpNamePos.LerpClamp(vecLastPos[i] + float4{ -38,0 }, float4{ rStartPos.x,rStartPos.y + (i * 17.f) } + float4{ -38,0 }, fLerpRatio);
            vecPlayerHpBar[i]->SetPosition(end);
            vecPlayerHpBar[i]->SetScale({ vecLastScale[i] - ((vecLastScale[i]-(200-(200 * fHpRatio))) * fLerpRatio) ,17});

            vecPlayerName[i]->SetPosition(NameEnd);
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

