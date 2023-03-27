#include "Cusor.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>

Cusor::Cusor()
{
}

Cusor::~Cusor()
{
}

void Cusor::Start()
{
    CusorRender = CreateRender("Cursor.bmp", WormsRenderOrder::Cusor);
    CusorRender->SetPosition({ 0,0 });
    CusorRender->SetScale({ 32,32 });
    CusorRender->EffectCameraOff();
}

void Cusor::Update(float _DeltaTime)
{
   // GetLevel()->GetMousePosToCamera()
    ShowCursor(false);
    CusorRender->SetPosition({ GameEngineWindow::GetMousePosition().x+17, GameEngineWindow::GetMousePosition().y+20 });
}
