#include "WeaponFirePunch.h"
#include "ContentsEnums.h"
#include "Map.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Player.h"

WeaponFirePunch::WeaponFirePunch()
{
}

WeaponFirePunch::~WeaponFirePunch()
{
}

void WeaponFirePunch::Start()
{


    MoveSpeed = 200;							// 무기속력
    //Dmg = 0.0f;								// 데미지

    float4 Dir = float4::Up;						// 무기 진행 방향
    BombScale = 15;				// 폭발 범위

    WeaponNumber = static_cast<int>(WeaponNum::FirePunch);							// 무기 이름에 해당하는 Number
    WeaponName = "FirePunch";							// 무기 이름

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");		//충돌맵

    //Player* CurPlayer = nullptr;
    Timer = 5.0f;								// 타이머
}

void WeaponFirePunch::Update(float _DeltaTime)
{
    if (false == isFire)
    {
        SetCurPlayer();// 플레이어 전환버튼 때문에 추가
    }
    if (false == isCharging && true == PressShoot())
    {
        CurPlayer->ChangePlayerAnimation("FirePunchCharging");
        isCharging = true;
    }
    if (false == isFire && true == GameEngineInput::IsUp("Shoot"))
    {
        CurPlayer->ChangePlayerAnimation("FirePunchFire");
        isFire = true;
        StartPos = CurPlayer->GetPos();
    }

    if (true == isFire && Timer > 0)
    {
        Timer -= _DeltaTime;
        StartPos += Dir * _DeltaTime * 1000.0f;////??????????????????????????????????????????????????????????????????????????????????????????
        CurPlayer->SetPos(StartPos);
    }
    if (Timer < 0 && false == isAfterAnimation)
    {
        CurPlayer->ChangePlayerAnimation("FirePunchAfter");
        isAfterAnimation = true;
    }

    if (Timer < 0 && true == isAfterAnimation && true == CurPlayer->IsPlayerAnimationEnd())
    {
        isWeaponDone = true;
    }
}
