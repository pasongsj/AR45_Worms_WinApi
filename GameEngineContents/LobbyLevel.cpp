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
   /* GameEngineDirectory Dir2;
    Dir2.MoveParentToDirectory("ContentsResources");
    Dir2.Move("ContentsResources");
    Dir2.Move("Image");
    Dir2.Move("Title");*/

    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("MapSelect.BMP"));
    //}

    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Teams.BMP"));
    //}

    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Barracks.BMP"));
    //}

    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Option.BMP"));
    //}

    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("StartGame.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Exit.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("8436.BMP"));
    //}
    //
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("24226.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("5618.BMP"));
    //}

    //// 맵 
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapBooks.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapCars.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapCity.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("LobbyMap_MapTrain.BMP"));
    //}
    //// 옵션
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("weaponoptions.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("gameoptions.BMP"));
    //}   
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("11280.BMP"));
    //}
    //// 플레이어 
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("1Up.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("2Up.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("3Up.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("4Up.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("5Up.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("6Up.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("1.BMP"));
    //}
    //// 턴시간 
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000000.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000001.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000002.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000003.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000004.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000005.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("000006.BMP"));
    //}
    //// 라운드 시간 
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round0.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round1.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round2.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round3.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round4.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round5.BMP"));
    //}
    //{
    //    GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Round6.BMP"));
    //}
    //// 이기는 횟수 
    //{
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins0.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins1.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins2.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins3.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins4.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins5.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Wins6.BMP"));
    //    }

    //}
    //// 웜 선택
    //{
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("WormSelectOFF.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("WormSelectON.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("WormSelectRANDOM.BMP"));
    //    }
    //}
    //// 웜 체력 
    //{
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp00.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp100.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp150.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("Hp200.BMP"));
    //    }
    //}
    //// 텔레포트 온오브 
    //{
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("TeleportinOFF.BMP"));
    //    }
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("TeleportinON.BMP"));
    //    }
    //}

    ////Select
    //{
    //    {
    //        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir2.GetPlusFileName("6868.BMP"));
    //    }
    //}
    //Cusor

   /* {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cursor.BMP"));
    }*/

    CreateActor<Lobby>();
}

void LobbyLevel::Update(float _DeltaTime)
{
}
