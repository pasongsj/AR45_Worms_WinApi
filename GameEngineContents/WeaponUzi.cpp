#include "WeaponUzi.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnums.h"
#include "MapModifier.h"
#include "Player.h"
#include "SmokeSparkEffect.h"
#include "Map.h"

WeaponUzi::WeaponUzi()
{
}

WeaponUzi::~WeaponUzi()
{
}

void WeaponUzi::Start()
{
	// 샷건 기본 설정
	WeaponName = "Uzi";
	MoveSpeed = 3000;
	//Dir = float4::Right;
    BombScale = 22;

    MaxDmg = 10;
    MinDmg = 3;
    MaxKnockBackPower = 40;
    MinKnockBackPower = 22;

    std::string Name = Map::MainMap->GetColMapName();
    MapCollision = GameEngineResources::GetInst().ImageFind(Name);

	//AllWeapons[WeaponName] = this;
	WeaponNumber = static_cast<int>(WeaponNum::Uzi);


	// 임시 조준선 - 수정필요 : 조준선 기준 위치, 이미지 , 이미지 각도
	AimingLine = CreateRender(WormsRenderOrder::Weapon);
	AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
	AimingLine->SetScale({ 20,20  });


}

void WeaponUzi::Update(float _DeltaTime)
{
	while (BulletCount > UziCollision.size()) // 총탄 개수만큼 WeaponInit
	{
		WeaponUziInit();
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



void WeaponUzi::Aiming(float _DeltaTime)
{
    if (CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON) // 현재 플레이어가 무기 State
    {
        // 위치
        float4 PlayerPos = CurPlayer->GetPos() + float4{ 0,-10 };
        Dir = GetShootDir();
        SetPos(PlayerPos);

        // 조준선
        SetAimFrameIndex();
        AimingLine->On();

        float Ratio = 6 * _DeltaTime;
        AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);

        CurPlayer->ChangePlayerAnimation("UziAim", static_cast<int>(AimIndex));
        AimingLine->SetPosition(Dir * 150 ); // 조준선 이동
        AimingLine->SetAngle(-Dir.GetAnagleDeg());
        float tmp = -Dir.GetAnagleDeg();
        CheckFiring(); // 방향체크, 발사 체크
    }
    else
    {
        AimingLine->Off();
    }
}

bool WeaponUzi::IsDone()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (true == UziCollision[i]->IsUpdate())
		{
			return false;
		}

	}
	return true;
}

void WeaponUzi::CheckFiring()
{
    if (PressShoot()) // 발사체크
    {
        isFire = true;
        AimingLine->Off();
        CurPlayer->ChangePlayerAnimation("UziFire", static_cast<int>(AimIndex));
        GameEngineResources::GetInst().SoundPlayToControl("UZIFIRE.wav").LoopCount(5);
    }
}

void WeaponUzi::SetAimFrameIndex()
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


void WeaponUzi::Firing(float _DeltaTime)
{
    // 카메라 이동
    float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), UziCollision[0]->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 100);
    GetLevel()->SetCameraPos(CamPos);

    DelayTime -= _DeltaTime;
    if (DelayTime < 0)
    {
        DelayTime = 0.05f;
        for (int i = 0; i < BulletCount; i++)
        {
            if (isShooted[i] == false)
            {
                isShooted[i] = true;
                UziCollision[i]->On();
                UziCollision[i]->SetMove(float4(0, GameEngineRandom::MainRandom.RandomFloat(-3.0f, 3.0f)));
                break;
            }

        }
    }

    for (int i = 0; i < BulletCount; i++)
    {
        if (true == isShooted[i] && true == UziCollision[i]->IsUpdate())
        {
            if (isIsFireAnimationDone == false && i == BulletCount - 1 && isWeaponDone == false)
            {
                CurPlayer->ChangePlayerAnimation("Idle");
                isIsFireAnimationDone = true;
            }

            float4 MoveVec = Dir * MoveSpeed * _DeltaTime;
            UziCollision[i]->SetMove(MoveVec);
            float4 CheckCol = Check4Side(UziCollision[i], UziCollision[i]->GetActorPlusPos());
            if (CheckCol.AddAllVec() > 0)
            {
                if (CheckCol.AddAllVec() == 4)
                {
                    UziCollision[i]->SetMove(-MoveVec * 0.3f);
                }
                //UziCollision[i]->SetMove(-MoveVec * 0.15f * CheckCol.AddAllVec());
                SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
                Smoke->SetPos(UziCollision[i]->GetActorPlusPos());
                Smoke->CreateSmokeSpark(6, 2, BombScale);

                UziCollision[i]->SetScale(float4{ static_cast<float>(BombScale) });


                AttackPlayerGun(UziCollision[i], 500);																				  // 3. Bomb콜리전 Player Check
                MapModifier::MainModifier->CreateHole(GetPos() + UziCollision[i]->GetPosition(), static_cast<int>(BombScale));					  // 4. 구멍 만들기
                UziCollision[i]->Off(); // 발사가 끝난 총탄 콜리전
                isExplosion = true;
            }
        }
    }

}


void WeaponUzi::WeaponUziInit()
{
	// Uzi은 랜더이미지가 존재하지 않음
	GameEngineCollision* Collision = CreateCollision(WormsCollisionOrder::Weapon);
	Collision->SetScale({ 20,20 });
    Collision->Off();

	UziCollision.push_back(Collision);
	isShooted.push_back(false);
	DelayTime = 0.1f;

}
