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

	void CreateHole();

	inline void SetRadius(int _Radius)
	{
		Radius = _Radius;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int White	= RGB(255, 255, 255);
	int Red		= RGB(255, 0, 0);
	//int Blue	= RGB(0, 0, 255);
	int Magenta = RGB(255, 0, 255);

	int Radius = 0;

};

