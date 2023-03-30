#pragma once
#include "MapObject.h"

// 설명 :
class Drum : public MapObject
{
public:
	// constrcuter destructer
	Drum();
	~Drum();

	// delete Function
	Drum(const Drum& _Other) = delete;
	Drum(Drum&& _Other) noexcept = delete;
	Drum& operator=(const Drum& _Other) = delete;
	Drum& operator=(Drum&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    bool IsExplosion = false;

    int Gauge = 150;
    int Dmg = 25;
    int BombScale = 50;


    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineRender* PootTextAnimation = nullptr;
    
    void HitWeaponCheck();                      //Weapon의 폭발 영향권에 있을때 드럼통에 영향 적용
    void HitPlayerCheck();                      //플레이어에게 데미지 적용
    void AnimCheck();                           //애니메이션 체크 및 변경
    void Explosion();                           //폭발

    bool CheckCollision(GameEngineCollision* _Col);

    void CreateSpark();

    void ExplosionAnimationOff();
    void ExplosionEffectInit();
};

