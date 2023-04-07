#include "SmokeSparkEffect.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ContentsEnums.h"

SmokeSparkEffect::SmokeSparkEffect()
{
}

SmokeSparkEffect::~SmokeSparkEffect()
{
}

void SmokeSparkEffect::CreateSmokeSpark(int _Smoke, int _Spark, float _Scale, float _MultiScale)
{
    SmokeCnt = _Smoke;
    SparkCnt = _Spark;
    float BombScale = _Scale / 2;

    AllSmoke.clear();
    AllSmokeDir.clear();
    AllSpark.clear();
    AllSparkDir.clear();


    AllSmoke.reserve(SmokeCnt);
    AllSmokeDir.reserve(SmokeCnt);
    AllSpark.reserve(SparkCnt);
    AllSparkDir.reserve(SparkCnt);


    for (int i = 0;i < SmokeCnt;i++)
    {
        GameEngineRender* NewSmoke = CreateRender(WormsRenderOrder::Weapon);
        float4 dir = float4{ GameEngineRandom::MainRandom.RandomFloat(-BombScale,BombScale), GameEngineRandom::MainRandom.RandomFloat(-BombScale,BombScale) };
        NewSmoke->SetPosition(dir);
        dir.Normalize();
        NewSmoke->SetScale(float4(60, 60) * _MultiScale);
        NewSmoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "Smoke100.bmp", .Start = 0, .End = 27, .InterTime = 0.02f , .Loop = false });
        NewSmoke->ChangeAnimation("Smoke");
        AllSmokeDir.push_back(dir);
        AllSmoke.push_back(NewSmoke);
    }

    for (int i = 0;i < SparkCnt;i++)
    {
        GameEngineRender* NewSpark = CreateRender(WormsRenderOrder::Weapon);
        float4 dir = float4{ GameEngineRandom::MainRandom.RandomFloat(-BombScale,BombScale), GameEngineRandom::MainRandom.RandomFloat(-BombScale,BombScale) }.NormalizeReturn() * BombScale;
        dir.y -= BombScale;
        NewSpark->SetPosition(dir);
        dir.Normalize();
        NewSpark->SetScale(float4(60, 60) * _MultiScale);
        NewSpark->CreateAnimation({ .AnimationName = "Spark", .ImageName = "Spark1.bmp", .Start = 0, .End = 31, .InterTime = 0.05f , .Loop = false });
        NewSpark->ChangeAnimation("Spark");
        AllSparkDir.push_back(dir);
        AllSpark.push_back(NewSpark);
    }
}


void SmokeSparkEffect::Update(float _DeltaTime)
{
    if (true == CheckEnd())
    {
        isEnd = true;
        this->Death();
        return;
    }

    for (int i = 0;i < SmokeCnt;i++)
    {
        if (true == AllSmoke[i]->IsAnimationEnd())
        {
            AllSmoke[i]->Off();
        }
        if (true == AllSmoke[i]->IsUpdate())
        {
            AllSmokeDir[i].y += Evaporation * _DeltaTime;
            AllSmokeDir[i].x *= (Resist * _DeltaTime);
            AllSmoke[i]->SetMove(AllSmokeDir[i] * MoveSpeed * _DeltaTime);

        }

    }
    for (int i = 0;i < SparkCnt;i++)
    {
        if (true == AllSpark[i]->IsAnimationEnd())
        {
            AllSpark[i]->Off();
        }
        if (true == AllSpark[i]->IsUpdate())
        {
            AllSparkDir[i].y -= Evaporation * _DeltaTime;
            AllSparkDir[i].x *= (Resist * _DeltaTime);
            AllSpark[i]->SetMove(AllSparkDir[i] * MoveSpeed * _DeltaTime);

        }

    }


}
bool SmokeSparkEffect::CheckEnd()
{
    for (int i = 0;i < SmokeCnt;i++)
    {
        if (true == AllSmoke[i]->IsUpdate())
        {
            return false;
        }
    }
    for (int i = 0;i < SparkCnt;i++)
    {
        if (true == AllSpark[i]->IsUpdate())
        {
            return false;
        }
    }
    return true;
}