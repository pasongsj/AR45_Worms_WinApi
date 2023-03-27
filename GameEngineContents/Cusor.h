#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Cusor : public GameEngineActor
{
public:
    // constrcuter destructer
    Cusor();
    ~Cusor();

    // delete Function
    Cusor(const Cusor& _Other) = delete;
    Cusor(Cusor&& _Other) noexcept = delete;
    Cusor& operator=(const Cusor& _Other) = delete;
    Cusor& operator=(Cusor&& _Other) noexcept = delete;

  
protected:
    void Start() override;
    void Update(float _DeltaTime) override;


private:

    GameEngineRender* CusorRender = nullptr;

    float4 MoveDir = float4::Zero;



};
