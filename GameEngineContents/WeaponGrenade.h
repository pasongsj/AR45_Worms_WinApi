#pragma once
#include "Weapon.h"

// ¼³¸í : F2-1 Grenade ¼ö·ùÅº
class MapModifier;
class WeaponGrenade : public Weapon
{
public:
	// constrcuter destructer
	WeaponGrenade();
	~WeaponGrenade();

	// delete Function
	WeaponGrenade(const WeaponGrenade& _Other) = delete;
	WeaponGrenade(WeaponGrenade&& _Other) noexcept = delete;
	WeaponGrenade& operator=(const WeaponGrenade& _Other) = delete;
	WeaponGrenade& operator=(WeaponGrenade&& _Other) noexcept = delete;
	
	void ResetWeapon() override;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;



private:

	void WeaponGrenadeInit();
	void FindCurPlayer();
	bool isFire = false;
	//MapModifier* Explosion = nullptr;
};

