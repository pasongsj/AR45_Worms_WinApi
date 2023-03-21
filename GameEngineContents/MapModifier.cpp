#include "MapModifier.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
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
	
}


void MapModifier::CreateHole(float4 _Pos, int _Radius)
{
	if (0 >= _Radius)
	{
		MsgAssert("반지름이 0보다 작거나 같을 수 없습니다.");
		return;
	}

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

void MapModifier::CreateMapModifier()
{
	MainModifier = GetLevel()->CreateActor<MapModifier>(WormsRenderOrder::Map);
	float4 MousePos = GetLevel()->GetMousePosToCamera();
	MainModifier->SetPos(MousePos);															//액터의 위치를 나중에 수정해야 함
}

void MapModifier::DrawArc(float4 _Pos, int _Radius)
{
	HDC MapDc = Map::MainMap->GetMapDC();
	float4 CircleRenderPos = _Pos;
	float4 ArcStartPos = GetStartArcPos(_Pos, _Radius);
	float4 ArcEndPos = GetEndArcPos(_Pos, _Radius);
	//Map에 그림
	{
		//선에 대한 팬 생성
		//PS_SOLID: 선
		HPEN MyPen = CreatePen(PS_SOLID, 3, Cyan);
		HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);
		//단색에 대한 논리적 브러쉬를 생성
		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);
		//지정된 DC로 개체 선택
		HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);

		Arc(MapDc,
			CircleRenderPos.ix() - _Radius,
			CircleRenderPos.iy() - _Radius,
			CircleRenderPos.ix() + _Radius,
			CircleRenderPos.iy() + _Radius,
			ArcStartPos.ix(),
			ArcStartPos.iy(),
			ArcEndPos.ix(),
			ArcEndPos.iy()
		);

		//다시 기존 브러쉬 선택
		SelectObject(MapDc, OldBrush);
		//생성한 브러쉬 삭제
		DeleteObject(MyBrush);

		SelectObject(MapDc, OldPen);
		DeleteObject(MyPen);
	}
}

float4 MapModifier::GetStartArcPos(float4 _Pos, int _Radius)
{
	std::string ColMapName = Map::MainMap->GetColMapName();
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);
	float4 NextPos = _Pos;							//CenterPos
	int RadForX = _Radius;							//X 좌표의 검사 범위
	int RadForY = _Radius;							//Y 좌표의 검사 범위
	bool IsBoundary = false;						//픽셀 충돌이 일어나면 반복문을 빠져 나오기 위한 값
	
	for (int i = 0; i <= RadForX; i++)
	{
		for (int i = 0; i <= RadForY; i++)
		{
			if (Blue != ColImage->GetPixelColor(NextPos, Magenta))
			{
				++NextPos.y;						//다음 픽셀 충돌에서 y값을 증가시켜 한 칸 아래의 점을 검사하도록 함
			}
			else
			{
				IsBoundary = true;
				break;
			}
		}

		if (true == IsBoundary)
		{
			break;
		}
		else
		{
			NextPos.y -= RadForY;					//y값을 처음 시작했던 원의 중점 위치로 올림
			--RadForY;
			++NextPos.x;
		}
	}

	return NextPos;
}

float4 MapModifier::GetEndArcPos(float4 _Pos, int _Radius)
{
	std::string ColMapName = Map::MainMap->GetColMapName();
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);
	float4 NextPos = _Pos;						//CenterPos
	int RadForX = _Radius;
	int RadForY = _Radius;
	bool IsBoundary = false;

	for (int i = 0; i <= RadForX; i++)
	{
		for (int i = 0; i <= RadForY; i++)
		{
			if (Blue != ColImage->GetPixelColor(NextPos, Magenta))
			{
				--NextPos.y;						//다음 픽셀 충돌에서 y값을 감소시켜 한 칸 위의 점을 검사하도록 함
			}
			else
			{
				IsBoundary = true;
				break;
			}
		}

		if (true == IsBoundary)
		{
			break;
		}
		else
		{
			NextPos.y += RadForY;					//y값을 처음 시작했던 원의 중점 위치로 내림
			--RadForY;
			++NextPos.x;
		}
	}
	
	return NextPos;
}