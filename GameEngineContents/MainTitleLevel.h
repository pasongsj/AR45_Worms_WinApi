#pragma once
#include <GameEngineCore/GameEngineLevel.h>
class MainTitleLevel : public GameEngineLevel
{
public:
    // constrcuter destructer
    MainTitleLevel();
    ~MainTitleLevel();

    // delete Function
    MainTitleLevel(const MainTitleLevel& _Other) = delete;
    MainTitleLevel(MainTitleLevel&& _Other) noexcept = delete;
    MainTitleLevel& operator=(const MainTitleLevel& _Other) = delete;
    MainTitleLevel& operator=(MainTitleLevel&& _Other) noexcept = delete;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;

    virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}
    virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}


private:
    GameEngineRender* AnimationBodyRender = nullptr;
};
