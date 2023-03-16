#include "PlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Map.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::SoundLoad()
{

}

void PlayLevel::ImageLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	{
		Dir.Move("Play");
		Dir.Move("Map");

		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity_Ground.bmp"));

		Dir.MoveParent();
	}
	{
		Dir.Move("Weapon");

		GameEngineImage* Weapon1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Weapon1.bmp"));
		GameEngineImage* Weapon2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Weapon2.bmp"));

		Dir.MoveParent();
	}
}

void PlayLevel::Loading()
{
	SoundLoad();
	ImageLoad();

	{
		Map* Actor = CreateActor<Map>();
	}
}

void PlayLevel::Update(float _DeltaTime)
{
}

