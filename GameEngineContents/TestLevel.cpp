#include "TestLevel.h"
#include <string_view>

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

#include "WeaponBazooka.h"
#include "Map.h"
#include "Player.h"
#include "WeaponShotgun.h"
#include "WeaponGrenade.h"
#include "ContentsEnums.h"
#include "GlobalValue.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::SoundLoad()
{

}

void TestLevel::ImageLoad()
{

}

void TestLevel::KeyLoad()
{	
}

void TestLevel::PlayerChange(float _DeltaTime)
{
	//Player벡터 오류 검사
	if (-1 == iPlayerNumber)
	{
		MsgAssert("PlayerNumber가 -1 입니다.");
	}

	//ChangePlayer 키가 눌렸을때
	//if (GameEngineInput::IsDown("ChangePlayer"))
	if (GameEngineInput::IsDown("ChangePlayer"))
	{
		//벡터 인덱스 증가
		++iPlayerNumber;

		//초과시 0
		if (vecAllPlayer.size() == iPlayerNumber)
		{
			iPlayerNumber = 0;
		}
		
		
		//현재 플레이어의 턴 종료
		GlobalValue::gValue.GetPlayer()->SetIsMyTurn(false);

		//다음 플레이어가 현재 플레이어가됨
		GlobalValue::GlobalValue::gValue.SetPlayer(vecAllPlayer[iPlayerNumber]);
		GlobalValue::gValue.GetPlayer()->SetIsMyTurn(true);

		CurPlayerPos = GlobalValue::gValue.GetPlayer()->GetPos();
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

void TestLevel::MoveCamForMouse(float _DeltaTime)
{
	float4 CurCamPos = GetCameraPos() + ScreenSize.half();
	float4 CurMousePos = GetMousePosToCamera();
	float4 DistancePos = CurMousePos - CurCamPos;
	float4 MoveCam = float4::Zero;

	if (DistancePos.x > 500.f)
	{
		MoveCam += float4::Right;
	}
	if (DistancePos.x < -500.f)
	{
		MoveCam += float4::Left;
	}
	if (DistancePos.y < -350.f)
	{
		MoveCam += float4::Up;
	}
	if (DistancePos.y > 350.f)
	{
		MoveCam += float4::Down;
	}

	if (MoveCam.ix() == 0 && MoveCam.iy() == 0)
	{
		return;
	}

	MoveCam.Normalize();
	SetCameraMove(MoveCam * fCamMoveSpeed * _DeltaTime);
}

void TestLevel::Loading()
{
	SoundLoad();
	ImageLoad();
	KeyLoad();

	{
		Map* Actor = CreateActor<Map>();
	}
	{
		ScreenSize = GameEngineWindow::GetScreenSize();

		vecAllPlayer.reserve(2);
		for (size_t i = 0; i < 2; i++)
		{
			int iRandxPos = 100;
			vecAllPlayer.push_back(CreateActor<Player>(WormsRenderOrder::Player));
			vecAllPlayer[i]->SetColImage("MapCity_Ground.bmp");
			float4 StartPos = float4{ 450,50 };
			StartPos.x += i * iRandxPos;
			vecAllPlayer[i]->SetPos(StartPos);
		}

		iPlayerNumber = 0;

		GlobalValue::gValue.SetPlayer(vecAllPlayer[iPlayerNumber]);

		GlobalValue::gValue.GetPlayer()->SetIsMyTurn(true);
		SetCameraPos(GlobalValue::gValue.GetPlayer()->GetPos() - ScreenSize.half());

	}
	vecAllPlayer[0]->SetName("0");

	vecAllPlayer[1]->SetName("1");

	CreateActor<WeaponBazooka>();
}

void TestLevel::Update(float _DeltaTime)
{
	//if (false == pCurPlayer->GetIsMyTurn())
	//{
	//	PlayerChange(_DeltaTime);
	//}

	PlayerChange(_DeltaTime);
	MoveCamForMouse(_DeltaTime);
	if (GameEngineInput::IsDown("DebugCollision"))
	{
		DebugRenderSwitch();
	}
}

void TestLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//CreateActor<WeaponShotgun>();
	//CreateActor<WeaponGrenade>();
}