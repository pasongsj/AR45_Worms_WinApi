#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class PlayerHPUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHPUI();
	~PlayerHPUI();

	// delete Function
	PlayerHPUI(const PlayerHPUI& _Other) = delete;
	PlayerHPUI(PlayerHPUI&& _Other) noexcept = delete;
	PlayerHPUI& operator=(const PlayerHPUI& _Other) = delete;
	PlayerHPUI& operator=(PlayerHPUI&& _Other) noexcept = delete;

	void SetPlayerHPUI(const std::string_view& _HPNumberImage, const std::string_view& _NametagImage, const std::string_view& _ArrowImage, int* _PlayerHP);
	void SetSelectPlayerRender(bool _Value);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	NumberRenderObject PlayerHPNumberRender;
	GameEngineRender* IDRender = nullptr; //아이디 이미지 렌더
	GameEngineRender* HPBarImageRender = nullptr; // 체력 창 뒤 이미지 렌더
	GameEngineRender* SelectPlayerRender = nullptr; // 화살표 이미지 렌더
	int *HPValue; // 플레이어 hp
	int CurrentValue = 100; //현재 NumberRender상 플레이어 hp
};

