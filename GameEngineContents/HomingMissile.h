#pragma once
#include <vector>
#include "Weapon.h"

class MapModifier;
class HomingMissile : public Weapon
{

public:

	HomingMissile();
	~HomingMissile();

	HomingMissile(const HomingMissile& _Other) = delete;
	HomingMissile(HomingMissile&& _Other) noexcept = delete;
	HomingMissile& operator=(const HomingMissile& _Other) = delete;
	HomingMissile& operator=(HomingMissile&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _DeltaTime) override;

private:

    void HomingMissileInit();
    void Aiming();
    void Charging();
    void Firing(float _DeltaTime);
    void Explosion();

    bool isHoming = false;
    bool isHomingSet = false;
    bool isAttack = false;
    bool isFire = false;

    float4 PrevDir = { 0,0 };

    GameEngineRender* WeaponRender = nullptr;
    GameEngineCollision* WeaponCollision = nullptr;

    float4 TargetPos = { 0, 0 };
    float Accel = 0;

    float PrevAngle = 0;
    float TargetAngle = 0;
};

