#pragma once
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
    GameEngineRender* MapObjRender = nullptr;
};

