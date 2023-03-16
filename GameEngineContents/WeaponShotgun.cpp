#include "WeaponShotgun.h"

WeaponShotgun::WeaponShotgun()
{
}

WeaponShotgun::~WeaponShotgun()
{
}

void WeaponShotgun::Start()
{
	WeaponBazookaInit();
}
void WeaponShotgun::Update(float _DeltaTime)
{
	if (nullptr == GetWeaponRender)
	{
		WeaponBazookaInit();
	}

}
void WeaponShotgun::Render(float _DeltaTime)
{

}

void WeaponShotgun::WeaponBazookaInit()
{
	GameEngineRender* Render = GetWeaponRender();


	GameEngineRender* Render = GetWeaponRender();

}