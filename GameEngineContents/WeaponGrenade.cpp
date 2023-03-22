#include "WeaponGrenade.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Player.h"
#include "MapModifier.h"


WeaponGrenade::WeaponGrenade() 
{
}

WeaponGrenade::~WeaponGrenade() 
{
}

void WeaponGrenade::Start()
{
	// 수류탄 기본 설정 -- 상수값 조정 필요
	MoveSpeed = 700.0f; // 임시값
	Gravity = 1.0f;// 임시값
	//Dmg = 0.0f;
	Timer = 2.0f;// 임시값
	Dir = float4::Right;
	BombScale = 120;
	WeaponName = "Grenade";

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 이미지 이름 변수or 함수화 필요

	AllWeapons[WeaponName] = this;
	WeaponNumber = static_cast<int>(WeaponNum::Grenade);

}

void WeaponGrenade::Update(float _DeltaTime)
{
	if (nullptr == WeaponRender) // 무기 랜더가 존재하지 않는 경우
	{
		WeaponGrenadeInit();
	}
	SetCurPlayer();
	//if (nullptr == CurPlayer || false == CurPlayer->GetIsMyTurn()) // 플레이어 재설정
	//{
	//	SetCurPlayer();
	//	ResetWeapon();
	//}

	Firing(_DeltaTime);
	// 폭발 체크
	if (Timer < 0 && isExplosion == false)
	{
		GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();
		BombCollision->SetPosition(GetPos() + WeaponCollision->GetPosition());

		AttackPlayer(BombCollision);

		MapModifier::MainModifier->CreateHole(GetPos() + WeaponCollision->GetPosition(), 120);
		isExplosion = true;
		WeaponRender->Off();
		WeaponCollision->Off();
	}

}

void WeaponGrenade::Firing(float _DeltaTime)
{
	if (false == isFire) // 발사하기 전
	{
		float4 PlayerPos = CurPlayer->GetPos();
		Dir = GetShootDir() * Charge;
		SetPos(PlayerPos);
		if (true == PressShoot())
		{
			SetCharge();// 차징포인트 계산
		}
		if (isEndCharging() == true) // 발사체크
		{
			isFire = true;
		}

	}

	else // 발사 중
	{
		Timer -= _DeltaTime;
		if (false == isExplosion)// && true == isFire)
		{
			Dir.y = Dir.y + Gravity * _DeltaTime; // dt동안 중력의 영향

			WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);
			WeaponCollision->SetMove(Dir * MoveSpeed * _DeltaTime);


			float4 CheckedCol = CheckCollisionSide(WeaponCollision);
			if (Dir.x * CheckedCol.x > 0) // 방향이 달라
			{
				WeaponRender->SetMove(-Dir * MoveSpeed * _DeltaTime);
				WeaponCollision->SetMove(-Dir * MoveSpeed * _DeltaTime);

				Dir.x = -Dir.x * 0.5f;										  //  x값은 마찰고려값
				Dir.y = -Dir.y * 0.25f;
			}

			else if (Dir.x * CheckedCol.x < 0 || CheckedCol.x == 0 && CheckedCol.y > 0)// 방향이 같아 or 좌우 이동x
			{
				WeaponRender->SetMove({ 0, -Dir.y * MoveSpeed * _DeltaTime });
				WeaponCollision->SetMove({ 0, -Dir.y * MoveSpeed * _DeltaTime });
				Dir.x = Dir.x * 0.5f;
				Dir.y = -Dir.y * 0.25f;
			}
		}
	}
}

void WeaponGrenade::SetCharge() // Charging으로 함수이름 통일
{
	if (Charge > GetChargeTime())
	{
		return;
	}
	if (GetChargeTime() > 2.0f) // 최대 2배 차징
	{
		Charge = 2.0f;
	}
	else if (GetChargeTime() < 1.0f)
	{
		Charge = 1.0f;
	}
	else {
		Charge = GetChargeTime();
	}
}

void WeaponGrenade::ResetWeapon()
{

	isFire = false;
	isExplosion = false;
	Timer = 2.0f;
	if (nullptr == WeaponRender)
	{
		return;
	}
	WeaponRender->On();
	WeaponRender->SetPosition(float4::Zero);

	WeaponCollision->On();
	WeaponCollision->SetPosition(float4::Zero);

}

void WeaponGrenade::WeaponGrenadeInit()
{
	WeaponRender = CreateRender(WormsRenderOrder::Weapon);		//렌더
	WeaponRender->SetImage("Grenade.bmp");
	WeaponRender->SetScale({ 20,40 }); // 임시 설정 값 

	WeaponCollision = CreateCollision(WormsCollisionOrder::Weapon);	//콜리전
	WeaponCollision->SetScale(WeaponRender->GetScale());
	isFire = false;
	ResetWeapon();
}
