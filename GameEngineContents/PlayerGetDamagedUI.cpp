#include "PlayerGetDamagedUI.h"
#include "ContentsEnums.h"
PlayerGetDamagedUI::PlayerGetDamagedUI() 
{
}

PlayerGetDamagedUI::~PlayerGetDamagedUI() 
{
}

void PlayerGetDamagedUI::Start()
{
	HPBarImageRender = CreateRender(WormsRenderOrder::UI);
	HPBarImageRender->SetImage("PlayerHPBackground.bmp");
	HPBarImageRender->SetScaleToImage();
}


void PlayerGetDamagedUI::Update(float _DeltaTime)
{
	if (GetLiveTime() < 1.0f)
	{
		SetMove(float4::Up * 100.0f * _DeltaTime);
	}

	if (GetLiveTime() > 1.5f)
	{
		Death();
	}
}

void PlayerGetDamagedUI::SetDamagedUI(const std::string_view& _HPNumberImage, int _Damage)
{
	HpNumberRender.SetOwner(this);
	HpNumberRender.SetCameraEffect(true);
	HpNumberRender.SetImage(_HPNumberImage, { 10, 10 }, 10, RGB(255, 0, 255));
	HpNumberRender.SetAlign(Align::Center);
	HpNumberRender.SetValue(_Damage);
}