#include "WeaponBazooka.h"
#include "ContentsEnums.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
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
}

void WeaponBazooka::Update(float _DeltaTime)
{

	firing(_DeltaTime);
}

void WeaponBazooka::Render(float _DeltaTime)
{

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

	Gravity = 100.0f; //임시 설정값
	GravityAccel = 0.0f; //임시 설정값

	MoveSpeed = 400.0f; //임시 설정값

	EffectGravity = true;
	isAnimation = true;
	isBlocked = true;
	isTarget = false;

	CreatePlayerAnimation();						
}

void WeaponBazooka::CreatePlayerAnimation()
{
	//플레이어를 받아와서 렌더에 애니메이션 추가
}

bool WeaponBazooka::CheckCollision()
{
	if (WeaponCollision != nullptr && true == WeaponCollision->Collision({ .TargetGroup = static_cast<int>(WormsRenderOrder::Player), .TargetColType = CollisionType::CT_Rect, .ThisColType = CollisionType::CT_CirCle }))
	{
		return true;
	}
	else
	{
		return false;
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

	if (isEndCharging() == true)
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
				break;
			}
		}
		WeaponRender->On();
		WeaponCollision->On();
		isSet = true;
	}

	Gravity += GravityAccel * _DeltaTime;
	GravityAccel += 150.0f * _DeltaTime;
	
	Dir = { 50, -150 + Gravity }; // 다른 함수를 통해, 최초 발사 각도를 저장한 후 Y축에 +Gravity 를 프레임마다 해줌으로써 천천히 우(좌)하향하게 만든다 
	Dir.Normalize();

	WeaponRender->SetAngle(-Dir.GetAnagleDeg() - 45);
	WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);

	if (RGB(0, 0, 255) == MapCollision->GetPixelColor(WeaponRender->GetActorPlusPos(), RGB(0, 0, 255))) //맵에 닿으면 사라짐
	{

		Gravity = 100.0f; //임시 설정값
		GravityAccel = 0.0f; //임시 설정값
		WeaponRender->Off();
		WeaponCollision->Off();
		isFire =false;
		isSet = false;
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