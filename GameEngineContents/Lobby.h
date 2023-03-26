#pragma once
#include <GameEngineCore/GameEngineActor.h>


class Lobby : public GameEngineActor
{
public:
    // constrcuter destructer
    Lobby();
    ~Lobby();

    // delete Function
    Lobby(const Lobby& _Other) = delete;
    Lobby(Lobby&& _Other) noexcept = delete;
    Lobby& operator=(const Lobby& _Other) = delete;
    Lobby& operator=(Lobby&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _DeltaTime) override;

private:
    GameEngineRender* BackGround = nullptr;
    GameEngineRender* MapSelect = nullptr;
    GameEngineRender* Teams = nullptr;
    GameEngineRender* Barracks = nullptr;
    GameEngineRender* Option = nullptr;

    GameEngineRender* StartGame = nullptr;
    GameEngineRender* Exit = nullptr;

    GameEngineRender* Map = nullptr;
    GameEngineRender* Map2 = nullptr;
    GameEngineRender* Map3 = nullptr;
    GameEngineRender* Map4 = nullptr;

    GameEngineRender* OptionWeapon = nullptr;
    GameEngineRender* OptionMap = nullptr;


    GameEngineRender* MouseSelect = nullptr;

    GameEngineCollision* OptionCollision = nullptr;
    GameEngineCollision* multiCollision = nullptr;
    GameEngineCollision* netCollision = nullptr;
    GameEngineCollision* MainPlayCollision = nullptr;

    float BlackAlpha = 0;
    float Time = 0;
};

