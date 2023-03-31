#include "EndingLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
EndingLevel::EndingLevel()
{

}
EndingLevel::~EndingLevel()
{

}
void EndingLevel::Loading()
{
    GameEngineDirectory Dir;
    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");
    Dir.Move("Title");

    {
        GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Worms_EndingBackDrop.BMP"));
    }

}

void EndingLevel::Update(float _DeltaTime)
{

}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
