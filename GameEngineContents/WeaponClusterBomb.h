#pragma once
#include "Weapon.h"
#include <GameEngineCore/NumberRenderObject.h>

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
    // 발사전
    float AimIndex = 17;
    int NextAimIndex = 16;

    //발사 후
    bool isExplosion = false; // MainBomb 폭발체크
    bool isPress = false;
    int MainBombScale = 104;

    //클러스터
    float ClusterSpeed = 100.0f; // 클러스터 폭탄 Speed
    bool isClusterFire = false;
    bool isClusterExplosion = false;
    float WaitTime = 0.0f;

    // 에임 조준선
    GameEngineRender* AimingLine = nullptr;
    // 차지 애니메이션
    GameEngineRender* ChargeAnimation = nullptr;

    // 메인 폭탄 이미지랜더, 콜리전
    GameEngineRender* WeaponRender = nullptr;		        //렌더
    GameEngineCollision* WeaponCollision = nullptr;	        //콜리전
    GameEngineCollision* NextPosCheckCollision = nullptr;


    //클러스터
    std::vector<GameEngineRender*> ClusterRender;           // 잔여 클러스터 랜더
    std::vector<GameEngineCollision*> ClusterCollision;     // 잔여 클러스터 콜리전
    std::vector<float4> ClusterDir;
    std::vector<float4> ClusterSmokeInterval;

    //타이머 랜더
    GameEngineRender* TimerRenderBack = nullptr;
    NumberRenderObject TimerRender;


    // 폭발 애니메이션 랜더 
    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineRender* BiffTextAnimation = nullptr;
    GameEngineRender* PowTextAnimation = nullptr;

    void WeaponClusterBombInit();   // 시작 시 폭탄 이미지 설정함수

    void SetAimFrameIndex();        // 현재 각도에 맞는 Frame Index찾는 함수

    void SetCharge();               // 차지 게이지 설정

    void Aiming(float _DeltaTime);  // 조준에 맞는 설정 변경

    void Firing(float _DeltaTime);   // 발사에 맞는 설정 변경

    void CheckAnimationDone();          // 폭발 애니메이션 랜더 끄기


    void ClusterFiring(float _DeltaTime);   // Cluster발사

    void ClusterOn(float4 _Pos);            // ClusterRender모두 On

    void ClusterOff();                      // ClusterRender모두 Off

    bool isDone();                          // MainBomb가 터지고, 모든 Cluster 가 터졌는지

    //float4 CulWindMoveVec(float _DeltaTime); //바람 추가 

    void MakeSmoke();                       // 클러스터
    
    void CheckTimer(float _DeltaTime);      // 타이머 폭발 체크
};

