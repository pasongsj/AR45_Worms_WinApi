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

    void TorchTimerOn();

    float TorchTime = 5.0f;

    bool isAttack = false;
    bool isFireEnd = false;

    float TorchCurTime = 0.0f;
    float TorchPrevTime = 0.0f;
    bool TorchTimeSet = false;

    float4 StartPos = { 0, 0 };
};

