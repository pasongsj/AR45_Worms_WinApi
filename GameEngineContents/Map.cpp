#include "Map.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "MapModifier.h"
//ScreenSize: { 1280, 960 }
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

	//마우스 좌측 키 입력 생성
	if (false == GameEngineInput::IsKey("LandHole"))
	{
		GameEngineInput::CreateKey("LandHole", VK_LBUTTON);
	}


	//MapRender 생성
	MapRender = CreateRender(WormsRenderOrder::Map);
	MapRender->SetImage("MapCity.bmp");
	float4 MapScale = MapRender->GetImage()->GetImageScale();
	MapRender->SetPosition(MapScale.half());
	MapRender->SetScaleToImage();

	
	//맵 위치 확인을 위한 테스트용 원---------삭제할 예정
	{
		HDC MapRenderDc = Map::MainMap->GetMapDC();
		float4 CircleRenderPos = float4::Zero;
		int Radius = 10;

		Ellipse(MapRenderDc,
			CircleRenderPos.ix() - Radius,
			CircleRenderPos.iy() - Radius,
			CircleRenderPos.ix() + Radius,
			CircleRenderPos.iy() + Radius);
	}


	//ColMapRender 생성
	{
		ColMapRender = CreateRender(WormsRenderOrder::Map);
		ColMapRender->SetImage("MapCity_Ground.bmp");
		ColMapRender->SetPosition(MapScale.half());
		ColMapRender->SetScaleToImage();

		ColMapRender->Off();
	}

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

		//WaveBack->Off();
	}
	//Wave Animation
	{
		GameEngineRender* Wave0 = CreateRender(WormsRenderOrder::Wave);
		Wave0->SetImage("Water_sprite.bmp");
		Wave0->SetPosition(WaveAnimPos0);
		Wave0->SetScale(WaveScale);
		Wave0->CreateAnimation({ .AnimationName = "Wave0",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave0->ChangeAnimation("Wave0");

		//Wave0->Off();
	}
	int RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);					//Animation을 시작할 랜덤한 인덱스
	{
		GameEngineRender* Wave1 = CreateRender(WormsRenderOrder::Wave);
		Wave1->SetImage("Water_sprite.bmp");
		Wave1->SetPosition(WaveAnimPos1);
		Wave1->SetScale(WaveScale);
		Wave1->CreateAnimation({ .AnimationName = "Wave1",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave1->ChangeAnimation("Wave1", RandIdx);

		//Wave1->Off();
	}
	RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
	{
		GameEngineRender* Wave2 = CreateRender(WormsRenderOrder::Wave);
		Wave2->SetImage("Water_sprite.bmp");
		Wave2->SetPosition(WaveAnimPos2);
		Wave2->SetScale(WaveScale);
		Wave2->CreateAnimation({ .AnimationName = "Wave2",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave2->ChangeAnimation("Wave2", RandIdx);

		//Wave2->Off();
	}
	RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
	{
		GameEngineRender* Wave3 = CreateRender(WormsRenderOrder::Wave);
		Wave3->SetImage("Water_sprite.bmp");
		Wave3->SetPosition(WaveAnimPos3);
		Wave3->SetScale(WaveScale);
		Wave3->CreateAnimation({ .AnimationName = "Wave3",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
		Wave3->ChangeAnimation("Wave3", RandIdx);

		//Wave3->Off();
	}	
}

void Map::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LandHole"))
	{
		CreateMapModifier(50);
	}

	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("DebugMode"))							//디버깅 모드_충돌맵 혹은 맵을 볼 수 있음
	{
		if (false == IsColMap)
		{
			IsColMap = true;
			MapRender->Off();
			ColMapRender->On();
		}
		else
		{
			IsColMap = false;
			MapRender->On();
			ColMapRender->Off();
		}
	}

	std::string PlayLevel = "FreeMoveSwitch Key : 0, DebugMode Key: 9";
	GameEngineLevel::DebugTextPush(PlayLevel);
}

bool FreeMove = false;
bool Map::FreeMoveState(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("FreeMoveSwitch"))
	{
		FreeMove = !FreeMove;
	}

	if (true == FreeMove)
	{
		if (GameEngineInput::IsPress("FreeLeft"))
		{
			GetLevel()->SetCameraMove(float4::Left * FreeSpeed * _DeltaTime);
		}
		if (GameEngineInput::IsPress("FreeRight"))
		{
			GetLevel()->SetCameraMove(float4::Right * FreeSpeed * _DeltaTime);
		}
		if (GameEngineInput::IsPress("FreeUp"))
		{
			GetLevel()->SetCameraMove(float4::Up * FreeSpeed * _DeltaTime);
		}
		if (GameEngineInput::IsPress("FreeDown"))
		{
			GetLevel()->SetCameraMove(float4::Down * FreeSpeed * _DeltaTime);
		}
	}

	return FreeMove;
}

HDC Map::GetMapDC() const
{
	HDC hdc = MapRender->GetImage()->GetImageDC();
	return hdc;
}

HDC Map::GetColMapDC() const
{
	HDC hdc = ColMapRender->GetImage()->GetImageDC();
	return hdc;
}

void Map::CreateMapModifier(int _Radius)
{
	MapModifier* MapMdfActor = GetLevel()->CreateActor<MapModifier>(WormsRenderOrder::Map);
	float4 MousePos = GetLevel()->GetMousePosToCamera();
	MapMdfActor->SetPos(MousePos);
	MapMdfActor->SetRadius(_Radius);
}

void Map::Render(float _DeltaTime)
{
	std::string MousePosStr = "MousePosition : ";
	MousePosStr += GetLevel()->GetMousePos().ToString();
	GameEngineLevel::DebugTextPush(MousePosStr);
}