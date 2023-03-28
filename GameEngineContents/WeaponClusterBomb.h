#pragma once
#include "Weapon.h"

// 설명 : F2-2 ClusterBomb 클러스터 폭탄 : 땅에 닿으면 폭발하는 클러스터가 방출된다

class WeaponClusterBomb : public Weapon
{
public:
	// constrcuter destructer
	WeaponClusterBomb() ;
	~WeaponClusterBomb();

	// delete Function
	WeaponClusterBomb(const WeaponClusterBomb& _Other) = delete;
	WeaponClusterBomb(WeaponClusterBomb&& _Other) noexcept = delete;
	WeaponClusterBomb& operator=(const WeaponClusterBomb& _Other) = delete;
	WeaponClusterBomb& operator=(WeaponClusterBomb&& _Other) noexcept = delete;

protected:

    void Start() override;
    void Update(float _DeltaTime) override;

private:

    void WeaponClusterBombInit();

    bool isExplosion = false;

    void SetCharge(); // charge
    void Firing(float _DeltaTime);
    void ResetWeapon();

    GameEngineRender* AimingLine = nullptr;

    GameEngineRender* WeaponRender = nullptr;		        //렌더
    GameEngineCollision* WeaponCollision = nullptr;	        //콜리전

    std::vector<GameEngineRender*> ClusterRender;           // 잔여 클러스터 랜더
    std::vector<GameEngineCollision*> ClusterCollision;     // 잔여 클러스터 콜리전
    std::vector<float4> ClusterDir;

    //렌더, 애니메이션 
    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineRender* BiffTextAnimation = nullptr;
    GameEngineRender* PootTextAnimation = nullptr;

    GameEngineRender* ChargeAnimation = nullptr;

    float ClusterSpeed = 100.0f;

    void ClusterFiring(float _DeltaTime);
    void ClusterOn(float4 _Pos);
    void ClusterOff();

    float4 DropDir = float4::Zero;
    bool isDone();


    float AimIndex = 15;
    int NextAimIndex = 15;
    void SetAimFrameIndex();
};

