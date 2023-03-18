#pragma once
#include "Weapon.h"

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


	void SetAngle();
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

	void ResetWeapon(float _DeltaTime) override;
private:
	GameEngineRender* shell = nullptr; //Æ÷Åº (Åõ»çÃ¼)

	bool isBazOn = false;
	bool isSet = false;
	bool isFire = false;
	bool isAiming = false;

	int Bazindex = 0;
	float4 ShootDir = { 0,0 };

	float4 StartDir = { 0,0 };
};

