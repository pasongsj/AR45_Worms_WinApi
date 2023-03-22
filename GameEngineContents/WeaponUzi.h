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
	void Render(float _DeltaTime) override;

private:

	int BulletCount = 10;
	bool isFire = false;

	float DelayTime = 0.1f;

	std::vector <GameEngineCollision*> UziCollision;							// index에 해당하는 총알 콜리전
	//std::vector <float4> UziDir;		//수정필요								// index에 해당하는 총알 발사 방향
	GameEngineRender* AimingLine = nullptr;

	std::vector<bool> isShooted;			//수정 필요								// index에 해당하는 총알이 발사되었는지

	void WeaponUziInit();														// 총알 추가
	//void WeaponMove(GameEngineCollision* _Col, float _DeltaTime, float4 _Dir);		// 총알 이동
	void Firing(float _DeltaTime);
	void CheckFiring();

	bool IsDone();
};

