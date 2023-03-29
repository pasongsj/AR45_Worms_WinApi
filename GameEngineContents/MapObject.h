#pragma once
//#include <vector>
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 맵에 배치될 오브젝트와 관련된 기능
class GameEngineImage;
class MapObject : public GameEngineActor
{
public:
	// constrcuter destructer
	MapObject();
	virtual ~MapObject() = 0;

	// delete Function
	MapObject(const MapObject& _Other) = delete;
	MapObject(MapObject&& _Other) noexcept = delete;
	MapObject& operator=(const MapObject& _Other) = delete;
	MapObject& operator=(MapObject&& _Other) noexcept = delete;

    float4 GetMapObjPos();

    void SetColImage();

protected:
    int Blue = RGB(0, 0, 255);
    int Magenta = RGB(255, 0, 255);

    float MoveSpeed = 50.0f;                                //속력
    float Gravity = 500.0f;                                 //중력 크기

    float4 ObjScale = { 60.0f, 60.0f };
    float4 MoveDir = float4::Zero;                          //오브젝트 이동용 벡터

    GameEngineRender* MapObjRender = nullptr;               //object Render
    GameEngineCollision* MapObjCol = nullptr;				//Map Object Collision

    GameEngineImage* ColImage = nullptr;

   

    void GravityApplied(float _DeltaTime);                  //중력적용
    float4 PullUp(float4 _NextPos, float _DeltaTime);       //중력에 의해 하강하는 위치값을 땅으로 끌어올림
    bool IsGroundCheck();                                   //현재 있는 위치가 땅인지 확인하는 함수
    bool IsUnderWaterCheck();
private:
   
};

