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

	void ChangeBazReadyAnimation();


	void BazookaOn();				//changeAnimation
	void BazookaOff();
	void BazAiming();

	void ChargingRenderInit();	//조준선 랜더
	void ChargingRenderOn();
	void ChargingRenderOff();

	void MakeSmoke();			//날라갈 때 무기 뒤에 스모크

	void Charging();			
	void firing(float _DeltaTime);
	void Explosion();
    void TimeCounting();
	void DamageToPlayer();

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

	//MapModifier* BazookaExplosion = nullptr;
	GameEngineRender* ExplosionAnimation = nullptr;

	bool isExplosion = false;
	bool isBazOn = false;

	bool isSet = false;

	bool isFire = false;
	bool isAiming = false;
	bool isAttack = false;

	bool isEndBazOn = false;
    bool isTimeSet = false;

    float TimeCount = 0.0f;
    float TimeCount_2 = 0.0f;

	int Bazindex = 0;
	int CurIndex = 16;

	int CountingIndex = 0;

	float4 ShootDir = { 0,0 };

	float4 StartDir = { 0,0 };

    float4 CurPos = { 0,0 };
    float4 NextPos = { 0,0 };

	Player* PrevPlayer = nullptr;

	std::vector<GameEngineRender*> ChargingRender;


	float4 PrevCamPos = float4::Zero;
	float4 CurPlayerPos = float4::Zero;
	float4 LerpCamPos = float4::Zero;
	float fLerpRatio = 0.f;
	float fLerpSpeed = 2.f;
	GameEngineRender* WeaponRender = nullptr;		//렌더
	GameEngineCollision* WeaponCollision = nullptr;	//콜리전
};

