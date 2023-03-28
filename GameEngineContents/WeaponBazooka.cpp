#include "WeaponBazooka.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"

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
		ExplosionCircle->ChangeAnimation("Idle");
		ExplosionCircle->Off();

		isEndBazOn = false;
		isExplosion = false;

		TimeCount = 0;
		fLerpRatio = 0;
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

	if (isFire == true)
	{
		GetLevel()->SetCameraPos(WeaponRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());
		MakeSmoke();
	}

	if (isExplosion == false && isAttack == true)
	{
		TimeCounting();
		if (TimeCount >= 3.0f && fLerpRatio < 1)
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

void WeaponBazooka::Render(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ChangePlayer"))
	{
		CurPlayer->ChangePlayerAnimation("BazookaOff");
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
	
	BombScale = 50;
	Dmg = 50;

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

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

	ExplosionCircle = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
	ExplosionCircle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End =  8, .InterTime = 0.05f , .Loop =false });
	ExplosionCircle->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End =  1, .InterTime = 0.05f , .Loop =false });
	ExplosionCircle->SetScale({ 100, 100 });

    ExplosionCircle->ChangeAnimation("Idle");
	ExplosionCircle->Off();

    ExplosionElipse = CreateRender("Elipse50.bmp", WormsRenderOrder::Weapon);
    ExplosionElipse->CreateAnimation({ .AnimationName = "ExplosionElipse", .ImageName = "Elipse50.bmp", .Start = 0, .End = 19, .InterTime = 0.03f , .Loop = false });
    ExplosionElipse->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Elipse50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionElipse->SetScale({ 150, 150 });

    ExplosionElipse->ChangeAnimation("Idle");
    ExplosionElipse->Off();

    PootTextAnimation = CreateRender("Poot.bmp", WormsRenderOrder::Weapon);
    PootTextAnimation->CreateAnimation({ .AnimationName = "Poot", .ImageName = "Poot.bmp", .Start = 0, .End = 17, .InterTime = 0.02f , .Loop = false });
    PootTextAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Poot.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    PootTextAnimation->SetScale({ 70, 70 });

    PootTextAnimation->ChangeAnimation("Idle");
    PootTextAnimation->Off();

    DebrisInit();

	Gravity = 20.0f; //임시 설정값

	MoveSpeed = 0.0f; //임시 설정값


	TimeCount = 0;

	std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);
	
	ChargingRenderInit();
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
		/* timer 로 시간을 재고, 시간에 맞게 차징정도를 설정 ( 0 ~ 1 까지 시간비례 ) => ( 차징정도 = 현재차징시간 / 최대차징시간 ) */
		/* 차지가 길게 될수록 발사 거리가 길어짐 (발사속도가 빨라짐) */
   		CurPlayer->SetCanIMove(false);
		ChargingRenderOn();


		MoveSpeed = 300 + GetChargeTime() * 1000.0f;

		//Charge 로 바꿔야함
		if (MoveSpeed < 300)
		{
			MoveSpeed = 300;
		}
		else if (MoveSpeed > 2000)
		{
			MoveSpeed = 2000;
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
		CurPlayer->ChangePlayerAnimation("BazookaOff");
		ChargingRenderOff();
		isFire = true;
	}

	if (isFire == false)
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

    CurPos = WeaponRender->GetPosition();
    NextPos = CurPos + (Dir * MoveSpeed + float4{0, Gravity}) * _DeltaTime;

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
	if (CheckCollision(WeaponCollision) == false /*발사되었는지 아닌지도 bool값으로 만들어서 조건에 넣어야함*/)
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

        MapModifier::MainModifier->CreateHole(WeaponRender->GetPosition(), BombScale);

        DebrisAnimation(0.0f);

		isAttack = true;
		isExplosion = true;


		DamageToPlayer();
	}
}

void WeaponBazooka::ChangeBazReadyAnimation()
{

}

void WeaponBazooka::BazookaOn()
{
	if ((CurPlayer->GetPlayerState() == PlayerState::IDLE || CurPlayer->GetPlayerState() == PlayerState::EQUIPWEAPON )&& isBazOn == false)
	{
		TimeCounting();
	}

	if (isBazOn == false && isAttack == false)
	{
		TimeCount = 0;
		isBazOn = true;
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
	isFire = false;
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

	if (isFire == true)
	{
		return;
	}

	if (isBazOn == true && CurPlayer->IsPlayerAnimationEnd() == true && isAiming == false)
	{
			isAiming = true;
			CurPlayer->ChangePlayerAnimation("BazookaAim", Bazindex);
			TimeCount = 0;
	}

	//에임조준 에니메이션이 시작되면, 방향키를 통해 각도조절 가능
	else if (isAiming == true)
	{		
		float Angle = ShootDir.GetAnagleDeg();

		if (ShootDir.x > 0 && Angle > 270)
		{
			Angle = Angle - 360;
		}

		else if (ShootDir.x < 0)
		{
			Angle = 180 - Angle;
		}

		Bazindex = Angle / 5 + 15;

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
			TimeCounting();

			if (TimeCount_3 >= 0.01f)
			{
				++CurIndex;
                CurPlayer->ChangePlayerAnimation("BazookaAim", CurIndex);
                TimeCount_3 = 0;
			}
		}
		else if (Bazindex < CurIndex)
		{
			TimeCounting();

			if (TimeCount_3 >= 0.01f)
			{
				--CurIndex;
                CurPlayer->ChangePlayerAnimation("BazookaAim", CurIndex);
                TimeCount_3 = 0;
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

void WeaponBazooka::ChargingRenderInit()
{
	ChargingRender.resize(16);
	size_t Size = ChargingRender.size();

	for (int i = 0; i < Size; i++)
	{
		ChargingRender[i] = CreateRender("Charging.bmp", WormsRenderOrder::Weapon);
		ChargingRender[i]->SetFrame(i);
		ChargingRender[i]->SetScale({ 64, 64 });
		ChargingRender[i]->Off();
	}
}

void WeaponBazooka::ChargingRenderOn()
{
	if (CountingIndex >= ChargingRender.size())
	{
		return;
	}

	size_t Size = ChargingRender.size();
	float4 PlayerPos = CurPlayer->GetPos();

	float4 StartPos = PlayerPos + float4{ ShootDir.x * 5, ShootDir.y * 5 } + float4{ 0, -8 };
	
	TimeCounting();
	
	if (TimeCount_2 > 0.05)
	{
		ChargingRender[CountingIndex]->SetPosition(StartPos + float4{ ShootDir.x * 4 * (CountingIndex + 1), ShootDir.y * 4 * (CountingIndex + 1) });
		ChargingRender[CountingIndex]->On();

		TimeCount_2 = 0;

		CountingIndex++;
	}


}

void WeaponBazooka::ChargingRenderOff()
{
	CountingIndex = 0;
	TimeCount_2 = 0;
	size_t Size = ChargingRender.size();

	for (int i = 0; i < Size; i++)
	{
		ChargingRender[i]->Off();
	}
}


void WeaponBazooka::DamageToPlayer()
{
	std::vector<GameEngineCollision*> CollisionPlayer;
    GameEngineCollision* HoleCollision = MapModifier::MainModifier->GetModifierCollision();

	if (true == HoleCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionPlayer))
	{
		for (int i = 0; i < CollisionPlayer.size(); i++)
		{
			dynamic_cast<Player*>(CollisionPlayer[i]->GetActor())->Damaged(Dmg);
		}
	}
}

void WeaponBazooka::MakeSmoke()
{
	TimeCounting();

	if (TimeCount > 0.03)
	{
		float4 BaZooka = WeaponRender->GetActorPlusPos();

		GameEngineRender* Smoke = CreateRender("BazSmoke.bmp", static_cast<int>(WormsRenderOrder::Weapon));
		Smoke->SetPosition(BaZooka + float4{0, -15});
		Smoke->SetScale({ 60, 60 });
		Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "BazSmoke.bmp", .Start = 0, .End = 63, .InterTime = 0.0001f , .Loop = false });
		Smoke->ChangeAnimation("Smoke");

		TimeCount = 0;
	}
}

void WeaponBazooka::TimeCounting()
{
    if (isTimeSet = false)
    {
        PrevTime = clock();
        isTimeSet = true;
    }

    CurTime = clock();

    TimeCount += (CurTime - PrevTime) / 1000;
    TimeCount_2 += (CurTime - PrevTime) / 1000;
    TimeCount_3 += (CurTime - PrevTime) / 1000;

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
            //Smokes[i]->SetMove(SmokesDir[i] * 25.0f * _DeltaTime);
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
        Spark->CreateAnimation({ .AnimationName = "Spark", .ImageName = "Spark1.bmp", .Start = 0, .End = 31, .InterTime = 0.1f , .Loop = false });
        Spark->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Spark1.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Spark->SetScale({ 60, 60 });
        Spark->Off();

        Sparks.push_back(Spark);
    }
}