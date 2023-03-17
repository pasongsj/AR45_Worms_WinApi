#include "WeaponShotgun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

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
	//float Gravity = 0.0f;
	//float Timer = 0.0f;
	//float WindPower = 0.0f;
	//float Dmg = 0.0f;
	//float Charge = 0.0f;

	Dir = float4{ 1,0 }.NormalizeReturn();
	//float4 PlayerPos = float4::Zero;
	BombScale = float4{ 100,100 };
	//float4 Scale = float4::Zero;	

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");
	//WeaponShotgunInit();
	//SetPos({50, 400});

	AimingLine = CreateRender(WormsRenderOrder::Weapon);
	AimingLine->SetImage("TempBomb.bmp");
	AimingLine->SetScale({ 10,10 });
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
	
	// 탄 사이의 딜레이
	if (DelayTime > 0)
	{
		DelayTime -= _DeltaTime;
	}

	if (PressShoot() && DelayTime <= 0)
	{
		for (int i = 0;i < BulletCount;i++)
		{
			if (isShooted[i] == false)
			{
				isShooted[i] = true;
				ShotGunDir[i] = Dir; // 발사시 방향설정
				DelayTime = 1.0f;
				break;
			}
		}
		int a = 0;
	}
	else
	{
		float4 PlayerPos = (GetLevel()->GetActors(WormsRenderOrder::Player))[0]->GetPos();// 임시 index0 PlayerPos
		SetPos(PlayerPos - float4{0,30});
		Dir = GetShootDir(); // 방향 조정
		AimingLine->SetPosition(Dir*50 + float4{ 0,30 });

	}

	for (int i = 0;i < BulletCount;i++)
	{
		if (true == isShooted[i] && true == ShotGunCollision[i]->IsUpdate())
		{
			WeaponMove(ShotGunCollision[i], _DeltaTime, ShotGunDir[i]);

			if (true == CheckCollision(ShotGunCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
			{
				MakeBomb(ShotGunCollision[i]->GetPosition()); // 폭발 범위 표시

				ShotGunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
			}
		}
	}


}

void WeaponShotgun::MakeBomb(float4 _Pos) // 임시 - 폭탄 터지는 위치 표기
{
	GameEngineRender* BombRender = CreateRender(WormsRenderOrder::Weapon);
	BombRender->SetImage("TempBomb.bmp"); // 임시 그림
	BombRender->SetPosition(_Pos);
	BombRender->SetScale(BombScale);

	/*GameEngineCollision* BombCollision = CreateCollision(WormsRenderOrder::Weapon);
	BombCollision->SetPosition(_Pos);
	BombCollision->SetScale(BombScale);*/
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
	GameEngineCollision* Collision = CreateCollision(WormsRenderOrder::Weapon);
	Collision->SetScale({ 25,25 });

	ShotGunCollision.push_back(Collision);
	isShooted.push_back(false);
	ShotGunDir.push_back(float4::Right);

}

bool WeaponShotgun::CheckCollision(GameEngineCollision* _Col)
{
	// 플레이어를 맞춘 경우
	if (nullptr != _Col && true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsRenderOrder::Player), .TargetColType = CollisionType::CT_Rect, .ThisColType = CollisionType::CT_CirCle }))
	{
		return true;
	}


	// 맵과 충돌하는 경우
	if (nullptr == MapCollision)
	{
		MsgAssert("콜리전 이미지가 설정되지 않았습니다.");
		return false;
	}
	//if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetPosition(), RGB(255, 0, 255))) // - 콜리전 맵 위치 수정 필요
	//{

	//	return true;
	//}

	//임시 타이머
	/*if (GetLiveTime() >= 5.0f)
	{
		return true;
	}*/

	// 스테이지 밖으로 나가는 경우 - 추가 필요

	return false;

}