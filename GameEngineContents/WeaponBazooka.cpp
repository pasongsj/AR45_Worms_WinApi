#include "WeaponBazooka.h"
#include "ContentsEnums.h"

#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>

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
	WeaponRender =  CreateRender("Weapon1.bmp", static_cast<int>(WormsRenderOrder::Weapon));
	WeaponCollision = CreateCollision(static_cast<int>(WormsRenderOrder::Weapon));

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

	WeaponRender->SetPosition({ 500, 200 }); //임시 설정값
	WeaponRender->SetScale({150, 150}); //임시 설정값

	WeaponName = "Bazooka";

	Gravity = 100.0f; //임시 설정값
	GravityAccel = 0.0f; //임시 설정값

	MoveSpeed = 400.0f; //임시 설정값

	EffectGravity = true;
	isAnimation = true;
	isBlocked = true;
	isTarget = false;


						
}

void WeaponBazooka::CreatePlayerAnimation()
{

}

void WeaponBazooka::firing(float _DeltaTime)
{
	Gravity += GravityAccel * _DeltaTime;
	GravityAccel += 150.0f * _DeltaTime;
	
	Dir = { 50, -150 + Gravity }; // 다른 함수를 통해, 최초 발사 각도를 저장한 후 Y축에 +Gravity 를 프레임마다 해줌으로써 천천히 우(좌)하향하게 만든다 
	Dir.Normalize();

	WeaponRender->SetMove(Dir * MoveSpeed * _DeltaTime);

	if (RGB(0, 0, 255) == MapCollision->GetPixelColor(WeaponRender->GetActorPlusPos(), RGB(0, 0, 255))) //맵에 닿으면 사라짐
	{
		WeaponRender->Off(); 
	}

}