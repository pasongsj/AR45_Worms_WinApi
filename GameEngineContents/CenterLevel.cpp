#include "CenterLevel.h"

#include <string>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>



CenterLevel::CenterLevel() 
{
}

CenterLevel::~CenterLevel() 
{
}

void CenterLevel::Loading()
{
	if (false == GameEngineInput::IsKey("Number1"))
	{
		GameEngineInput::CreateKey("Number1", '1');
	}
	if (false == GameEngineInput::IsKey("Number2"))
	{
		GameEngineInput::CreateKey("Number2", '2');
	}
	if (false == GameEngineInput::IsKey("Number3"))
	{
		GameEngineInput::CreateKey("Number3", '3');
	}
    if (false == GameEngineInput::IsKey("Number4"))
    {
        GameEngineInput::CreateKey("Number4", '4');
    }
    if (false == GameEngineInput::IsKey("Number5"))
    {
        GameEngineInput::CreateKey("Number5", '5');
    }
}

void CenterLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Number1"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Title");
	}
	if (GameEngineInput::IsDown("Number2"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Play");
	}
	if (GameEngineInput::IsDown("Number3"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Test");
	}
    if (GameEngineInput::IsDown("Number4"))
    {
        GameEngineCore::GetInst()->ChangeLevel("MainTitle");
    }
    if (GameEngineInput::IsDown("Number5"))
    {
        GameEngineCore::GetInst()->ChangeLevel("Lobby");
    }
	std::string TitleLevel = "TitleLevel Key : Number1";
	DebugTextPush(TitleLevel);
	std::string PlayLevel = "PlayLevel Key : Number2";
	DebugTextPush(PlayLevel);
	std::string TestLevel = "TestLevel Key : Number3";
	DebugTextPush(TestLevel);
    std::string MainTitleLevel = "MainTitleLevel Key : Number4";
    DebugTextPush(MainTitleLevel);

    std::string LobbyLevel = "LobbyLevel Key : Number5";
    DebugTextPush(LobbyLevel);

}


