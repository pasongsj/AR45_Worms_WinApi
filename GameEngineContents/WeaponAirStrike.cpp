#include "WeaponAirStrike.h"
#include "ContentsEnums.h"
#include "Player.h"

#include <cmath>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

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

}

void WeaponAirStrike::Render(float _DeltaTime)
{
	Attack(_DeltaTime);
}

void WeaponAirStrike::WeaponAirStrikeInit()
{
	SetCurPlayer();
	Airplane = CreateRender("Airplane.bmp", WormsRenderOrder::Weapon);
	Airplane->SetScaleToImage();
	Airplane->Off();

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

	}


}

void WeaponAirStrike::SetAirPlanePos()
{
	AirPlaneStartPos.x = GetLevel()->GetMousePosToCamera().x;
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

void WeaponAirStrike::MissileMove(float _DeltaTime)
{

	for (int i = 0; i < MissileList.size(); i++)
	{
	}
}

void WeaponAirStrike::SetMissiles()
{
	float4 AirPlanePos = Airplane->GetPosition();
	float MissileXpos = 0;

	for (int i = 0; i < 5; i++)
	{
		MissileList.push_back(CreateRender("AirMissile.bmp", WormsRenderOrder::Weapon));
		MissileList[i]->SetScaleToImage();
		MissileList[i]->SetPosition(AirPlanePos - float4{ MissileXpos, -50 });

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