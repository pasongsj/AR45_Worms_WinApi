#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 맵의 지형 변화와 관련된 기능
class GameEngineActor;
class MapModifier :public GameEngineActor
{
public:
	// constrcuter destructer
	MapModifier();
	~MapModifier();

	// delete Function
	MapModifier(const MapModifier& _Other) = delete;
	MapModifier(MapModifier&& _Other) noexcept = delete;
	MapModifier& operator=(const MapModifier& _Other) = delete;
	MapModifier& operator=(MapModifier&& _Other) noexcept = delete;

	void CreateHole(int _Radius);
	void CreateMapModifier(float4 _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Render(float _DeltaTime) override;
private:

};

