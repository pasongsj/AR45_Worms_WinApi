#pragma once
#include "Weapon.h"

// 설명 : F3-1 Shotgun 샷건
class MapModifier;
class WeaponShotgun : public Weapon
{
public:
	// constrcuter destructer
	WeaponShotgun() ;
	~WeaponShotgun();

	// delete Function
	WeaponShotgun(const WeaponShotgun& _Other) = delete;
	WeaponShotgun(WeaponShotgun&& _Other) noexcept = delete;
	WeaponShotgun& operator=(const WeaponShotgun& _Other) = delete;
	WeaponShotgun& operator=(WeaponShotgun&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:

	int BulletCount = 2;
    float AimIndex = 17;
    int NextAimIndex = 16;
    bool isExplosion = false;


    float LoadDelay = 0.0f;
    float WaitingTime = 0.0f;

	GameEngineRender* AimingLine = nullptr;

	std::vector <GameEngineCollision*> ShotGunCollision;							// index에 해당하는 총알 콜리전
	std::vector <float4> ShotGunDir;												// index에 해당하는 총알 발사 방향
	std::vector<bool> isShooted;													// index에 해당하는 총알이 발사되었는지



	bool IsDone();
	void WeaponShotgunInit();														// 총알 추가
	void Firing(float _DeltaTime);	
	void CheckFiring();
    void SetAimFrameIndex();

    void Aiming(float _DeltaTime);


};

