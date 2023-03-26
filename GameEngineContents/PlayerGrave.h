#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class GraveDir
{
    Up,
    Down
};

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

    void SetPlayerGrave(const std::string_view& _GraveImage, GameEngineImage* _ColImage, float4 PlayerPos);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    GraveDir CurrentDir = GraveDir::Up;

    GameEngineRender* AnimationRender = nullptr;  //애니메이션 렌더러

    GameEngineImage* ColImage = nullptr; //colimage

    int JumpTime = 0;

    void MoveCalculation(float _DeltaTime);

    float4 PullUpObject(float4 _NextPos, float _DeltaTime);

    float4 MoveDir = float4::Zero;

    void GravityApplied(float _DeltaTime); //중력적용

    void GravePixelCheck();
    bool UpPixelCheck = false;
    bool DownPixelCheck = false;

    void DirCheck();
};

