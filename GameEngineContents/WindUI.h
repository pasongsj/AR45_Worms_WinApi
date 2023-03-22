#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν :
class GameEngineRender;
class WindUI : public GameEngineActor
{
public:
	// constrcuter destructer
	WindUI();
	~WindUI();

	// delete Function
	WindUI(const WindUI& _Other) = delete;
	WindUI(WindUI&& _Other) noexcept = delete;
	WindUI& operator=(const WindUI& _Other) = delete;
	WindUI& operator=(WindUI&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Deltatime) override;


private:
    GameEngineRender* pLAnim = nullptr;
    GameEngineRender* pRAnim = nullptr;

};

