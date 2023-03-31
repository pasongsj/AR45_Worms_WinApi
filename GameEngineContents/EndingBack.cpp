#include "EndingBack.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
EndingBack::EndingBack()
{
}

EndingBack::~EndingBack()
{
}

void EndingBack::Start()
{
    Ending = CreateRender("Worms_EndingBackDrop.bmp", WormsTitle::Intro);
    Ending->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    Ending->SetScale(GameEngineWindow::GetScreenSize());
}

void EndingBack::Update(float _DeltaTime)
{

}
