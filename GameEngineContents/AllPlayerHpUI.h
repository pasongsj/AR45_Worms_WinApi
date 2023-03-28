#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// 설명 :
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


    // 개편 필요. 렌더벡터와 HP벡터를 만든후 HP비교를 통해 HP벡터의 순서를 변경하면 렌더또한 순서를 동일하게 변경해서
    // 러프를 통해 위치값을 변경해야함. 위치값은 초기지점을 y를 850.f 로 두고 반복문을통해 17.f씩 더함
    // Scale이 줄어드는것 또한 순차적으로 줄어들어야한다(?)

private:
    std::vector<int> vecMixNum;
    std::vector<GameEngineRender*> vecPlayerHpBar;
    std::vector<GameEngineRender*> vecPlayerName;
    std::vector<int> vecPlayerCurHp;
    std::vector<float4> vecLastPos;
    float4 StartPos = { 640.f,850.f };

    float fLerpRatio = 0.f;

    bool bSetHP = false;
    bool bSort = false;

};

