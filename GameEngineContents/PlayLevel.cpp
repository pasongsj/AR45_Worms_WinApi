#include "PlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Map.h"
#include "Player.h"

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
	Dir.Move("Play");

	{
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
	{
		Dir.Move("Player");
		Dir.Move("Image");
		{
			//Left 플레이어 이미지
			GameEngineImage* IdleLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleLeft.bmp"));
			IdleLeft->Cut(1, 6);
		}
		{
			//Right 플레이어 이미지
			GameEngineImage* IdleRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleRight.bmp"));
			IdleRight->Cut(1, 6);
		}
	}
}

void PlayLevel::Loading()
{
	SoundLoad();
	ImageLoad();

	{
		Map* Actor = CreateActor<Map>();
	}
	{
		WormPlayer1 = CreateActor<Player>();
		WormPlayer1->SetColImage("MapCity_Ground.bmp");
	}
}

void PlayLevel::Update(float _DeltaTime)
{
}

