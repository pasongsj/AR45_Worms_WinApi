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
    void TorchOn(float _DeltaTime);

    void Timer();

    float TorchTime = 0.0f;

    bool isAttack = false;
    bool isFireEnd = false;

    float TurnChangeCount = 0.0f;

    float CurTime = 0.0f;
    float PrevTime = 0.0f;

    float attackTimeCount = 0.0f;

    float TimeCount = 0.0f;

    float4 StartPos = { 0, 0 };

    int AniIndex = 0;
    float AniTimeCount = 0.0f;

    GameEngineCollision* HoleCollision = nullptr;
};

