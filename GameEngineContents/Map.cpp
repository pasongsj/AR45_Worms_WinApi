#include "Map.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "GlobalValue.h"
#include "PlayLevel.h"
#include "MapModifier.h"
#include "Medikit.h"
#include "Drum.h"
#include "MapDecoration.h"
#include "WeaponInterFace.h"
#include "PetrolEffect.h"

//ScreenSize: { 1280, 960 }


Map* Map::MainMap = nullptr;
int Map::MapMode = 0;

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
    MainMap = this;

    if (nullptr == MainMap)
    {
        MsgAssert("MainMap이 nullptr입니다.");
        return;
    }


    Maps.push_back("MapCity.bmp");
    Maps.push_back("MapBooks.bmp");
    Maps.push_back("MapCars.bmp");
    Maps.push_back("MapTrain.bmp");

    ColMaps.push_back("MapCity_Ground.bmp");
    ColMaps.push_back("MapBooks_Ground.bmp");
    ColMaps.push_back("MapCars_Ground.bmp");
    ColMaps.push_back("MapTrain_Ground.bmp");

    MapName = Maps[MapMode];
    ColMapName = ColMaps[MapMode];

    //입력 키 생성
    if (false == GameEngineInput::IsKey("FreeLeft"))
    {
        GameEngineInput::CreateKey("FreeLeft", VK_LEFT);
        GameEngineInput::CreateKey("FreeRight", VK_RIGHT);
        GameEngineInput::CreateKey("FreeUp", VK_UP);
        GameEngineInput::CreateKey("FreeDown", VK_DOWN);
    }

    //맵 오브젝트용 키 입력 생성
    if (false == GameEngineInput::IsKey("MediKitButton"))
    {
        GameEngineInput::CreateKey("MediKitButton", 'I');
        GameEngineInput::CreateKey("OilDrumButton", 'O');
    }


    //CreateHole 사용을 위한 키 생성
    if (false == GameEngineInput::IsKey("CreateHoleButton"))
    {
        GameEngineInput::CreateKey("CreateHoleButton", 'H');
    }

    //MapRender 생성
    MapRender = CreateRender(WormsRenderOrder::Map);
    MapRender->SetImage(MapName);
    float4 MapScale = MapRender->GetImage()->GetImageScale();
    MapRender->SetPosition(MapScale.half());
    MapRender->SetScaleToImage();

    //ColMapRender 생성
    {
        ColMapRender = CreateRender(WormsRenderOrder::Map);
        ColMapRender->SetImage(ColMapName);
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
        WaveBack->SetScale(BackScale);
    }
    //Wave Animation
    {
        GameEngineRender* Wave0 = CreateRender(WormsRenderOrder::BackGround);
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
    RandIdx = GameEngineRandom::MainRandom.RandomInt(0, 10);
    {
        GameEngineRender* Wave4 = CreateRender(WormsRenderOrder::Wave);
        Wave4->SetImage("Water_sprite.bmp");
        Wave4->SetPosition(WaveAnimPos4);
        Wave4->SetScale(WaveScale);
        Wave4->CreateAnimation({ .AnimationName = "Wave4",  .ImageName = "Water_sprite.bmp", .Start = 0, .End = 10 });
        Wave4->ChangeAnimation("Wave4", RandIdx);
    }

    std::string LevelName = "Play";
    if (LevelName == GetLevel()->GetName())
    {
        //데코적용
        int NumOfObj = GameEngineRandom::MainRandom.RandomInt(1, 4);
        for (int i = 0; i < NumOfObj; i++)
        {
            MapDecoration* Deco = GetLevel()->CreateActor<MapDecoration>(WormsRenderOrder::Map);
            float4 pos = Deco->GetRandomPos();
            Deco->SetPos(pos);
            Deco->MergeMap();
        }

        //고정 위치에 드럼 생성(시연회용_드럼통 3단계 생상 변화를 위함)
        {
            Drum* Drum1 = GetLevel()->CreateActor<Drum>(WormsRenderOrder::MapObject);
            Drum1->SetPos({640.0f, 100.0f});

            Drum* Drum2 = GetLevel()->CreateActor<Drum>(WormsRenderOrder::MapObject);
            Drum2->SetPos({ 670.0f, 100.0f });

            Drum* Drum3 = GetLevel()->CreateActor<Drum>(WormsRenderOrder::MapObject);
            Drum3->SetPos({ 710.0f, 100.0f });
        
        }
    }
}

void Map::Update(float _DeltaTime)
{
    WaitTime -= _DeltaTime;

    //일정 시간이 지나면 랜덤한 개수의 회복 아이템이 랜덤한 위치에서 드랍
    if (0.0f >= WaitTime)
    {
        int NumOfObj = GameEngineRandom::MainRandom.RandomInt(0, 3);
        for (int i = 0; i < NumOfObj; ++i)
        {
            Medikit* Object = GetLevel()->CreateActor<Medikit>(WormsRenderOrder::MapObject);
            Object->SetPos(Object->GetMapObjPos());
        }
        WaitTime = 70.0f;
    }
	
    if (true == GameEngineInput::IsDown("CreateHoleButton"))
    {
        float4 Pos = GetLevel()->GetMousePosToCamera();
        MapModifier::MainModifier->CreateHole(Pos, 50);

        return;
    }
    

    if (true == GameEngineInput::IsDown("MediKitButton"))
    {
        float4 Pos = GetLevel()->GetMousePosToCamera();
        Medikit* Object = GetLevel()->CreateActor<Medikit>(WormsRenderOrder::MapObject);
        Object->SetPos(Pos);
   
        return;
    }

    if (true == GameEngineInput::IsDown("OilDrumButton"))
    {
        float4 Pos = GetLevel()->GetMousePosToCamera();
        Drum* Object = GetLevel()->CreateActor<Drum>(WormsRenderOrder::MapObject);
        Object->SetPos(Pos);

        return;
    }

	if (true == GameEngineInput::IsDown("DebugMode"))							    //디버깅 모드_충돌맵 혹은 맵을 볼 수 있음
	{
		if (false == IsColMap)
		{
			IsColMap = !IsColMap;
			MapRender->Off();
			ColMapRender->On();
		}
		else
		{
			IsColMap = !IsColMap;
			MapRender->On();
			ColMapRender->Off();
		}
	}

    FreeMoveState(_DeltaTime);
}

void Map::FreeMoveState(float _DeltaTime)
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

void Map::Render(float _DeltaTime)
{
    PlayLevel* CurLevel = GlobalValue::gValue.GetPlayLevel();    

    if (CurLevel->IsDebugTextModeOn())
    {
        std::string MousePosStr = "MousePosition : ";
        MousePosStr += GetLevel()->GetMousePosToCamera().ToString();
        GameEngineLevel::DebugTextPush(MousePosStr);
    }   
}