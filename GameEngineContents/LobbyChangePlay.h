#pragma once
#include <GameEngineCore/GameEngineActor.h>


class LobbyChangePlay : public GameEngineActor
{
public:
    // constrcuter destructer
    LobbyChangePlay();
    ~LobbyChangePlay();

    // delete Function
    LobbyChangePlay(const LobbyChangePlay& _Other) = delete;
    LobbyChangePlay(LobbyChangePlay&& _Other) noexcept = delete;
    LobbyChangePlay& operator=(const LobbyChangePlay& _Other) = delete;
    LobbyChangePlay& operator=(LobbyChangePlay&& _Other) noexcept = delete;

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

