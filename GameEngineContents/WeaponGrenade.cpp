#include "WeaponGrenade.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"
#include "MapModifier.h"
#include "GlobalValue.h"


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
	Gravity = 1.2f;// 임시값
	Timer = 3.0f;// 임시값
	WeaponName = "Grenade";
	BombScale = 147;

    MaxDmg = 75;
    MinDmg = 35;

    MaxKnockBackPower = 294;
    MinKnockBackPower = 146;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 이미지 이름 변수or 함수화 필요
	WeaponNumber = static_cast<int>(WeaponNum::Grenade);



    // 차지 애니메이션
    ChargeAnimation = CreateRender(WormsRenderOrder::Weapon);
    ChargeAnimation->CreateAnimation({ .AnimationName = "Charge", .ImageName = "ChargeAni.bmp",.FilterName = "ChargeAniRot.bmp", .Start = 0, .End = 15, .InterTime = 0.07f , .Loop = false });
    ChargeAnimation->ChangeAnimation("Charge");
    ChargeAnimation->SetScale({ 64,192 });
    ChargeAnimation->Off();
    ChargeAnimation->SetPosition({ 0,-10 });

    // 임시 조준선 - 수정필요 : 조준선 기준 위치
    AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
    AimingLine->SetScale({ 20,20 });

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
        AimingLine->SetPosition(Dir * 150); // 조준선 이동
        if (Dir.x > 0)
        {
            AimingLine->SetAngle(Dir.GetAnagleDeg());
        }
        else
        {
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
            }
            SetCharge();// 차징포인트 계산
        }
        if (true == isEndCharging()) // IsUp
        {
            ChargeAnimation->Off();
            AimingLine->Off();

            WeaponRender->On();
            WeaponCollision->On();

            MoveSpeed *= Charge;
            isFire = true;
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

    NewIndex = Angle / 5 + 15;

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

    Timer -= _DeltaTime;
    if (false == isExplosion) // 아직 폭발하지 않았다면
    {
        Dir.y = Dir.y + Gravity * _DeltaTime; // dt동안 중력의 영향 V == Vo + At

        float4 MoveVec = CulWindMoveVec(_DeltaTime);

        WeaponRender->SetAngle(Dir.GetAnagleDeg());

        WeaponRender->SetMove(MoveVec);         //WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);
        WeaponCollision->SetMove(MoveVec);      //WeaponCollision->SetMove(Dir * MoveSpeed * _DeltaTime);

        if (Timer > 3.0f - 0.08f) // 보정값 ( 땅에 박히는 오류 )
        {
            return;
        }


        float4 CheckedCol = CheckCollisionSide(WeaponCollision);

        if (Dir.x * CheckedCol.x > 0) // 방향이 달라
        {
            WeaponRender->SetMove(-MoveVec);    //WeaponRender->SetMove(-Dir * MoveSpeed * _DeltaTime);
            WeaponCollision->SetMove(-MoveVec); //WeaponCollision->SetMove(-Dir * MoveSpeed * _DeltaTime);

            Dir.x = -Dir.x * 0.5f;										  //  x값은 마찰고려값
            Dir.y = -Dir.y * 0.25f;
        }
        else if (Dir.x * CheckedCol.x < 0 || CheckedCol.x == 0 && CheckedCol.y > 0)// 방향이 같아 or 좌우 이동x
        {
            WeaponRender->SetMove({ 0, -MoveVec.y });       //WeaponRender->SetMove({ 0, -Dir.y * MoveSpeed * _DeltaTime });
            WeaponCollision->SetMove({ 0, -MoveVec.y });    //WeaponCollision->SetMove({ 0, -Dir.y * MoveSpeed * _DeltaTime });
            Dir.x = Dir.x * 0.5;
            Dir.y = -Dir.y * 0.25f;
        }
        else if(CheckedCol == float4::Up)
        {
            WeaponRender->SetMove(-MoveVec);
            WeaponCollision->SetMove(-MoveVec);
            Dir *= 0.1f;
        }
    }

    // 폭발 체크
    if (Timer < 0 && isExplosion == false) //폭발, isExplosion중복 체크
    {
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
        GameEngineCollision* BombCollision = MapModifier::MainModifier->GetModifierCollision();
        BombCollision->SetPosition(GetPos() + WeaponCollision->GetPosition());
        BombCollision->SetScale(float4{ static_cast<float>(BombScale) });
        AttackPlayer(BombCollision); // 임시값
        BombCollision->SetPosition(float4::Zero);

        // 땅 파이게
        MapModifier::MainModifier->CreateHole(GetPos() + WeaponCollision->GetPosition(), BombScale);




        isExplosion = true;
        WeaponRender->Off();
        WeaponCollision->Off();
        WaitTime = GetLiveTime() + 1.5;

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
	WeaponRender->SetScale({ 15,25 }); // 임시 설정 값 

	WeaponCollision = CreateCollision(WormsCollisionOrder::Weapon);	//콜리전
    WeaponCollision->SetScale({15,25});
    WeaponRender->Off();
    WeaponCollision->Off();
	isFire = false;
    ExplosionEffectInit(BombScale);
}

float4 WeaponGrenade::CulWindMoveVec(float _DeltaTime)
{
    //if (abs(Dir.x * MoveSpeed) > 2000)
    //{
    //    return Dir * MoveSpeed * _DeltaTime;
    //}
    //Dir.x += GlobalValue::gValue.GetWindPhase() * 0.1f * _DeltaTime; 가속
    float4 ReturnVec = Dir * MoveSpeed * _DeltaTime;
    ReturnVec.x += (GlobalValue::gValue.GetWindPhase() / 7) * (MoveSpeed / 2) * _DeltaTime; // 등속
    return ReturnVec;
}