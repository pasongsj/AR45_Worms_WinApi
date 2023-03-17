#include "MapModifier.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Map.h"
#include "ContentsEnums.h"

MapModifier::MapModifier() 
{
}

MapModifier::~MapModifier() 
{
}

void MapModifier::Start()
{
	//마우스 좌측 키 입력 생성
	if (false == GameEngineInput::IsKey("LandHole"))
	{
		GameEngineInput::CreateKey("LandHole", VK_LBUTTON);
	}
}

void MapModifier::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("LandHole"))
	{

		CreateHole(200);
	}
}

void MapModifier::CreateMapModifier(float4 _Pos)
{
	MapModifier* MapMdfActor = GetLevel()->CreateActor<MapModifier>(WormsRenderOrder::Map);
	MapMdfActor->SetPos(_Pos);
}

void MapModifier::CreateHole(int _Radius)
{
	std::string CurMapName = Map::MainMap->GetMapName();

	HDC MapRenderDc = Map::MainMap->GetMapRenderDC();
	float4 CircleRenderPos = GetLevel()->GetMousePosToCamera(); //-GetLevel()->GetCameraPos();
	int Radius = _Radius;

	Ellipse(MapRenderDc,
		CircleRenderPos.ix() - Radius,
		CircleRenderPos.iy() - Radius,
		CircleRenderPos.ix() + Radius,
		CircleRenderPos.iy() + Radius);


	{
		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH OldBrush = (HBRUSH)SelectObject(MapRenderDc, MyBrush);

		int r = 5;

		Ellipse(MapRenderDc,
			CircleRenderPos.ix() - r,
			CircleRenderPos.iy() - r,
			CircleRenderPos.ix() + r,
			CircleRenderPos.iy() + r);

		SelectObject(MapRenderDc, OldBrush);
		DeleteObject(MyBrush);
	}

	
}

void MapModifier::Render(float _DeltaTime)
{
	std::string MousePosStr = "MousePosition : ";
	MousePosStr += GetLevel()->GetMousePos().ToString();
}