#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>
#include "MapModifier.h"

// 설명 : 맵관련 기능
class Map : public GameEngineActor
{
public:
	static Map* MainMap;
	static int MapMode;									//Map 선택
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	const std::string& GetMapName() const
	{
		return MapName;
	}

	const std::string& GetColMapName() const
	{
		return ColMapName;
	}

	float4 GetWavePos()	const
	{
		return WaveStartPos;
	}

	//HDC를 얻어오는 함수
	HDC GetMapDC() const;
	HDC GetColMapDC() const;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	bool IsColMap = false;								//픽셀 충돌맵의 랜더링 여부

    int NumOfObj = 0;                                   //생성할 드럼 오브젝트의 개수

    float WaitTime = 40.0f;
	float WaveAnimeDiff = 55.0f;						//Wave Animation Render 간의 높이 차
	float FreeSpeed = 900.0f;							//FreeMove 스피드

    float4 WaveStartPos = { 1920.0f, 1392.0f };         //Wave BackGround 시작 위치

	float4 MountainPos = { 1920.0f, 1264.0f };          //Mountain BackGround 위치
	float4 WaveBackPos = { 1920.0f, 1950.0f };			//Wave BackGround 위치 


    float4 WaveAnimPos0 = { 1920.0f, 1340.0f };			//Wave Animation 위치	
	float4 WaveAnimPos1 = { 1920.0f, 1400.0f };
	float4 WaveAnimPos2 = { 1920.0f, 1447.0f };
	float4 WaveAnimPos3 = { 1920.0f, 1492.0f };
	float4 WaveAnimPos4 = { 1920.0f, 1537.0f };

	float4 BackScale = { 7680.0f, 1116.0f };             //mountain, wave의 크기
	float4 WaveScale = { 7680.0f, 165.0f };              //Wave의 크기

	std::string MapName = "";
	std::string ColMapName = "";



	std::vector<std::string> Maps = std::vector<std::string>();
	std::vector<std::string> ColMaps = std::vector<std::string>();

	GameEngineRender* MapRender = nullptr;
	GameEngineRender* ColMapRender = nullptr;


	//카메라를 자유롭게 움직임
	void FreeMoveState(float _DeltaTime);
};

