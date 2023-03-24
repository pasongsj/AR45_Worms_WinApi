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
    void MarkerInit();
    void Aiming();
    void Charging();
    void Firing(float _DeltaTime);
    void Explosion();
    void CameraUpdate(float _DeltaTime);
    void TimeCounting(float* TimeCount);
    void DamageToPlayer();

    void ChargingRenderInit();
    void ChargingRenderOn();
    void ChargingRenderOff();

    bool isTimeSet = false;
    bool isHoming = false;
    bool isHomingSet = false;
    bool isAttack = false;
    bool isFire = false;
    bool isExplosion = false;
    bool isAiming = false;
    bool isAimSet = false;

    int AngleIndex = 16;
    int CurIndex = 16;

    float ChargingTimeCount = 0.0f;
    float CameraTimeCount = 0.0f;
    float4 PrevDir = { 0,0 };

    GameEngineRender* WeaponRender = nullptr;
    GameEngineCollision* WeaponCollision = nullptr;

    GameEngineRender* Marker = nullptr;


    std::vector<GameEngineRender*> ChargingRender;
    int CountingIndex = 0;

    float4 TargetPos = { 0, 0 };
    float Accel = 0;

    float PrevAngle = 0;
    float TargetAngle = 0;

    float TimeCount = 0;

    
};

