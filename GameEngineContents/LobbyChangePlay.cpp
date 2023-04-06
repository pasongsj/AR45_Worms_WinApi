#include "LobbyChangePlay.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineCore.h>

bool LobbyChangePlay::test = false;

LobbyChangePlay::LobbyChangePlay()
{
    
}

LobbyChangePlay::~LobbyChangePlay()
{

}

void LobbyChangePlay::Start()
{
    BackGround = CreateRender("backGround.bmp", WormsRenderOrder::LobbyChange);
    BackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    BackGround->SetScale(GameEngineWindow::GetScreenSize());
    BackGround->EffectCameraOff();
    Animation = CreateRender(WormsRenderOrder::LobbyChange);
    Animation->SetPosition({ GameEngineWindow::GetScreenSize().half().x ,GameEngineWindow::GetScreenSize().half().y });
    Animation->SetScale({ 160,160 });
    Animation->CreateAnimation({ .AnimationName = "TitleAnimation", .ImageName = "cdrom.bmp", .Start = 0, .End = 24, .InterTime = 0.07f,.Loop = false });
    Animation->ChangeAnimation("TitleAnimation");
    Animation->EffectCameraOff();


    BackGround1 = CreateRender("backGround.bmp", WormsRenderOrder::LobbyChange);
    BackGround1->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    BackGround1->SetScale(GameEngineWindow::GetScreenSize());
    BackGround1->EffectCameraOff();
    BackGround1->SetAlpha(0);
}

void LobbyChangePlay::Update(float _DeltaTime)
{
    if (Animation->IsAnimationEnd())
    {
        AnimationCheck = true;
    }
    if (AnimationCheck == true)
    {
        if (UpBlackAlpha < 254.0f)
        {
            UpBlackAlpha += 1000.0f * _DeltaTime;
            BackGround1->SetAlpha(UpBlackAlpha);
           
        }
        if (UpBlackAlpha > 254.0f)
        {
            BackGround->Off();
            Animation->Off();
            DownBlackAlpha += 200.0f * _DeltaTime;

            BackGround1->SetAlpha(255.0f - DownBlackAlpha);
        }

        if (DownBlackAlpha > 254.0f)
        {
            BackGround1->Off();
            BackGround->Off();
            Animation->Off();
            test = true;
        }


      /*  if (BlackCheck == true)
        {

            BlackAlpha -= 200 * _DeltaTime;
            BackGround1->SetAlpha(255- BlackAlpha);
        }

        if (BlackAlpha > 253)
        {
            BackGround->Off();
            Animation->Off();
            BackGround1->Off();
        }*/


    }



}
