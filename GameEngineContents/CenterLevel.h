#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CenterLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CenterLevel();
	~CenterLevel();

	// delete Function
	CenterLevel(const CenterLevel& _Other) = delete;
	CenterLevel(CenterLevel&& _Other) noexcept = delete;
	CenterLevel& operator=(const CenterLevel& _Other) = delete;
	CenterLevel& operator=(CenterLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;	

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}

private:
};

