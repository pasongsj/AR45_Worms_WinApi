#pragma once
#include "Weapon.h"
// Ό³Έν : F11-3 ΄η³ͺ±Ν
class WeaponDonkey :public Weapon
{
public:
	// constrcuter destructer
	WeaponDonkey() ;
	~WeaponDonkey();

	// delete Function
	WeaponDonkey(const WeaponDonkey& _Other) = delete;
	WeaponDonkey(WeaponDonkey&& _Other) noexcept = delete;
	WeaponDonkey& operator=(const WeaponDonkey& _Other) = delete;
	WeaponDonkey& operator=(WeaponDonkey&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    float4 TargetPos = { 0,0 };
    bool isSettedTarget = false;

    GameEngineRender* Marker = nullptr;

    GameEngineRender* DonkeyRender = nullptr;
    GameEngineCollision* DonkeyCollision = nullptr;


    void DonkeyInit();
    void MarkerInit();

    void SetTarget();

    void Firing(float _DeltaTime);
    void CheckAnimationDone();
};

