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
    bool IsGravityOff = false;
    bool IsJump = false;
    bool IsWindEffectEnd = false;
    bool IsBlowOut = false;
  
    float JumpPower = -150.0f;
    float Gravity = 500.0f;
    float MoveSpeed = 150.0f;
    float WaitTime = 0.2f;
    float LiveTime = 2.0f;

    float4 MoveDir = float4::Zero;

    GameEngineRender* PetrolRender = nullptr;
    GameEngineCollision* PetrolCol = nullptr;

    bool IsGroundCheck(float4 _Pos);

    void CreateFireEffect(float _DeltaTime);
   
    void HitDrumCheck();
};



