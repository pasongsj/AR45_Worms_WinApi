#pragma once
#include <vector>
#include "Weapon.h"

class MapModifier;
class WeaponBazooka : public Weapon
{

public:	

	WeaponBazooka();
	~WeaponBazooka();

	void WeaponBazookaInit();
	void CreatePlayerAnimation();

	void ChangeBazReadyAnimation();
	void BazookaOn();
	void BazookaOff();
	void BazAiming();

	void ChargingRenderInit();
	void ChargingRenderOn();
	void ChargingRenderOff();

	void Charging();
	void firing(float _DeltaTime);
	void Explosion();

	WeaponBazooka(const WeaponBazooka& _Other) = delete;
	WeaponBazooka(WeaponBazooka&& _Other) noexcept = delete;
	WeaponBazooka& operator=(const WeaponBazooka& _Other) = delete;
	WeaponBazooka& operator=(WeaponBazooka&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void ResetWeapon() override;
private:
	GameEngineRender* shell = nullptr; //Æ÷Åº (Åõ»çÃ¼)

	//MapModifier* BazookaExplosion = nullptr;
	GameEngineRender* ExplosionAnimation = nullptr;

	bool isExplosion = false;
	bool isBazOn = false;
	bool isSet = false;
	bool isFire = false;
	bool isAiming = false;
	bool isAttack = false;

	bool isEndBazOn = false;

	int Bazindex = 0;
	int CurIndex = 16;

	int CountingIndex = 0;

	float4 ShootDir = { 0,0 };

	float4 StartDir = { 0,0 };

	Player* PrevPlayer = nullptr;

	std::vector< GameEngineRender*> ChargingRender;
};

