#pragma once
#include <GameEngineCore/GameEngineCore.h>

// Ό³Έν :
class WormsCore : public GameEngineCore
{
public:

	// delete Function
	WormsCore(const WormsCore& _Other) = delete;
	WormsCore(WormsCore&& _Other) noexcept = delete;
	WormsCore& operator=(const WormsCore& _Other) = delete;
	WormsCore& operator=(WormsCore&& _Other) noexcept = delete;
	static WormsCore* GetInst()
	{
		static WormsCore Inst;
		return &Inst;
	}


protected:
	void Start() override;
	void Update() override;
	void End() override;

private:
	// constrcuter destructer
	WormsCore();
	~WormsCore();
   
};

