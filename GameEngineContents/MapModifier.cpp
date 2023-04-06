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


void MapModifier::SetModifierColScale(float4 _Scale)
{
    ModifierCollision->SetScale(_Scale);
}

void MapModifier::SetModifierColPosition(float4 _Pos)
{
     ModifierCollision->SetPosition(_Pos);
}

void MapModifier::CreateHole(float4 _Pos, int _Diameter, bool _DrawLine)
{
    int Radius = _Diameter / 2;

	if (this == nullptr)
	{
		MsgAssert("ModifierActor가 nullptr 입니다.");
        return;
	}

	if (0 >= Radius)
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
			CircleRenderPos.ix() - Radius,
			CircleRenderPos.iy() - Radius,
			CircleRenderPos.ix() + Radius,
			CircleRenderPos.iy() + Radius);

		
		SelectObject(MapDc, OldBrush);                                          //다시 기존 브러쉬 선택
		
		DeleteObject(MyBrush);                                                  //생성한 브러쉬 삭제

		SelectObject(MapDc, OldPen);
		DeleteObject(MyPen);
	}

    if (true == _DrawLine)
    {
        //충돌맵과 맞닿은 부분의 픽셀에 색을 넣는 함수
	    DrawPixel(_Pos, Radius);
    }

	//ColMap에 그림
	{
		HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
		HPEN OldPen = (HPEN)SelectObject(ColMapDc, MyPen);

		HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);                     //단색에 대한 논리적 브러쉬를 생성
		HBRUSH OldBrush = (HBRUSH)SelectObject(ColMapDc, MyBrush);              //지정된 DC로 개체 선택

		Ellipse(ColMapDc,
			CircleRenderPos.ix() - Radius,
			CircleRenderPos.iy() - Radius,
			CircleRenderPos.ix() + Radius,
			CircleRenderPos.iy() + Radius);

		SelectObject(ColMapDc, OldBrush);
		DeleteObject(MyBrush);

		SelectObject(ColMapDc, OldPen);
		DeleteObject(MyPen);
	}
}

void MapModifier::CreateRect(float4 _Pos, int _Horz, int _Vert, bool _DrawLine)
{

    int HalfHorz = _Horz / 2;
    int HalfVert = _Vert / 2;

    if (this == nullptr)
    {
        MsgAssert("ModifierActor가 nullptr 입니다.");
        return;
    }

    if (0 >= HalfHorz)
    {
        MsgAssert("사각형 가로 길이가 0보다 작거나 같을 수 없습니다.");
        return;
    }

    if (0 >= HalfVert)
    {
        MsgAssert("사각형 세로 길이가 0보다 작거나 같을 수 없습니다.");
        return;
    }

    HDC MapDc = Map::MainMap->GetMapDC();
    HDC ColMapDc = Map::MainMap->GetColMapDC();

    float4 RectRenderPos = _Pos;

    //Map에 그림
    {
        //선에 대한 팬 생성
        //PS_SOLID: 실선              || 두께  || 색상
        HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
        HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);

        HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);                     //단색에 대한 논리적 브러쉬를 생성
        HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                 //지정된 DC로 개체 선택

        Rectangle(MapDc,
            RectRenderPos.ix() - HalfHorz,                                         //Left
            RectRenderPos.iy() - HalfVert,                                         //Top
            RectRenderPos.ix() + HalfHorz,
            RectRenderPos.iy() + HalfVert);

        SelectObject(MapDc, OldPen);
        DeleteObject(MyPen);

        SelectObject(MapDc, OldBrush);                                          //다시 기존 브러쉬 선택
        DeleteObject(MyBrush);                                                  //생성한 브러쉬 삭제

    }

    if (true == _DrawLine)
    {
        DrawPixelRect(_Pos, HalfHorz, HalfVert);
    }

    //ColMap에 그림
    {
        HPEN MyPen = CreatePen(PS_SOLID, 1, Magenta);
        HPEN OldPen = (HPEN)SelectObject(ColMapDc, MyPen);

        HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(Magenta);                     //단색에 대한 논리적 브러쉬를 생성
        HBRUSH OldBrush = (HBRUSH)SelectObject(ColMapDc, MyBrush);              //지정된 DC로 개체 선택

        Rectangle(ColMapDc,
            RectRenderPos.ix() - HalfHorz,
            RectRenderPos.iy() - HalfVert,
            RectRenderPos.ix() + HalfHorz,
            RectRenderPos.iy() + HalfVert);

        SelectObject(ColMapDc, OldBrush);
        DeleteObject(MyBrush);

        SelectObject(ColMapDc, OldPen);
        DeleteObject(MyPen);
    }
}

void MapModifier::DrawPixel(float4 _Pos, int _Radius)
{
	HDC MapDc = Map::MainMap->GetMapDC();

	std::string ColMapName = Map::MainMap->GetColMapName();
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);

    if (nullptr == ColImage)
    {
        MsgAssert("충돌검사를 위한 ColImage가 nullptr입니다.");
        return;
    }

	int lineThick = 2;
    float Radius = static_cast<float>(_Radius);
    float Angle = 0.0f;

	float4 CenterPos = _Pos;						                                        //체크 시작점: 원의 중점

    //360도로 변경해야 함
	for (; Angle < 360.0f; ++Angle)
	{
		float4 CheckPos = { 0.0f, -Radius };		                                        //원점에서 반지름만큼 올라간 점, 각도가 변하기 전 원래 값으로 초기화
		CheckPos.RotaitonZDeg(Angle);				                                        //회전변환 적용
		CheckPos += CenterPos;						                                        //회전시킨 후 위치 변화

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

void MapModifier::DrawPixelRect(float4 _Pos, int _Horz, int _Vert)
{
    HDC MapDc = Map::MainMap->GetMapDC();

    std::string ColMapName = Map::MainMap->GetColMapName();
    GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);

    if (nullptr == ColImage)
    {
        MsgAssert("충돌검사를 위한 ColImage가 nullptr입니다.");
        return;
    }

    int lineThick = 2;
    float Horizon = static_cast<float>(_Horz);
    float Vertical = static_cast<float>(_Vert);

    float4 Pos = { _Pos.x - Horizon - 1.0f, _Pos.y - Vertical - 1.0f };                       //사각형 좌측상단에서 가로세로 1pix 옮겨간 점


    float4 ChecUp       = {Pos.x, Pos.y };                                                    //사각형 좌측 상단
    float4 CheckDown    = { Pos.x, Pos.y + Vertical*2 + 2.0f};                                //사각형 좌측 하단

    float4 ChecLeft     = { Pos.x, Pos.y };                                                   //사각형 좌측 상단
    float4 CheckRight   = { Pos.x + Horizon*2 + 2.0f, Pos.y };                                //사각형 우측 상단

    float4 Boundary = { Pos.x + Horizon * 2 + 2.0f, Pos.y + Vertical * 2 + 2.0f };

    for (; ChecUp.x < Boundary.x;)
    {
         if (Blue == ColImage->GetPixelColor(ChecUp, Magenta))
        {
            //선에 대한 팬 생성
            //PS_SOLID: 실선
            HPEN MyPen = CreatePen(PS_SOLID, lineThick, LineColor);
            HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);

            HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(LineColor);                       //단색에 대한 논리적 브러쉬를 생성
            HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                     //지정된 DC로 개체 선택

            Rectangle(MapDc,
                ChecUp.ix() - lineThick,
                ChecUp.iy() - lineThick,
                ChecUp.ix() + lineThick,
                ChecUp.iy() + lineThick);


            SelectObject(MapDc, OldBrush);                                              //다시 기존 브러쉬 선택
            DeleteObject(MyBrush);                                                      //생성한 브러쉬 삭제

            SelectObject(MapDc, OldPen);
            DeleteObject(MyPen);
        }

        if (Blue == ColImage->GetPixelColor(CheckDown, Magenta))
        {
            //선에 대한 팬 생성
            //PS_SOLID: 실선
            HPEN MyPen = CreatePen(PS_SOLID, lineThick, LineColor);
            HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);

            HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(LineColor);                       //단색에 대한 논리적 브러쉬를 생성
            HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                     //지정된 DC로 개체 선택

            Rectangle(MapDc,
                CheckDown.ix() - lineThick,
                CheckDown.iy() - lineThick,
                CheckDown.ix() + lineThick,
                CheckDown.iy() + lineThick);


            SelectObject(MapDc, OldBrush);                                              //다시 기존 브러쉬 선택
            DeleteObject(MyBrush);                                                      //생성한 브러쉬 삭제

            SelectObject(MapDc, OldPen);
            DeleteObject(MyPen);
        }

        ++ChecUp.x;
        ++CheckDown.x;
    }

    for (; ChecLeft.y < Boundary.y;)
    {

        if (Blue == ColImage->GetPixelColor(ChecLeft, Magenta))
        {
            //선에 대한 팬 생성
            //PS_SOLID: 실선
            HPEN MyPen = CreatePen(PS_SOLID, lineThick, LineColor);
            HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);

            HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(LineColor);                       //단색에 대한 논리적 브러쉬를 생성
            HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                     //지정된 DC로 개체 선택

            Rectangle(MapDc,
                ChecLeft.ix() - lineThick,
                ChecLeft.iy() - lineThick,
                ChecLeft.ix() + lineThick,
                ChecLeft.iy() + lineThick);


            SelectObject(MapDc, OldBrush);                                              //다시 기존 브러쉬 선택
            DeleteObject(MyBrush);                                                      //생성한 브러쉬 삭제

            SelectObject(MapDc, OldPen);
            DeleteObject(MyPen);
        }

        if (Blue == ColImage->GetPixelColor(CheckRight, Magenta))
        {
            //선에 대한 팬 생성
            //PS_SOLID: 실선
            HPEN MyPen = CreatePen(PS_SOLID, lineThick, LineColor);
            HPEN OldPen = (HPEN)SelectObject(MapDc, MyPen);

            HBRUSH MyBrush = (HBRUSH)CreateSolidBrush(LineColor);                       //단색에 대한 논리적 브러쉬를 생성
            HBRUSH OldBrush = (HBRUSH)SelectObject(MapDc, MyBrush);                     //지정된 DC로 개체 선택

            Rectangle(MapDc,
                CheckRight.ix() - lineThick,
                CheckRight.iy() - lineThick,
                CheckRight.ix() + lineThick,
                CheckRight.iy() + lineThick);


            SelectObject(MapDc, OldBrush);                                              //다시 기존 브러쉬 선택
            DeleteObject(MyBrush);                                                      //생성한 브러쉬 삭제

            SelectObject(MapDc, OldPen);
            DeleteObject(MyPen);
        }

        ++ChecLeft.y;
        ++CheckRight.y;
    }
     
}
