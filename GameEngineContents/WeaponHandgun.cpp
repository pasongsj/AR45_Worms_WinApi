#include "WeaponHandgun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "MapModifier.h"
#include "Player.h"
#include "SmokeSparkEffect.h"

WeaponHandgun::WeaponHandgun()
{
}

WeaponHandgun::~WeaponHandgun()
{
}

void WeaponHandgun::Start()
{
	// 핸드건 기본 설정
	WeaponName = "Handgun";
	MoveSpeed = 3000;
	//Dir = float4::Right;
	BombScale = 22;

    MaxDmg = 10;
    MinDmg = 3;
    MaxKnockBackPower = 22;
    MinKnockBackPower = 22;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함

	//AllWeapons[WeaponName] = this;
	WeaponNumber = static_cast<int>(WeaponNum::Handgun);
	SetCurPlayer();


	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
	AimingLine->SetScale({ 20,20 });


}

void WeaponHandgun::Aiming(float _DeltaTime)
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

        CurPlayer->ChangePlayerAnimation("HandgunAim", static_cast<int>(AimIndex));
        AimingLine->SetPosition(Dir * 150 + float4{ 0,15 }); // 조준선 이동
        AimingLine->SetAngle(-Dir.GetAnagleDeg());


        CheckFiring(); // 방향체크, 발사 체크
    }
    else
    {
        AimingLine->Off();
    }
}

void WeaponHandgun::Update(float _DeltaTime)
{
    // 총알 수만큼 init
	while (BulletCount > HandgunCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponHandgunInit();
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

void WeaponHandgun::SetAimFrameIndex()
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

    NewIndex = static_cast<int>(Angle / 5 + 15);

    if (NewIndex < 0)
    {
        NewIndex = 0;
    }
    NextAimIndex = NewIndex;

}

bool WeaponHandgun::IsDone()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == HandgunCollision[i]->IsUpdate())
		{
			return false;
		}

	}
	return true;
}

void WeaponHandgun::CheckFiring()
{
    if (PressShoot()) // 발사체크
    {
        isFire = true;
        AimingLine->Off();
        CurPlayer->ChangePlayerAnimation("HandgunFire", static_cast<int>(AimIndex));

    }
}


void WeaponHandgun::Firing(float _DeltaTime)
{
    // 카메라 이동
    float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), HandgunCollision[0]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 100);
    GetLevel()->SetCameraPos(CamPos);

    DelayTime -= _DeltaTime;
    if (DelayTime < 0)
    {
        DelayTime = 0.3f;
        for (int i = 0; i < BulletCount; i++)
        {
            if (isShooted[i] == false)
            {
                isShooted[i] = true;
                HandgunCollision[i]->On();
                if (0 == (1 & i))
                {
                    HandgunCollision[i]->SetMove({ 0,1.0f*i });
                }
                else
                {
                    HandgunCollision[i]->SetMove({ 0,-1.0f * i });
                }
                break;
            }

        }
    }

    for (int i = 0; i < BulletCount; i++)
    {
        if (true == isShooted[i] && true == HandgunCollision[i]->IsUpdate())
        {
            if (isIsFireAnimationDone == false && i == BulletCount - 1 && isWeaponDone == false)
            {
                CurPlayer->ChangePlayerAnimation("Idle");
                isIsFireAnimationDone = true;
            }
            HandgunCollision[i]->SetMove(Dir * _DeltaTime * MoveSpeed);
            float4 CheckCollision = CheckCollisionSide(HandgunCollision[i]);
            if (CheckCollision == float4::Up && Dir.Size() > 0.001f)
            {
                HandgunCollision[i]->SetMove(-Dir * _DeltaTime * MoveSpeed);
                Dir *= 0.3f;
                return;
            }
            if (CheckCollision.Size() > 0 || Dir.Size() < 0.001f) // 콜리전 체크(플레이어, 맵, 전체 맵 밖)
            {
                SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
                Smoke->SetPos(HandgunCollision[i]->GetActorPlusPos());
                Smoke->CreateSmokeSpark(6, 2, BombScale);

                GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();								  // 1. Bomb 콜리전 가져오기
                BombCollision->SetPosition(GetPos() + HandgunCollision[i]->GetPosition());											  // 2. Bomb 콜리전 이동
                BombCollision->SetScale(float4{ static_cast<float>(BombScale) });


                AttackPlayerGun(BombCollision, 500);																				  // 3. Bomb콜리전 Player Check
                MapModifier::MainModifier->CreateHole(GetPos() + HandgunCollision[i]->GetPosition(), static_cast<int>(BombScale));					  // 4. 구멍 만들기

                HandgunCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
                isExplosion = true;
            }
        }
    }
	
}


void WeaponHandgun::WeaponHandgunInit()
{
	// Handgun은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 15,15 });
    Collision->Off();

	HandgunCollision.push_back(Collision);
	isShooted.push_back(false);
	DelayTime = 0.3f;

}
