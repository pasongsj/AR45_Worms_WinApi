#pragma once
#include "MapObject.h"

// Ό³Έν : Oil Effect
class PetrolEffect :public MapObject
{
public:
	// constrcuter destructer
	PetrolEffect();
	~PetrolEffect();

	// delete Function
	PetrolEffect(const PetrolEffect& _Other) = delete;
	PetrolEffect(PetrolEffect&& _Other) noexcept = delete;
	PetrolEffect& operator=(const PetrolEffect& _Other) = delete;
	PetrolEffect& operator=(PetrolEffect&& _Other) noexcept = delete;

    void CreatePetrolEffect(int _NumOfPetrol, float4 _StartPos);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

    void GravityApplied(float _DeltaTime) override;
    float4 PullUp(float4 _NextPos,  float _DeltaTime) override;
private:
    bool IsJump = false;
    bool IsWindEffectEnd = false;
  

    float Gravity = 900.0f;
    float MoveSpeed = 5.0f;
    float WaitTime = 0.2f;
    float LiveTime = 1.5f;

    float4 MoveDir = float4::Zero;

    GameEngineRender* PetrolRender = nullptr;
    GameEngineCollision* PetrolCol = nullptr;

    void IsWallCheck(float4 _Pos);
    bool IsGroundCheck(float4 _Pos);


    void CreateFireEffect(float _DeltaTime);
   
    void HitDrumCheck();
};



