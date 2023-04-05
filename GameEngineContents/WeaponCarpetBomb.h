#pragma once
#include "Weapon.h"

class WeaponCarpetBomb : public Weapon
{

public:

    struct Carpet{
        GameEngineRender* CarpetRender = nullptr;
        GameEngineCollision* CarpeCollisionList = nullptr;

        float4 CurPos = { 0,0 };
        float4 NextPos = { 0,0 };
        float4 Dir = { 0, 0 };
    };

	WeaponCarpetBomb();
	~WeaponCarpetBomb();

	WeaponCarpetBomb(const WeaponCarpetBomb& _Other) = delete;
	WeaponCarpetBomb(WeaponCarpetBomb&& _Other) noexcept = delete;
	WeaponCarpetBomb& operator=(const WeaponCarpetBomb& _Other) = delete;
	WeaponCarpetBomb& operator=(WeaponCarpetBomb&& _Other) noexcept = delete;

protected:

private:

    std::vector<Carpet*> CarpetList;
};

