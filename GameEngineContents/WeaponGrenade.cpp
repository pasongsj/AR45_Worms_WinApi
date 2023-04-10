#include "WeaponGrenade.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"
#include "GlobalValue.h"
#include "Map.h"


WeaponGrenade::WeaponGrenade()
{
}

WeaponGrenade::~WeaponGrenade()
{
}

void WeaponGrenade::Start()
{
    // 수류탄 기본 설정 -- 상수값 조정 필요
    MoveSpeed = 1200; // 임시값
    Gravity = 2;// 임시값
    Timer = 2.0f;// 임시값
    WeaponName = "Grenade";
    BombScale = 147;

    MaxDmg = 75;
    MinDmg = 35;

    MaxKnockBackPower = 294;
    MinKnockBackPower = 146;

    std::string Name = Map::MainMap->GetColMapName();
    MapCollision = GameEngineResources::GetInst().ImageFind(Name);
    WeaponNumber = static_cast<int>(WeaponNum::Grenade);



    // 차지 애니메이션
    ChargeAnimation = CreateRender(WormsRenderOrder::Weapon);
    ChargeAnimation->CreateAnimation({ .AnimationName = "Charge", .ImageName = "ChargeAni.bmp",.FilterName = "ChargeAniRot.bmp", .Start = 0, .End = 15, .InterTime = 0.07f , .Loop = false });
    ChargeAnimation->ChangeAnimation("Charge");
    ChargeAnimation->SetScale({ 64,192 });
    ChargeAnimation->Off();
    //ChargeAnimation->SetPosition({ 0,-10 });

    // 임시 조준선 - 수정필요 : 조준선 기준 위치
    AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
    AimingLine->SetScale({ 20,20 });

    // 타이머
    TimerRenderBack = CreateRender("TimerBack.bmp", WormsRenderOrder::UI);
    TimerRenderBack->SetScaleToImage();
    TimerRenderBack->Off();

    TimerRender.SetOwner(this);
    TimerRender.SetCameraEffect(true);
    TimerRender.SetImage("RedNumberRender.bmp", { 15, 15 }, 10, RGB(255, 0, 255));
    TimerRender.SetAlign(Align::Center);
    TimerRender.SetValue(static_cast<int>(Timer));
    TimerRender.Off();

}

void WeaponGrenade::Update(float _DeltaTime)
{
    if (nullptr == WeaponRender) // 무기 랜더가 존재하지 않는 경우
    {
        WeaponGrenadeInit();
        SetCurPlayer();
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
            CheckTimer(_DeltaTime);
        }
        else   // 발사 되고 터진 후
        {
            CheckExplosion();
        }
    }
}

void WeaponGrenade::CheckExplosion()
{

    if (true == ExplosionCircle->IsAnimationEnd())
    {
        ExplosionCircle->Off();
    }
    if (true == ExplosionElipse->IsAnimationEnd())
    {
        ExplosionElipse->Off();
    }
    if (true == PootTextAnimation->IsAnimationEnd())
    {
        PootTextAnimation->Off();
    }
    if (WaitTime < GetLiveTime())
    {
        isWeaponDone = true;
        GetLevel()->SetCameraPos(GetPos() - GameEngineWindow::GetScreenSize().half()); //다음 턴 Player로 카메라 이동- 삭제필요
    }
}

void WeaponGrenade::Aiming(float _DeltaTime)
{

    if (CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON) // 현재 플레이어가 무기 State
    {
        if (isPress == false)
        {
            // 위치
            float4 PlayerPos = CurPlayer->GetPos() + float4{ 0,-15 };
            Dir = GetShootDir();
            SetPos(PlayerPos);


            // 조준선
            SetAimFrameIndex();// Aim 조준선 index 찾기
            AimingLine->On();
            // lerf한 프레임 변경
            float Ratio = (3 * _DeltaTime > 1 ? 1 : 3 * _DeltaTime);
            AimIndex = AimIndex * (1.0f - Ratio) + (NextAimIndex * Ratio);

            // FrameIndex 설정
            CurPlayer->ChangePlayerAnimation("GrenadeAim", static_cast<int>(AimIndex));
            AimingLine->SetPosition(Dir * 150 + float4{ 0,15 }); // 조준선 이동
            AimingLine->SetAngle(-Dir.GetAnagleDeg());
        }

        // 발사 체크
        if (true == PressShoot()) // IsPress
        {
            if (false == isPress)
            {
                ChargeAnimation->On();
                ChargeAnimation->ChangeAnimation("Charge", 0);
                ChargeAnimation->SetAngle(270 - Dir.GetAnagleDeg());
                isPress = true;
                GameEngineResources::GetInst().SoundPlay("Charging.wav");
                GameEngineResources::GetInst().SoundPlay("WATCHTHIS.wav");
            }
            SetCharge();// 차징포인트 계산
        }
        if (true == isEndCharging()) // IsUp
        {
            ChargeAnimation->Off();
            AimingLine->Off();

            WeaponRender->On();
            WeaponCollision->On();
            NextPosCheckCollision->On();


            MoveSpeed *= Charge;
            isFire = true;
            // 타이머랜더
            TimerRenderBack->On();
            TimerRender.On();
            GameEngineResources::GetInst().SoundPlay("THROWRELEASE.wav");
        }

    }
    else
    {
        AimingLine->Off();
    }

}


void WeaponGrenade::SetAimFrameIndex()
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

void WeaponGrenade::Firing(float _DeltaTime)// 발사 중 isFire == true
{
    // 카메라 이동
    float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), WeaponRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 10);
    GetLevel()->SetCameraPos(CamPos);

    // 타이머
    Timer -= _DeltaTime;
    TimerRenderBack->SetPosition(WeaponRender->GetPosition() - float4{ 30,30 });
    TimerRender.SetRenderPos(WeaponRender->GetPosition() - float4{ 30,30 });
    if (static_cast<int>(Timer) + 1 >= 0)
    {
        TimerRender.SetValue(static_cast<int>(Timer) + 1);

    }


    if (false == isExplosion) // 아직 폭발하지 않았다면
    {
        Dir.y += Gravity * _DeltaTime;
        Dir.x += GlobalValue::gValue.GetWindPhase() / 10 * _DeltaTime;
        float4 MoveVec = Dir * MoveSpeed * _DeltaTime;
        NextPosCheckCollision->SetPosition(WeaponCollision->GetPosition() + MoveVec);
        float4 CheckCol = Check4Side(NextPosCheckCollision, NextPosCheckCollision->GetActorPlusPos());
        if (CheckCol.AddAllVec() == 0)
        {
            WeaponRender->SetAngle(Dir.GetAnagleDeg());
            WeaponRender->SetMove(MoveVec);
            WeaponCollision->SetMove(MoveVec);
            return;
        }
        else if (1 == CheckCol.AddAllVec() || 2 == CheckCol.AddAllVec())
        {
            if (1 == CheckCol.z)
            {
                Dir.y = -abs(Dir.y) * 0.25f;
            }
            if (1 == CheckCol.w)
            {
                Dir.y = abs(Dir.y) * 0.25f;
            }

            if (1 == CheckCol.x)
            {
                Dir.x = -abs(Dir.x * 0.5f);
            }
            if (1 == CheckCol.y)
            {
                Dir.x = abs(Dir.x * 0.5f);
            }

            return;
        }
        else if (3 == CheckCol.AddAllVec())
        {
            if (0 == CheckCol.z)
            {
                Dir.y = abs(Dir.y) * 0.25f;
            }
            if (0 == CheckCol.w)
            {
                Dir.y = -abs(Dir.y) * 0.25f;
            }

            if (0 == CheckCol.x)
            {
                Dir.x = abs(Dir.x * 0.5f);
            }
            if (0 == CheckCol.y)
            {
                Dir.x = -abs(Dir.x * 0.5f);
            }
        }
        else
        {
            //WeaponRender->SetMove(-MoveVec);
            //WeaponCollision->SetMove(-MoveVec);
            Dir.x = -Dir.x * 0.5f;
            Dir.y = -Dir.y * 0.25f;
        }


    }



}

void WeaponGrenade::CheckTimer(float _DeltaTime)
{
    // 폭발 체크
    if (Timer < 0 && isExplosion == false) //폭발, isExplosion중복 체크
    {
        TimerRenderBack->Off();
        TimerRender.Off();
        // 터지는 애니메이션
        ExplosionCircle->SetPosition(WeaponRender->GetPosition());
        ExplosionCircle->On();
        ExplosionCircle->ChangeAnimation("Explosion", 0);

        ExplosionElipse->SetPosition(WeaponRender->GetPosition());
        ExplosionElipse->On();
        ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);

        PootTextAnimation->SetPosition(WeaponRender->GetPosition());
        PootTextAnimation->On();
        PootTextAnimation->ChangeAnimation("Poot", 0);

        //Player 공격
        GameEngineCollision* BombCollision = CreateCollision(WormsCollisionOrder::Weapon);
        BombCollision->SetPosition( WeaponCollision->GetPosition());
        BombCollision->SetScale(float4{ static_cast<float>(BombScale) });
        AttackPlayer(BombCollision); // 임시값
        BombCollision->SetPosition(float4::Zero);

        // 땅 파이게
        MapModifier::MainModifier->CreateHole(GetPos() + WeaponCollision->GetPosition(), static_cast<int>(BombScale));




        isExplosion = true;
        WeaponRender->Off();
        WeaponCollision->Off();
        NextPosCheckCollision->Off();
        WaitTime = GetLiveTime() + 1.5f;

        GameEngineResources::GetInst().SoundPlay("Explosion3.wav");

    }
}

void WeaponGrenade::SetCharge() // Charging으로 함수이름 통일
{
    if (Charge > GetChargeTime())
    {
        return;
    }
    if (GetChargeTime() > 1.5f) // 최대 2배 차징
    {
        Charge = 1.5f;
    }
    else if (GetChargeTime() < 0.5f)
    {
        Charge = 0.5f;
    }
    else {
        Charge = GetChargeTime();
    }
}

void WeaponGrenade::ResetWeapon()
{

    isFire = false;
    isExplosion = false;
    Timer = 3.0f;
    if (nullptr == WeaponRender)
    {
        return;
    }
    WeaponRender->On();
    WeaponRender->SetPosition(float4::Zero);

    WeaponCollision->On();
    WeaponCollision->SetPosition(float4::Zero);

}

void WeaponGrenade::WeaponGrenadeInit()
{
    WeaponRender = CreateRender(WormsRenderOrder::Weapon);		//렌더
    WeaponRender->SetImage("Grenade.bmp");
    WeaponRender->SetRotFilter("GrenadeRot.bmp");
    WeaponRender->SetPosition(float4{ 0,-30 });
    WeaponRender->SetScale({ 15,25 }); // 임시 설정 값 

    WeaponCollision = CreateCollision(WormsCollisionOrder::Weapon);	//콜리전
    WeaponCollision->SetScale({ 15,25 });
    WeaponCollision->SetPosition(float4{ 0,-30 });

    NextPosCheckCollision = CreateCollision(WormsCollisionOrder::Weapon);	//콜리전
    NextPosCheckCollision->SetScale({ 15,25 });
    NextPosCheckCollision->SetPosition(float4{ 0,-30 });



    WeaponRender->Off();
    WeaponCollision->Off();
    NextPosCheckCollision->Off();
    isFire = false;
    ExplosionEffectInit(BombScale);
}
