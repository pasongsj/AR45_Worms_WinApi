#include "WeaponBazooka.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"
#include "GlobalValue.h"

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineBase/GameEngineRandom.h>

WeaponBazooka::WeaponBazooka()
{
}

WeaponBazooka::~WeaponBazooka()
{
}

void WeaponBazooka::Start()
{
	WeaponBazookaInit();
}

void WeaponBazooka::Update(float _DeltaTime)
{
    Timer();

    if (CurPlayer->GetPlayerState() != PlayerState::EQUIPWEAPON)
    {
        AimingLine->Off();
    }

	if(isAttack == false)
	{
		firing(_DeltaTime);
		Charging();
		BazookaOn();
		BazAiming();
	}

	if(GameEngineInput::IsPress("Shoot") == false)
	{
		ShootDir = GetShootDir();
	}
    
    if (isAttack == true)
    {
        DebrisAnimation(_DeltaTime);
    }

	if (isExplosion == true && ExplosionCircle->IsAnimationEnd() == true)
	{
		isEndBazOn = false;
		isExplosion = false;

		TimeCount = 0;
		fLerpRatio = 0;
	}


	if (isShoot == true)
	{
		MakeSmoke();
	}
    
    ExplosionAnimationOff();
    CameraUpdate(_DeltaTime);
}

void WeaponBazooka::Render(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ChangePlayer"))
	{
		CurPlayer->SetCanIMove(true);
		ResetWeapon();
		isAttack = false;
	}
}

void WeaponBazooka::WeaponBazookaInit()
{
	WeaponRender =  CreateRender("bazooka.bmp", static_cast<int>(WormsRenderOrder::Weapon));
	WeaponCollision = CreateCollision(static_cast<int>(WormsCollisionOrder::Weapon));

	WeaponRender->SetRotFilter("bazookaRot.bmp");
	BombScale = 104;
    MinDmg = 35;
    MaxDmg = 75;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");


    AimingLine = CreateRender(WormsRenderOrder::Weapon);
    AimingLine->SetImage("AimingLine.bmp");
    AimingLine->SetRotFilter("AimingLineRot.bmp");
    AimingLine->SetScale({ 20,20 });

	WeaponRender->SetPosition({ 500, 200 }); //임시 설정값
	WeaponRender->SetScaleToImage(); //임시 설정값
	WeaponRender->Off();

	WeaponCollision->SetPosition(WeaponRender->GetPosition());
	WeaponCollision->SetScale({30,30});
	WeaponCollision->Off();

	GetLevel()->CreateActor<MapModifier>();

	ScreenSize = GameEngineWindow::GetScreenSize();
	WeaponNumber = static_cast<int>(WeaponNum::Bazooka);

	WeaponName = "Bazooka";
   
    ExplosionEffectInit(BombScale);

    ChargingGage = CreateRender("ChargeAni.bmp", WormsRenderOrder::Weapon);
    ChargingGage->SetRotFilter("ChargeAniRot.bmp");
    ChargingGage->SetScale({ 64, 192 });
    ChargingGage->Off();

    DebrisInit();

	Gravity = 20.0f; //임시 설정값

	MoveSpeed = 0.0f; //임시 설정값

	TimeCount = 0;

	//플레이어 바뀔 때마다 CurPlayer 바꿔서 저장
	SetCurPlayer();
}


void WeaponBazooka::Charging() // 딱 Charging기능만으로 분리
{
	if (CurPlayer->GetPlayerState() != PlayerState::IDLE && CurPlayer->GetPlayerState() != PlayerState::EQUIPWEAPON)
	{
		return;
	}

	if (isAiming == false)
	{
		return;
	}


	if (isAiming == true && GameEngineInput::IsPress("Shoot") == true)
	{

        if (isSoundPlay_Fire == false && isSoundPlay_Charging == false)
        {
            GameEngineResources::GetInst().SoundPlay("Fire.Wav");
            GameEngineResources::GetInst().SoundPlay("Charging.Wav");
            isSoundPlay_Fire = true;
            isSoundPlay_Charging = true;
        }
		/* timer 로 시간을 재고, 시간에 맞게 차징정도를 설정 ( 0 ~ 1 까지 시간비례 ) => ( 차징정도 = 현재차징시간 / 최대차징시간 ) */
		/* 차지가 길게 될수록 발사 거리가 길어짐 (발사속도가 빨라짐) */
   		//CurPlayer->SetCanIMove(false);
		ChargingRenderOn();


		MoveSpeed = 300 + GetChargeTime() * 1350.0f;

		//Charge 로 바꿔야함
		if (MoveSpeed < 300)
		{
			MoveSpeed = 300;
		}
		else if (MoveSpeed > 1900)
		{
			MoveSpeed = 1900;
		}
	}
}

void WeaponBazooka::firing(float _DeltaTime) //발사
{
	if (GameEngineInput::IsKey("Shoot") == false)
	{
		return;
	}

	if (CurPlayer->GetPlayerState() != PlayerState::IDLE && CurPlayer->GetPlayerState() != PlayerState::EQUIPWEAPON)
	{
		return;
	}

	if (isAiming == true && isEndCharging() == true)
	{
		ChargingRenderOff();
        GameEngineResources::GetInst().SoundPlay("Shoot.wav");
		isShoot = true;
        isFire = true;
	}

	if (isShoot == false)
	{
		return;
	}

	if (isSet == false)
	{
		WeaponRender->SetPosition(CurPlayer->GetPos() + ShootDir * 30);
		WeaponCollision->SetPosition(CurPlayer->GetPos() + ShootDir * 30);

		Dir = ShootDir;
        Dir.Normalize();

		WeaponRender->On();
		WeaponCollision->On();
		isSet = true;
	}
	
    
    Gravity += 10.0f * _DeltaTime;

    float WindPower = GlobalValue::gValue.GetWindSpeed();

    CurPos = WeaponRender->GetPosition();
    NextPos = CurPos + (Dir * MoveSpeed + float4{WindPower / 10 , Gravity}) * _DeltaTime;

    Dir = NextPos - CurPos;
    Dir.Normalize();

	WeaponRender->SetAngle(-Dir.GetAnagleDeg());

	WeaponRender->SetPosition(NextPos);
	WeaponCollision->SetPosition(NextPos);    

	if (CheckCollision(WeaponCollision) == true)
	{
		Explosion();
		ResetWeapon();
	}
}

void WeaponBazooka::Explosion() //폭발
{
	if (CheckCollision(WeaponCollision) == false)
	{
		return;
	}

	else
	{
		//Dmg만큼 Player의 HP가 감소, 폭발반경의 맵이 깎여야함, 넉백이 있을 수도, 
		ExplosionCircle->SetPosition(WeaponRender->GetPosition());
		ExplosionCircle->On();
		ExplosionCircle->ChangeAnimation("Explosion", 0);
		
        ExplosionElipse->SetPosition(WeaponRender->GetPosition());
        ExplosionElipse->On();
        ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);	

        PootTextAnimation->SetPosition(WeaponRender->GetPosition());
        PootTextAnimation->On();
        PootTextAnimation->ChangeAnimation("Poot", 0);

        MapModifier::MainModifier->CreateHole(WeaponRender->GetPosition(), static_cast<int>(BombScale));

        DebrisAnimation(0.0f);

		isAttack = true;
		isExplosion = true;

        GameEngineResources::GetInst().SoundPlay("Explosion1.wav");
		DamageToPlayer();
	}
}

void WeaponBazooka::BazookaOn()
{
	if (CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON && isBazOn == false)
	{
        if(CurPlayer->IsPlayerAnimationEnd() == true)
        {
            isBazOn = true;
        }
	}
    else
    {
        isBazOn = false;
    }
}

void WeaponBazooka::ResetWeapon()
{
	//플레이어 바뀔 때마다 CurPlayer 바꿔서 저장
	SetCurPlayer();
	ChargingRenderOff();
	//위치 재설정
	WeaponRender->SetPosition(CurPlayer->GetPos());
	WeaponCollision->SetPosition(CurPlayer->GetPos());

	Gravity = 0.0f; //임시 설정값
	WeaponRender->Off();
	WeaponCollision->Off();

	isBazOn = false;
	isSet = false;
	isShoot = false;
	isAiming = false;

	Bazindex = 0;

	ShootDir = { 0,0 };
	StartDir = { 0,0 };

	TimeCount = 0;
}

void WeaponBazooka::BazAiming()
{
	if (CurPlayer->GetPlayerState() != PlayerState::IDLE && CurPlayer->GetPlayerState() != PlayerState::EQUIPWEAPON)
	{
		return;
	}

	if (isAiming == true && GameEngineInput::IsPress("Shoot") == true)
	{
		return;
	}

	if (isShoot == true)
	{
		return;
	}

	if (isBazOn == true && isAiming == false)
	{
		isAiming = true;
		TimeCount = 0;
	}

	//에임조준 에니메이션이 시작되면, 방향키를 통해 각도조절 가능
	else if (isAiming == true)
	{		
		float Angle = ShootDir.GetAnagleDeg();

        AimingLine->On();
        AimingLine->SetPosition(CurPlayer->GetPos() + ShootDir * 150.0f);

		if (ShootDir.x > 0 && Angle > 270)
		{
			Angle = Angle - 360;
		}

		else if (ShootDir.x < 0)
		{
			Angle = 180 - Angle;
		}

		Bazindex = static_cast<int>(Angle / 5 + 15);

		if (Bazindex < 0)
		{
			Bazindex = 0;
		}

		if(Bazindex == CurIndex)
		{
			CurPlayer->ChangePlayerAnimation("BazookaAim", Bazindex);
		}

		else if (Bazindex > CurIndex)
		{
            IndexTimeCount += TimeCount;

			if (IndexTimeCount >= 0.01f)
			{
				++CurIndex;
                CurPlayer->ChangePlayerAnimation("BazookaAim", CurIndex);
                IndexTimeCount = 0;
			}
		}
		else if (Bazindex < CurIndex)
		{
            IndexTimeCount += TimeCount;

			if (IndexTimeCount >= 0.01f)
			{
				--CurIndex;
                CurPlayer->ChangePlayerAnimation("BazookaAim", CurIndex);
                IndexTimeCount = 0;
			}
		}
	}

	if (GameEngineInput::IsDown("MoveRight") || GameEngineInput::IsDown("MoveLeft"))
	{
		isAiming = false;
		isBazOn = false;
		CurIndex = 16;
        Bazindex = 16;

        ShootDir = CurPlayer->GetPlayerDir();
	}
}


void WeaponBazooka::ChargingRenderOn()
{
    if (ChargingGage->GetFrame() == 15)
    {
        return;
    }

	float4 PlayerPos = CurPlayer->GetPos();

	float4 StartPos = PlayerPos + float4{ ShootDir.x * 5, ShootDir.y * 5 } + float4{ 0, -8 };
    float4 Dir = CurPlayer->GetPlayerDir();

    ChargingTimeCount += TimeCount;
	
	if (ChargingTimeCount > 0.08)
	{
        ChargingGage->On();
        ChargingGage->SetFrame(CountingIndex); 
        ChargingGage->SetPosition(StartPos + float4{ ShootDir.x * 2, ShootDir.y * 2 });
        ChargingGage->SetAngle(-ShootDir.GetAnagleDeg() - 90);
        ChargingTimeCount = 0;

		CountingIndex++;
	}

}

void WeaponBazooka::ChargingRenderOff()
{
    CountingIndex = 0;
    ChargingTimeCount = 0;

    ChargingGage->Off();
}

void WeaponBazooka::DamageToPlayer()
{
	std::vector<GameEngineCollision*> CollisionPlayer;

    MapModifier::MainModifier->SetModifierColScale({ BombScale, BombScale });
    GameEngineCollision* HoleCollision = MapModifier::MainModifier->GetModifierCollision();

    AttackPlayer(HoleCollision);
}

void WeaponBazooka::MakeSmoke()
{
    SmokeTimeCount += TimeCount;

	if (SmokeTimeCount > 0.1)
	{

		float4 BaZooka = WeaponRender->GetActorPlusPos();

		GameEngineRender* Smoke = CreateRender("BazSmoke.bmp", static_cast<int>(WormsRenderOrder::Weapon));
		Smoke->SetPosition(BaZooka + float4{0, -15});
		Smoke->SetScale({ 60, 60 });
		Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "BazSmoke.bmp", .Start = 0, .End = 63, .InterTime = 0.0001f , .Loop = false });
		Smoke->ChangeAnimation("Smoke");

        SmokeTimeCount = 0;
	}
}


void WeaponBazooka::Timer()
{
    CurTime = static_cast<float>(clock());
    TimeCount = (CurTime - PrevTime) / 1000;
    PrevTime = CurTime;
}

void WeaponBazooka::DebrisAnimation(float _DeltaTime)
{
    if (isDebrisSet == false)
    {
        for (int i = 0; i < Sparks.size(); i++)
        {
            float X = GameEngineRandom::MainRandom.RandomFloat(-20, 20);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-20, 20);

            Sparks[i]->SetPosition(WeaponRender->GetPosition() + float4{ X,Y });
            Sparks[i]->ChangeAnimation("Spark");
            Sparks[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SparksDir.push_back(Dir);
        }

        for (int i = 0; i < Smokes.size(); i++)
        {
            float X = GameEngineRandom::MainRandom.RandomFloat(-40, 40);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-40, 40);

            Smokes[i]->SetPosition(WeaponRender->GetPosition() + float4{ X,Y });
            Smokes[i]->ChangeAnimation("Smoke");
            Smokes[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SmokesDir.push_back(Dir);
        }

        isDebrisSet = true;
    }
    else
    {
        for (int i = 0; i < Sparks.size(); i++)
        {
            Sparks[i]->SetMove(SparksDir[i] * 150.0f * _DeltaTime + float4{0, DebrisGravity} *_DeltaTime);
        }

        DebrisGravity += 250.0f * _DeltaTime;

        for (int i = 0; i < Smokes.size(); i++)
        {
            if (Smokes[i]->IsAnimationEnd() == true)
            {
                Smokes[i]->Off();
            }
        }
    }
}

void WeaponBazooka::DebrisInit()
{
    for (int i = 0; i < 9; i++)
    {
        GameEngineRender* Smoke = CreateRender("Smoke100.bmp", WormsRenderOrder::Weapon);
        Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "Smoke100.bmp", .Start = 0, .End = 27, .InterTime = 0.03f , .Loop = false });
        Smoke->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Smoke100.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Smoke->SetScale({ 134, 134 });
        Smoke->Off();

        Smokes.push_back(Smoke);
    }
    
    for (int i = 0; i < 10; i++)
    {
        GameEngineRender* Spark = CreateRender("Spark1.bmp", WormsRenderOrder::Weapon);
        Spark->CreateAnimation({ .AnimationName = "Spark", .ImageName = "Spark1.bmp", .Start = 0, .End = 31, .InterTime = 0.05f , .Loop = false });
        Spark->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Spark1.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Spark->SetScale({ 60, 60 });
        Spark->Off();

        Sparks.push_back(Spark);
    }
}

void WeaponBazooka::ExplosionAnimationOff()
{
    if (ExplosionCircle->IsAnimationEnd() == true)
    {
        ExplosionCircle->ChangeAnimation("Idle");
        ExplosionCircle->Off();
    }
    if (ExplosionElipse->IsAnimationEnd() == true)
    {
        ExplosionElipse->ChangeAnimation("Idle");
        ExplosionElipse->Off();
    }

    if (PootTextAnimation->IsAnimationEnd() == true)
    {
        PootTextAnimation->ChangeAnimation("Idle");
        PootTextAnimation->Off();
    }
}

void WeaponBazooka::CameraUpdate(float _DeltaTime)
{
    if (isShoot == true)
    {
        GetLevel()->SetCameraPos(WeaponRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());
    }

    if (isExplosion == false && isAttack == true)
    {
        CameraTimeCount += TimeCount;

        if (CameraTimeCount >= 3.0f && fLerpRatio < 1)
        {
            CurPlayerPos = CurPlayer->GetPos();
            PrevCamPos = GetLevel()->GetCameraPos();
            fLerpRatio += _DeltaTime * fLerpSpeed;
            GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
        }

        if (fLerpRatio >= 1)
        {
            isWeaponDone = true;
        }
    }
}