#include "WormsCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "CenterLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "TestLevel.h"
#include "MainTitleLevel.h"
#include "LobbyLevel.h"
#include "EndingLevel.h"
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
	ChangeLevel("Center");
}

void WormsCore::Update()
{
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

