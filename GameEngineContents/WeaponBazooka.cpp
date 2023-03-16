#include "WeaponBazooka.h"
#include "ContentsEnums.h"

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


	WeaponRender->SetPosition({ 500, 500 });
	WeaponRender->SetScale({150, 150});

	EffectGravity = true;
	Gravity = 10.0f;
}

void WeaponBazooka::firing(float _DeltaTime)
{
	float4 Dir = { 10, (- 1 - Gravity) };
	Dir.Normalize();
	Gravity -= 5.0f * _DeltaTime;
	WeaponRender->SetMove(Dir * 100.0f * _DeltaTime);
}