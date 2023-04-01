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

    int NumOfPetrol = 0;

    float Scale = 100.0f;
    float Gravity = 900.0f;
    float MoveSpeed = 5.0f;
    float WaitTime = 1.5f;
    float LiveTime = 7.0f;

    float4 Dir = float4::Zero;
    float4 MoveDir = float4::Zero;

    std::vector<bool> AllPetrolGroundcheck;
    std::vector<GameEngineRender*> AllPetrol;
    std::vector<float4> AllPetrolPos;


    bool IsGroundCheck(float4 _Pos);

    void GravityApplied(float _DeltaTime);
    float4 PullUp(float4 _NextPos, float4 _CurPos, float _DeltaTime);

    void CreateFireEffect(float _DeltaTime);

    bool IsAllGroundCheck();
};

