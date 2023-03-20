#include "WeaponSheep.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineImage.h>

WeaponSheep::WeaponSheep()
{
}

WeaponSheep::~WeaponSheep()
{
}

void WeaponSheep::Start()
{
	WeaponSheepInit();
}

void WeaponSheep::Update(float _DeltaTime)
{				
	SheepFalling(_DeltaTime);
	SheepWalking(_DeltaTime);
}		
		
void WeaponSheep::Render(float _DeltaTime)
{			
			
}			
			
void WeaponSheep::ResetWeapon()
{

}

void WeaponSheep::WeaponSheepInit()
{
	SetCurPlayer();

	WeaponRender = CreateRender("SheepWalk.bmp", static_cast<int>(WormsRenderOrder::Weapon));
	WeaponCollision = CreateCollision(static_cast<int>(WormsCollisionOrder::Weapon));

	//WeaponRender->SetRotFilter("bazookaRot.bmp");

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

	SetPos({ 500, 0 });

	WeaponRender->SetPosition({0, -10});
	WeaponRender->SetScale({ 60, 60 });
	WeaponRender->Off();

	WeaponCollision->SetPosition(WeaponRender->GetPosition());
	WeaponCollision->SetScale(WeaponRender->GetScale());
	WeaponCollision->Off();

	WeaponName = "Sheep";

	//SheepExplosion = GetLevel()->CreateActor<MapModifier>();

	WeaponRender->CreateAnimation({ .AnimationName = "SheepMove", .ImageName = "SheepWalk.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	//ExplosionAnimation = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
	//ExplosionAnimation->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End = 8, .InterTime = 0.03f , .Loop = false });
	//ExplosionAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
	//ExplosionAnimation->SetScale({ 100, 100 });
	//ExplosionAnimation->Off();

	Gravity = 0.0f; //임시 설정값
	GravityAccel = 0.0f; //임시 설정값

	MoveSpeed = 1500.0f; //임시 설정값

	EffectGravity = true;
	isAnimation = true;
	isBlocked = true;
	//isTarget = false;

	TimeCount = 0;
}

void WeaponSheep::SheepFalling(float _DeltaTime)
{
	if (isSheepOn == false)
	{
		//WeaponRender->SetPosition(CurPlayer->GetPos());
		WeaponRender->ChangeAnimation("SheepMove");
		WeaponRender->On();
		isSheepOn = true;
	}


	if (RGB(0, 0, 255) != MapCollision->GetPixelColor(GetPos() + float4::Down, RGB(0, 0, 255)))
	{
		MoveDir += float4::Down * 20.0f * _DeltaTime + float4{0, Gravity};
		Gravity += 2.0f * _DeltaTime;
	}
	else
	{
		MoveDir += float4::Up * 20.0f *  _DeltaTime;
	}	

	SetMove(MoveDir);

	MoveDir = float4::Zero;
}

void WeaponSheep::SheepWalking(float _DeltaTime)
{

}