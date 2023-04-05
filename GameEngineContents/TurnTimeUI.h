#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class Player;
class NumberRenderObject;
class TurnTimeUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TurnTimeUI();
	~TurnTimeUI();

	// delete Function
	TurnTimeUI(const TurnTimeUI& _Other) = delete;
	TurnTimeUI(TurnTimeUI&& _Other) noexcept = delete;
	TurnTimeUI& operator=(const TurnTimeUI& _Other) = delete;
	TurnTimeUI& operator=(TurnTimeUI&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;


private:
    NumberRenderObject pTimeRender;
    GameEngineRender* pTimeEdgeRender = nullptr;
    Player* pCurPlayer = nullptr;
    bool IsFire = false;
    float fTurnTime = 46.f;

    void CheckFire();
};

