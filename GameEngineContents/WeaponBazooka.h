#pragma once
#include <vector>
#include "Weapon.h"

class MapModifier;
class WeaponBazooka : public Weapon
{

public:	

	WeaponBazooka();
	~WeaponBazooka();

	void WeaponBazookaInit();

	void BazookaOn();				//changeAnimation
	void BazAiming();

	void ChargingRenderOn();
	void ChargingRenderOff();

	void MakeSmoke();			//날라갈 때 무기 뒤에 스모크

	void Charging();			
	void firing(float _DeltaTime);
	void Explosion();

    void Timer();

	void DamageToPlayer();
    
    void ExplosionAnimationOff();

    void DebrisAnimation(float _DeltaTime);
    void DebrisInit();

    void CameraUpdate(float _DeltaTime);

	WeaponBazooka(const WeaponBazooka& _Other) = delete;
	WeaponBazooka(WeaponBazooka&& _Other) noexcept = delete;
	WeaponBazooka& operator=(const WeaponBazooka& _Other) = delete;
	WeaponBazooka& operator=(WeaponBazooka&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void ResetWeapon();
private:
	GameEngineRender* shell = nullptr; //포탄 (투사체)

    //렌더, 애니메이션 

	GameEngineRender* ChargingGage = nullptr;

    std::vector<GameEngineRender*> Sparks;
    std::vector<GameEngineRender*> Smokes;

    std::vector<float4> SparksDir;
    std::vector<float4> SmokesDir;

    bool isDebrisSet = false;
    float DebrisGravity = false;

    //기능
	bool isExplosion = false;
	bool isBazOn = false;

	bool isSet = false;

	bool isFire = false;
	bool isAiming = false;
	bool isAttack = false;

	bool isEndBazOn = false;
    bool isTimeSet = false;

    float CurTime = 0.0f;
    float PrevTime = 0.0f;

    float TimeCount = 0.0f;

    float IndexTimeCount = 0.0f;
    float ChargingTimeCount = 0.0f;
    float SmokeTimeCount = 0.0f;
    float CameraTimeCount = 0.0f;

	int Bazindex = 0;
	int CurIndex = 16;

	int CountingIndex = 0;

	float4 ShootDir = { 0,0 };

	float4 StartDir = { 0,0 };

    float4 CurPos = { 0,0 };
    float4 NextPos = { 0,0 };

	Player* PrevPlayer = nullptr;



	float4 PrevCamPos = float4::Zero;
	float4 CurPlayerPos = float4::Zero;
	float4 LerpCamPos = float4::Zero;
	float fLerpRatio = 0.f;
	float fLerpSpeed = 2.f;

	GameEngineRender* WeaponRender = nullptr;		//렌더
	GameEngineCollision* WeaponCollision = nullptr;	//콜리전
};

