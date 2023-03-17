#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class Map : public GameEngineActor
{
public:
	static Map* MainMap;
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	const std::string GetMapName() const
	{
		return MapName;
	}

	const std::string GetColMapName() const
	{
		return ColMapName;
	}

	float4 GetWavePos()	const
	{
		return WaveBackPos;
	}

	HDC GetMapRenderDC() const;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsColMap = false;								//픽셀 충돌맵의 랜더링 여부
	
	float WaveAnimeDiff = 55.0f;						//Wave Animation Render 간의 높이 차
	float FreeSpeed = 900.0f;							//FreeMove 스피드

	float4 WaveBackPos = { 0.0f, 1068.0f };				//Wave BackGround 위치
	float4 WaveAnimPos0 = { 0.0f, 696.0f };				//Wave Animation 위치	
	float4 WaveAnimPos1 = { 0.0f, 751.0f };
	float4 WaveAnimPos2 = { 0.0f, 806.0f };
	float4 WaveAnimPos3 = { 0.0f, 861.0f };

	float4 WaveBackScale = { 5120.0f, 744.0f };
	float4 WaveScale = { 5120.0f, 110.0f };

	std::string MapName = "MapCity.bmp";
	std::string ColMapName = "MapCity_Ground.bmp";

	GameEngineRender* MapRender = nullptr;

	//카메라를 자유롭게 움직임
	bool FreeMoveState(float _DeltaTime);
};

