#include "MapModifier.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
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

	ModifierCollision = CreateCollision(static_cast<int>(WormsCollisionOrder::MapModifier));
	ModifierCollision->SetDebugRenderType(CT_CirCle);
}

void MapModifier::Update(float _DeltaTime)
{
	
}


void MapModifier::CreateHole(float4 _Pos, int _Radius)
{
	ModifierCollision->SetPosition(_Pos);

	if (this == nullptr)
	{
		MsgAssert("ModifierActor가 nullptr 입니다.");
        return;
	}

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
		//PS_SOLID: 실선
		HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
		HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);

		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);                     //단색에 대한 논리적 브러쉬를 생성
		HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                 //지정된 DC로 개체 선택
	
		Ellipse(MapDc,
			CircleRenderPos.ix() - _Radius,
			CircleRenderPos.iy() - _Radius,
			CircleRenderPos.ix() + _Radius,
			CircleRenderPos.iy() + _Radius);

		
		SelectObject(MapDc, OldBrush);                                          //다시 기존 브러쉬 선택
		
		DeleteObject(MyBrush);                                                  //생성한 브러쉬 삭제

		SelectObject(MapDc, OldPen);
		DeleteObject(MyPen);
	}

	//ColMap에 그림
	{
		HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
		HPEN OldPen = (HPEN)SelectObject(ColMapDc, MyPen);

		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);                     //단색에 대한 논리적 브러쉬를 생성
		HBRUSH OldBrush = (HBRUSH)SelectObject(ColMapDc, MyBrush);              //지정된 DC로 개체 선택

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

    //충돌맵과 맞닿은 부분의 픽셀에 색을 넣는 함수
	DrawPixel(_Pos, _Radius);
}

void MapModifier::CreateMapModifier()
{
	MainModifier = GetLevel()->CreateActor<MapModifier>(WormsRenderOrder::Map);
	float4 MousePos = GetLevel()->GetMousePosToCamera();
	MainModifier->SetPos(MousePos);
}


void MapModifier::DrawPixel(float4 _Pos, int _Radius)
{
	HDC MapDc = Map::MainMap->GetMapDC();

	std::string ColMapName = Map::MainMap->GetColMapName();
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);

	int lineThick = 2;
    float Angle = 0.0f;

	float4 CenterPos = _Pos;						                                        //체크 시작점: 원의 중점

	for (; Angle < 370; ++Angle)
	{
		float4 CheckPos = { 0.0f, -_Radius };		                                        //원점에서 반지름만큼 올라간 점, 각도가 변하기 전 원래 값으로 초기화
		CheckPos.RotaitonZDeg(Angle);				                                        //회전변환 적용
		CheckPos += CenterPos;						                                        //회전시킨 후 위치 변화


		//충돌맵의 파란색 부분과 깎이는 부분의 원 둘레가 닿으면 색칠
        DWORD color = ColImage->GetPixelColor(CheckPos, Magenta);

        //문제점 262 ~279도->Magenta로 확인
        int R = GetRValue(color);
        int G = GetGValue(color);
        int B = GetBValue(color);

        int a = 10;

		if (Blue == ColImage->GetPixelColor(CheckPos, Magenta))
		{
			//Map에 그림
			{
				//선에 대한 팬 생성
				//PS_SOLID: 실선
				HPEN MyPen = CreatePen(PS_SOLID, lineThick, LineColor);
				HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);

				HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(LineColor);                       //단색에 대한 논리적 브러쉬를 생성
				HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                     //지정된 DC로 개체 선택

				Ellipse(MapDc,
					CheckPos.ix() - lineThick,
					CheckPos.iy() - lineThick,
					CheckPos.ix() + lineThick,
					CheckPos.iy() + lineThick);

				
				SelectObject(MapDc, OldBrush);                                              //다시 기존 브러쉬 선택
				DeleteObject(MyBrush);                                                      //생성한 브러쉬 삭제

				SelectObject(MapDc, OldPen);
				DeleteObject(MyPen);
			}		
		}
	}
}


//충돌맵의 Magenta 부분에 구분선이 남은 경우, 지우기 위한 함수
//void MapModifier::CleanLineColor()
//{
//    HDC MapDc = Map::MainMap->GetMapDC();
//
//    std::string MapName = Map::MainMap->GetMapName();
//    GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(MapName);
//
//    std::string ColMapName = Map::MainMap->GetColMapName();
//    GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);
//
//    float4 CheckPos = float4::Zero;
//
//    for (; CheckPos.y < Scale.y; ++CheckPos.y)
//    {
//        for (; CheckPos.x < Scale.x; ++CheckPos.x)
//        {
//            if (LineColor == Image->GetPixelColor(CheckPos, Magenta))
//            {
//                if (Blue != ColImage->GetPixelColor(CheckPos, Magenta))
//                {
//                    //SetPixel(MapDc, CheckPos.x, CheckPos.y, Magenta);
//                    //Map에 그림
//                    {
//                        int lineThick = 2;
//                        //선에 대한 팬 생성
//                        //PS_SOLID: 실선
//                        HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
//                        HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);
//
//                        HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);                       //단색에 대한 논리적 브러쉬를 생성
//                        HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                     //지정된 DC로 개체 선택
//
//                        Ellipse(MapDc,
//                            CheckPos.ix() - lineThick,
//                            CheckPos.iy() - lineThick,
//                            CheckPos.ix() + lineThick,
//                            CheckPos.iy() + lineThick);
//
//
//                        SelectObject(MapDc, OldBrush);                                              //다시 기존 브러쉬 선택
//                        DeleteObject(MyBrush);                                                      //생성한 브러쉬 삭제
//
//                        SelectObject(MapDc, OldPen);
//                        DeleteObject(MyPen);
//                    }
//                }
//            }
//        }
//    }
//
//}