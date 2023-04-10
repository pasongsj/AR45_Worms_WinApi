#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include <vector>
#include <list>

// Ό³Έν :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;
    void SoundLoad();
    
protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}
    virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	

private:
	GameEngineRender* AnimationBodyRender = nullptr;
};

