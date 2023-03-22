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
	CreatePlayerAnimation();
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

	if (isExplosion == true && ExplosionAnimation->IsAnimationEnd() == true)
	{
		ExplosionAnimation->ChangeAnimation("Idle");
		ExplosionAnimation->Off();

		isEndBazOn = false;
		isExplosion = false;

		TimeCount = 0;
		fLerpRatio = 0;
	}

	if (isFire == true)
	{
		GetLevel()->SetCameraPos(WeaponRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());
		MakeSmoke();
	}

	if (isExplosion == false && isAttack == true)
	{
		TimeCounting();
		if (TimeCount >= 1.0f && fLerpRatio < 1)
		{
			CurPlayerPos = CurPlayer->GetPos();
			PrevCamPos = GetLevel()->GetCameraPos();
			fLerpRatio += _DeltaTime * fLerpSpeed;
			GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
		}

		if (fLerpRatio >= 1)
		{
			CurPlayer->ChangePlayerAnimation("BazOff");
		}
	}
}

void WeaponBazooka::Render(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ChangePlayer"))
	{
		CurPlayer->ChangePlayerAnimation("BazOff");
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

	WeaponName = "Bazooka";

	ExplosionAnimation = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
	ExplosionAnimation->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End =  8, .InterTime = 0.03f , .Loop =false });
	ExplosionAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End =  0, .InterTime = 0.05f , .Loop =false });
	ExplosionAnimation->SetScale({ 100, 100 });
	ExplosionAnimation->Off();

	Gravity = 10.0f; //임시 설정값

	MoveSpeed = 0.0f; //임시 설정값


	TimeCount = 0;

	std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);
	
	ChargingRenderInit();
	//플레이어 바뀔 때마다 CurPlayer 바꿔서 저장
	SetCurPlayer();
}

void WeaponBazooka::CreatePlayerAnimation()
{
	std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

	for (int i = 0; i < PlayerList.size(); i++)
	{
		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Left_bazAim", "bazAimLeft.bmp", 0, 31, 0.1f, false);
		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Right_bazAim", "bazAimRight.bmp", 0, 31, 0.1f, false);

		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Left_bazOff", "bazOffLeft.bmp", 0, 6, 0.05f, false);
		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Right_bazOff", "bazOffRight.bmp", 0, 6, 0.05f, false);

		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Left_bazOn", "bazOnLeft.bmp", 0, 7, 0.05f, false);
		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Right_bazOn", "bazOnRight.bmp", 0, 7, 0.05f, false);
	}
}


void WeaponBazooka::Charging() // 딱 Charging기능만으로 분리
{
	if (CurPlayer->GetPlayerState() != PlayerState::IDLE)
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
		CurPlayer->SetPlayerAnimationFrame(Bazindex);

		MoveSpeed = 100 + GetChargeTime() * 1000.0f;
		
		//Charge 로 바꿔야함
		if (MoveSpeed < 100)
		{
			MoveSpeed = 100;
		}
		else if (MoveSpeed > 900)
		{
			MoveSpeed = 900;
		}
	}
}

void WeaponBazooka::firing(float _DeltaTime) //발사
{
	if (GameEngineInput::IsKey("Shoot") == false)
	{
		return;
	}

	if (CurPlayer->GetPlayerState() != PlayerState::IDLE)
	{
		return;
	}

	if (isAiming == true && isEndCharging() == true)
	{
		CurPlayer->ChangePlayerAnimation("BazOff");
		ChargingRenderOff();
		isFire = true;
	}

	if (isFire == false)
	{
		return;
	}

	std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

	if (isSet == false)
	{

		for (int i = 0; i < PlayerList.size(); i++)
		{
			if (true == dynamic_cast<Player*>(PlayerList[i])->GetIsMyTurn())
			{
				WeaponRender->SetPosition(PlayerList[i]->GetPos() + ShootDir * 30);
				WeaponCollision->SetPosition(PlayerList[i]->GetPos() + ShootDir * 30);
				break;
			}
		}

		Dir = ShootDir;

		WeaponRender->On();
		WeaponCollision->On();
		isSet = true;
	}

	Gravity += 0.05f * _DeltaTime;
	
	float4 NextPos;

	Dir += {Dir.x, Dir.y + Gravity};
	Dir.Normalize();

	WeaponRender->SetAngle(-Dir.GetAnagleDeg());
	WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);
	WeaponCollision->SetMove(Dir * MoveSpeed * _DeltaTime);

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
		ExplosionAnimation->SetPosition(WeaponRender->GetPosition());
		ExplosionAnimation->On();
		ExplosionAnimation->ChangeAnimation("Explosion", 0);
		
		MapModifier::MainModifier->CreateHole(WeaponRender->GetPosition(), BombScale);

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
	if (CurPlayer->GetPlayerState() == PlayerState::IDLE && isBazOn == false)
	{
		TimeCounting();
	}

	if (TimeCount >= 0.2f && isBazOn == false && isAttack == false)
	{
		CurPlayer->ChangePlayerAnimation("BazOn");
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
	if (CurPlayer->GetPlayerState() != PlayerState::IDLE)
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


	//바주카를 꺼내는 모션이 끝나고 0.5초뒤에 에임조준 애니메이션으로 변경
	if (isBazOn == true && CurPlayer->IsPlayerAnimationEnd() == true && isAiming == false)
	{
			isAiming = true;
			CurPlayer->ChangePlayerAnimation("bazAim", CurIndex);
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
			CurPlayer->SetPlayerAnimationFrame(Bazindex);
		}

		else if (Bazindex > CurIndex)
		{
			TimeCounting();

			if (TimeCount >= 0.01f)
			{
				++CurIndex;
				CurPlayer->SetPlayerAnimationFrame(CurIndex);
				TimeCount = 0;
			}
		}
		else if (Bazindex < CurIndex)
		{
			TimeCounting();

			if (TimeCount >= 0.01f)
			{
				--CurIndex;
				CurPlayer->SetPlayerAnimationFrame(CurIndex);
				TimeCount = 0;
			}
		}
	}

	if (GameEngineInput::IsDown("MoveRight") || GameEngineInput::IsDown("MoveLeft"))
	{
		isAiming = false;
		isBazOn = false;
		CurIndex = 16;
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

	//웨폰콜리전이 아니라, Hole의 콜리전이 필요함
	if (true == WeaponCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionPlayer))
	{
		for (int i = 0; i < CollisionPlayer.size(); i++)
		{
			dynamic_cast<Player*>(CollisionPlayer[i]->GetActor())->GetDamaged(Dmg);
		}
	}
}

void WeaponBazooka::MakeSmoke()
{
	TimeCounting();

	if (TimeCount > 0.03)
	{
		float4 BaZooka = WeaponRender->GetActorPlusPos();

		for (int i = 0; i < 8; i++)
		{
			float X = GameEngineRandom::MainRandom.RandomFloat(-5, 5);
			float Y = GameEngineRandom::MainRandom.RandomFloat(-5, 5);

			GameEngineRender* Smoke = CreateRender("BazSmoke.bmp", static_cast<int>(WormsRenderOrder::Weapon));
			Smoke->SetPosition(BaZooka + -ShootDir * float4{X, Y} + float4{0, -15});
			Smoke->SetScale({ 60, 60 });
			Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "BazSmoke.bmp", .Start = 0, .End = 63, .InterTime = 0.01f , .Loop = false });
			Smoke->ChangeAnimation("Smoke");
		}

		TimeCount = 0;
	}
}