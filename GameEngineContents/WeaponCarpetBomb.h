#pragma once
#include "Weapon.h"

class WeaponCarpetBomb : public Weapon
{

public:

	WeaponCarpetBomb();
	~WeaponCarpetBomb();

	WeaponCarpetBomb(const WeaponCarpetBomb& _Other) = delete;
	WeaponCarpetBomb(WeaponCarpetBomb&& _Other) noexcept = delete;
	WeaponCarpetBomb& operator=(const WeaponCarpetBomb& _Other) = delete;
	WeaponCarpetBomb& operator=(WeaponCarpetBomb&& _Other) noexcept = delete;

protected:

private:

    std::vector<GameEngineRender*> CarpetList;
    std::vector<GameEngineCollision*> CarpeCollisionList;
};

