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

}

void WeaponBazooka::Render(float _DeltaTime)
{

}

void WeaponBazooka::WeaponBazookaInit()
{
	SetWeaponRender(CreateRender("Waepon1.bmp", static_cast<int>(WormsRenderOrder::Weapon)));
	SetWeaponCollision(CreateCollision(static_cast<int>(WormsRenderOrder::Weapon)));
}