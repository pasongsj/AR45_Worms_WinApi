#pragma once
#include "Weapon.h"

// 설명 : F4-1 Uzi 우지 : 직접 위쪽으로 펀치를 날리며 땅을 잘라냅니다
class WeaponFirePunch : public Weapon
{
public:
	// constrcuter destructer
	WeaponFirePunch() ;
	~WeaponFirePunch();

	// delete Function
	WeaponFirePunch(const WeaponFirePunch& _Other) = delete;
	WeaponFirePunch(WeaponFirePunch&& _Other) noexcept = delete;
	WeaponFirePunch& operator=(const WeaponFirePunch& _Other) = delete;
	WeaponFirePunch& operator=(WeaponFirePunch&& _Other) noexcept = delete;

protected:

    void Start() override;
    void Update(float _DeltaTime) override;

private:

    bool isAfterAnimation = false;
    bool isCharging = false;

    float4 StartPos = float4::Zero;

    float EffectTimer = 0.05f;
    GameEngineCollision* PunchCollision = nullptr;
};

