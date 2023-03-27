#include "TitleBack.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineCore.h>
TitleBack::TitleBack()
{
}

TitleBack::~TitleBack()
{
}

void TitleBack::Start()
{
	InTro = CreateRender("Intro_Logo.bmp", WormsTitle::Intro);
	InTro->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y});
	InTro->SetScale(GameEngineWindow::GetScreenSize());

    backGround = CreateRender("backGround.bmp", WormsTitle::Finish);
    backGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
    backGround->SetScale(GameEngineWindow::GetScreenSize());
    backGround->SetAlpha(0);
    backGround->Off();

	InTroBackGround = CreateRender("BackGround.bmp", WormsTitle::IntroBackGround);
	InTroBackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y  });
	InTroBackGround->SetScale(GameEngineWindow::GetScreenSize());


	TitleLogo = CreateRender("Title_Logo.bmp", WormsTitle::Intro);
	TitleLogo->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y - 300 });
	TitleLogo->SetScale({600,350});
	TitleLogo->Off();

	WhiteBackGround = CreateRender("Fade_White.bmp", WormsTitle::WhiteBackGround);
	WhiteBackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
	WhiteBackGround->SetScale(GameEngineWindow::GetScreenSize());
	WhiteBackGround->Off();


	TitleAnimation = CreateRender(WormsTitle::Intro);
	TitleAnimation->SetPosition({ GameEngineWindow::GetScreenSize().half().x-100,GameEngineWindow::GetScreenSize().half().y - 300 });
	TitleAnimation->SetScale({ 200,200 });
	TitleAnimation->CreateAnimation({ .AnimationName = "TitleAnimation", .ImageName = "TitleLogo_Actor.bmp", .Start = 0, .End = 4, .InterTime = 0.1f,.Loop = false ,.FrameIndex{0,1,2,3,4,3,2,1,0} });
	TitleAnimation->ChangeAnimation("TitleAnimation");
	TitleAnimation->Off(); 

	TitleAnimationStop = CreateRender(WormsTitle::Intro);
	TitleAnimationStop->SetPosition({ GameEngineWindow::GetScreenSize().half().x-100,GameEngineWindow::GetScreenSize().half().y - 300 });
	TitleAnimationStop->SetScale({ 200,200 });
	TitleAnimationStop->CreateAnimation({ .AnimationName = "TitleAnimation",  .ImageName = "TitleLogo_Actor.bmp", .Start = 0, .End = 0, .InterTime = 0.1f,.Loop = true});
	TitleAnimationStop->ChangeAnimation("TitleAnimation");
	TitleAnimationStop->Off();

	BackDrop = CreateRender("Title_Backdrop.bmp", WormsTitle::IntroBackGround);
	BackDrop->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y  });
	BackDrop->SetScaleToImage();
	BackDrop->Off();
	InTro->SetAlpha(0);

	A = CreateRender("Armageddon_4.bmp", WormsTitle::Intro);
	A->SetPosition({420,350});
	A->SetScale({64,88});
	A->Off();

	R = CreateRender("Armageddon_2.bmp", WormsTitle::Intro);
	R->SetPosition({ 470,350 });
	R->SetScale({ 64,88 });
	R->Off();

	M = CreateRender("Armageddon_3.bmp", WormsTitle::Intro);
	M->SetPosition({ 520,350 });
	M->SetScale({ 64,88 });
	M->Off();

	A1 = CreateRender("Armageddon_4.bmp", WormsTitle::Intro);
	A1->SetPosition({ 570,350 });
	A1->SetScale({ 64,88 });
	A1->Off();

	G = CreateRender("Armageddon_5.bmp", WormsTitle::Intro);
	G->SetPosition({ 620,350 });
	G->SetScale({ 64,88 });
	G->Off();

	E = CreateRender("Armageddon_6.bmp", WormsTitle::Intro);
	E->SetPosition({ 670,350 });
	E->SetScale({ 64,88 });
	E->Off();

	D = CreateRender("Armageddon_7.bmp", WormsTitle::Intro);
	D->SetPosition({ 720,350 });
	D->SetScale({ 64,88 });
	D->Off();

	D1 = CreateRender("Armageddon_8.bmp", WormsTitle::Intro);
	D1->SetPosition({ 770,350 });
	D1->SetScale({ 64,88 });
	D1->Off();

	O = CreateRender("Armageddon_9.bmp", WormsTitle::Intro);
	O->SetPosition({ 820,350 });
	O->SetScale({ 64,88 });
	O->Off();

	N = CreateRender("Armageddon_10.bmp", WormsTitle::Intro);
	N->SetPosition({ 870,350 });
	N->SetScale({ 64,88 });
	N->Off();

}

void TitleBack::Update(float _DeltaTime)
{
	IntroLogTime += GameEngineTime::GlobalTime.GetFloatDeltaTime();
	
	if (IntroCheck == false)
	{
		IntroLogColor += 200 * _DeltaTime;
		InTro->SetAlpha(IntroLogColor);

		if (IntroLogColor >= 254)
		{
			IntroCheck = true; 
			IntroLogColor = 0;
		}

		
	}

	if (IntroCheck == true )
	{
		IntroLogTime += GameEngineTime::GlobalTime.GetFloatDeltaTime();

		if (IntroLogTime > 2)
		{

			if (IntroLogColor <= 254)
			{
				IntroLogColor += 200 * _DeltaTime;
			}

			InTro->SetAlpha(255 - IntroLogColor);
		}

		if (IntroLogColor > 253)
		{
			InTro->Off(); 
			TitleLogo->On();
			TitleAnimation->On();
			AnimationWhiteTime += GameEngineTime::GlobalTime.GetFloatDeltaTime();
		}
	}

	if (TitleAnimation->IsAnimationEnd())
	{
		TitleCheck = true;
	}

	if (TitleCheck == true)
	{
		AnimatonCheck += GameEngineTime::GlobalTime.GetFloatDeltaTime();
	}

	if (AnimatonCheck > 0.5)
	{
		TitleAnimation->ChangeAnimation("TitleAnimation",0,true);
		TitleCheck = false;
		AnimatonCheck = 0;
	}

	if (AnimationWhiteTime > 4)
	{
		WhiteBackGround->On();
		BackDrop->On();
		InTroBackGround->Off();
		TitleAnimation->Off();
		TitleAnimationStop->On();

		if (WhiteColor < 254)
		{
			WhiteColor += 200 * _DeltaTime;
		}

		if (WhiteColor >= 254)
		{
			WhiteColor = 255;
			WriteCheck = true;
		}

		WhiteBackGround->SetAlpha(255 - WhiteColor);
	}
	if (WriteCheck == true)
	{
		WriteTime += GameEngineTime::GlobalTime.GetFloatDeltaTime();

		if (WriteTime > 0.5)
		{
			A->On();
		}
		if (WriteTime > 1)
		{
			R->On();
		}
		if (WriteTime > 1.5)
		{
			M->On();
		}
		if (WriteTime > 2.0)
		{
			A1->On();
		}
		if (WriteTime > 2.5)
		{
			G->On();
		}
		if (WriteTime > 3)
		{
			E->On();
		}
		if (WriteTime > 3.5)
		{
			D->On();
		}
		if (WriteTime > 4.0)
		{
			D1->On();
		}
		if (WriteTime > 4.5)
		{
			O->On();
		}
		if (WriteTime > 5.0)
		{
			N->On();
		}
	}
    if (WriteTime > 5.0)
    {
        if (GameEngineInput::IsAnyKey())
        {
            finialCheck = true;
            backGround->On();
        }
    }
    if(finialCheck ==true)
    {
        BlackAlpha += 200 * _DeltaTime;
        backGround->SetAlpha(BlackAlpha);


    }
    if (BlackAlpha > 254)
    {
        GameEngineCore::GetInst()->ChangeLevel("MainTitle");
    }

}
