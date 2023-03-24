#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Star : public GameEngineActor
{
public:
    // constrcuter destructer
    Star();
    ~Star();

    // delete Function
    Star(const Star& _Other) = delete;
    Star(Star&& _Other) noexcept = delete;
    Star& operator=(const Star& _Other) = delete;
    Star& operator=(Star&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;


private:

    GameEngineRender* star = nullptr;
    
    float4 MoveDir = float4::Zero;


    
};
