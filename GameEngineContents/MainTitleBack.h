#pragma once

#include <GameEngineCore/GameEngineActor.h>


class MainTitleBack : public GameEngineActor
{
public:
    // constrcuter destructer
    MainTitleBack();
    ~MainTitleBack();

    // delete Function
    MainTitleBack(const MainTitleBack& _Other) = delete;
    MainTitleBack(MainTitleBack&& _Other) noexcept = delete;
    MainTitleBack& operator=(const MainTitleBack& _Other) = delete;
    MainTitleBack& operator=(MainTitleBack&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _DeltaTime) override;

private:
    GameEngineRender* BlackBackGround = nullptr;
    GameEngineRender* Logo = nullptr;
    GameEngineRender* UpTitle = nullptr;
    GameEngineRender* options = nullptr;
    GameEngineRender* multi = nullptr;
    GameEngineRender* net = nullptr;
    GameEngineRender* MouseSelect = nullptr;
    GameEngineRender* MainPlay = nullptr;
   
    float BlackAlpha = 0;
    float Time = 0;
    GameEngineCollision* OptionCollision = nullptr;
    GameEngineCollision* multiCollision = nullptr;
    GameEngineCollision* netCollision = nullptr;
    GameEngineCollision* MainPlayCollision = nullptr;


};

