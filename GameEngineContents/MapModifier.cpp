#include "MapModifier.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Map.h"
#include "ContentsEnums.h"

MapModifier* MapModifier::MainModifier = nullptr;

MapModifier::MapModifier() 
{
}

MapModifier::~MapModifier() 
{
}

void MapModifier::Start()
{
	MainModifier = this;

	if (nullptr == MainModifier)
	{
		MsgAssert("MainModifier가 nullptr입니다.");
		return;
	}
}

void MapModifier::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LandHole"))
	{
		float4 Pos = GetLevel()->GetMousePosToCamera();
		CreateHole(Pos);
		return;
	}
}


void MapModifier::CreateHole(float4 _Pos, int _Radius)
{
	if (0 >= _Radius)
	{
		MsgAssert("반지름이 0보다 작거나 같을 수 없습니다.");
		return;
	}

	std::string CurMapName = Map::MainMap->GetMapName();

	HDC MapDc = Map::MainMap->GetMapDC();
	HDC ColMapDc = Map::MainMap->GetColMapDC();

	float4 CircleRenderPos = _Pos;

	//Map에 그림
	{
		//선에 대한 팬 생성
		//PS_SOLID: 선
		HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
		HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);
		//단색에 대한 논리적 브러쉬를 생성
		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);
		//지정된 DC로 개체 선택
		HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);
	
		Ellipse(MapDc,
			CircleRenderPos.ix() - _Radius,
			CircleRenderPos.iy() - _Radius,
			CircleRenderPos.ix() + _Radius,
			CircleRenderPos.iy() + _Radius);

		//다시 기존 브러쉬 선택
		SelectObject(MapDc, OldBrush);
		//생성한 브러쉬 삭제
		DeleteObject(MyBrush);

		SelectObject(MapDc, OldPen);
		DeleteObject(MyPen);
	}

	//ColMap에 그림
	{
		HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
		HPEN OldPen = (HPEN)SelectObject(ColMapDc, MyPen);
		//단색에 대한 논리적 브러쉬를 생성
		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);
		//지정된 DC로 개체 선택
		HBRUSH OldBrush = (HBRUSH)SelectObject(ColMapDc, MyBrush);

		Ellipse(ColMapDc,
			CircleRenderPos.ix() - _Radius,
			CircleRenderPos.iy() - _Radius,
			CircleRenderPos.ix() + _Radius,
			CircleRenderPos.iy() + _Radius);

		SelectObject(ColMapDc, OldBrush);
		DeleteObject(MyBrush);

		SelectObject(ColMapDc, OldPen);
		DeleteObject(MyPen);
	}


	//테스트 코드-------삭제 예정
	{

		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Red);
		HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);

		int r = 5;

		Ellipse(MapDc,
			CircleRenderPos.ix() - r,
			CircleRenderPos.iy() - r,
			CircleRenderPos.ix() + r,
			CircleRenderPos.iy() + r);

		SelectObject(MapDc, OldBrush);
		DeleteObject(MyBrush);
	}
}