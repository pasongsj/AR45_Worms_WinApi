#include "WeaponBazooka.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

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
	firing(_DeltaTime);
	BazookaOn();
	BazAiming();

	if (isExplosion == true && ExplosionAnimation->IsAnimationEnd() == true)
	{
		ExplosionAnimation->ChangeAnimation("Idle");
		ExplosionAnimation->Off();

		CurPlayer->ChangePlayerAnimation("BazOff");
		isExplosion = false;
	}
}

void WeaponBazooka::Render(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ChangePlayer"))
	{
		CurPlayer->ChangePlayerAnimation("BazOff");
		ResetWeapon();
		isAttack = false;
	}
	//HDC _hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	//Rectangle(_hdc, static_cast<int>(WeaponCollision->GetActorPlusPos().x) - static_cast<int>(WeaponCollision->GetScale().hx()) - static_cast<int>(GetLevel()->GetCameraPos().x),
	//				static_cast<int>(WeaponCollision->GetActorPlusPos().y) - static_cast<int>(WeaponCollision->GetScale().hy()) - static_cast<int>(GetLevel()->GetCameraPos().y),
	//				static_cast<int>(WeaponCollision->GetActorPlusPos().x) + static_cast<int>(WeaponCollision->GetScale().hx()) - static_cast<int>(GetLevel()->GetCameraPos().x),
	//				static_cast<int>(WeaponCollision->GetActorPlusPos().y) + static_cast<int>(WeaponCollision->GetScale().hy()) - static_cast<int>(GetLevel()->GetCameraPos().y));
}

void WeaponBazooka::WeaponBazookaInit()
{
	WeaponRender =  CreateRender("bazooka.bmp", static_cast<int>(WormsRenderOrder::Weapon));
	WeaponCollision = CreateCollision(static_cast<int>(WormsCollisionOrder::Weapon));

	WeaponRender->SetRotFilter("bazookaRot.bmp");

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

	WeaponRender->SetPosition({ 500, 200 }); //임시 설정값
	WeaponRender->SetScaleToImage(); //임시 설정값
	WeaponRender->Off();

	WeaponCollision->SetPosition(WeaponRender->GetPosition());
	WeaponCollision->SetScale(WeaponRender->GetScale());
	WeaponCollision->Off();

	WeaponName = "Bazooka";

	BazookaExplosion = GetLevel()->CreateActor<MapModifier>();
	BazookaExplosion->SetRadius(50);

	ExplosionAnimation = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
	ExplosionAnimation->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End =  8, .InterTime = 0.03f , .Loop =false });
	ExplosionAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End =  0, .InterTime = 0.05f , .Loop =false });
	ExplosionAnimation->SetScale({ 100, 100 });
	ExplosionAnimation->Off();

	Gravity = 0.0f; //임시 설정값
	GravityAccel = 0.0f; //임시 설정값

	MoveSpeed = 1500.0f; //임시 설정값

	EffectGravity = true;
	isAnimation = true;
	isBlocked = true;
	isTarget = false;

	TimeCount = 0;

	std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

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

		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Left_bazOff", "bazOffLeft.bmp", 0, 6, 0.1f, false);
		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Right_bazOff", "bazOffRight.bmp", 0, 6, 0.1f, false);

		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Left_bazOn", "bazOnLeft.bmp", 0, 7, 0.075f, false);
		dynamic_cast<Player*>(PlayerList[i])->CreatePlayerAnimation("Right_bazOn", "bazOnRight.bmp", 0, 7, 0.075f, false);
	}
}


void WeaponBazooka::Charging()
{
	if (/* isPress(스페이스바) == true */ true)
	{
		/* timer 로 시간을 재고, 시간에 맞게 차징정도를 설정 ( 0 ~ 1 까지 시간비례 ) => ( 차징정도 = 현재차징시간 / 최대차징시간 ) */
		/* 차지가 길게 될수록 발사 거리가 길어짐 (발사속도가 빨라짐) */
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
				WeaponRender->SetPosition(PlayerList[i]->GetPos());
				WeaponCollision->SetPosition(PlayerList[i]->GetPos());
				break;
			}
		}

		Dir = ShootDir;

		WeaponRender->On();
		WeaponCollision->On();
		isSet = true;
	}

	Gravity = 0.005f;

	Dir += {Dir.x, Dir.y + Gravity};
	Dir.Normalize();

	WeaponRender->SetAngle(-Dir.GetAnagleDeg() - 45);
	WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);
	WeaponCollision->SetMove(Dir * MoveSpeed * _DeltaTime);

	if (CheckCollision() == true)
	{
		Explosion();
		ResetWeapon();
	}
}

void WeaponBazooka::Explosion() //폭발
{
	if (CheckCollision() == false /*발사되었는지 아닌지도 bool값으로 만들어서 조건에 넣어야함*/)
	{
		return;
	}

	else
	{
		//Dmg만큼 Player의 HP가 감소, 폭발반경의 맵이 깎여야함, 넉백이 있을 수도, 
		ExplosionAnimation->SetPosition(WeaponRender->GetPosition());
		ExplosionAnimation->On();
		ExplosionAnimation->ChangeAnimation("Explosion", 0);

		BazookaExplosion->SetPos(WeaponRender->GetPosition());
		BazookaExplosion->CreateHole();

		isAttack = true;
		isExplosion = true;
	}
}

void WeaponBazooka::SetAngle()
{
	if (/*플레이어가 이동중이라면*/ true)
	{
		return;
	}
	else if (/*플레이어가 이동을 멈췄다면*/ true)
	{
		//바주카를 꺼내는 모션으로 애니메이션을 변경
	}

	if (/*바주카를 꺼내는 모션을 모두 끝냈다면(isAnimationEnd) */ true)
	{
		//키입력을 받아 위아래로 각도를 조절 Dir에 각도를 넣는다.
		//각도가 변하면서 Dir의 좌표값이 변하고, Dir - PlayerPos 해서 방향벡터를 구한다음 Normalize
	}
}

void WeaponBazooka::ChangeBazReadyAnimation()
{

}

void WeaponBazooka::BazookaOn()
{
	if (CurPlayer->GetPlayerState() == PlayerState::IDLE && isBazOn == false && isAttack == false)
	{
		TimeCounting();
	}

	if (TimeCount >= 1.0f && isBazOn == false)
	{
		CurPlayer->ChangePlayerAnimation("BazOn");
		TimeCount = 0;
		isBazOn = true;
	}

}

void WeaponBazooka::ResetWeapon()
{
	std::vector<GameEngineActor*> PlayerList = GetLevel()->GetActors(WormsRenderOrder::Player);

	//플레이어 바뀔 때마다 CurPlayer 바꿔서 저장
	SetCurPlayer();

	//위치 재설정
	WeaponRender->SetPosition(CurPlayer->GetPos());
	WeaponCollision->SetPosition(CurPlayer->GetPos());

	Gravity = 0.0f; //임시 설정값
	GravityAccel = 0.0f; //임시 설정값
	WeaponRender->Off();
	WeaponCollision->Off();

	isBazOn = false;
	isSet = false;
	isFire = false;
	isAiming = false;

	Bazindex = 0;

	ShootDir = { 0,0 };
	StartDir = { 0,0 };
}

void WeaponBazooka::BazAiming()
{
	if (CurPlayer->GetPlayerState() != PlayerState::IDLE)
	{
		return;
	}

	if (isBazOn == true && CurPlayer->IsPlayerAnimationEnd() == true && isAiming == false)
	{
		TimeCounting();
		CurPlayer->SetPlayerAnimationFrame(6);

		if (TimeCount > 0.5f) 
		{
			isAiming = true;
			CurPlayer->ChangePlayerAnimation("bazAim", CurIndex);
			TimeCount = 0;
		}
	}

	else if (isAiming == true)
	{
		ShootDir = GetShootDir();
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

