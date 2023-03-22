#include "WeaponAirStrike.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"

#include <cmath>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

WeaponAirStrike::WeaponAirStrike()
{
}

WeaponAirStrike::~WeaponAirStrike()
{
}

void WeaponAirStrike::Start()
{
	WeaponAirStrikeInit();
}

void WeaponAirStrike::Update(float _DeltaTime)
{
	Attack(_DeltaTime);
	CameraUpdate();
}

void WeaponAirStrike::Render(float _DeltaTime)
{

}

void WeaponAirStrike::WeaponAirStrikeInit()
{
	SetCurPlayer();
	Airplane = CreateRender("Airplane.bmp", WormsRenderOrder::Weapon);
	Airplane->SetScaleToImage();
	Airplane->Off();

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

	ScreenSize = GameEngineWindow::GetScreenSize();

	MissileList.reserve(5);
}

void WeaponAirStrike::Attack(float _DeltaTime)
{
	if (GameEngineInput::IsKey("LeftMouseClick") == false)
	{
		GameEngineInput::CreateKey("LeftMouseClick", VK_LBUTTON);
	}

	if (GameEngineInput::IsDown("LeftMouseClick") == true)
	{
		SetAirPlanePos();
	}

	AirPlaneMove(_DeltaTime);

	if (isHideAirPlane == true && MissileList.size() == 0)
	{
		SetMissiles();
	}

	else if (isHideAirPlane == true && MissileList.size() > 0)
	{
		Firing(_DeltaTime);
	}

	Explosion();
}

void WeaponAirStrike::SetAirPlanePos()
{
	TargetPos = GetLevel()->GetMousePosToCamera();

	AirPlaneStartPos.x = TargetPos.x;
	AirPlaneStartPos.y = -200.0f;

	if (AirPlaneStartPos.x > CurPlayer->GetPos().x)
	{
		isMoveRight = true;
	}
	else
	{
		isMoveRight = false;
	}

	if (isMoveRight == true)
	{
		AirPlaneStartPos.x -= 300.0f;
	}
	else
	{
		AirPlaneStartPos.x += 300.0f;
	}

	Airplane->SetPosition(AirPlaneStartPos);
	Airplane->On();
}

void WeaponAirStrike::AirPlaneMove(float _DeltaTime)
{
	if (Airplane->IsUpdate() == true)
	{
		if (isMoveRight == true)
		{
			Airplane->SetMove(float4::Right * 200.0f * _DeltaTime);
		}

		else
		{
			Airplane->SetMove(float4::Left * 200.0f * _DeltaTime);
		}
	}

	float MovePos = Airplane->GetPosition().x - AirPlaneStartPos.x;
	
	if (abs(MovePos) > 200.0f)
	{
		Airplane->Off();
		isHideAirPlane = true;
	}
}

void WeaponAirStrike::Firing(float _DeltaTime)
{
	Gravity += 0.01f * _DeltaTime;
	
	if(Dir == float4{0,0})
	{
		Dir = TargetPos - MiddleMissileStartPos;
		Dir.Normalize();


		for (int i = 0; i < MissileList.size(); i++)
		{
			MissileList[i]->On();
		}
	}

	Dir += float4{ 0, Gravity };

	for (int i = 0; i < MissileList.size(); i++)
	{
		MissileList[i]->SetMove(Dir * 400.0f * _DeltaTime + float4{0, Gravity * _DeltaTime});
		MissileCollisionList[i]->SetMove(Dir * 400.0f * _DeltaTime + float4{ 0, Gravity * _DeltaTime });
	}

	CurPos = MissileList[2]->GetPosition();

	for (int i = 0; i < MissileList.size(); i++)
	{
		MissileList[i]->SetAngle(-Dir.GetAnagleDeg());
	}

}

void WeaponAirStrike::SetMissiles()
{
	float4 AirPlanePos = Airplane->GetPosition();
	float MissileXpos = 0;

	for (int i = 0; i < 5; i++)
	{
		MissileList.push_back(CreateRender("AirMissile.bmp", WormsRenderOrder::Weapon));
		MissileList[i]->SetRotFilter("AirMissileRot.bmp");
		MissileList[i]->SetScaleToImage();
		MissileList[i]->SetPosition(AirPlanePos - float4{ MissileXpos, -50 });
		MissileList[i]->Off();

		MissileCollisionList.push_back(CreateCollision(WormsCollisionOrder::Weapon));
		MissileCollisionList[i]->SetScale({ 30, 30 });
		MissileCollisionList[i]->SetPosition(MissileList[i]->GetPosition());

		if (isMoveRight == true)
		{
			MissileXpos += 50.0f;
		}
		else
		{
			MissileXpos -= 50.0f;
		}
	}

	MiddleMissileStartPos = MissileList[2]->GetPosition();
}

void WeaponAirStrike::Explosion()
{
	for (int i = 0; i < MissileCollisionList.size(); i++)
	{
		if (MissileCollisionList[i]->GetPosition().y > 0 && MissileCollisionList[i]->IsUpdate() == true && CheckCollision(MissileCollisionList[i]) == true)
		{
			MapModifier::MainModifier->CreateHole(MissileCollisionList[i]->GetActorPlusPos(), 50);
			MissileCollisionList[i]->Off();
			MissileList[i]->Off();
		}
	}
}

void WeaponAirStrike::CameraUpdate()
{
	if (Airplane->IsUpdate() == true)
	{
		GetLevel()->SetCameraPos(Airplane->GetActorPlusPos() - ScreenSize.half());
	}
	else if (MissileList.size() >= 3 && MissileList[2]->IsUpdate() == true)
	{
		GetLevel()->SetCameraPos(MissileList[2]->GetActorPlusPos() - ScreenSize.half());
	}
}