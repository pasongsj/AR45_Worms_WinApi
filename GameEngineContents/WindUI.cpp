#include "WindUI.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

WindUI::WindUI() 
{
}

WindUI::~WindUI() 
{
}

void WindUI::Start()
{
    GameEngineRender* WindBarHide = CreateRender(WormsRenderOrder::UI);
    WindBarHide->SetImageToScaleToImage("windBarHider.bmp");
    WindBarHide->Off();
    //WindBarHide->SetPosition({})
    WindBarHide->EffectCameraOff();

    GameEngineRender* WindBarGauge = CreateRender(WormsRenderOrder::UI);
    WindBarGauge->SetImageToScaleToImage("windGauge.bmp");
    WindBarGauge->SetPosition({ 1170,910 });
    WindBarGauge->EffectCameraOff();

    pLAnim = CreateRender(WormsRenderOrder::UI);
    pLAnim->CreateAnimation({ .AnimationName = "LWind",.ImageName = "windBar.bmp",.Start = 0,.End = 7 });
    pLAnim->SetPosition({ 1125,930 });
    pLAnim->SetScale({87,13});
    pLAnim->ChangeAnimation("LWind");
    pLAnim->EffectCameraOff();

    pRAnim = CreateRender(WormsRenderOrder::UI);
    pRAnim->CreateAnimation({ .AnimationName = "RWind",.ImageName = "windBar.bmp",.Start = 8,.End = 15 });
    pRAnim->SetPosition({ 1215,930 });
    pRAnim->ChangeAnimation("RWind");
    pRAnim->SetScale({ 87,13 });
    pRAnim->EffectCameraOff();
}

void WindUI::Update(float _Deltatime)
{
}

