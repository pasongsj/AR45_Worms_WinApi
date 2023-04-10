#pragma once
#include "MapObject.h"

// 설명 :
class Drum : public MapObject
{
 public:
    static bool EffectEnd;
    static int Count;
public:
	// constrcuter destructer
	Drum();
	~Drum();

	// delete Function
	Drum(const Drum& _Other) = delete;
	Drum(Drum&& _Other) noexcept = delete;
	Drum& operator=(const Drum& _Other) = delete;
	Drum& operator=(Drum&& _Other) noexcept = delete;

    void DamageDrum(int _Value)
    {
        Gauge -= _Value;
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    bool IsExplosion = false;
    bool IsPetrolEffectOn = false;
    bool IsSoundOn = false;

    int Gauge = 150;
    int BombScale = 100;
    int NumOfPetrol = 0;                          //생성할 오일 입자 수

    float SoundWaitTime = 1.0f;
    float RangeX = 70.0f;                         //생성할 오일 입자의 x값 범위
    float MaxDmg = 50;
    float MinDmg = 20;
    float MinKnockBackPower = 35.0f;
    float MaxKnockBackPower = 75.0f;


    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineRender* PootTextAnimation = nullptr;
    
    void HitWeaponCheck();                          //Weapon의 폭발 영향권에 있을때 드럼통에 영향 적용
    void HitPlayerCheck();                          //플레이어와 충돌한 Modifier충돌체를 받아서 넘김
    void AttackPlayer(GameEngineCollision* _Col);   //플레이어에게 데미지 적용

    void Explosion();                               //폭발

    bool CheckCollision(GameEngineCollision* _Col);


    void AnimCheck();                               //애니메이션 체크 및 변경
    void ExplosionAnimationOff();
    void ExplosionEffectInit();

    void CreatePetrol(int _NumOfPetrol);            //오일 입자 생성
};

