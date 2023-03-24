#pragma once
#include <vector>
#include "Weapon.h"

class MapModifier;
class WeaponSheep : public Weapon
{

public:

	WeaponSheep();
	~WeaponSheep();

	WeaponSheep(const WeaponSheep& _Other) = delete;
	WeaponSheep(WeaponSheep&& _Other) noexcept = delete;
	WeaponSheep& operator=(const WeaponSheep& _Other) = delete;
	WeaponSheep& operator=(WeaponSheep&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void ResetWeapon();
private:

    void WeaponSheepInit();
    void SheepFalling(float _DeltaTime);
    void SheepWalking(float _DeltaTime);
    void CheckMoveAngle();
    bool CanIMove();
    void Explosion();
    void SheepJump(float _DeltaTime);

	MapModifier* SheepExplosion = nullptr;

	bool isSheepOn = false;
	bool isOnMap = false;
	bool isDirRight = false;
	bool isShoot = false;
	bool isJump = true;
	bool isJumpDirSet = false;
	bool isSet = false;

    int test = 0;

	float4 JumpDir = float4::Zero;
	float4 MoveDir = float4::Zero;

    float LeftMoveAngle = 0;
    float RightMoveAngle = 0;

    float JumpGravity = 0.0f;

	GameEngineRender* WeaponRender = nullptr;		//·»´õ
	GameEngineCollision* WeaponCollision = nullptr;	//ÄÝ¸®Àü
};

