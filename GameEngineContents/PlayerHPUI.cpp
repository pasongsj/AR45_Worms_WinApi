#include "PlayerHPUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/NumberRenderObject.h>

#include "ContentsEnums.h"

PlayerHPUI::PlayerHPUI() 
{
}

PlayerHPUI::~PlayerHPUI() 
{
}

void PlayerHPUI::Start()
{
	SelectPlayerRender = CreateRender(WormsRenderOrder::UI);
	HPBarImageRender = CreateRender(WormsRenderOrder::UI);
	IDRender = CreateRender(WormsRenderOrder::UI);
}

void PlayerHPUI::Update(float _DeltaTime)
{
	if (GetLiveTime() >= 5.0f)
	{
		if (TestValue <= 0)
		{
			TestValue = 100;
		}

		PlayerHPNumberRender.SetValue(--TestValue);
	}

}

void PlayerHPUI::SetPlayerHPUI(const std::string_view& _HPNumberImage, const std::string_view& _NametagImage, const std::string_view& _ArrowImage)
{
	PlayerHPNumberRender.SetOwner(this);
	PlayerHPNumberRender.SetCameraEffect(true);
	PlayerHPNumberRender.SetImage(_HPNumberImage, { 10, 10 }, 10, RGB(255, 0, 255));
	PlayerHPNumberRender.SetAlign(Align::Center);
	PlayerHPNumberRender.SetValue(TestValue);

	IDRender->SetImage(_NametagImage);
	IDRender->SetScaleToImage();
	IDRender->SetPosition({ 0, -17 });

	HPBarImageRender->SetImage("PlayerHPBackground.bmp");
	HPBarImageRender->SetScaleToImage();

	SelectPlayerRender->SetOwner(this);
	SelectPlayerRender->SetPosition({ 0, -55 });
	SelectPlayerRender->SetScale({ 60, 60 });
	SelectPlayerRender->CreateAnimation({ .AnimationName = "ArrowAnimation", .ImageName = _ArrowImage, .Start = 0, .End = 29, .InterTime = 0.05f });
	SelectPlayerRender->ChangeAnimation("ArrowAnimation");

}

void PlayerHPUI::Render(float _DeltaTime)
{
	//현재 UI 위치 확인

	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}
