#include "Map.h"
#include <string>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"

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
		
	}
	{
		GameEngineRender* MapRender0 = CreateRender(WormsRenderOrder::Map);
		MapRender0->SetImage("MapCity.bmp");
		float4 MapScale = MapRender0->GetImage()->GetImageScale().half();
		MapRender0->SetPosition(MapScale);
		//MapRender0->SetScale(MapScale);
		MapRender0->SetScaleToImage();		//1840, 1392
	}
}

void Map::Update(float _DeltaTime)
{
	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	std::string PlayLevel = "FreeMoveSwitch Key : Number0";
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