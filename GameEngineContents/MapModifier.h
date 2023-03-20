#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 맵의 지형 변화와 관련된 기능
class GameEngineActor;
class MapModifier :public GameEngineActor
{
public:
	static MapModifier* MainModifier;
public:
	// constrcuter destructer
	MapModifier();
	~MapModifier();

	// delete Function
	MapModifier(const MapModifier& _Other) = delete;
	MapModifier(MapModifier&& _Other) noexcept = delete;
	MapModifier& operator=(const MapModifier& _Other) = delete;
	MapModifier& operator=(MapModifier&& _Other) noexcept = delete;


	void CreateHole(float4 _Pos, int _Radius);

	void CreateMapModifier();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	int White	= RGB(255, 255, 255);
	int Red		= RGB(255, 0, 0);
	int Magenta = RGB(255, 0, 255);

};