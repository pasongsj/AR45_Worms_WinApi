#pragma once
#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class EndingLevel : public GameEngineLevel
{
public:
    // constrcuter destructer
    EndingLevel();
    ~EndingLevel();

    // delete Function
    EndingLevel(const EndingLevel& _Other) = delete;
    EndingLevel(EndingLevel&& _Other) noexcept = delete;
    EndingLevel& operator=(const EndingLevel& _Other) = delete;
    EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;

    virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}
    virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


private:
    GameEngineRender* AnimationBodyRender = nullptr;
};

