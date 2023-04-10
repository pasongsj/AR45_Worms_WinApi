#include "PlayerEsc.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineCore.h>

bool PlayerEsc::Check = false;
PlayerEsc::PlayerEsc()
{
}

PlayerEsc::~PlayerEsc()
{
}

void PlayerEsc::Start()
{
    BackGround = CreateRender("backGround.bmp", WormsRenderOrder::PlayChange);
    BackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    BackGround->SetScale(GameEngineWindow::GetScreenSize());
    BackGround->EffectCameraOff();
    BackGround->SetAlpha(0);

}

void PlayerEsc::Update(float _DeltaTime)
{
    UpBlackAlpha += 400.0f * _DeltaTime;

    if (UpBlackAlpha < 253.0f)
    {

        BackGround->SetAlpha(static_cast<int>(UpBlackAlpha));


    }

    if (UpBlackAlpha > 253.0f)
    {
        Check = true;
    }

}
