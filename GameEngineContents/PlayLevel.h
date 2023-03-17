#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <vector>

// Ό³Έν :
class Player;
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}

private:
	int iPlayerNumber = -1;
	Player* pCurPlayer = nullptr;
	std::vector<Player*> vecAllPlayer;
	bool bFreeCamMove = false;

	float4 ScreenSize = float4::Zero;
	void SoundLoad();
	void ImageLoad();
};

