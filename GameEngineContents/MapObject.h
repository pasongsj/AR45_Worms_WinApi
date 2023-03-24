#pragma once
//#include <vector>
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 맵에 배치될 오브젝트와 관련된 기능
class MapObject : public GameEngineActor
{
public:
	// constrcuter destructer
	MapObject();
	~MapObject();

	// delete Function
	MapObject(const MapObject& _Other) = delete;
	MapObject(MapObject&& _Other) noexcept = delete;
	MapObject& operator=(const MapObject& _Other) = delete;
	MapObject& operator=(MapObject&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    int Blue = RGB(0, 0, 255);
    int Magenta = RGB(255, 0, 255);

    float4 ObjScale = float4::Zero;              //오브젝트들의 스케일을 저장하는 용도
    float4 MapScale = { 3840.0f, 1392.0f };      //사용하는 맵의 크기


    GameEngineRender* TestRender = nullptr;

    std::vector<float4> GetRandomPos();
    float4 SetObjPosRand();
    void MergeMap();                             //기존 맵과 충돌맵에 오브젝트이미지를 합성하는 함수

};

