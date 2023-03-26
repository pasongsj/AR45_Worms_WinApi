#include "Lobby.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

Lobby::Lobby()
{

}

Lobby::~Lobby()
{

}

void Lobby::Start()
{
    // ±âº»Ã¢ 
    {
        BackGround = CreateRender("Lobby_Backdrop.bmp", WormsMainTitle::BlackBackGround);
        BackGround->SetPosition({ GameEngineWindow::GetScreenSize().half().x,GameEngineWindow::GetScreenSize().half().y });
        BackGround->SetScale({ GameEngineWindow::GetScreenSize().x,GameEngineWindow::GetScreenSize().y });

        MapSelect = CreateRender("MapSelect.bmp", WormsMainTitle::BlackBackGround);
        MapSelect->SetPosition({ 330,200 });
        MapSelect->SetScale({ 580, 300 });

        Teams = CreateRender("Teams.bmp", WormsMainTitle::BlackBackGround);
        Teams->SetPosition({ 950,200 });
        Teams->SetScale({ 580, 300 });

        Option = CreateRender("Option.bmp", WormsMainTitle::BlackBackGround);
        Option->SetPosition({ 330,530 });
        Option->SetScale({ 580, 300 });

        Barracks = CreateRender("Barracks.bmp", WormsMainTitle::BlackBackGround);
        Barracks->SetPosition({ 950,525 });
        Barracks->SetScale({ 580, 305 });
    }


   // ¸Ê 
   {
        Map = CreateRender("LobbyMap_MapBooks.bmp", WormsMainTitle::BlackBackGround);
        Map->SetPosition({ 330,200 });
        Map->SetScale({ 500, 200 });

       /* Map2 = CreateRender("LobbyMap_MapCars.bmp", WormsMainTitle::BlackBackGround);
        Map2->SetPosition({ 950,525 });
        Map2->SetScale({ 580, 305 });

        Map3 = CreateRender("LobbyMap_MapCity.bmp", WormsMainTitle::BlackBackGround);
        Map3->SetPosition({ 950,525 });
        Map3->SetScale({ 580, 305 });

        Map4 = CreateRender("LobbyMap_MapTrain.bmp", WormsMainTitle::BlackBackGround);
        Map4->SetPosition({ 950,525 });
        Map4->SetScale({ 580, 305 });*/

   }


   StartGame = CreateRender("StartGame.bmp", WormsMainTitle::BlackBackGround);
   StartGame->SetPosition({ 1040,750 });
   StartGame->SetScale({ 392, 126 });

   Exit = CreateRender("Exit.bmp", WormsMainTitle::BlackBackGround);
   Exit->SetPosition({ 1125,870 });
   Exit->SetScale({ 224, 72 });
  
  /* MouseSelect = CreateRender("5618.bmp", WormsMainTitle::BlackBackGround);
   MouseSelect->SetPosition({ 1040,750 });
   MouseSelect->SetScale({ 392, 126 });*/

}

void Lobby::Update(float _DeltaTime)
{

}

void Lobby::Render(float _DeltaTime)
{

}
