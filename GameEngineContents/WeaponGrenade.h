#pragma once
#include "Weapon.h"

// 설명 : F2-1 Grenade 수류탄
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
	
	void ResetWeapon();

protected:

	void Start() override;
	void Update(float _DeltaTime) override;



private:

	void WeaponGrenadeInit();

	bool isExplosion = false;

	void SetCharge(); // charge
	void Firing(float _DeltaTime);

    GameEngineRender* AimingLine = nullptr;

	GameEngineRender* WeaponRender = nullptr;		//렌더
	GameEngineCollision* WeaponCollision = nullptr;	//콜리전

    //렌더, 애니메이션 
    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineRender* PootTextAnimation = nullptr;



    float AimIndex = 15;
    int NextAimIndex = 15;
    void SetAimFrameIndex();

};

