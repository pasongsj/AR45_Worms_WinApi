#pragma once
#include "Weapon.h"

class WeaponShotgun : public Weapon
{
public:
	// constrcuter destructer
	WeaponShotgun() ;
	~WeaponShotgun();

	// delete Function
	WeaponShotgun(const WeaponShotgun& _Other) = delete;
	WeaponShotgun(WeaponShotgun&& _Other) noexcept = delete;
	WeaponShotgun& operator=(const WeaponShotgun& _Other) = delete;
	WeaponShotgun& operator=(WeaponShotgun&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:


	int BulletCount = 2;


	GameEngineRender* BombRender = nullptr;
	GameEngineCollision* BombCollision = nullptr;


	void WeaponShotgunInit();
	void WeaponMove(float _DeltaTime);

	bool CheckCollision();
};

