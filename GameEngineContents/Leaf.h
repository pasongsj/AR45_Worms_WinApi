#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Leaf : public GameEngineActor
{
public:
	// constrcuter destructer
	Leaf();
	~Leaf();

	// delete Function
	Leaf(const Leaf& _Other) = delete;
	Leaf(Leaf&& _Other) noexcept = delete;
	Leaf& operator=(const Leaf& _Other) = delete;
	Leaf& operator=(Leaf&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float fGravity = 300.f;
	float fRandPower = 0.f;
	float4 MoveDir = float4::Zero;

};

