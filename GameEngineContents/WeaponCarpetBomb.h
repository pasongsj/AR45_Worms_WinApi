#pragma once
#include "Weapon.h"

class WeaponCarpetBomb : public Weapon
{

public:

    struct Carpet
    {
        GameEngineRender* CarpetRender = nullptr;
        GameEngineCollision* CarpetCollision = nullptr;

        float4 CurPos = { 0,0 };
        float4 PrevPos = { 0,0 };
        float4 MoveDir = { 0, 0 };
        float4 RotDir = { 0, 0 };

        float MoveSpeed = 600.0f;
        float Gravity = 1.5f;
        float GravityAccel = 25.0f;
        float Wind = 0.0f;

        int BounceCount = 3;

        float CollisionCount = 0.0f;
    };

	WeaponCarpetBomb();
	~WeaponCarpetBomb();

	WeaponCarpetBomb(const WeaponCarpetBomb& _Other) = delete;
	WeaponCarpetBomb(WeaponCarpetBomb&& _Other) noexcept = delete;
	WeaponCarpetBomb& operator=(const WeaponCarpetBomb& _Other) = delete;
	WeaponCarpetBomb& operator=(WeaponCarpetBomb&& _Other) noexcept = delete;


protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _DeltaTime) override;
private:
    void CarpetInit();
    void SetTruck();
    void SetTarget();
    void MarkerInit();
    void Firing(float _DeltaTime);
    void TruckMove(float _DeltaTime);
    void DropCarpet(float _DeltaTime);
    void Explosion(Carpet* _Carpet);
    void SetCarpet();
    void ExplosionAnimation(float4 _Pos);
    void CameraUpdate();
    void Timer();
    void DamageToPlayer(int _Index);
    
    void MakeSmoke(float4 _pos);
    void MakeSpark(float4 _pos);
    void SparkMove(float _DeltaTime);

    std::vector<Carpet*> CarpetList;

    GameEngineRender* TruckRender = nullptr;
    GameEngineRender* Marker = nullptr;

    float4 TargetPos = { 0,0 };
    float4 TruckStartPos = { 0,0 };

    float CurTime = 0.0f;
    float PrevTime = 0.0f;
    float TimeCount = 0.0f;

    float TurnChangeCount = 0.0f;

    bool isMoveRight = false;
    bool isHideTruck = false;
    bool isCarpetSet = false;

    bool isTruckSoundOn = false;

    int ExplosionEndCount = 0;

    int CarpetNum = 5;

    std::vector<GameEngineRender*> SparkList;
    std::vector<float> GravityList;
    std::vector<float4> DirList;
};

