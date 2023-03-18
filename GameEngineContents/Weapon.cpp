#include "Weapon.h"
#include "Player.h"
#include "ContentsEnums.h"

#include <time.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>


std::map<std::string, Weapon*> Weapon::AllWeapons;

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}


float4 Weapon::GetShootDir()
{
	float4 ReturnDir = float4::Zero;
	//if (GameEngineInput::IsKey("WeaponUp") == false)
	//{
	//	// 무기 방향
	//	GameEngineInput::CreateKey("WeaponUp", 'W');
	//	GameEngineInput::CreateKey("WeaponDown", 'S');
	//	GameEngineInput::CreateKey("WeaponRight", 'D');
	//	GameEngineInput::CreateKey("WeaponLeft", 'A');

	//}

	if (GameEngineInput::IsPress("WeaponUp") && -0.96 < Height) // 윈도우 좌표계 위로
	{
		Height -= 0.03f;
	}
	else if (GameEngineInput::IsPress("WeaponDown") && 0.96 > Height)
	{
		Height += 0.03f;
	}

	// 지속적으로 마지막 방향 업데이트
	if (GameEngineInput::IsDown("MoveRight"))
	{
	
		if (false == isRightDir)
		{
			Height = 0.0f;
		}
		isRightDir = true;
	}
	else if (GameEngineInput::IsDown("MoveLeft"))
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
	/*if (GameEngineInput::IsKey("Shoot") == false)
	{
		GameEngineInput::CreateKey("Shoot", VK_SPACE);
	}*/

	if (GameEngineInput::IsDown("Shoot")) // 상하
	{
		return true;
	}

	return false;
}

bool Weapon::isEndCharging() //스페이스를 눌러서 차징을 하다가 끝나는 순간 공격이 시작되므로 끝나는 시점에 대한 검사가 필요
{
	if (GameEngineInput::IsUp("Shoot"))
	{
		return true;
	}

	if (/*스페이스바를 놓지는 않았는데, 제한시간이 끝났을 때*/ true)
	{
		//return true;
	}

	return false;
}

void Weapon::TimeCounting()
{
	CurTime = clock();
	TimeCount += (CurTime - PrevTime) / 1000;
	PrevTime = CurTime;
}


void Weapon::SetCurPlayer()
{
	std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

	for (int i = 0; i < PlayerList.size(); i++)
	{
		if (true == dynamic_cast<Player*>(PlayerList[i])->GetIsMyTurn())
		{
			CurPlayer = dynamic_cast<Player*>(PlayerList[i]);
			break;
		}
	}
}

bool Weapon::CheckCollision(GameEngineCollision* _Col)
{
	if (nullptr == _Col)
	{
		_Col = WeaponCollision;
	}
	std::vector<GameEngineCollision*> CollisionList;

	if (_Col != nullptr && true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
	{
		for (int i = 0; i < CollisionList.size(); i++)
		{
			Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());

			if (ColPlayer->GetIsMyTurn() == false)
			{
				return true;
			}
		}
	}
	else if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos(), RGB(255, 0, 255))) //맵에 닿으면 사라짐
	{
		return true;
	}
	return false;

}