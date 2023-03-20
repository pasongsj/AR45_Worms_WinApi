#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <vector>

// Ό³Έν :
class Player;
class TestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}

private:
	int iPlayerNumber = -1;
	Player* pCurPlayer = nullptr;
	std::vector<Player*> vecAllPlayer;


	bool bCamMove = false;
	float4 PrevCamPos = float4::Zero;
	float4 CurPlayerPos = float4::Zero;
	float4 LerpCamPos = float4::Zero;
	float fLerpRatio = 0.f;
	float fCamMoveSpeed = 500.f;

	float4 ScreenSize = float4::Zero;
	void SoundLoad();
	void ImageLoad();
	void KeyLoad();

	void PlayerChange(float _DeltaTime);
	void MoveCamForMouse(float _DeltaTime);

};

