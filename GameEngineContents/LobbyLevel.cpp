#include "LobbyLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Lobby.h"
LobbyLevel::LobbyLevel()
{
}

LobbyLevel::~LobbyLevel()
{
}

void LobbyLevel::Loading()
{
    GameEngineDirectory Dir;
    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");
    Dir.Move("Title");

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapSelect.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Teams.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Barracks.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Option.BMP"));
    }

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StartGame.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Exit.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("8436.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("12864.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("24226.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("5618.BMP"));
    }

    // ¸Ê 
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LobbyMap_MapBooks.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LobbyMap_MapCars.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LobbyMap_MapCity.BMP"));
    }
    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LobbyMap_MapTrain.BMP"));
    }

    CreateActor<Lobby>();
}

void LobbyLevel::Update(float _DeltaTime)
{
}
