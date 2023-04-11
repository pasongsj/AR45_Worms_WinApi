#include "WormsCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "CenterLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "TestLevel.h"
#include "MainTitleLevel.h"
#include "LobbyLevel.h"
#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/PlayerEsc.h>
#include <GameEngineContents/LobbyChangePlay.h>


void WormsCore::Start()
{
	GameEngineWindow::SettingWindowSize({ 1280, 960 });

	CreateLevel<CenterLevel>("Center");
	CreateLevel<TitleLevel>("Title");
    CreateLevel<MainTitleLevel>("MainTitle");
    CreateLevel<LobbyLevel>("Lobby");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<TestLevel>("Test");
    CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");



    if (false == GameEngineInput::IsKey("ESCAPE"))
    {
        GameEngineInput::CreateKey("ESCAPE", VK_ESCAPE);
    }




   

}

void WormsCore::Update()
{
    if (PlayerEsc::Check ==true)
    {     
        Levels.erase("Play");
        Levels.erase("Lobby");
        CreateLevel<PlayLevel>("Play");
        CreateLevel<LobbyLevel>("Lobby");
        LobbyChangePlay::test = false;
        ChangeLevel("Lobby");
        PlayerEsc::Check = false;
    }

   


}

void WormsCore::End()
{
}

WormsCore::WormsCore()
{
}

WormsCore::~WormsCore() 
{
}

