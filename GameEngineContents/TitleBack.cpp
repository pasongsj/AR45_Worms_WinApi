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
	InTro = CreateRender("Intro_Logo.bmp", WormsRenderOrder::Intro);
	InTro->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y-100 });
	InTro->SetScale(GameEngineWindow::GetScreenSize());

	InTroBackGround = CreateRender("BackGround.bmp", WormsRenderOrder::IntroBackGround);
	InTroBackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y - 100 });
	InTroBackGround->SetScale(GameEngineWindow::GetScreenSize());


	TitleLogo = CreateRender("Title_Logo.bmp", WormsRenderOrder::IntroBackGround);
	TitleLogo->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y - 300 });
	TitleLogo->SetScale({600,350});
	TitleLogo->Off();

	
	TitleAnimation = CreateRender(WormsRenderOrder::IntroBackGround);
	TitleAnimation->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y - 300 });
	TitleAnimation->SetScale({ 280,200 });
    TitleAnimation->CreateAnimation({ .AnimationName = "TitleAnimation",  .ImageName = "TitleLogo_Actor.bmp", .Start = 0, .End = 4, .InterTime = 0.1f,.Loop = true });
	TitleAnimation->ChangeAnimation("TitleAnimation");
	TitleAnimation->Off(); 


	BackDrop = CreateRender("Title_Backdrop.bmp", WormsRenderOrder::IntroBackGround);
	BackDrop->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y - 100 });
	BackDrop->SetScale(GameEngineWindow::GetScreenSize());
	BackDrop->Off();
	InTro->SetAlpha(0);


}

void TitleBack::Update(float _DeltaTime)
{
	//IntroLogTime += GameEngineTime::GlobalTime.GetFloatDeltaTime();

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
		}
	}



}
