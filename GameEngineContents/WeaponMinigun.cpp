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
	MoveSpeed = 1200.0f;
	Dir = float4::Right;
	//float Dmg = 0.0f;
	BombScale = 30;//??

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함
	AllWeapons[WeaponName] = this;
	WeaponNumber = static_cast<int>(WeaponNum::Minigun);



	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
	AimingLine->SetImage("TempBomb.bmp");
	AimingLine->SetScale({ 20,20 });


}

void WeaponMinigun::Update(float _DeltaTime)
{
	while (BulletCount > MinigunCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponMinigunInit();
	}

	SetCurPlayer();
	//if (nullptr == CurPlayer || false == CurPlayer->GetIsMyTurn()) // 플레이어 재설정 - 수정 필요함
	//{
	//	SetCurPlayer();
	//	ResetWeapon();
	//}

	CheckFiring(); // 방향체크, 발사 체크
	Firing(_DeltaTime); // 총알이 지정된 속도로 날아가고 폭발하게 함
	if (true == IsDone())
	{
		isWeaponDone = true;
	}

}

bool WeaponMinigun::IsDone()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == MinigunCollision[i]->IsUpdate())
		{
			return false;
		}

	}
	return true;
}

void WeaponMinigun::CheckFiring()
{
	if (false == isFire)
	{
		if (PressShoot()) // 발사체크
		{
			isFire = true;
		}
		float4 PlayerPos = CurPlayer->GetPos();
		SetPos(PlayerPos);
		Dir = GetShootDir(); // 방향 조정
		AimingLine->SetPosition(Dir * 100); // 조준선 이동

	}

}


void WeaponMinigun::Firing(float _DeltaTime)
{
	if (true == isFire)
	{
		DelayTime -= _DeltaTime;
		if (DelayTime < 0)
		{
			DelayTime = 0.1f;
			for (int i = 0; i < BulletCount; i++)
			{
				if (isShooted[i] == false)
				{
					isShooted[i] = true;
					break;
				}

			}
		}

		for (int i = 0; i < BulletCount; i++)
		{
			if (true == isShooted[i] && true == MinigunCollision[i]->IsUpdate())
			{
				MinigunCollision[i]->SetMove(Dir * _DeltaTime * MoveSpeed);
				if (true == CheckCollision(MinigunCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
				{

					GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();										  // 1. Bomb 콜리전 가져오기
					BombCollision->SetPosition(GetPos() + MinigunCollision[i]->GetPosition());													  // 2. Bomb 콜리전 이동

					AttackPlayer(BombCollision);																								  // 3. Bomb콜리전 Player Check

					MapModifier::MainModifier->CreateHole(GetPos() + MinigunCollision[i]->GetPosition(), BombScale);							  // 4. 구멍 만들기
					MinigunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
				}
			}
		}
	}

}


void WeaponMinigun::WeaponMinigunInit()
{
	// Minigun은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 25,25 });

	MinigunCollision.push_back(Collision);
	isShooted.push_back(false);
	DelayTime = 0.05f;
}

void WeaponMinigun::ResetWeapon()
{
	isFire = false;
	DelayTime = 0.05f;
	for (int i = 0; i < BulletCount; i++)
	{
		isShooted[i] = false;
		MinigunCollision[i]->SetPosition(float4::Zero);
		MinigunCollision[i]->On();
	}
}