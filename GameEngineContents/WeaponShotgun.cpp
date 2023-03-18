#include "WeaponShotgun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "MapModifier.h"

WeaponShotgun::WeaponShotgun()
{
}

WeaponShotgun::~WeaponShotgun()
{
}

void WeaponShotgun::Start()
{
	// 샷건 기본 설정
	WeaponName = "Shotgun";
	EffectGravity = false;
	isAnimation = false;
	isBlocked = true;
	isTarget = false;

	MoveSpeed = 600.0f;
	//float Dmg = 0.0f;

	Dir = float4{ 1,0 }.NormalizeReturn();
	//float4 PlayerPos = float4::Zero;
	BombScale = float4{ 100,100 };
	//float4 Scale = float4::Zero;	

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");
	//WeaponShotgunInit();


	// 폭발 맵깍기
	Bomb = GetLevel()->CreateActor<MapModifier>();
	Bomb->SetRadius(BombScale.hix());

	// - 조준선 
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
	AimingLine->SetImage("TempBomb.bmp");
	AimingLine->SetScale({ 20,20 });
	AllWeapons[WeaponName] = this;
}

void WeaponShotgun::Update(float _DeltaTime)
{

	if (0 == ShotGunCollision.size()) // 무기가 생성되지 않았을 경우 생성되도록 함.
	{
		for (int i = 0;i < BulletCount;i++)
		{
			WeaponShotgunInit();
		}
	}
	

	if (PressShoot())
	{
		for (int i = 0;i < BulletCount;i++)
		{
			if (isShooted[i] == false)
			{
				isShooted[i] = true;
				ShotGunDir[i] = Dir; // 발사시 방향설정
				break;
			}
		}
	}
	else
	{
		float4 PlayerPos = (GetLevel()->GetActors(WormsRenderOrder::Player))[0]->GetPos();// 임시 index0 PlayerPos
		SetPos(PlayerPos /*- float4{0,30}*/);
		Dir = GetShootDir(); // 방향 조정
		// 조준선 이동
		AimingLine->SetPosition(Dir*100 /*+ float4{ 0,30 }*/);

	}

	for (int i = 0;i < BulletCount;i++)
	{
		if (true == isShooted[i] && true == ShotGunCollision[i]->IsUpdate())
		{
			WeaponMove(ShotGunCollision[i], _DeltaTime, ShotGunDir[i]);

			if (true == WeaponShotgun::CheckCollision(ShotGunCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
			{
				MakeBomb(GetPos()+ShotGunCollision[i]->GetPosition()); // 폭발 범위 표시

				ShotGunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
			}
		}
	}


}

void WeaponShotgun::MakeBomb(float4 _Pos) // 임시 - 폭탄 터지는 위치 표기
{
	Bomb->SetPos(_Pos);
	Bomb->CreateHole();
}


void WeaponShotgun::WeaponMove(GameEngineCollision* _Col, float _DeltaTime,float4 _Dir)
{
	if (false == _Col->IsUpdate())
	{
		return;
	}

	if (true == EffectGravity)
	{

	}
	else // 중력의 영향을 받지 않음.
	{
		_Col->SetMove(_Dir * _DeltaTime * MoveSpeed);
	}
}

void WeaponShotgun::Render(float _DeltaTime)
{

}

void WeaponShotgun::WeaponShotgunInit()
{
	// ShotGun은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 25,25 });

	ShotGunCollision.push_back(Collision);
	isShooted.push_back(false);
	ShotGunDir.push_back(float4::Right);

}

void WeaponShotgun::ResetWeapon(float _DeltaTime)
{

}