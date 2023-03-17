#include "TitleBack.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
TitleBack::TitleBack()
{
}

TitleBack::~TitleBack()
{
}

void TitleBack::Start()
{
	InTro = CreateRender("Intro_Logo.bmp", WormsTitle::Intro);
	InTro->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y-100 });
	InTro->SetScale(GameEngineWindow::GetScreenSize());

	InTroBackGround = CreateRender("BackGround.bmp", WormsTitle::IntroBackGround);
	InTroBackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y - 100 });
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
	TitleAnimation->CreateAnimation({ .AnimationName = "TitleAnimation",  .ImageName = "TitleLogo_Actor.bmp", .Start = 0, .End = 4, .InterTime = 0.1f,.Loop = false ,.FrameIndex{0,1,2,3,4,3,2,1,0} });
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

	if (AnimatonCheck > 1)
	{
		TitleAnimation->ChangeAnimation("TitleAnimation",0,true);
		TitleCheck = false;
		AnimatonCheck = 0;
	}

	if (AnimationWhiteTime > 5)
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
		}

		WhiteBackGround->SetAlpha(255 - WhiteColor);






	}



}
