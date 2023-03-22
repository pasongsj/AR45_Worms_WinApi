#pragma once
#include "Weapon.h"

// 설명 : F2-2 ClusterBomb 클러스터 폭탄 : 땅에 닿으면 폭발하는 클러스터가 방출된다
class WeaponClusterBomb : public Weapon
{
public:
	// constrcuter destructer
	WeaponClusterBomb() ;
	~WeaponClusterBomb();

	// delete Function
	WeaponClusterBomb(const WeaponClusterBomb& _Other) = delete;
	WeaponClusterBomb(WeaponClusterBomb&& _Other) noexcept = delete;
	WeaponClusterBomb& operator=(const WeaponClusterBomb& _Other) = delete;
	WeaponClusterBomb& operator=(WeaponClusterBomb&& _Other) noexcept = delete;

protected:

    void Start() override;
    void Update(float _DeltaTime) override;

private:

    void WeaponClusterBombInit();

    bool isExplosion = false;

    void SetCharge(); // charge
    void Firing(float _DeltaTime);
    void ResetWeapon();

    GameEngineRender* WeaponRender = nullptr;		//렌더
    GameEngineCollision* WeaponCollision = nullptr;	//콜리전

};

