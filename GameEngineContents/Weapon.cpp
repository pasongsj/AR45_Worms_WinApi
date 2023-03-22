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

	if (GameEngineInput::IsPress("WeaponUp") && -5.7 < Height) // 윈도우 좌표계 위로
	{
		Height -= 0.05f;
	}
	else if (GameEngineInput::IsPress("WeaponDown") && 5.7 > Height)
	{
		Height += 0.05f;
	}

	if (nullptr == CurPlayer)
	{
		MsgAssert("현재 턴인 플레이어가 없습니다.");
	}
	float4 PlayerDir = CurPlayer->GetPlayerDir();

	// 지속적으로 마지막 방향 업데이트
	
	if (float4::Left == PlayerDir)
	{
		if (isRightDir == true)
		{
			Height = 0.0f;
		}

		isRightDir = false;
	}
	else if (float4::Right == PlayerDir)
	{
		if (isRightDir == false)
		{
			Height = 0.0f;
		}

		isRightDir = true;
	}

	ReturnDir.y = Height;
	ReturnDir.x = static_cast<float>(isRightDir ? 1 : -1);

	return ReturnDir.NormalizeReturn();

}


bool Weapon::PressShoot()
{
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
	TimeCount_2 += (CurTime - PrevTime) / 1000;

	PrevTime = CurTime;
}


void Weapon::SetCurPlayer() // 곧 없어질 것
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
	if (nullptr == CurPlayer)
	{
		MsgAssert("현재 턴인 플레이어가 없습니다.");
	}
}

bool Weapon::CheckCollision(GameEngineCollision* _Col)
{
	if (nullptr == _Col)
	{
		MsgAssert("체크할 콜리전이 없습니다.");
	}

	// 플레이어 체크
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

	// 맵체크
	else if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos(), RGB(255, 0, 255))) //맵에 닿으면 사라짐
	{
		return true;
	}
	// 맵 밖으로 나갔는지 체크

	return false;
}

float Weapon::GetChargeTime()
{
	return GameEngineInput::GetPressTime("Shoot");
}

float4 Weapon::CheckCollisionSide(GameEngineCollision* _Col)
{
	float4 ReturnValue = float4::Zero;
	std::vector<GameEngineCollision*> CollisionList;

	if (true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
	{
		for (int i = 0; i < CollisionList.size(); i++)
		{
			Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());

			if (ColPlayer->GetIsMyTurn() == false)
			{
				float4 Range = (ColPlayer->GetPos() - GetPos());
				if (abs(Range.y) < abs(Range.x))
				{
					ReturnValue.y += 1;
				}
				else if (Range.x > 0)
				{
					ReturnValue.x += 1;
				}
				else
				{
					ReturnValue.x -= 1;
				}
				return ReturnValue;
			}
		}
	}

	// 30 30 20,40
	if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ 10,0 }, RGB(255, 0, 255)))
	{
		ReturnValue.x += 1;
	}
	if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ -10,0 }, RGB(255, 0, 255)))
	{
		ReturnValue.x -= 1;
	}
	if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ 0,2  }, RGB(255, 0, 255)))
	{
		ReturnValue.y += 1;
	}

	return ReturnValue;
}