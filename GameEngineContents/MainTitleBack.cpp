#include "MainTitleBack.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCore.h>
#include "MouseObject.h"
#include "Star.h"
#include "Cusor.h"
MainTitleBack::MainTitleBack()
{
}

MainTitleBack::~MainTitleBack()
{
}

void MainTitleBack::Start()
{
    BlackBackGround = CreateRender("backGround.bmp", WormsMainTitle::BlackBackGround);
    BlackBackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    BlackBackGround->SetScale(GameEngineWindow::GetScreenSize());
    

   Logo = CreateRender("Lobby_Backdrop.bmp", WormsMainTitle::BackGround);
   Logo->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
   Logo->SetScale(GameEngineWindow::GetScreenSize());

   UpTitle = CreateRender("wgn.bmp", WormsMainTitle::Select);
   UpTitle->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y-340 });
   UpTitle->SetScale({ 640, 212 });

   MainPlay = CreateRender("MainPlay.bmp", WormsMainTitle::Select);
   MainPlay->SetPosition({ 400,400});
   MainPlay->SetScale({ 480,300 });

   multi = CreateRender("multi.bmp", WormsMainTitle::Select);
   multi->SetPosition({ 900,400 });
   multi->SetScale({ 480,300 });

   net = CreateRender("net.bmp", WormsMainTitle::Select);
   net->SetPosition({ 400,720 });
   net->SetScale({ 480,300 });

   options = CreateRender("options.bmp", WormsMainTitle::Select);
   options->SetPosition({ 900,720 });
   options->SetScale({ 480,300 });

   MouseSelect = CreateRender("MouseSelect.bmp", WormsMainTitle::Select);
   MouseSelect->SetPosition({ 900,720 });
   MouseSelect->SetScale({ 480,300 });
   MouseSelect->Off();



   {
       MainPlayCollision = CreateCollision();
       MainPlayCollision->SetScale({ 480,300 });
       MainPlayCollision->SetPosition({ 400,400 });
   }


   {
       OptionCollision = CreateCollision();
       OptionCollision->SetScale({ 480,300 });
       OptionCollision->SetPosition({ 900,720 });

   }

   {
       multiCollision = CreateCollision();
       multiCollision->SetScale({ 480,300 });
       multiCollision->SetPosition({ 900,400 });

   }

   {
       netCollision = CreateCollision();
       netCollision->SetScale({ 480,300 });
       netCollision->SetPosition({ 400,720 });

   }

   if (false == GameEngineInput::IsKey("LeftClock"))
   {
       GameEngineInput::CreateKey("LeftClock", VK_LBUTTON);
   }

   MouseObject* Object = GetLevel()->CreateActor<MouseObject>();
   Cusor* Actor = GetLevel()->CreateActor<Cusor>();
}

void MainTitleBack::Update(float _DeltaTime)
{
   float RandomX =  GameEngineRandom::MainRandom.RandomFloat(-600, 1000);
   float RandomY = GameEngineRandom::MainRandom.RandomFloat(-200, 0);
   Time += GameEngineTime::GlobalTime.GetFloatDeltaTime();

   MouseSelect->Off();
    if (BlackAlpha < 253)
    {
        BlackAlpha += 200 * _DeltaTime;

        BlackBackGround->SetAlpha(static_cast<int>(255 - BlackAlpha));
    }
    if (BlackAlpha > 253)
    {
        BlackBackGround->Off();
    }

    if (Time > 0.2)
    {
        Star* Actor = GetLevel()->CreateActor<Star>();
        Actor->SetMove({ RandomX ,RandomY });
        Time = 0;

    }
    
    if (nullptr != MainPlayCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == MainPlayCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            MouseSelect->SetPosition({ 400,400 });
            MouseSelect->SetScale({ 480,300 });
            MouseSelect->On();
        }
    }

    if (nullptr != OptionCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == OptionCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point  ,.ThisColType = CT_Rect }, collision))
        {
            MouseSelect->SetPosition({ 900,720 });
            MouseSelect->SetScale({ 480,300 });
            MouseSelect->On();
        }
    }
    if (nullptr != multiCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == multiCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point  ,.ThisColType = CT_Rect }, collision))
        {
            MouseSelect->SetPosition({ 900,400 });
            MouseSelect->SetScale({ 480,300 });
            MouseSelect->On();
            if (GameEngineInput::IsDown("LeftClock"))
            {
                GameEngineCore::GetInst()->ChangeLevel("Lobby");
            }


        }
    }
    if (nullptr != netCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == netCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            MouseSelect->SetPosition({ 400,720 });
            MouseSelect->SetScale({ 480,300 });
            MouseSelect->On();
        }
    }


}

void MainTitleBack::Render(float _DeltaTime)
{
   /// MainPlayCollision->DebugRender();
   // OptionCollision->DebugRender();
}

