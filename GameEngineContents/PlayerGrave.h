#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineImage;
class PlayerGrave : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerGrave();
	~PlayerGrave();

	// delete Function
	PlayerGrave(const PlayerGrave& _Other) = delete;
	PlayerGrave(PlayerGrave&& _Other) noexcept = delete;
	PlayerGrave& operator=(const PlayerGrave& _Other) = delete;
	PlayerGrave& operator=(PlayerGrave&& _Other) noexcept = delete;

    void SetPlayerGrave(const std::string_view& _GraveImage, float4 PlayerPos);

protected:
    void Start() override;

private:
    GameEngineRender* AnimationRender = nullptr;  //애니메이션 렌더러

    GameEngineImage* ColImage = nullptr; //colimage
};

