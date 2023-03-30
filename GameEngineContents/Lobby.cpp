#include "Lobby.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCore.h>
#include "MouseObject.h"
#include "Cusor.h"
#include "Star.h"
#include "GlobalValue.h"
#include "PlayLevel.h"
#include "Map.h"
Lobby::Lobby()
{

}

Lobby::~Lobby()
{

}



void Lobby::Start()
{
    // 기본창 
    {
        BackGround = CreateRender("Lobby_Backdrop.bmp", WormsMainTitle::BackGround);
        BackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
        BackGround->SetScale({ GameEngineWindow::GetScreenSize().x,GameEngineWindow::GetScreenSize().y });

        MapSelect = CreateRender("MapSelect.bmp", WormsMainTitle::Select);
        MapSelect->SetPosition({ 330,200 });
        MapSelect->SetScale({ 580, 300 });

        Teams = CreateRender("Teams.bmp", WormsMainTitle::Select);
        Teams->SetPosition({ 950,200 });
        Teams->SetScale({ 580, 300 });

        Option = CreateRender("Option.bmp", WormsMainTitle::Select);
        Option->SetPosition({ 330,530 });
        Option->SetScale({ 580, 300 });

        Barracks = CreateRender("Barracks.bmp", WormsMainTitle::Select);
        Barracks->SetPosition({ 950,525 });
        Barracks->SetScale({ 580, 305 });
    }


   // 맵 
   {
        Map = CreateRender("LobbyMap_MapBooks.bmp", WormsMainTitle::Select);
        Map->SetPosition({ 330,200 });
        Map->SetScale({ 500, 200 });


        Map2 = CreateRender("LobbyMap_MapCars.bmp", WormsMainTitle::Select);
        Map2->SetPosition({ 330,200 });
        Map2->SetScale({ 500, 200 });
        Map2->Off();

        Map3 = CreateRender("LobbyMap_MapCity.bmp", WormsMainTitle::Select);
        Map3->SetPosition({ 330,200 });
        Map3->SetScale({ 500, 200 });
        Map3->Off();

        Map4 = CreateRender("LobbyMap_MapTrain.bmp", WormsMainTitle::Select);
        Map4->SetPosition({ 330,200 });
        Map4->SetScale({ 500, 200 });
        Map4->Off();
   }
   // 옵션
   {
       OptionWeapon = CreateRender("weaponoptions.bmp", WormsMainTitle::Select);
       OptionWeapon->SetPosition({ 185,530 });
       OptionWeapon->SetScale({ 266,190 });

       OptionMap = CreateRender("gameoptions.bmp", WormsMainTitle::Select);
       OptionMap->SetPosition({ 470,530 });
       OptionMap->SetScale({ 266,190 });

   }
   //플레이어 
   {
       Player = CreateRender("1Up.bmp", WormsMainTitle::Select);
       Player->SetPosition({ 740,455 });
       Player->SetScale({ 80,26 });

       Player2 = CreateRender("2Up.bmp", WormsMainTitle::Select);
       Player2->SetPosition({ 740,483 });
       Player2->SetScale({ 80,26 });

       Player3 = CreateRender("3Up.bmp", WormsMainTitle::Select);
       Player3->SetPosition({ 740,511 });
       Player3->SetScale({ 80,26 });

       Player4 = CreateRender("4Up.bmp", WormsMainTitle::Select);
       Player4->SetPosition({ 740,539 });
       Player4->SetScale({ 80,26 });

       Player5 = CreateRender("5Up.bmp", WormsMainTitle::Select);
       Player5->SetPosition({ 740,567 });
       Player5->SetScale({ 80,26 });

       Player6 = CreateRender("6Up.bmp", WormsMainTitle::Select);
       Player6->SetPosition({ 740,595 });
       Player6->SetScale({ 80,26 });
   }
   // 턴 시간 
   {
       TurnTime15 = CreateRender("000000.bmp", WormsMainTitle::Select);
       TurnTime15->SetPosition({ 90,740 });
       TurnTime15->SetScale({ 68,68 });

       TurnTime20 = CreateRender("000001.bmp", WormsMainTitle::Select);
       TurnTime20->SetPosition({ 90,740 });
       TurnTime20->SetScale({ 68,68 });
       TurnTime20->Off();

       TurnTime30 = CreateRender("000002.bmp", WormsMainTitle::Select);
       TurnTime30->SetPosition({ 90,740 });
       TurnTime30->SetScale({ 68,68 });
       TurnTime30->Off();

       TurnTime45 = CreateRender("000003.bmp", WormsMainTitle::Select);
       TurnTime45->SetPosition({ 90,740 });
       TurnTime45->SetScale({ 68,68 });
       TurnTime45->Off();

       TurnTime60 = CreateRender("000004.bmp", WormsMainTitle::Select);
       TurnTime60->SetPosition({ 90,740 });
       TurnTime60->SetScale({ 68,68 });
       TurnTime60->Off();

       TurnTime90 = CreateRender("000005.bmp", WormsMainTitle::Select);
       TurnTime90->SetPosition({ 90,740 });
       TurnTime90->SetScale({ 68,68 });
       TurnTime90->Off();

       TurnTime00 = CreateRender("000006.bmp", WormsMainTitle::Select);
       TurnTime00->SetPosition({ 90,740 });
       TurnTime00->SetScale({ 68,68 });
       TurnTime00->Off();
   }
   // 라운드 시간 
   {
       RoundTime0 = CreateRender("Round0.bmp", WormsMainTitle::Select);
       RoundTime0->SetPosition({ 180,740 });
       RoundTime0->SetScale({ 68,68 });

       RoundTime1 = CreateRender("Round1.bmp", WormsMainTitle::Select);
       RoundTime1->SetPosition({ 180,740 });
       RoundTime1->SetScale({ 68,68 });
       RoundTime1->Off();

       RoundTime2 = CreateRender("Round2.bmp", WormsMainTitle::Select);
       RoundTime2->SetPosition({ 180,740 });
       RoundTime2->SetScale({ 68,68 });
       RoundTime2->Off();

       RoundTime3 = CreateRender("Round3.bmp", WormsMainTitle::Select);
       RoundTime3->SetPosition({ 180,740 });
       RoundTime3->SetScale({ 68,68 });
       RoundTime3->Off();

       RoundTime4 = CreateRender("Round4.bmp", WormsMainTitle::Select);
       RoundTime4->SetPosition({ 180,740 });
       RoundTime4->SetScale({ 68,68 });
       RoundTime4->Off();

       RoundTime5 = CreateRender("Round5.bmp", WormsMainTitle::Select);
       RoundTime5->SetPosition({ 180,740 });
       RoundTime5->SetScale({ 68,68 });
       RoundTime5->Off();

       RoundTime6 = CreateRender("Round6.bmp", WormsMainTitle::Select);
       RoundTime6->SetPosition({ 180,740 });
       RoundTime6->SetScale({ 68,68 });
       RoundTime6->Off();
   }
   // 이기는 횟수 
   {
       

       Wins1 = CreateRender("Wins1.bmp", WormsMainTitle::Select);
       Wins1->SetPosition({ 270,740 });
       Wins1->SetScale({ 68,68 });

       Wins2 = CreateRender("Wins2.bmp", WormsMainTitle::Select);
       Wins2->SetPosition({ 270,740 });
       Wins2->SetScale({ 68,68 });

       Wins3 = CreateRender("Wins3.bmp", WormsMainTitle::Select);
       Wins3->SetPosition({ 270,740 });
       Wins3->SetScale({ 68,68 });

       Wins4 = CreateRender("Wins4.bmp", WormsMainTitle::Select);
       Wins4->SetPosition({ 270,740 });
       Wins4->SetScale({ 68,68 });

       Wins5 = CreateRender("Wins5.bmp", WormsMainTitle::Select);
       Wins5->SetPosition({ 270,740 });
       Wins5->SetScale({ 68,68 });

       Wins6 = CreateRender("Wins6.bmp", WormsMainTitle::Select);
       Wins6->SetPosition({ 270,740 });
       Wins6->SetScale({ 68,68 });

       Wins0 = CreateRender("Wins0.bmp", WormsMainTitle::Select);
       Wins0->SetPosition({ 270,740 });
       Wins0->SetScale({ 68,68 });

   }
   // 웜즈 선택
   {
       WormSelectOFF = CreateRender("WormSelectOFF.bmp", WormsMainTitle::Select);
       WormSelectOFF->SetPosition({ 360,740 });
       WormSelectOFF->SetScale({ 68,68 });

       WormSelectON = CreateRender("WormSelectON.bmp", WormsMainTitle::Select);
       WormSelectON->SetPosition({ 360,740 });
       WormSelectON->SetScale({ 68,68 });

       WormSelectRANDOM = CreateRender("WormSelectRANDOM.bmp", WormsMainTitle::Select);
       WormSelectRANDOM->SetPosition({ 360,740 });
       WormSelectRANDOM->SetScale({ 68,68 });
   }
   // 웜즈 체력 
   {
 
       Hp100 = CreateRender("Hp100.bmp", WormsMainTitle::Select);
       Hp100->SetPosition({ 450,740 });
       Hp100->SetScale({ 68,68 });
       Hp100->On();

       Hp150 = CreateRender("Hp150.bmp", WormsMainTitle::Select);
       Hp150->SetPosition({ 450,740 });
       Hp150->SetScale({ 68,68 });
       Hp150->Off();

       Hp200 = CreateRender("Hp200.bmp", WormsMainTitle::Select);
       Hp200->SetPosition({ 450,740 });
       Hp200->SetScale({ 68,68 });
       Hp200->Off();

       Hp00 = CreateRender("Hp00.bmp", WormsMainTitle::Select);
       Hp00->SetPosition({ 450,740 });
       Hp00->SetScale({ 68,68 });
       Hp00->Off();

   }
   // 텔레포트 온오브 
   {
       SelectOn = CreateRender("TeleportinON.bmp", WormsMainTitle::Select);
       SelectOn->SetPosition({ 540,740 });
       SelectOn->SetScale({ 68,68 });

       SelectOff = CreateRender("TeleportinOFF.bmp", WormsMainTitle::Select);
       SelectOff->SetPosition({ 540,740 });
       SelectOff->SetScale({ 68,68 });
       SelectOff->Off(); 
      
   }

   StartGame = CreateRender("StartGame.bmp", WormsMainTitle::Select);
   StartGame->SetPosition({ 1040,750 });
   StartGame->SetScale({ 392, 126 });

   OptionsSelect = CreateRender("6868.bmp", WormsMainTitle::Select);
   OptionsSelect->SetPosition({ 540,740 });
   OptionsSelect->SetScale({ 68,68 });
   OptionsSelect->Off();

   Exit = CreateRender("Exit.bmp", WormsMainTitle::Select);
   Exit->SetPosition({ 1125,870 });
   Exit->SetScale({ 224, 72 });



   MouseSelect = CreateRender("5618.bmp", WormsMainTitle::Select);
   MouseSelect->SetPosition({ 1040,750 });
   MouseSelect->SetScale({ 392, 126 });
   MouseSelect->Off();

   OptionSelect = CreateRender("11280.bmp", WormsMainTitle::Select);
   OptionSelect->SetPosition({ 185,530 });
   OptionSelect->SetScale({ 266,190 });
   OptionSelect->Off();



   {
       GameStartCollision = CreateCollision();
       GameStartCollision->SetPosition({ 1040,750 });
       GameStartCollision->SetScale({ 392, 126 });
      
       ExitCollision = CreateCollision();
       ExitCollision->SetPosition({ 1125,870 });
       ExitCollision->SetScale({ 224, 72 });

       MapCollision = CreateCollision();
       MapCollision->SetPosition({ 330,200 });
       MapCollision->SetScale({ 500, 200 });

       OptionCollision = CreateCollision();
       OptionCollision->SetPosition({ 470,530 });
       OptionCollision->SetScale({ 266,190 });

       WeaponCollision = CreateCollision();
       WeaponCollision->SetPosition({ 185,530 });
       WeaponCollision->SetScale({ 266,190 });

       TurnCollision = CreateCollision();
       TurnCollision->SetPosition({ 90,740 });
       TurnCollision->SetScale({ 68,68 });

       RoundCollision = CreateCollision();
       RoundCollision->SetPosition({ 180,740 });
       RoundCollision->SetScale({ 68,68 });

       WinsCollision = CreateCollision();
       WinsCollision->SetPosition({ 270,740 });
       WinsCollision->SetScale({ 68,68 });

       WormsCollision = CreateCollision();
       WormsCollision->SetPosition({ 360,740 });
       WormsCollision->SetScale({ 68,68 });

       HpCollision = CreateCollision();
       HpCollision->SetPosition({ 450,740 });
       HpCollision->SetScale({ 68,68 });

       SelectOnCollision = CreateCollision();
       SelectOnCollision->SetPosition({ 540,740 });
       SelectOnCollision->SetScale({ 68,68 });

       PlayerCollision = CreateCollision();
       PlayerCollision->SetPosition({ 950,525 });
       PlayerCollision->SetScale({ 580, 305 });

       PlayerDownCollision = CreateCollision();
       PlayerDownCollision->SetPosition({ 950,200 });
       PlayerDownCollision->SetScale({ 580, 300 });

   }
   if (false == GameEngineInput::IsKey("LeftClock"))
   {
       GameEngineInput::CreateKey("LeftClock", VK_LBUTTON);
   }

   MouseObject* Object = GetLevel()->CreateActor<MouseObject>();
   Cusor* cusor = GetLevel()->CreateActor<Cusor>();
}

void Lobby::Update(float _DeltaTime)
{
    float RandomX = GameEngineRandom::MainRandom.RandomFloat(-800, 1000);
    float RandomY = GameEngineRandom::MainRandom.RandomFloat(-200, 0);
    Time += GameEngineTime::GlobalTime.GetFloatDeltaTime();

    if (Time > 0.15)
    {
        Star* Actor = GetLevel()->CreateActor<Star>();
        Actor->SetMove({ RandomX ,RandomY });
        Time = 0;
    }

    MouseSelect->Off();
    OptionSelect->Off();
    OptionsSelect->Off();

    if (nullptr != GameStartCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == GameStartCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            MouseSelect->SetPosition({ 1040,750 });
            MouseSelect->SetScale({ 392, 126 });

            MouseSelect->On();

            if (GameEngineInput::IsDown("LeftClock"))
            {
                GameEngineCore::GetInst()->ChangeLevel("Play");
            }
        }

        
    }

    if (nullptr != ExitCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == ExitCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            MouseSelect->SetPosition({ 1125,870 });
            MouseSelect->SetScale({ 224, 72 });

            MouseSelect->On();
        }
    }
    
    if (nullptr != MapCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == MapCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            if (GameEngineInput::IsDown("LeftClock"))
            {             
                ++MapChoice;             
            }
        }
    }

    if (nullptr != OptionCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == OptionCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            OptionSelect->On();
            OptionSelect->SetPosition({ 470,530 });

        }
    }

    if (nullptr != WeaponCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == WeaponCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {

            OptionSelect->On();
            OptionSelect->SetPosition({ 185, 530 });
        }      
    }

    if (nullptr != TurnCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == TurnCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            OptionsSelect->On();
            OptionsSelect->SetPosition({ 90,740 });



            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++TurnChoice;
            }

        }
    }

    if (nullptr != RoundCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == RoundCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            OptionsSelect->On();
            OptionsSelect->SetPosition({ 180,740 });

            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++RoundChoice;
            }

        }
    }

    if (nullptr != WinsCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == WinsCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            OptionsSelect->On();
            OptionsSelect->SetPosition({ 270,740 });

            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++WinChoice;
            }
        }
    }

    if (nullptr != WormsCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == WormsCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            OptionsSelect->On();
            OptionsSelect->SetPosition({ 360,740 });

            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++WormsChoice;
            }

        }
    }

    if (nullptr != HpCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == HpCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            OptionsSelect->On();
            OptionsSelect->SetPosition({ 450,740 });

            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++HpChoice;
            }


            
        }
    }
    if (nullptr != SelectOnCollision)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == SelectOnCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
            OptionsSelect->On();
            OptionsSelect->SetPosition({ 540,740 });

            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++TeleportChoice;
            }
        }
    }
    if (nullptr != PlayerCollision && PlayerChoice < 6)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == PlayerCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {
        
            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++PlayerChoice;
                --PlayerDown;
            }
        }
    }
    if (nullptr != PlayerDownCollision && PlayerDown < 6)
    {
        std::vector<GameEngineCollision*> collision;
        if (true == PlayerDownCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::WeaPonInterFace), .TargetColType = CT_Point ,.ThisColType = CT_Rect }, collision))
        {

            if (GameEngineInput::IsDown("LeftClock"))
            {
                ++PlayerDown;
                --PlayerChoice;
            }
        }
    }


    Mapchoice();
    Turnchoice();
    Roundchoice(); 
    Winchoice();
    Wormschoice();
    Hpchoice();
    Teleportchoice();
    Playerchoice();
    Playerdown();
}
void Lobby::Mapchoice()
{
    if (MapChoice == 4)
    {
        MapChoice = 0;
    }

    switch (MapChoice)
    {
    case 0:
        Map->On();
        Map2->Off();
        Map3->Off();
        Map4->Off();
        Map::MapMode = 0;
        break;
    case 1:
        Map->Off();
        Map2->On();
        Map3->Off();
        Map4->Off();
        Map::MapMode = 1;
        break;
    case 2:
        Map->Off();
        Map2->Off();
        Map3->On();
        Map4->Off();
        Map::MapMode = 2;
        break;
    case 3:
        Map->Off();
        Map2->Off();
        Map3->Off();
        Map4->On();
        Map::MapMode = 3;
        break;
    default:
        break;
    }
}
void Lobby::Turnchoice()
{
    if (TurnChoice == 7)
    {
        TurnChoice = 0;
    }

    switch (TurnChoice)
    {
    case 0:
        TurnTime15->On();
        TurnTime20->Off();
        TurnTime30->Off();
        TurnTime45->Off();
        TurnTime60->Off();
        TurnTime90->Off();
        TurnTime00->Off();
        SetLevel.fTime = 15.f;
        break;
    case 1:
        TurnTime15->Off();
        TurnTime20->On();
        TurnTime30->Off();
        TurnTime45->Off();
        TurnTime60->Off();
        TurnTime90->Off();
        TurnTime00->Off();
        SetLevel.fTime = 20.f;
        break;
    case 2:
        TurnTime15->Off();
        TurnTime20->Off();
        TurnTime30->On();
        TurnTime45->Off();
        TurnTime60->Off();
        TurnTime90->Off();
        TurnTime00->Off();
        SetLevel.fTime = 30.f;
        break;
    case 3:
        TurnTime15->Off();
        TurnTime20->Off();
        TurnTime30->Off();
        TurnTime45->On();
        TurnTime60->Off();
        TurnTime90->Off();
        TurnTime00->Off();
        SetLevel.fTime = 45.f;
        break;
    case 4:
        TurnTime15->Off();
        TurnTime20->Off();
        TurnTime30->Off();
        TurnTime45->Off();
        TurnTime60->On();
        TurnTime90->Off();
        TurnTime00->Off();
        SetLevel.fTime = 60.f;
        break;
    case 5:
        TurnTime15->Off();
        TurnTime20->Off();
        TurnTime30->Off();
        TurnTime45->Off();
        TurnTime60->Off();
        TurnTime90->On();
        TurnTime00->Off();
        SetLevel.fTime = 90.f;
        break;
    case 6:
        TurnTime15->Off();
        TurnTime20->Off();
        TurnTime30->Off();
        TurnTime45->Off();
        TurnTime60->Off();
        TurnTime90->Off();
        TurnTime00->On();
        break;
    default:
        break;
    }
}
void Lobby::Roundchoice()
{
    if (RoundChoice == 7)
    {
        RoundChoice = 0;
    }

    switch (RoundChoice)
    {
    case 0:
        RoundTime0->On();
        RoundTime1->Off();
        RoundTime2->Off();
        RoundTime3->Off();
        RoundTime4->Off();
        RoundTime5->Off();
        RoundTime6->Off();
        break;
    case 1:
        RoundTime0->Off();
        RoundTime1->On();
        RoundTime2->Off();
        RoundTime3->Off();
        RoundTime4->Off();
        RoundTime5->Off();
        RoundTime6->Off();
        break;
    case 2:
        RoundTime0->Off();
        RoundTime1->Off();
        RoundTime2->On();
        RoundTime3->Off();
        RoundTime4->Off();
        RoundTime5->Off();
        RoundTime6->Off();
        break;
    case 3:
        RoundTime0->Off();
        RoundTime1->Off();
        RoundTime2->Off();
        RoundTime3->On();
        RoundTime4->Off();
        RoundTime5->Off();
        RoundTime6->Off();
        break;
    case 4:
        RoundTime0->Off();
        RoundTime1->Off();
        RoundTime2->Off();
        RoundTime3->Off();
        RoundTime4->On();
        RoundTime5->Off();
        RoundTime6->Off();
        break;
    case 5:
        RoundTime0->Off();
        RoundTime1->Off();
        RoundTime2->Off();
        RoundTime3->Off();
        RoundTime4->Off();
        RoundTime5->On();
        RoundTime6->Off();
        break;
    case 6:
        RoundTime0->Off();
        RoundTime1->Off();
        RoundTime2->Off();
        RoundTime3->Off();
        RoundTime4->Off();
        RoundTime5->Off();
        RoundTime6->On();
        break;
    default:
        break;
    }
}
void Lobby::Winchoice()
{
    if (WinChoice == 7)
    {
        WinChoice = 0;
    }

    switch (WinChoice)
    {
    case 0:
        Wins1->On();
        Wins2->Off();
        Wins3->Off();
        Wins4->Off();
        Wins5->Off();
        Wins6->Off();
        Wins0->Off();
      
        break;
    case 1:
        Wins1->Off();
        Wins2->On();
        Wins3->Off();
        Wins4->Off();
        Wins5->Off();
        Wins6->Off();
        Wins0->Off();
        break;
    case 2:
        Wins1->Off();
        Wins2->Off();
        Wins3->On();
        Wins4->Off();
        Wins5->Off();
        Wins6->Off();
        Wins0->Off();
        break;
    case 3:
        Wins1->Off();
        Wins2->Off();
        Wins3->Off();
        Wins4->On();
        Wins5->Off();
        Wins6->Off();
        Wins0->Off();
        break;
    case 4:
        Wins1->Off();
        Wins2->Off();
        Wins3->Off();
        Wins4->Off();
        Wins5->On();
        Wins6->Off();
        Wins0->Off();
        break;
    case 5:
        Wins1->Off();
        Wins2->Off();
        Wins3->Off();
        Wins4->Off();
        Wins5->Off();
        Wins6->On();
        Wins0->Off();
        break;
    case 6:
        Wins1->Off();
        Wins2->Off();
        Wins3->Off();
        Wins4->Off();
        Wins5->Off();
        Wins6->Off();
        Wins0->On();
        break;
    default:
        break;
    }
}
void Lobby::Wormschoice()
{
    if (WormsChoice == 3)
    {
        WormsChoice = 0;
    }



    switch (WormsChoice)
    {
    case 0:
        WormSelectOFF->On();
        WormSelectON->Off();
        WormSelectRANDOM->Off();
        SetLevel.iTurnRandom = 0;
        break;
    case 1:
        WormSelectOFF->Off();
        WormSelectON->On();
        WormSelectRANDOM->Off();
        SetLevel.iTurnRandom = 1;
        break;
    case 2:
        WormSelectOFF->Off();
        WormSelectON->Off();
        WormSelectRANDOM->On();
        SetLevel.iTurnRandom = 2;
        break;
   
    default:
        break;
    }
}
void Lobby::Hpchoice()
{
    if (HpChoice == 4)
    {
        HpChoice = 0;
    }
    switch (HpChoice)
    {
    case 0:
        Hp100->On();
        Hp150->Off();
        Hp200->Off();
        Hp00->Off();
        SetLevel.iPlayerHp = 100;
        break;
    case 1:
        Hp100->Off();
        Hp150->On();
        Hp200->Off();
        Hp00->Off();
        SetLevel.iPlayerHp = 150;

        break;
    case 2:
        Hp100->Off();
        Hp150->Off();
        Hp200->On();
        Hp00->Off();
        SetLevel.iPlayerHp = 200;
        
        break;
    case 3:
        Hp100->Off();
        Hp150->Off();
        Hp200->Off();
        Hp00->On();

        break;

    default:
        break;
    }
}
void Lobby::Teleportchoice()
{
    if (TeleportChoice == 2)
    {
        TeleportChoice = 0;
    }
    switch (TeleportChoice)
    {
    case 0:
        SelectOn->On();
        SelectOff->Off();        
        SetLevel.bMousePosPlayerSet = true;
        break;
    case 1:
        SelectOn->Off();
        SelectOff->On();
        SetLevel.bMousePosPlayerSet = false;
        break;
    default:
        break;
    }

}
void Lobby::Playerchoice()
{

  

    switch (PlayerChoice)
    {
    case 1:
        Player->SetPosition({ 740,105 });
        Player->SetScale({ 100,32 });     
        SetLevel.iPlayerNum = 1;
        break;
    case 2:
        Player2->SetPosition({ 740,145 });
        Player2->SetScale({ 100,32 });
        SetLevel.iPlayerNum = 2;
        break;
    case 3:
        Player3->SetPosition({ 740,185 });
        Player3->SetScale({ 100,32 });
        SetLevel.iPlayerNum = 3;
        break;
    case 4:
        Player4->SetPosition({ 740,225 });
        Player4->SetScale({ 100,32 });
        SetLevel.iPlayerNum = 4;
        break;
    case 5:
        Player5->SetPosition({ 740,265 });
        Player5->SetScale({ 100,32 });
        SetLevel.iPlayerNum = 5;
        break;
    case 6:
        Player6->SetPosition({ 740,305 });
        Player6->SetScale({ 100,32 });
        SetLevel.iPlayerNum = 6;
        break;

    default:
        break;
    }

}
void Lobby::Playerdown()
{
    switch (PlayerDown)
    {
    case 1:
        Player6->SetPosition({ 740,455 });
        Player6->SetScale({ 80,26 });
        break;
    case 2:

        Player5->SetPosition({ 740,455 });
        Player5->SetScale({ 80,26 });
        Player6->SetPosition({ 740,483 });
        Player6->SetScale({ 80,26 });     
        break;
    case 3:
        Player4->SetPosition({ 740,455 });
        Player4->SetScale({ 80,26 });
        Player5->SetPosition({ 740,483 });
        Player5->SetScale({ 80,26 });
        Player6->SetPosition({ 740,511 });
        Player6->SetScale({ 80,26 });
        break;
    case 4:
        Player3->SetPosition({ 740,455 });
        Player3->SetScale({ 80,26 });
        Player4->SetPosition({ 740,483 });
        Player4->SetScale({ 80,26 });
        Player5->SetPosition({ 740,511 });
        Player5->SetScale({ 80,26 });
        Player6->SetPosition({ 740,539 });
        Player6->SetScale({ 80,26 });
        break;
    case 5:
        Player2->SetPosition({ 740,455 });
        Player2->SetScale({ 80,26 });
        Player3->SetPosition({ 740,483 });
        Player3->SetScale({ 80,26 });
        Player4->SetPosition({ 740,511 });
        Player4->SetScale({ 80,26 });
        Player5->SetPosition({ 740,539 });
        Player5->SetScale({ 80,26 });
        Player6->SetPosition({ 740,567 });
        Player6->SetScale({ 80,26 });
        break;
    case 6:
        Player->SetPosition({ 740,455 });
        Player->SetScale({ 80,26 });
        Player2->SetPosition({ 740,483 });
        Player2->SetScale({ 80,26 });
        Player3->SetPosition({ 740,511 });
        Player3->SetScale({ 80,26 });
        Player4->SetPosition({ 740,539 });
        Player4->SetScale({ 80,26 });
        Player5->SetPosition({ 740,567 });
        Player5->SetScale({ 80,26 });
        Player6->SetPosition({ 740,595 });
        Player6->SetScale({ 80,26 });
        break;

    default:
        break;
    }
}

void Lobby::Render(float _DeltaTime)
{

}

void Lobby::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
    GlobalValue::gValue.GetPlayLevel()->SetLevelSetting(SetLevel);
}
