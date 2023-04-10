#pragma once
#include <GameEngineCore/GameEngineActor.h>
class PlayerEsc : public GameEngineActor
{
public:
    // constrcuter destructer
    PlayerEsc();
    ~PlayerEsc();

    // delete Function
    PlayerEsc(const PlayerEsc& _Other) = delete;
    PlayerEsc(PlayerEsc&& _Other) noexcept = delete;
    PlayerEsc& operator=(const PlayerEsc& _Other) = delete;
    PlayerEsc& operator=(PlayerEsc&& _Other) noexcept = delete;
    static bool Check;

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

