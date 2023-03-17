#include "Map.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "MapModifier.h"
//ScreenSize: { 1280, 720 }
//BackGround_Hrz: 5120


Map* Map::MainMap;

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	MainMap = this;

	//입력 키 생성
	if (false == GameEngineInput::IsKey("FreeMoveSwitch"))
	{
		GameEngineInput::CreateKey("FreeMoveSwitch", '0');
		GameEngineInput::CreateKey("FreeLeft", VK_LEFT);
		GameEngineInput::CreateKey("FreeRight", VK_RIGHT);
		GameEngineInput::CreateKey("FreeUp", VK_UP);
		GameEngineInput::CreateKey("FreeDown", VK_DOWN);

		//디버깅 모드_충돌맵 확인
		GameEngineInput::CreateKey("DebugMode", '9');
	}


	//랜더 생성
	MapRender = CreateRender(WormsRenderOrder::Map);
	MapRender->SetImage("MapCity.bmp");
	float4 MapScale = MapRender->GetImage()->GetImageScale();
	//MapRender->SetPosition(MapScale.half());
	MapRender->SetPosition(float4::Zero);
	MapRender->SetScaleToImage();

	
	//맵 위치 확인을 위한 테스트용 원---------삭제할 예정
	{
		HDC MapRenderDc = Map::MainMap->GetMapRenderDC();
		float4 CircleRenderPos = MapRender->GetPosition();
		int Radius = 10;

		Ellipse(MapRenderDc,
			CircleRenderPos.ix() - Radius,
			CircleRenderPos.iy() - Radius,
			CircleRenderPos.ix() + Radius,
			CircleRenderPos.iy() + Radius);
	}


	//BackGround_Sky
	{
		GameEngineRender* BackGround = CreateRender(WormsRenderOrder::BackGround);
		BackGround->SetImage("gradient.bmp");
		//BackGround->SetPosition(MapScale.half());
		BackGround->SetPosition(float4::Zero);
		BackGround->SetScaleToImage();
	}
	//BackGround_Wave
	{
		GameEngineRender* WaveBack = CreateRender(WormsRenderOrder::BackGround);
		WaveBack->SetImage("Under_Water.bmp");
		WaveBack->SetPosition(WaveBackPos);
		WaveBack->SetScale(WaveBackScale);
	}
	//Wave Animation
	{
		GameEngineRender* Wave0 = CreateRender(WormsRenderOrder::Wave);
		Wave0->SetImage("Water_sprite.bmp");
		Wave0->SetPosition(WaveAnimPos0);
		Wave0->SetScale(WaveScale);
		Wave0->CreateAnimation({ .AnimationName = "Wave0",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave0->ChangeAnimation("Wave0");
	}
	int RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);					//Animation을 시작할 랜덤한 인덱스
	{
		GameEngineRender* Wave1 = CreateRender(WormsRenderOrder::Wave);
		Wave1->SetImage("Water_sprite.bmp");
		Wave1->SetPosition(WaveAnimPos1);
		Wave1->SetScale(WaveScale);
		Wave1->CreateAnimation({ .AnimationName = "Wave1",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave1->ChangeAnimation("Wave1", RandIdx);
	}
	RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
	{
		GameEngineRender* Wave2 = CreateRender(WormsRenderOrder::Wave);
		Wave2->SetImage("Water_sprite.bmp");
		Wave2->SetPosition(WaveAnimPos2);
		Wave2->SetScale(WaveScale);
		Wave2->CreateAnimation({ .AnimationName = "Wave2",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave2->ChangeAnimation("Wave2", RandIdx);
	}
	RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
	{
		GameEngineRender* Wave3 = CreateRender(WormsRenderOrder::Wave);
		Wave3->SetImage("Water_sprite.bmp");
		Wave3->SetPosition(WaveAnimPos3);
		Wave3->SetScale(WaveScale);
		Wave3->CreateAnimation({ .AnimationName = "Wave3",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave3->ChangeAnimation("Wave3", RandIdx);
	}

	MapModifier* MapMdfActor = GetLevel()->CreateActor<MapModifier>(WormsRenderOrder::Wave);
	MapMdfActor->SetPos({ 1920.0f, 1200.0f });
	MapMdfActor->CreateHole(100);
}

void Map::Update(float _DeltaTime)
{

	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("DebugMode"))							//디버깅 모드_충돌맵 혹은 맵을 볼 수 있음
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

HDC Map::GetMapRenderDC() const
{
	HDC hdc = MapRender->GetImage()->GetImageDC();
	return hdc;
}