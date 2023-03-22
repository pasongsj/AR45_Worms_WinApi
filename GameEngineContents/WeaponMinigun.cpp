#include "WeaponMinigun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
//#include <GameEnginePlatform/GameEngineInput.h>

#include "MapModifier.h"
#include "Player.h"

WeaponMinigun::WeaponMinigun()
{
}

WeaponMinigun::~WeaponMinigun()
{
}

void WeaponMinigun::Start()
{
	// 샷건 기본 설정
	WeaponName = "Minigun";
	//EffectGravity = false;
	//isBlocked = true;
	MoveSpeed = 600.0f;
	//float Dmg = 0.0f;
	Dir = float4::Right;


	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함



	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
	AimingLine->SetImage("TempBomb.bmp");
	AimingLine->SetScale({ 20,20 });


	AllWeapons[WeaponName] = this;
}

void WeaponMinigun::Update(float _DeltaTime)
{
	while (BulletCount > MinigunCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponMinigunInit();
	}

	if (nullptr == CurPlayer || false == CurPlayer->GetIsMyTurn()) // 플레이어 재설정
	{
		SetCurPlayer();
		ResetWeapon();
	}

	CheckFiring(); // 방향체크, 발사 체크
	Firing(_DeltaTime); // 총알이 지정된 속도로 날아가고 폭발하게 함

}

void WeaponMinigun::CheckFiring()
{
	if (PressShoot()) // 발사체크
	{
		for (int i = 0; i < BulletCount; i++)
		{
			if (isShooted[i] == false)
			{
				isShooted[i] = true;
				MinigunDir[i] = Dir; // 발사시 방향설정
				break;
			}
		}
	}
	else // 방향체크
	{
		float4 PlayerPos = CurPlayer->GetPos();
		SetPos(PlayerPos);
		Dir = GetShootDir(); // 방향 조정
		AimingLine->SetPosition(Dir * 100); // 조준선 이동
	}

}


void WeaponMinigun::Firing(float _DeltaTime)
{
	//bool isRemainBullet = false;
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == isShooted[i] && true == MinigunCollision[i]->IsUpdate())
		{
			//isRemainBullet = true;
			WeaponMove(MinigunCollision[i], _DeltaTime, MinigunDir[i]);

			if (true == WeaponMinigun::CheckCollision(MinigunCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
			{
				MapModifier::MainModifier->CreateHole(GetPos() + MinigunCollision[i]->GetPosition(), 50);
				MinigunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
			}
		}
	}

}


void WeaponMinigun::WeaponMove(GameEngineCollision* _Col, float _DeltaTime, float4 _Dir)
{
	if (false == _Col->IsUpdate())
	{
		return;
	}

	else // 중력의 영향을 받지 않음.
	{
		_Col->SetMove(_Dir * _DeltaTime * MoveSpeed);
	}
}

void WeaponMinigun::Render(float _DeltaTime)
{
}

void WeaponMinigun::WeaponMinigunInit()
{
	// Minigun은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 25,25 });

	MinigunCollision.push_back(Collision);
	isShooted.push_back(false);
	MinigunDir.push_back(float4::Right);

}

void WeaponMinigun::ResetWeapon()
{
	for (int i = 0; i < BulletCount; i++)
	{
		isShooted[i] = false;
		MinigunDir[i] = float4::Right;
		MinigunCollision[i]->SetPosition(float4::Zero);
		MinigunCollision[i]->On();
	}
}