#include "WindUI.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
#include "GlobalValue.h"


WindUI::WindUI() 
{
}

WindUI::~WindUI() 
{
}

void WindUI::Start()
{
    GameEngineRender* WindBarGauge = CreateRender(WormsRenderOrder::UI);
    WindBarGauge->SetImageToScaleToImage("windGauge.bmp");
    WindBarGauge->SetPosition({ 1170,950 });
    WindBarGauge->EffectCameraOff();

    pLAnim = CreateRender(WormsRenderOrder::UI);
    pLAnim->CreateAnimation({ .AnimationName = "LWind",.ImageName = "windBar.bmp",.Start = 0,.End = 7 ,.InterTime = 0.01f});
    pLAnim->SetPosition({ 1125,950 });
    pLAnim->SetScale({87,13});
    pLAnim->ChangeAnimation("LWind");
    pLAnim->EffectCameraOff();

    pRAnim = CreateRender(WormsRenderOrder::UI);
    pRAnim->CreateAnimation({ .AnimationName = "RWind",.ImageName = "windBar.bmp",.Start = 8,.End = 15 ,.InterTime = 0.01f });
    pRAnim->SetPosition({ 1215,950 });
    pRAnim->ChangeAnimation("RWind");
    pRAnim->SetScale({ 87,13 });
    pRAnim->EffectCameraOff();


    pLWindBarHide = CreateRender(WormsRenderOrder::UI);
    pLWindBarHide->SetImageToScaleToImage("windBarHider.bmp");
    //pLWindBarHide->Off();
    pLWindBarHide->SetPosition({ 1125,950 });
    pLWindBarHide->EffectCameraOff();

    pRWindBarHide = CreateRender(WormsRenderOrder::UI);
    pRWindBarHide->SetImageToScaleToImage("windBarHider.bmp");
    //pRWindBarHide->Off();
    pRWindBarHide->SetPosition({ 1215,950 });
    pRWindBarHide->EffectCameraOff();

    LHiderScale = pLWindBarHide->GetScale();
    RHiderScale = pRWindBarHide->GetScale();
}

void WindUI::Update(float _Deltatime)
{
    int WindPhase = GlobalValue::gValue.GetWindPhase();
    if (iLastWindPhase == WindPhase)
    {
        return;
    }
    else
    {
        iLastWindPhase = WindPhase;
    }

    if (WindPhase < 0)
    {
        int CalWindPhase = 10 - abs(WindPhase);
        LHiderResult.x = LHiderScale.x * CalWindPhase /10;

        float fLCalibration = LHiderScale.x - LHiderResult.x;
        pLWindBarHide->SetScale(LHiderResult);
        pLWindBarHide->SetPosition(float4{ 1125,950 } - float4{ fLCalibration / 2.f,0 });

        RHiderResult = RHiderScale;

        pRWindBarHide->SetScale(RHiderResult);
        pRWindBarHide->SetPosition(float4{ 1215,950 });

    }
    else if (WindPhase == 0)
    {
        RHiderResult = RHiderScale;
        pRWindBarHide->SetScale(RHiderResult);
        pRWindBarHide->SetPosition(float4{ 1215,950 });


        LHiderResult = LHiderScale;
        pLWindBarHide->SetScale(LHiderResult);
        pLWindBarHide->SetPosition(float4{ 1125,950 });
    }
    else if (WindPhase > 0)
    {
        int CalWindPhase = 10 - abs(WindPhase);
        RHiderResult.x = RHiderScale.x * CalWindPhase / 10;
    
        float fRCalibration = RHiderScale.x - RHiderResult.x;
        pRWindBarHide->SetScale(RHiderResult);
        pRWindBarHide->SetPosition(float4{ 1216,950 } + float4{ fRCalibration / 2.f,0 });
    
        LHiderResult = LHiderScale;
    
        pLWindBarHide->SetScale(LHiderResult);
        pLWindBarHide->SetPosition(float4{ 1125,950 });
    }
}
