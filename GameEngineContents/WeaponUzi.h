#pragma once
#include "Weapon.h"

// 설명 : F3-3 Uzi 우지 : 6프레임마다 1발씩 빠르게 연속해서 10발의 총알을 발사합니다
class MapModifier;
class WeaponUzi : public Weapon
{
public:
	// constrcuter destructer
	WeaponUzi();
	~WeaponUzi();

	// delete Function
	WeaponUzi(const WeaponUzi& _Other) = delete;
	WeaponUzi(WeaponUzi&& _Other) noexcept = delete;
	WeaponUzi& operator=(const WeaponUzi& _Other) = delete;
	WeaponUzi& operator=(WeaponUzi&& _Other) noexcept = delete;

	void ResetWeapon();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	int BulletCount = 10;
	float DelayTime = 0.1f;

	GameEngineRender* AimingLine = nullptr;
	std::vector <GameEngineCollision*> UziCollision;							// index에 해당하는 총알 콜리전
	std::vector<bool> isShooted;			//수정 필요								// index에 해당하는 총알이 발사되었는지



	bool IsDone();
	void WeaponUziInit();														// 총알 추가
	void Firing(float _DeltaTime);
	void CheckFiring();

};

