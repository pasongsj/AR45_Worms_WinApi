#pragma once
#include <vector>
#include "Weapon.h"

class MapModifier;
class WeaponAirStrike : public Weapon
{

public:

	WeaponAirStrike();
	~WeaponAirStrike();

	WeaponAirStrike(const WeaponAirStrike& _Other) = delete;
	WeaponAirStrike(WeaponAirStrike&& _Other) noexcept = delete;
	WeaponAirStrike& operator=(const WeaponAirStrike& _Other) = delete;
	WeaponAirStrike& operator=(WeaponAirStrike&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	void WeaponAirStrikeInit();
	void SetAirPlanePos();
	void AirPlaneMove(float _DeltaTime);
	void Attack(float _DeltaTime);
	void Firing(float _DeltaTime);
	void SetMissiles();
	void Explosion();
	void CameraUpdate(float _DeltaTime);

    void DamageToPlayer();

    void DebrisAnimation(float _DeltaTime);
    void DebrisSet(int MissileIndex);
    void DebrisInit();

    void ExplosionEffectInit();
    void ExplosionAnimation(int _Index);
    void ExplosionAnimationOff();

    void MarkerInit();

    void TimeCounting();

    bool isTimeSet = false;

    float CurTime = 0.0f;
    float PrevTime = 0.0f;
    float TimeCount = 0.0f;

	GameEngineRender* Airplane = nullptr;

    //렌더, 애니메이션 
    std::vector<GameEngineRender*> ExplosionCircleList;
    std::vector<GameEngineRender*> ExplosionElipseList;
    std::vector<GameEngineRender*> PootTextAnimationList;

    std::vector<GameEngineRender*> Sparks;
    std::vector<GameEngineRender*> Smokes;

    std::vector<float4> SparksDir;
    std::vector<float4> SmokesDir;

    std::vector<bool> isDebrisSetList;

    bool isDebrisSet = false;
    std::vector<float> DebrisGravityList;

	float4 AirPlaneStartPos = { 0,0 };
	float4 TargetPos = { 0,0 };

	float4 PrevPos = { 0,0 };
	float4 CurPos = { 0,0 };

	bool isMoveRight = 0;
	bool isHideAirPlane = false;
    
    int MissileNum = 0;

    GameEngineRender* Marker = nullptr;

	float4 MiddleMissileStartPos = { 0,0 };

	std::vector<GameEngineRender*> MissileList;
	std::vector<GameEngineCollision*> MissileCollisionList;
};

