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
    Ending = CreateRender("Worms_EndingBackDrop.bmp", WormsTitle::Finish);
    Ending->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y -330 });
    Ending->SetScale({1279,299});


    BlackGround = CreateRender("backGround.bmp", WormsTitle::IntroBackGround);
    BlackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y});
    BlackGround->SetScale(GameEngineWindow::GetScreenSize());

    BlackGroundAlpha = CreateRender("backGround.bmp", WormsTitle::Finish);
    BlackGroundAlpha->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    BlackGroundAlpha->SetScale(GameEngineWindow::GetScreenSize());

    EndingWrite = CreateRender("testEnding.bmp", WormsTitle::Write);
    EndingWrite->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y+1000 });
    EndingWrite->SetScale(GameEngineWindow::GetScreenSize());

    


}

void EndingBack::Update(float _DeltaTime)
{
    if (BlackAlpha < 200)
    {
        
        BlackAlpha += 200 * _DeltaTime;

        BlackGroundAlpha->SetAlpha(static_cast<int>(255 - BlackAlpha));
       // EndingWrite->SetAlpha(255-);
    }

    if (BlackAlpha > 100)
    {
        EndingWrite->SetMove({ 0, -150 * _DeltaTime });
    }
}
