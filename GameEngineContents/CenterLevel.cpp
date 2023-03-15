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

	std::string TitleLevel = "TitleLevel Key : Number1";
	DebugTextPush(TitleLevel);
	std::string PlayLevel = "PlayLevel Key : Number2";
	DebugTextPush(PlayLevel);
}


