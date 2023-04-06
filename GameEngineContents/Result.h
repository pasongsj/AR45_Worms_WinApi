#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class GameEngineRender;
class Result : public GameEngineActor
{
public:
	// constrcuter destructer
	Result();
	~Result();

	// delete Function
	Result(const Result& _Other) = delete;
	Result(Result&& _Other) noexcept = delete;
	Result& operator=(const Result& _Other) = delete;
	Result& operator=(Result&& _Other) noexcept = delete;

protected:
    void Start() override;

    void Update(float _DeltaTime)override;

private: 
    GameEngineRender* pWin = nullptr;
    GameEngineRender* pDraw = nullptr;

};

