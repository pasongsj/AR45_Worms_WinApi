#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GlobalValue.h"

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

    void Mapchoice();
    void Turnchoice(); 
    void Roundchoice();
    void Winchoice(); 
    void Wormschoice();
    void Hpchoice();
    void Teleportchoice(); 
    void Playerchoice();
    void Playerdown();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _DeltaTime) override;

    virtual void LevelChangeEnd(GameEngineLevel* _PrevLevel);
   

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
    GameEngineRender* OptionSelect = nullptr;



    GameEngineRender* Player = nullptr;
    GameEngineRender* Player2 = nullptr;
    GameEngineRender* Player3 = nullptr;
    GameEngineRender* Player4 = nullptr;
    GameEngineRender* Player5 = nullptr;
    GameEngineRender* Player6 = nullptr;

    GameEngineRender* TurnTime15 = nullptr;
    GameEngineRender* TurnTime20 = nullptr;
    GameEngineRender* TurnTime30 = nullptr;
    GameEngineRender* TurnTime45 = nullptr;
    GameEngineRender* TurnTime60 = nullptr;
    GameEngineRender* TurnTime90 = nullptr;
    GameEngineRender* TurnTime00 = nullptr;

    GameEngineRender* RoundTime0 = nullptr;
    GameEngineRender* RoundTime1 = nullptr;
    GameEngineRender* RoundTime2 = nullptr;
    GameEngineRender* RoundTime3 = nullptr;
    GameEngineRender* RoundTime4 = nullptr;
    GameEngineRender* RoundTime5 = nullptr;
    GameEngineRender* RoundTime6 = nullptr;

    GameEngineRender* Wins0 = nullptr;
    GameEngineRender* Wins1 = nullptr;
    GameEngineRender* Wins2 = nullptr;
    GameEngineRender* Wins3 = nullptr;
    GameEngineRender* Wins4 = nullptr;
    GameEngineRender* Wins5 = nullptr;
    GameEngineRender* Wins6 = nullptr;

    GameEngineRender* WormSelectOFF = nullptr;
    GameEngineRender* WormSelectON = nullptr;
    GameEngineRender* WormSelectRANDOM = nullptr;

    GameEngineRender* Hp00 = nullptr;
    GameEngineRender* Hp100 = nullptr;
    GameEngineRender* Hp150 = nullptr;
    GameEngineRender* Hp200 = nullptr;
    
    GameEngineRender* SelectOff = nullptr;
    GameEngineRender* SelectOn = nullptr;

    GameEngineRender* MouseSelect = nullptr;
    GameEngineRender* OptionsSelect = nullptr;
    

    GameEngineCollision* GameStartCollision = nullptr;
    GameEngineCollision* ExitCollision = nullptr;
    GameEngineCollision* MapCollision = nullptr;
    GameEngineCollision* OptionCollision = nullptr;
    GameEngineCollision* WeaponCollision = nullptr;
    
    GameEngineCollision* TurnCollision = nullptr;
    GameEngineCollision* RoundCollision = nullptr;
    GameEngineCollision* WinsCollision = nullptr;
    GameEngineCollision* WormsCollision = nullptr;
    GameEngineCollision* HpCollision = nullptr;
    GameEngineCollision* SelectOnCollision = nullptr;
    GameEngineCollision* PlayerCollision = nullptr;
    GameEngineCollision* PlayerDownCollision = nullptr;


    int MapChoice = 0;
    int TurnChoice = 0;
    int RoundChoice = 0; 
    int WinChoice = 0;
    int WormsChoice = 0; 
    int HpChoice = 0; 
    int TeleportChoice = 0;
    int PlayerChoice = 0;
    int PlayerDown = 6;

    float BlackAlpha = 0;
    float Time = 0;

    LevelSetting SetLevel = {};
};

