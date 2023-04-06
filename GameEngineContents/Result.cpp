#include "Result.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "PlayLevel.h"
#include "ContentsEnums.h"
#include "GlobalValue.h"

Result::Result() 
{
}

Result::~Result() 
{
}

void Result::Start()
{
    pWin = CreateRender(WormsRenderOrder::UI);
    pWin->SetImage("win.bmp");
    pWin->SetScaleToImage();
    pWin->SetPosition(GetLevel()->GetCameraPos() + GameEngineWindow::GetScreenSize().half()+float4(0,-300));
    pWin->Off();

    pDraw = CreateRender(WormsRenderOrder::UI);
    pDraw->SetImage("draw.bmp");
    pDraw->SetScaleToImage();
    pDraw->SetPosition(GetLevel()->GetCameraPos() + GameEngineWindow::GetScreenSize().half() + float4(0, -300));
    pDraw->Off();

    int iResult = GlobalValue::gValue.GetPlayLevel()->GetGameSet();
    if (1== iResult)
    {
        pWin->On();
    }
    else if (2 == iResult)
    {
        pDraw->On();
    }
    else
    {
        assert(false);
    }
    
}

void Result::Update(float _DeltaTime)
{
}

