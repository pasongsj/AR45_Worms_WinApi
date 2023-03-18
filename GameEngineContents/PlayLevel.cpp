#include "PlayLevel.h"
#include "WeaponBazooka.h"
#include "Map.h"
#include "Player.h"
#include "WeaponShotgun.h"
#include "ContentsEnums.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
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
			GameEngineImage* bazAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimLeft.bmp"));
			bazAimLeft->Cut(1, 32);
			GameEngineImage* bazOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffLeft.bmp"));
			bazOffLeft->Cut(1, 7);
			GameEngineImage* bazOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnLeft.bmp"));
			bazOnLeft->Cut(1, 8);

		}

		{
			//Right 플레이어 이미지
			GameEngineImage* IdleRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleRight.bmp"));
			IdleRight->Cut(1, 6);
			GameEngineImage* WalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkRight.bmp"));
			WalkRight->Cut(1, 15);
			GameEngineImage* bazAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimRight.bmp"));
			bazAimRight->Cut(1, 32);
			GameEngineImage* bazOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffRight.bmp"));
			bazOffRight->Cut(1, 7);
			GameEngineImage* bazOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnRight.bmp"));
			bazOnRight->Cut(1, 8);
		}
	}

}

void PlayLevel::KeyLoad()
{
	if (false == GameEngineInput::IsKey("ChangePlayer"))
	{
		GameEngineInput::CreateKey("ChangePlayer", 'n');
		GameEngineInput::CreateKey("DebugCollision", '8');
		GameEngineInput::CreateKey("WeaponUp", 'W');
		GameEngineInput::CreateKey("WeaponDown", 'S');
		GameEngineInput::CreateKey("Shoot", VK_SPACE);
	}
}

void PlayLevel::PlayerChange(float _DeltaTime)
{
	//Player벡터 오류 검사
	if (-1 == iPlayerNumber)
	{
		MsgAssert("PlayerNumber가 -1 입니다.");
	}

	//ChangePlayer 키가 눌렸을때
	if (GameEngineInput::IsDown("ChangePlayer"))
	{
		//벡터 인덱스 증가
		++iPlayerNumber;

		//초과시 0
		if (8 == iPlayerNumber)
		{
			iPlayerNumber = 0;
		}

		//현재 플레이어의 턴 종료
		pCurPlayer->SetIsMyTurn(false);

		//다음 플레이어가 현재 플레이어가됨
		pCurPlayer = vecAllPlayer[iPlayerNumber];
		pCurPlayer->SetIsMyTurn(true);

		CurPlayerPos = pCurPlayer->GetPos();
		PrevCamPos = GetCameraPos();
		bCamMove = true;
	}

	//플레이어가 변경되었다면
	if (bCamMove)
	{
		//1초동안 플레이어 카메라 위치 변경
		fLerpRatio += _DeltaTime;
		SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - ScreenSize.half(), fLerpRatio));

		if (fLerpRatio > 1.f)
		{
			bCamMove = false;
			fLerpRatio = 0.f;
		}
	}
}

void PlayLevel::MoveCamForMouse(float _DeltaTime)
{
	float4 CurCamPos = GetCameraPos() + ScreenSize.half();
	float4 CurMousePos = GetMousePosToCamera();
	float4 DistancePos = CurMousePos - CurCamPos;
	float4 MoveCam = float4::Zero;

	if (DistancePos.x>500.f)
	{
		MoveCam += float4::Right;
	}
	if (DistancePos.x < -500.f)
	{
		MoveCam += float4::Left;
	}
	if (DistancePos.y< -350.f)
	{
		MoveCam += float4::Up;
	}
	if (DistancePos.y > 350.f)
	{
		MoveCam += float4::Down;
	}
	
	if (MoveCam.ix() == 0&& MoveCam.iy()==0)
	{
		return;
	}
	
	MoveCam.Normalize();
	SetCameraMove(MoveCam*500.f *_DeltaTime);
}

void PlayLevel::Loading()
{
	SoundLoad();
	ImageLoad();
	KeyLoad();

	{
		Map* Actor = CreateActor<Map>();
	}
	{
		ScreenSize = GameEngineWindow::GetScreenSize(); 

		vecAllPlayer.reserve(8);
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
		SetCameraPos(pCurPlayer->GetPos() - ScreenSize.half());
	}

	CreateActor<WeaponBazooka>();
}

void PlayLevel::Update(float _DeltaTime)
{
	PlayerChange(_DeltaTime);
	MoveCamForMouse(_DeltaTime);
	if (GameEngineInput::IsDown("DebugCollision"))
	{
		DebugRenderSwitch();
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<WeaponShotgun>();
}