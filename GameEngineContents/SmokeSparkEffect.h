#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SmokeSparkEffect :public GameEngineActor
{
public:
	// constrcuter destructer
	SmokeSparkEffect() ;
	~SmokeSparkEffect();

	// delete Function
	SmokeSparkEffect(const SmokeSparkEffect& _Other) = delete;
	SmokeSparkEffect(SmokeSparkEffect&& _Other) noexcept = delete;
	SmokeSparkEffect& operator=(const SmokeSparkEffect& _Other) = delete;
	SmokeSparkEffect& operator=(SmokeSparkEffect&& _Other) noexcept = delete;

    void CreateSmokeSpark(int _Smoke, int _Spark, int _Scale);

    bool IsEnd()
    {
        return isEnd;
    }

protected:
    void Update(float _DeltaTime) override;
private:

    float Evaporation = -2.5f; // Y축 증발
    float Resist = 0.5f; //x축 공기저항

    float MoveSpeed = 300;
    bool isEnd = false;

    int SmokeCnt = 0;
    int SparkCnt = 0;

    std::vector<GameEngineRender*> AllSmoke;
    std::vector<float4> AllSmokeDir;
    std::vector<GameEngineRender*> AllSpark;
    std::vector<float4> AllSparkDir;

    bool CheckEnd();
};

