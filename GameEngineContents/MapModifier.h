#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 맵의 지형 변화와 관련된 기능
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

	//원형으로 땅을 깎는 함수(지름 필요)
	void CreateHole(float4 _Pos, int _Diameter, bool _DrawLine = true);

    //사각형으로 땅을 깎는 함수(직사각형 가로와 세로 크기 필요)
    void CreateRect(float4 _Pos, int _Horz, int _Vert, bool _DrawLine = true);

	//충돌체 포인터 얻는 함수
	GameEngineCollision* GetModifierCollision()
	{
		return ModifierCollision;
	}

    void SetModifierColScale(float4 _Scale);
    void SetModifierColPosition(float4 _Pos);
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int Blue	    = RGB(0, 0, 255);
	int Magenta     = RGB(255, 0, 255);
	int LineColor	= RGB(165, 184, 223);

    float4 Scale = { 3840.0f, 1392.0f };


	GameEngineCollision* ModifierCollision = nullptr;				//Modifier Collision
	
	
	//맵의 건물과 닿은 곳에 구분선을 넣는 함수
    void DrawPixel(float4 _Pos, int _Radius);
    //맵의 건물과 닿은 곳에 구분선을 넣는 함수_사각형 버전
    void DrawPixelRect(float4 _Pos, int _Horz, int _Vert);
};