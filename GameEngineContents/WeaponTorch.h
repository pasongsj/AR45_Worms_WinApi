#pragma once
#include <vector>

#include "Weapon.h"

class MapModifier;
class WeaponTorch : public Weapon
{

public:

	WeaponTorch();
	~WeaponTorch();

	WeaponTorch(const WeaponTorch& _Other) = delete;
	WeaponTorch(WeaponTorch&& _Other) noexcept = delete;
	WeaponTorch& operator=(const WeaponTorch& _Other) = delete;
	WeaponTorch& operator=(WeaponTorch&& _Other) noexcept = delete;

protected:

    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _DeltaTime) override;

private:
    void TorchInit();
    void TorchOn();

    bool isAttack = false;
};

