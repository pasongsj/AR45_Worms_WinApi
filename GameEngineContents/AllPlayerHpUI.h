#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class AllPlayerHpUI : public GameEngineActor
{
public:
    static AllPlayerHpUI* AllHpUI;
	// constrcuter destructer
	AllPlayerHpUI();
	~AllPlayerHpUI();

	// delete Function
	AllPlayerHpUI(const AllPlayerHpUI& _Other) = delete;
	AllPlayerHpUI(AllPlayerHpUI&& _Other) noexcept = delete;
	AllPlayerHpUI& operator=(const AllPlayerHpUI& _Other) = delete;
	AllPlayerHpUI& operator=(AllPlayerHpUI&& _Other) noexcept = delete;

    void SetAllPlayerHP();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    GameEngineRender* pPlayer0 = nullptr;
    GameEngineRender* pPlayer1 = nullptr;
    GameEngineRender* pPlayer2 = nullptr;
    GameEngineRender* pPlayer3 = nullptr;
    GameEngineRender* pPlayer4 = nullptr;
    GameEngineRender* pPlayer5 = nullptr;

    int iPlayer0HP = 0;
    int iPlayer1HP = 0;
    int iPlayer2HP = 0;
    int iPlayer3HP = 0;
    int iPlayer4HP = 0;
    int iPlayer5HP = 0;

    bool bSetHP = false;
};

