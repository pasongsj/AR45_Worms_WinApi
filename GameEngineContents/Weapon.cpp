#include "Weapon.h"

#include <GameEnginePlatform/GameEngineInput.h>

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}


float4 Weapon::GetShootDir()
{
	float4 ReturnDir = float4::Zero;
	if (GameEngineInput::IsKey("WeaponUp") == false)
	{
		// 무기 방향
		GameEngineInput::CreateKey("WeaponUp", 'W');
		GameEngineInput::CreateKey("WeaponDown", 'S');
		GameEngineInput::CreateKey("WeaponRight", 'D');
		GameEngineInput::CreateKey("WeaponLeft", 'A');

	}

	if (GameEngineInput::IsPress("WeaponUp") && -1 < Height) // 윈도우 좌표계 위로
	{
		Height -= 0.05f;
	}
	else if (GameEngineInput::IsPress("WeaponDown") && 1 > Height)
	{
		Height += 0.05f;
	}

	// 지속적으로 마지막 방향 업데이트
	if (GameEngineInput::IsPress("WeaponRight"))
	{
	
		if (false == isRightDir)
		{
			Height = 0.0f;
		}
		isRightDir = true;
	}
	else if (GameEngineInput::IsPress("WeaponLeft"))
	{
		if (true == isRightDir)
		{
			Height = 0.0f;
		}
		isRightDir = false;
	}

	ReturnDir.y = Height;
	ReturnDir.x = static_cast<float>(isRightDir ? 1 : -1);

	return ReturnDir.NormalizeReturn();

}


bool Weapon::PressShoot()
{
	if (GameEngineInput::IsKey("Shoot") == false)
	{
		GameEngineInput::CreateKey("Shoot", VK_SPACE);
	}

	if (GameEngineInput::IsPress("Shoot")) // 상하
	{
		return true;
	}

	return false;
}