#pragma once
#include <GameEngineCore/GameEngineActor.h>
class PlayChangeEnding : public GameEngineActor
{
public:
    // constrcuter destructer
    PlayChangeEnding();
    ~PlayChangeEnding();

    // delete Function
    PlayChangeEnding(const PlayChangeEnding& _Other) = delete;
    PlayChangeEnding(PlayChangeEnding&& _Other) noexcept = delete;
    PlayChangeEnding& operator=(const PlayChangeEnding& _Other) = delete;
    PlayChangeEnding& operator=(PlayChangeEnding&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;


private:

    GameEngineRender* BackGround = nullptr;
    GameEngineRender* Animation = nullptr;
    GameEngineRender* BackGround1 = nullptr;

    float IntroLogTime = 0;
    float IntroLogColor = 0;

    float UpBlackAlpha = 0;
    float DownBlackAlpha = 0;

    bool AnimationCheck = false;
    bool BlackCheck = false;
};
