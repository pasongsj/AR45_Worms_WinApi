#pragma once
#include "Weapon.h"

// 설명 : F3-4 Minigun 미니건 : 미니건을 사용하면 3프레임마다 1발씩 20발의 총알을 연속적으로 발사합니다.
class MapModifier;
class WeaponMinigun : public Weapon
{
public:
	// constrcuter destructer
	WeaponMinigun();
	~WeaponMinigun();

	// delete Function
	WeaponMinigun(const WeaponMinigun& _Other) = delete;
	WeaponMinigun(WeaponMinigun&& _Other) noexcept = delete;
	WeaponMinigun& operator=(const WeaponMinigun& _Other) = delete;
	WeaponMinigun& operator=(WeaponMinigun&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	int BulletCount = 20;
	float DelayTime = 0.05f;
    float WaitingTime = 1.5f;
    bool isExplosion = false;

	GameEngineRender* AimingLine = nullptr;
	std::vector <GameEngineCollision*> MinigunCollision;							// index에 해당하는 총알 콜리전
	std::vector<bool> isShooted;			//수정 필요								// index에 해당하는 총알이 발사되었는지

	bool IsDone();
	void WeaponMinigunInit();														// 총알 추가
	void Firing(float _DeltaTime);
	void CheckFiring();

    float AimIndex = 15;
    int NextAimIndex = 15;
    void SetAimFrameIndex();

    bool isIsFireAnimationDone = false;
    void Aiming(float _DeltaTime);

};

