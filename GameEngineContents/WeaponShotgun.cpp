#include "WeaponShotgun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "MapModifier.h"
#include "Player.h"
#include "SmokeSparkEffect.h"

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
	MoveSpeed = 1000.0f;
	//float Dmg = 0.0f;
	Dir = float4::Right;
	BombScale = 50;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함

	//AllWeapons[WeaponName] = this;
	WeaponNumber = static_cast<int>(WeaponNum::Shotgun);


	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
	AimingLine->SetScale({ 20,20 });

}

void WeaponShotgun::Update(float _DeltaTime)
{
	while (BulletCount > ShotGunCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponShotgunInit();
	}
    if (false == isFire)
    {
        SetCurPlayer();// 플레이어 전환버튼 때문에 추가
        SetAimFrameIndex();

        if (AimIndex != NextAimIndex && CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON && CurPlayer->GetCurWeapon()->GetWeaponNumber() == WeaponNumber)
        {
            float Ratio = 6 * _DeltaTime;
            AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);
            CurPlayer->ChangePlayerAnimation("ShotgunAim", static_cast<int>(AimIndex));
            AimingLine->On();
            AimingLine->SetPosition(Dir * 200); // 조준선 이동
            if (Dir.x > 0)
            {
                AimingLine->SetAngle(Dir.GetAnagleDeg());
            }
            else
            {
                AimingLine->SetAngle(-Dir.GetAnagleDeg());
            }
        }
        else
        {
            AimingLine->Off();
        }
        CheckFiring(); // 방향체크, 발사 체크
    }
	Firing(_DeltaTime); // 총알이 지정된 속도로 날아가고 폭발하게 함

	if (true == IsDone())
	{
		isWeaponDone = true;
        GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half()); //다음 턴 Player로 카메라 이동- 삭제필요
	}

}

void WeaponShotgun::SetAimFrameIndex()
{
    float Angle = Dir.GetAnagleDeg();


    int NewIndex = 0;
    if (Dir.x > 0 && Angle > 270)
    {
        Angle = Angle - 360;
    }

    else if (Dir.x < 0)
    {
        Angle = 180 - Angle;
    }

    NewIndex = Angle / 5 + 15;

    if (NewIndex < 0)
    {
        NewIndex = 0;
    }
    NextAimIndex = NewIndex;

}

bool WeaponShotgun::IsDone()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == ShotGunCollision[i]->IsUpdate())
		{
			return false;
		}

	}
	return true;
}

void WeaponShotgun::CheckFiring()
{
	if (true == GameEngineInput::IsDown("Shoot")) // 발사체크
	{
		for (int i = 0; i < BulletCount; i++)
		{
			if (isShooted[i] == false)
			{
                AimingLine->Off();
				isFire = true;
				isShooted[i] = true;
				ShotGunDir[i] = Dir; // 발사시 방향설정
                CurPlayer->ChangePlayerAnimation("HandgunFire", static_cast<int>(AimIndex));
                isIsFireAnimationDone = true;
                break;
			}
		}
	}
	else // 방향체크
	{
		float4 PlayerPos = CurPlayer->GetPos();
		SetPos(PlayerPos);
		Dir = GetShootDir(); // 방향 조정
	}

}


void WeaponShotgun::Firing(float _DeltaTime)
{
	//bool isRemainBullet = false;
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == isShooted[i] && true == ShotGunCollision[i]->IsUpdate())
		{
            if (isIsFireAnimationDone == false && i == BulletCount - 1 && isWeaponDone == false)
            {
                CurPlayer->ChangePlayerAnimation("Idle");
                isIsFireAnimationDone = true;
            }

            GetLevel()->SetCameraPos(ShotGunCollision[i]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());
			//isRemainBullet = true;
			WeaponMove(ShotGunCollision[i], _DeltaTime, ShotGunDir[i]);

			if (true == WeaponShotgun::CheckCollision(ShotGunCollision[i])) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
			{
                SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
                Smoke->SetPos(ShotGunCollision[i]->GetActorPlusPos());
                Smoke->CreateSmokeSpark(6, 2, BombScale);

				GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();				// 1. Bomb 콜리전 가져오기
				BombCollision->SetPosition(GetPos() + ShotGunCollision[i]->GetPosition());							// 2. Bomb 콜리전 이동

				AttackPlayer(BombCollision);																		// 3. Bomb콜리전 Player Check

				MapModifier::MainModifier->CreateHole(GetPos() + ShotGunCollision[i]->GetPosition(), BombScale);	// 4. 구멍 만들기

				ShotGunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
                if (i+1 < BulletCount)
                {
                    GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half());
                    isFire = false;
                }
			}
		}
	}

}


void WeaponShotgun::WeaponMove(GameEngineCollision* _Col, float _DeltaTime,float4 _Dir)
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