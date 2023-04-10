#include "WeaponFirePunch.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnums.h"
#include "Player.h"
#include "SmokeSparkEffect.h"
#include "MapModifier.h"
#include "SmokeSparkEffect.h"
#include "Map.h"

WeaponFirePunch::WeaponFirePunch()
{
}

WeaponFirePunch::~WeaponFirePunch()
{
}

void WeaponFirePunch::Start()
{


    MoveSpeed = 200;							// 무기속력

    Dir = float4::Up;						// 무기 진행 방향
    BombScale = 26;

    MaxDmg = 45;
    MinDmg = 21;

    MaxKnockBackPower = 300; // dir Y값 조정 필요함
    MinKnockBackPower = 200;

    WeaponNumber = static_cast<int>(WeaponNum::FirePunch);							// 무기 이름에 해당하는 Number
    WeaponName = "FirePunch";							// 무기 이름

    std::string Name = Map::MainMap->GetColMapName();
    MapCollision = GameEngineResources::GetInst().ImageFind(Name);
    PunchCollision = CreateCollision(WormsCollisionOrder::Weapon);
    PunchCollision->SetPosition({ 0,50 });
    PunchCollision->SetScale({ 50,50 });

    Timer = 0.45f;								// 타이머
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
            if (true == UpShoot()) // 스페이스바를 뗏다면
            {
                CurPlayer->ChangePlayerAnimation("FirePunchFire");
                isFire = true;
                StartPos = CurPlayer->GetPos();
                SetPos(StartPos);
                GameEngineResources::GetInst().SoundPlay("DRAGONPUNCH.wav");
                PunchCollision->SetMove(CurPlayer->GetPlayerDir() * 10);
            }
            else if (true == PressShoot() && GetChargeTime() > 0.6f)
            {
                CurPlayer->ChangePlayerAnimation("FirePunchCharging",7);
            }
        }
        else
        {
            //float4 CurPos = CurPlayer->GetPos();
            if (Timer > 0) // 위쪽으로 펀치
            {
                // 카메라 이동
                float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), StartPos - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 10);
                GetLevel()->SetCameraPos(CamPos);

                Timer -= _DeltaTime;
                EffectTimer -= _DeltaTime;
                HitTimer -= _DeltaTime;
                if ((StartPos + Dir * _DeltaTime * 300.0f).y > 0)
                {
                    StartPos += Dir * _DeltaTime * 300.0f;
                    PunchCollision->SetMove(Dir * _DeltaTime * 300.0f);
                }
                CurPlayer->SetPos(StartPos); // 플레이어 이동
                
                //PunchCollision->SetPosition(StartPos - GetPos() + float4{0,50});

                if (EffectTimer < 0) // - 수정필요 스모크 대신 이펙트로 변경 필요함
                {
                    GameEngineRender* StarSmoke = CreateRender(WormsRenderOrder::Weapon);
                    StarSmoke->SetPosition(PunchCollision->GetPosition() + float4{0,-50} + float4{ GameEngineRandom::MainRandom.RandomFloat(-15.0f,15.0f) });
                    StarSmoke->SetScale({ 60, 60 });
                    StarSmoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "starEffect.bmp", .Start = 0, .End = 9, .InterTime = 0.1f , .Loop = false });
                    StarSmoke->ChangeAnimation("Smoke");
                    EffectTimer = 0.03f;
                }


                if (true == AttackPlayer(PunchCollision, false) && HitTimer <0)																  // 3. Bomb콜리전 Player Check
                {
                    GameEngineRender* StarSmoke = CreateRender(WormsRenderOrder::Weapon);
                    StarSmoke->SetPosition(PunchCollision->GetPosition() + float4{ 0,-50 });
                    StarSmoke->SetScale({ 50, 50 });
                    StarSmoke->CreateAnimation({ .AnimationName = "Hit", .ImageName = "firehit.bmp", .Start = 0, .End = 8, .InterTime = 0.1f , .Loop = false });
                    StarSmoke->ChangeAnimation("Hit");
                    HitTimer = 0.1f;
                    GameEngineResources::GetInst().SoundPlay("FirePunchImpact.wav");
                }

                MapModifier::MainModifier->CreateHole(StartPos + float4(0,-20), static_cast<int>(BombScale));                                         //4. createHole
            }
            else // 펀치가 끝났다면
            {
                if (false == isAfterAnimation) // 떨어지느 애니메이션
                {
                    CurPlayer->ChangePlayerAnimation("FirePunchAfter");
                    isAfterAnimation = true;
                }
                else
                {
                    CurPlayer->SetMove(float4(0, 120*_DeltaTime));
                    if (true == CurPlayer->IsPlayerAnimationEnd()) // 떨어지는 애니메이션이 끝났다면
                    {
                        isWeaponDone = true; // 무기종료
                    }
                }
            }
        }
    }
}
