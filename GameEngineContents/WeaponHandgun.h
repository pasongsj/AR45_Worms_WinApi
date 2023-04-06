#pragma once
#include "Weapon.h"

// 설명 : F3-2 Handgun 권총 : 연속해서 6발을 발사합니다
class MapModifier;
class WeaponHandgun : public Weapon
{
public:
	// constrcuter destructer
	WeaponHandgun();
	~WeaponHandgun();

	// delete Function
	WeaponHandgun(const WeaponHandgun& _Other) = delete;
	WeaponHandgun(WeaponHandgun&& _Other) noexcept = delete;
	WeaponHandgun& operator=(const WeaponHandgun& _Other) = delete;
	WeaponHandgun& operator=(WeaponHandgun&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	int BulletCount = 6;
	float DelayTime = 0.0f;
    float WaitingTime = 1.5f;
    bool isExplosion = false;

	GameEngineRender* AimingLine = nullptr;
	std::vector <GameEngineCollision*> HandgunCollision;							// index에 해당하는 총알 콜리전
	std::vector<bool> isShooted;			//수정 필요								// index에 해당하는 총알이 발사되었는지

	bool IsDone();
	void WeaponHandgunInit();														// 총알 추가
	void Firing(float _DeltaTime);
	void CheckFiring();

    float AimIndex = 17;
    int NextAimIndex = 16;
    void SetAimFrameIndex();

    bool isIsFireAnimationDone = false;

    void Aiming(float _DeltaTime);

};

