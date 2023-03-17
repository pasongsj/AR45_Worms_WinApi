#include "PlayLevel.h"
#include "WeaponBazooka.h"
#include "Map.h"
#include "Player.h"
#include "WeaponShotgun.h"
#include "ContentsEnums.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>


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
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("gradient.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Under_Water.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Water_sprite.bmp"));
		Image->Cut(1, 11);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Water_sprite_surfice.bmp"));
		Image->Cut(1, 11);

		Dir.MoveParent();
	}
	{
		Dir.Move("Weapon");

		GameEngineImage* bazooka = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazooka.bmp"));
		GameEngineImage* bazookaRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazookaRot.bmp"));
		GameEngineImage* Weapon2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Weapon2.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TempBomb.bmp"));

		Dir.MoveParent();
	}
	{
		Dir.Move("Player");
		Dir.Move("Image");
		{
			//Left 플레이어 이미지
			GameEngineImage* IdleLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleLeft.bmp"));
			IdleLeft->Cut(1, 6);
			GameEngineImage* WalkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkLeft.bmp"));
			WalkLeft->Cut(1, 15);
		}
		{
			//Right 플레이어 이미지
			GameEngineImage* IdleRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleRight.bmp"));
			IdleRight->Cut(1, 6);
			GameEngineImage* WalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkRight.bmp"));
			WalkRight->Cut(1, 15);
		}
	}

}

void PlayLevel::Loading()
{
	SoundLoad();
	ImageLoad();

	if (false == GameEngineInput::IsKey("ChangePlayer"))
	{
		GameEngineInput::CreateKey("ChangePlayer", 'n');
		GameEngineInput::CreateKey("DebugCollision", '8');
		GameEngineInput::CreateKey("WeaponUp", 'W');
		GameEngineInput::CreateKey("WeaponDown", 'S');
		GameEngineInput::CreateKey("Shoot", VK_SPACE);
	}

	{
		Map* Actor = CreateActor<Map>();
	}
	{
		ScreenSize = GameEngineWindow::GetScreenSize(); 

		//vecAllPlayer.resize(8);
		for (size_t i = 0; i < 8; i++)
		{
			int iRandxPos = GameEngineRandom::MainRandom.RandomInt(0, 300);

			vecAllPlayer.push_back(CreateActor<Player>(WormsRenderOrder::Player));
			vecAllPlayer[i]->SetColImage("MapCity_Ground.bmp");

			float4 StartPos = float4{ 350,50 };
			StartPos.x *= i+1;
			StartPos.x += iRandxPos;
			vecAllPlayer[i]->SetPos(StartPos);
		}

		iPlayerNumber = 0;
		pCurPlayer = vecAllPlayer[iPlayerNumber];
		pCurPlayer->SetIsMyTurn(true);
	}

	CreateActor<WeaponBazooka>();
}

void PlayLevel::Update(float _DeltaTime)
{
	if (-1 == iPlayerNumber)
	{
		MsgAssert("PlayerNumber가 -1 입니다.");
	}
	if (GameEngineInput::IsDown("ChangePlayer"))
	{
		++iPlayerNumber;
		if (8 == iPlayerNumber)
		{
			iPlayerNumber = 0;
		}
		pCurPlayer->SetIsMyTurn(false);
		pCurPlayer = vecAllPlayer[iPlayerNumber];
		pCurPlayer->SetIsMyTurn(true);

		float4 CurPlayerPos = pCurPlayer->GetPos();
		SetCameraPos(CurPlayerPos - ScreenSize.half());
	}

	if (GameEngineInput::IsDown("DebugCollision"))
	{
		DebugRenderSwitch();
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<WeaponShotgun>();
}