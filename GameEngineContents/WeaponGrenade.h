#pragma once
#include "Weapon.h"
#include <GameEngineCore/NumberRenderObject.h>


// 설명 : F2-1 Grenade 수류탄
class MapModifier;

class WeaponGrenade : public Weapon
{
public:
	// constrcuter destructer
	WeaponGrenade();
	~WeaponGrenade();

	// delete Function
	WeaponGrenade(const WeaponGrenade& _Other) = delete;
	WeaponGrenade(WeaponGrenade&& _Other) noexcept = delete;
	WeaponGrenade& operator=(const WeaponGrenade& _Other) = delete;
	WeaponGrenade& operator=(WeaponGrenade&& _Other) noexcept = delete;
	
	void ResetWeapon();

protected:

	void Start() override;
	void Update(float _DeltaTime) override;



private:


	bool isExplosion = false;
    bool isPress = false;
    float AimIndex = 12;
    int NextAimIndex = 15;
    float WaitTime = 0.0f;

    // 에임 조준선
    GameEngineRender* AimingLine = nullptr;
    // 차지 애니메이션
    GameEngineRender* ChargeAnimation = nullptr;

    // 폭탄 이미지랜더, 콜리전
	GameEngineRender* WeaponRender = nullptr;		//렌더
	GameEngineCollision* WeaponCollision = nullptr;	//콜리전

    //타이머 랜더
    GameEngineRender* TimerRenderBack = nullptr;
    NumberRenderObject TimerRender;
    
    // 시작 시 폭탄 이미지 설정함수
	void WeaponGrenadeInit();

    // 현재 각도에 맞는 Frame Index찾는 함수
    void SetAimFrameIndex();

    // 차지 게이지 설정
	void SetCharge(); // charge
	
    // 조준에 맞는 설정 변경
    void Aiming(float _DeltaTime);
    
    // 발사에 맞는 설정 변경
    void Firing(float _DeltaTime);

    // 타이머 폭발 체크
    void CheckTimer(float _DeltaTime);

    //바람 추가
    //float4 CulWindMoveVec(float _DeltaTime);

    // 폭발 애니메이션 랜더 끄기
    void CheckExplosion();
};

