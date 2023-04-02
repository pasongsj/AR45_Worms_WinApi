#include "WeaponMinigun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapModifier.h"
#include "Player.h"
#include "SmokeSparkEffect.h"

WeaponMinigun::WeaponMinigun()
{
}

WeaponMinigun::~WeaponMinigun()
{
}

void WeaponMinigun::Start()
{
	// 미니건 기본 설정
	WeaponName = "Minigun";
	MoveSpeed = 3000;
	//Dir = float4::Right;
    BombScale = 22;

    MaxDmg = 10;
    MinDmg = 3;

    MaxKnockBackPower = 22;
    MinKnockBackPower = 22;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함
	//AllWeapons[WeaponName] = this;
	WeaponNumber = static_cast<int>(WeaponNum::Minigun);



	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
	AimingLine->SetScale({ 20,20 });


}

void WeaponMinigun::Update(float _DeltaTime)
{
	while (BulletCount > MinigunCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponMinigunInit();
        SetCurPlayer();// 플레이어 전환버튼 때문에 추가
	}

    if (false == isFire) //발사가 안되었다면
    {
        Aiming(_DeltaTime);
    }
    else
    {
        Firing(_DeltaTime); // 총알이 지정된 속도로 날아가고 폭발하게 함
        if (true == isExplosion)
        {
            // 모든 총알발사되어 터졌는지 체크
            if (true == IsDone())
            {
                if (WaitingTime < 0)
                {
                    isWeaponDone = true;
                    GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half()); //다음 턴 Player로 카메라 이동- 삭제필요
                    return;
                }
                WaitingTime -= _DeltaTime;
            }
        }

    }

}


void WeaponMinigun::Aiming(float _DeltaTime)
{
    if (CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON) // 현재 플레이어가 무기 State
    {
        // 위치
        float4 PlayerPos = CurPlayer->GetPos() + float4{ 0,-15 };
        Dir = GetShootDir();
        SetPos(PlayerPos);

        // 조준선
        SetAimFrameIndex();
        AimingLine->On();

        float Ratio = 6 * _DeltaTime;
        AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);

        CurPlayer->ChangePlayerAnimation("MinigunAim", static_cast<int>(AimIndex));
        AimingLine->SetPosition(Dir * 150); // 조준선 이동

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

void WeaponMinigun::SetAimFrameIndex()
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
    if (PressShoot()) // 발사체크
    {
        isFire = true;
        AimingLine->Off();
        CurPlayer->ChangePlayerAnimation("MinigunFire", static_cast<int>(AimIndex));

    }

}


void WeaponMinigun::Firing(float _DeltaTime)
{
    // 카메라 이동
    float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), MinigunCollision[0]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 100);
    GetLevel()->SetCameraPos(CamPos);

    SetPos(CurPlayer->GetPos());

    DelayTime -= _DeltaTime;
    if (DelayTime < 0)
    {
        DelayTime = 0.05f;
        for (int i = 0; i < BulletCount; i++)
        {
            if (isShooted[i] == false)
            {
                isShooted[i] = true;
                MinigunCollision[i]->On();
                if (MinigunCollision[i]->GetActorPlusPos().y  < GetPos().y)
                {
                    int a = 0;
                }
                if (0 == (1 & i))
                {
                    MinigunCollision[i]->SetMove({ 0,2.0f * i });
                }
                else
                {
                    MinigunCollision[i]->SetMove({ 0,-2.0f * i });
                }
                break;
            }

        }
    }

    for (int i = 0; i < BulletCount; i++)
    {
        if (true == isShooted[i] && true == MinigunCollision[i]->IsUpdate())
        {
            if (isIsFireAnimationDone == false && i == BulletCount - 1 && isWeaponDone == false)
            {
                CurPlayer->ChangePlayerAnimation("Idle");
                isIsFireAnimationDone = true;
            }
            MinigunCollision[i]->SetMove(Dir * _DeltaTime * MoveSpeed);
            float4 CheckCollision = CheckCollisionSide(MinigunCollision[i]);

            if (CheckCollision == float4::Up && Dir.Size() > 0.001f)
            {
                MinigunCollision[i]->SetMove(-Dir * _DeltaTime * MoveSpeed);
                Dir *= 0.3;
                return;
            }

            if (CheckCollision.Size() > 0 || Dir.Size() < 0.001f) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
            {
                SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
                Smoke->SetPos(MinigunCollision[i]->GetActorPlusPos());
                Smoke->CreateSmokeSpark(3, 1, BombScale);

                GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();								  // 1. Bomb 콜리전 가져오기
                BombCollision->SetPosition(GetPos() + MinigunCollision[i]->GetPosition());											  // 2. Bomb 콜리전 이동
                BombCollision->SetScale(float4{ static_cast<float>(BombScale) });


                AttackPlayerGun(BombCollision, 500);																				  // 3. Bomb콜리전 Player Check
                MapModifier::MainModifier->CreateHole(GetPos() + MinigunCollision[i]->GetPosition(), BombScale);					  // 4. 구멍 만들기

                MinigunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
                isExplosion = true;
            }
        }
    }

}


void WeaponMinigun::WeaponMinigunInit()
{
	// Minigun은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 10,10 });
    Collision->Off();

	MinigunCollision.push_back(Collision);
	isShooted.push_back(false);
	DelayTime = 0.05f;
}

