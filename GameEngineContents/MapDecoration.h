#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 맵에 배치될 장식들과 관련된 기능
class MapDecoration : public GameEngineActor
{
public:
	// constrcuter destructer
	MapDecoration();
	~MapDecoration();

	// delete Function
	MapDecoration(const MapDecoration& _Other) = delete;
	MapDecoration(MapDecoration&& _Other) noexcept = delete;
	MapDecoration& operator=(const MapDecoration& _Other) = delete;
	MapDecoration& operator=(MapDecoration&& _Other) noexcept = delete;

    float4 GetRandomPos();
    void MergeMap();                             //기존 맵과 충돌맵에 오브젝트이미지를 합성하는 함수

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    int Blue = RGB(0, 0, 255);
    int Magenta = RGB(255, 0, 255);

    int RandIdx = 0;

    float4 DecoScale = float4::Zero;              //꾸미기용 오브젝트들의 스케일을 저장하는 용도

    std::vector<float4> RandPosSets = std::vector<float4>();

    std::vector<std::string> Objects = std::vector<std::string>();
    std::vector<std::string> ColObjects = std::vector<std::string>();

    void MakeRandomPosSets();                    //랜덤한 위치를 체크해서 벡터에 넣는 함수
};