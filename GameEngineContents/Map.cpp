#include "Map.h"
#include <string>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
//ScreenSize: { 1280, 720 }
//BackGround_Hrz: 5120


Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	if (false == GameEngineInput::IsKey("FreeMoveSwitch"))
	{
		GameEngineInput::CreateKey("FreeMoveSwitch", '0');
		GameEngineInput::CreateKey("FreeLeft", VK_LEFT);
		GameEngineInput::CreateKey("FreeRight", VK_RIGHT);
		GameEngineInput::CreateKey("FreeUp", VK_UP);
		GameEngineInput::CreateKey("FreeDown", VK_DOWN);

		//µð¹ö±ë ¸ðµå_Ãæµ¹¸Ê È®ÀÎ
		GameEngineInput::CreateKey("DebugMode", '9');
	}


	MapRender = CreateRender(WormsRenderOrder::Map);
	MapRender->SetImage("MapCity.bmp");
	float4 MapScale = MapRender->GetImage()->GetImageScale();
	MapRender->SetPosition(MapScale.half());
	MapRender->SetScaleToImage();

	//BackGround_Sky
	{
		GameEngineRender* BackGround = CreateRender(WormsRenderOrder::BackGround);
		BackGround->SetImage("gradient.bmp");
		BackGround->SetPosition(MapScale.half());
		BackGround->SetScaleToImage();
	}
	//BackGround_Wave
	{
		GameEngineRender* WaveBack = CreateRender(WormsRenderOrder::BackGround);
		WaveBack->SetImage("Under_Water.bmp");
		WaveBack->SetPosition(WaveBackPos);
		WaveBack->SetScale(WaveBackScale);
	}
	{
		GameEngineRender* Wave0 = CreateRender(WormsRenderOrder::Wave);
		Wave0->SetImage("Water_sprite.bmp");
		Wave0->SetPosition(WaveAnimPos0);
		Wave0->SetScale(WaveScale);
		Wave0->CreateAnimation({ .AnimationName = "Wave0",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave0->ChangeAnimation("Wave0");
	}
	{
		GameEngineRender* Wave1 = CreateRender(WormsRenderOrder::Wave);
		Wave1->SetImage("Water_sprite.bmp");
		Wave1->SetPosition(WaveAnimPos1);
		Wave1->SetScale(WaveScale);
		Wave1->CreateAnimation({ .AnimationName = "Wave1",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave1->ChangeAnimation("Wave1");
	}
	{
		GameEngineRender* Wave2 = CreateRender(WormsRenderOrder::Wave);
		Wave2->SetImage("Water_sprite.bmp");
		Wave2->SetPosition(WaveAnimPos2);
		Wave2->SetScale(WaveScale);
		Wave2->CreateAnimation({ .AnimationName = "Wave2",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave2->ChangeAnimation("Wave2");
	}
	{
		GameEngineRender* Wave3 = CreateRender(WormsRenderOrder::Wave);
		Wave3->SetImage("Water_sprite.bmp");
		Wave3->SetPosition(WaveAnimPos3);
		Wave3->SetScale(WaveScale);
		Wave3->CreateAnimation({ .AnimationName = "Wave3",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave3->ChangeAnimation("Wave3");
	}
}

void Map::Update(float _DeltaTime)
{

	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("DebugMode"))							//µð¹ö±ë ¸ðµå_Ãæµ¹¸Ê È¤Àº ¸ÊÀ» º¼ ¼ö ÀÖÀ½
	{
		if (false == IsColMap)
		{
			IsColMap = true;
			MapRender->SetImage("MapCity_Ground.bmp");
		}
		else
		{
			IsColMap = false;
			MapRender->SetImage("MapCity.bmp");
		}
	}

	std::string PlayLevel = "FreeMoveSwitch Key : 0, DebugMode Key: 9";
	GameEngineLevel::DebugTextPush(PlayLevel);
}

bool FreeMove = false;

bool Map::FreeMoveState(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("FreeMoveSwitch"))
	{
		FreeMove = true;
	}

	if (true == FreeMove)
	{
		if (GameEngineInput::IsPress("FreeLeft"))
		{
			GetLevel()->SetCameraMove(float4::Left * FreeSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("FreeRight"))
		{
			GetLevel()->SetCameraMove(float4::Right * FreeSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("FreeUp"))
		{
			GetLevel()->SetCameraMove(float4::Up * FreeSpeed * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("FreeDown"))
		{
			GetLevel()->SetCameraMove(float4::Down * FreeSpeed * _DeltaTime);
		}
	}
	if (true == FreeMove)
	{
		return true;
	}
	return false;
}