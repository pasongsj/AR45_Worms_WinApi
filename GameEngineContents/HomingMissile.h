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
    void Timer();
    void DamageToPlayer();

    void MakeSmoke();

    void ChargingRenderInit();
    void ChargingRenderOn();
    void ChargingRenderOff();

    void DebrisInit();
    void DebrisAnimation(float _DeltaTime);

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

    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineRender* PootTextAnimation = nullptr;

    std::vector<GameEngineRender*> Sparks;
    std::vector<GameEngineRender*> Smokes;

    std::vector<float4> SparksDir;
    std::vector<float4> SmokesDir;

    bool isDebrisSet = false;
    float DebrisGravity = false;

    std::vector<GameEngineRender*> ChargingRender;
    int CountingIndex = 0;

    float4 TargetPos = { 0, 0 };
    float Accel = 0;

    float PrevAngle = 0;
    float TargetAngle = 0;

    float TimeCount = 0;

    float CurTime = 0.0f;
    float PrevTime = 0.0f;

    float AngleTimeCount = 0.0f;
    float SmokeTimeCount = 0.0f;

    
};

