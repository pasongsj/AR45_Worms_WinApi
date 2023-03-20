#pragma once
#include <vector>
#include "Weapon.h"

class MapModifier;
class WeaponSheep : public Weapon
{

public:

	WeaponSheep();
	~WeaponSheep();

	void WeaponSheepInit();
	void SheepFalling(float _DeltaTime);
	void SheepWalking(float _DeltaTime);

	float4 PullUpSheep(float4 _NextPos, float _DeltaTime);

	WeaponSheep(const WeaponSheep& _Other) = delete;
	WeaponSheep(WeaponSheep&& _Other) noexcept = delete;
	WeaponSheep& operator=(const WeaponSheep& _Other) = delete;
	WeaponSheep& operator=(WeaponSheep&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void ResetWeapon() override;
private:
	MapModifier* SheepExplosion = nullptr;
	bool isSheepOn = false;

	float4 MoveDir = float4::Zero;
};

