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
	MoveSpeed = 2500;
	//Dir = float4::Right;
    BombScale = 22;

    MaxDmg = 50;
    MinDmg = 12;
    MaxKnockBackPower = 97;
    MinKnockBackPower = 22;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함

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
        SetCurPlayer();// 플레이어 전환버튼 때문에 추가
	}

    if (WeaponDoneTime < GetLiveTime())
    {
        GetLevel()->SetCameraPos(CurPlayer->GetPos() - GameEngineWindow::GetScreenSize().half());
        WeaponDoneTime = 0.0f;
    }
    if (false == isFire) //발사가 안되었다면
    {
        Aiming(_DeltaTime);
    }
    else
    {
        if (false == isExplosion) // 발사되고 아직 터지기 전
        {
            Firing(_DeltaTime);
        }
        else // 발사하고 터진 후
        {
            if (true == IsDone()) // 총알 모두 사용하였는지 체크
            {
                isWeaponDone = true;
                GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half());
            }
        }
    }


}
void  WeaponShotgun::Aiming(float _DeltaTime)
{

    if (CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON) // 현재 플레이어가 무기 State
    {
        // 위치
        float4 PlayerPos = CurPlayer->GetPos();
        Dir = GetShootDir();
        SetPos(PlayerPos);

        // 조준선
        SetAimFrameIndex();
        AimingLine->On();

        float Ratio = 6 * _DeltaTime;
        AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);

        CurPlayer->ChangePlayerAnimation("ShotgunAim", static_cast<int>(AimIndex));
        AimingLine->SetPosition(Dir * 150 + float4{ 0, -10 }); // 조준선 이동

        if (Dir.x > 0)
        {
            AimingLine->SetAngle(Dir.GetAnagleDeg());
        }
        else
        {
            AimingLine->SetAngle(-Dir.GetAnagleDeg());
        }

        CheckFiring(); // 방향체크, 발사 체크
    }
    else
    {
        AimingLine->Off();
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

void WeaponShotgun::CheckFiring()
{
	if (true == GameEngineInput::IsDown("Shoot")) // 발사체크
	{
		for (int i = 0; i < BulletCount; i++)
		{
			if (isShooted[i] == false)
			{
				isShooted[i] = true;
				ShotGunDir[i] = Dir; // 발사시 방향설정
                //isIsFireAnimationDone = true;
                AimingLine->Off();
				isFire = true;
                isExplosion = false;
                LoadDelay = 0.5f;
                break;
			}
		}
	}

}


void WeaponShotgun::Firing(float _DeltaTime)
{
    LoadDelay -= _DeltaTime;
    if (LoadDelay > 0) // 장전 딜레이(장전소리)
    {
        return;
    }
    CurPlayer->ChangePlayerAnimation("HandgunFire", static_cast<int>(AimIndex));

	for (int i = 0; i < BulletCount; i++)
	{
		if (true == isShooted[i] && true == ShotGunCollision[i]->IsUpdate()) // 현재 On인 총알
		{

            float4 MoveVec = ShotGunDir[i] * _DeltaTime * MoveSpeed;
            ShotGunCollision[i]->SetMove(MoveVec);
			if (0 < CheckCollisionSide(ShotGunCollision[i]).Size()) // 콜리전 체크(플레이어, 맵)
			{
                ShotGunCollision[i]->SetMove(-MoveVec * 0.1f);
                // 연기이펙트
                SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
                Smoke->SetPos(ShotGunCollision[i]->GetActorPlusPos());
                Smoke->CreateSmokeSpark(6, 2, BombScale);

                // Player 와 콜리전 체크를 위함
				GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();				// 1. Bomb 콜리전 가져오기
				BombCollision->SetPosition(ShotGunCollision[i]->GetActorPlusPos());							        // 2. Bomb 콜리전 이동

                // shotgun은 다른 총들과 다르게 최대 데미지가 크기때문에 BombScale을 재 설정한다.
                float4 Dis = BombCollision->GetActorPlusPos() - GetPos();
                float Dis_Ratio = (Dis.Size() / 500) > 1 ? 1 : Dis.Size() / 500;
                BombScale = static_cast<int>(MaxKnockBackPower * (1 - Dis_Ratio) + MinKnockBackPower * Dis_Ratio);
                BombCollision->SetScale(float4{ static_cast<float>(BombScale) });  // 폭탄크기 재설정

                AttackPlayerGun(BombCollision, 500);																// 3. Bomb콜리전 Player Check

				MapModifier::MainModifier->CreateHole(GetPos() + ShotGunCollision[i]->GetPosition(), BombScale);	// 4. 구멍 만들기

				ShotGunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
                isExplosion = true;

                if (i+1 < BulletCount)
                {
                    isFire = false;

                }
                WeaponDoneTime = GetLiveTime() + 1.0f;
                CurPlayer->ChangePlayerAnimation("Idle");
			}
            // 카메라 이동
            float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), ShotGunCollision[i]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 50);
            GetLevel()->SetCameraPos(CamPos);
		}
	}

}


void WeaponShotgun::WeaponShotgunInit()
{
	// ShotGun은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 10,10 });
    Collision->SetPosition({ 0,-10 });

	ShotGunCollision.push_back(Collision);
	isShooted.push_back(false);
	ShotGunDir.push_back(float4::Right);

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
    if (WeaponDoneTime > GetLiveTime())
    {
        return false;
    }
	return true;
}