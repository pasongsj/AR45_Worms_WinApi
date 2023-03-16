#include "WormsCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "CenterLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

void WormsCore::Start()
{
	GameEngineWindow::SettingWindowSize({ 1280, 960 });

	CreateLevel<CenterLevel>("Center");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
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

