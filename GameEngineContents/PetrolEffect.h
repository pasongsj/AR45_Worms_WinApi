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

private:
    bool IsJump = false;
    bool IsDamageToDrum = false;
    bool IsWindEffectEnd = false;


    float Gravity = 900.0f;
    float MoveSpeed = 5.0f;
    float WaitTime = 0.3f;
    float LiveTime = 2.0f;

    float4 Dir = float4::Zero;
    float4 MoveDir = float4::Zero;


  

    void IsWallCheck(float4 _Pos);
    bool IsGroundCheck(float4 _Pos);

    void GravityApplied(float _DeltaTime);
    float4 PullUp(float4 _NextPos,  float _DeltaTime);

    void CreateFireEffect(float _DeltaTime);
   
    void HitDrumCheck();


    GameEngineRender* PetrolRender = nullptr;
    GameEngineCollision* PetrolCol = nullptr;


};



