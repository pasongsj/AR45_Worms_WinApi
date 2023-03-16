#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float FreeSpeed = 500.0f;				//FreeMove 스피드

	GameEngineRender* MapRender0 = nullptr;

	//카메라를 자유롭게 움직임
	bool FreeMoveState(float _DeltaTime);
};

