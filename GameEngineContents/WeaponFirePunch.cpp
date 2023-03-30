#include "WeaponFirePunch.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Player.h"
#include "SmokeSparkEffect.h"
#include "MapModifier.h"
#include "SmokeSparkEffect.h"
#include <GameEngineCore/GameEngineLevel.h>

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

    Dir = float4::Up;						// 무기 진행 방향
    BombScale = 13;				// 폭발 범위

    WeaponNumber = static_cast<int>(WeaponNum::FirePunch);							// 무기 이름에 해당하는 Number
    WeaponName = "FirePunch";							// 무기 이름

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");		//충돌맵

    //Player* CurPlayer = nullptr;
    Timer = 1.5f;								// 타이머
}

void WeaponFirePunch::Update(float _DeltaTime)
{
    if (false == isFire && false == isCharging)
    {
        SetCurPlayer();// 플레이어 전환버튼 때문에 추가
    }


    if (false == isCharging) // 추가 수정 필요 : isFire이랑 합칠 방안 생각해보기
    {
        if (true == PressShoot()) // 스페이스바를 눌렀다면
        {
            CurPlayer->ChangePlayerAnimation("FirePunchCharging");
            isCharging = true;
        }
    }
    else
    {
        if (false == isFire) 
        {
            if (true == GameEngineInput::IsUp("Shoot")) // 스페이스바를 뗏다면
            {
                CurPlayer->ChangePlayerAnimation("FirePunchFire");
                isFire = true;
                StartPos = CurPlayer->GetPos();
            }
        }
        else
        {
            if (Timer > 0) // 위쪽으로 펀치
            {
                Timer -= _DeltaTime;
                EffectTimer -= _DeltaTime;
                if ((StartPos + Dir * _DeltaTime * 300.0f).y > 0)
                {
                    StartPos += Dir * _DeltaTime * 300.0f;
                }
                if (EffectTimer < 0) // - 수정필요 스모크 대신 이펙트로 변경 필요함
                {
                    SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
                    Smoke->SetPos(StartPos);
                    Smoke->CreateSmokeSpark(1, 0, BombScale);
                    EffectTimer = 0.05f;
                }

                CurPlayer->SetPos(StartPos); // 플레이어 이동

                GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();								  // 1. Bomb 콜리전 가져오기
                BombCollision->SetPosition(StartPos);											                                       // 2. Bomb 콜리전 이동

                AttackPlayer(BombCollision, BombScale);																						  // 3. Bomb콜리전 Player Check

                MapModifier::MainModifier->CreateHole(StartPos + float4{0,-10}, BombScale);                                         //4. createHole
            }
            else // 펀치가 끝났다면
            {
                if (false == isAfterAnimation) // 떨어지느 애니메이션
                {
                    CurPlayer->ChangePlayerAnimation("FirePunchAfter");
                    isAfterAnimation = true;
                }
                else if (true == CurPlayer->IsPlayerAnimationEnd()) // 떨어지는 애니메이션이 끝났다면
                {
                    isWeaponDone = true; // 무기종료
                }
            }
        }
    }
}
