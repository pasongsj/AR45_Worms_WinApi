#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 맵의 지형 변화와 관련된 기능
class GameEngineActor;
class MapModifier : public GameEngineActor
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

	//원형으로 땅을 깎는 함수
	void CreateHole(float4 _Pos, int _Radius);

	//MapModifier의 액터를 만드는 함수
	void CreateMapModifier();

	//건물과 맞닿은 구덩이에 선을 그리는 함수
	void DrawArc(float4 _Pos, int _Radius);

	//충돌체 하나 만들기_레벨에서 콜리전->

	GameEngineCollision* GetModifierCollision()
	{
		return ModifierCollision;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	int White	= RGB(255, 255, 255);
	int Red		= RGB(255, 0, 0);
	int Blue	= RGB(0, 0, 255);
	int Magenta = RGB(255, 0, 255);
	int Cyan	= RGB(0, 255, 255);

	GameEngineCollision* ModifierCollision = nullptr;				//Modifier Collision

	float4 GetStartArcPos(float4 _Pos, int _Radius);
	float4 GetEndArcPos(float4 _Pos, int _Radius);
};