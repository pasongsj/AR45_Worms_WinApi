#include "WeaponShotgun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
//#include <GameEnginePlatform/GameEngineInput.h>

#include "MapModifier.h"
#include "Player.h"

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
	isBlocked = true;
	MoveSpeed = 600.0f;
	//float Dmg = 0.0f;
	Dir = float4::Right;
	BombScale = float4{ 100,100 };
	//float4 Scale = float4::Zero;	

	
	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함



	// 폭발 맵깍기 - 수정필요 : WeaponClass에서 Bomb를 관리해야 여러 액터를 만들지 않아도 됨
	//Explosion = GetLevel()->CreateActor<MapModifier>();
	//Explosion->SetRadius(BombScale.hix());

	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
	AimingLine->SetImage("TempBomb.bmp");
	AimingLine->SetScale({ 20,20 });


	AllWeapons[WeaponName] = this;
}

void WeaponShotgun::Update(float _DeltaTime)
{
	while (BulletCount > ShotGunCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponShotgunInit();
	}
	


	CheckFiring(); // 방향체크, 발사 체크
	Firing(_DeltaTime); // 총알이 지정된 속도로 날아가고 폭발하게 함

}

void WeaponShotgun::CheckFiring()
{
	if (PressShoot()) // 발사체크
	{
		for (int i = 0; i < BulletCount; i++)
		{
			if (isShooted[i] == false)
			{
				isShooted[i] = true;
				ShotGunDir[i] = Dir; // 발사시 방향설정
				break;
			}
		}
	}
	else // 방향체크
	{
		if (nullptr == CurPlayer || false == CurPlayer->GetIsMyTurn())
		{
			FindCurPlayer();
		}
		PlayerPos = CurPlayer->GetPos();
		SetPos(PlayerPos);
		Dir = GetShootDir(); // 방향 조정
		AimingLine->SetPosition(Dir * 100); // 조준선 이동
	}

}

void WeaponShotgun::FindCurPlayer()
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
		MsgAssert("현재플레이어를 찾지 못했습니다.");
	}
}


void WeaponShotgun::Firing(float _DeltaTime)
{
	//bool isRemainBullet = false;
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == isShooted[i] && true == ShotGunCollision[i]->IsUpdate())
		{
			//isRemainBullet = true;
			WeaponMove(ShotGunCollision[i], _DeltaTime, ShotGunDir[i]);

			if (true == WeaponShotgun::CheckCollision(ShotGunCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
			{
				MapModifier::MainModifier->CreateHole(GetPos() + ShotGunCollision[i]->GetPosition(), 50);
				//Explosion->SetPos(GetPos() + ShotGunCollision[i]->GetPosition()); // 폭발 범위 마젠타 색칠하기
				//Explosion->CreateHole();
				ShotGunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
			}
		}
	}

	// 수정 필요 : 터지는 애니메이션까지 Weapon이 On되어있어야 하는지 논의 필요
	//if (false == isRemainBullet) // 남아있는 총탄이 없다면 WeaponOff
	//{
	//	this->Off();
	//	return;
	//}

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

void WeaponShotgun::ResetWeapon()
{
	for (int i = 0; i < BulletCount; i++)
	{
		isShooted[i] = false;
		ShotGunDir[i] = float4::Right;
		ShotGunCollision[i]->SetPosition(float4::Zero);
		ShotGunCollision[i]->On();
	}
}