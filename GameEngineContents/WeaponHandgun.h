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

	void ResetWeapon() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void Render(float _DeltaTime) override;

private:

	int BulletCount = 6;
	bool isFire = false;

	float DelayTime = 0.5f;

	std::vector <GameEngineCollision*> HandgunCollision;							// index에 해당하는 총알 콜리전
	//std::vector <float4> HandgunDir;		//수정필요								// index에 해당하는 총알 발사 방향

	std::vector<bool> isShooted;			//수정 필요								// index에 해당하는 총알이 발사되었는지

	void WeaponHandgunInit();														// 총알 추가
	//void WeaponMove(GameEngineCollision* _Col, float _DeltaTime, float4 _Dir);		// 총알 이동
	void Firing(float _DeltaTime);
	void CheckFiring();

	bool IsDone();

};

