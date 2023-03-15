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
}

void CenterLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Number1"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Title");
	}

	std::string TitleLevel = "TitleLevel : Number1";
	DebugTextPush(TitleLevel);
}


