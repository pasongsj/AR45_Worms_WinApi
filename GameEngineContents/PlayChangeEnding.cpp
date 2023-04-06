#include "PlayChangeEnding.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineCore.h>

PlayChangeEnding::PlayChangeEnding()
{
}

PlayChangeEnding::~PlayChangeEnding()
{
}

void PlayChangeEnding::Start()
{
    BackGround = CreateRender("backGround.bmp", WormsRenderOrder::PlayChange);
    BackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    BackGround->SetScale(GameEngineWindow::GetScreenSize());
    BackGround->EffectCameraOff();
    BackGround->SetAlpha(0);
}

void PlayChangeEnding::Update(float _DeltaTime)
{
    UpBlackAlpha += 400.0f * _DeltaTime;

    if (UpBlackAlpha < 253.0f )
    {
       
        BackGround->SetAlpha(UpBlackAlpha);

       
    }

    if (UpBlackAlpha > 253.0f )
    {
        GameEngineCore::GetInst()->ChangeLevel("Ending");
    }


}
