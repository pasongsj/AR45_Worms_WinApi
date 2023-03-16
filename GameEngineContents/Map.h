#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsColMap = false;								//픽셀 충돌맵의 랜더링 여부
	
	float WaveAnimeDiff = 55.0f;						//Wave Animation Render 간의 높이 차
	float FreeSpeed = 800.0f;							//FreeMove 스피드

	float4 WaveBackPos = { 1920.0f, 1764.0f };			//x: Map 크기.x 0.5 && y: Map 크기.y + (sky 크기.y - Map 크기.y)/4 
	float4 WaveAnimPos0 = { 1920.0f, 1392.0f };			//Wave Animation 위치	
	float4 WaveAnimPos1 = { 1920.0f, 1447.0f };
	float4 WaveAnimPos2 = { 1920.0f, 1502.0f };
	float4 WaveAnimPos3 = { 1920.0f, 1557.0f };

	float4 WaveBackScale = { 5120.0f, 744.0f };
	float4 WaveScale = { 5120.0f, 110.0f };

	GameEngineRender* MapRender = nullptr;

	//카메라를 자유롭게 움직임
	bool FreeMoveState(float _DeltaTime);
};

