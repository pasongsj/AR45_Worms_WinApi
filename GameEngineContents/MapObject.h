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
	~MapObject();

	// delete Function
	MapObject(const MapObject& _Other) = delete;
	MapObject(MapObject&& _Other) noexcept = delete;
	MapObject& operator=(const MapObject& _Other) = delete;
	MapObject& operator=(MapObject&& _Other) noexcept = delete;

    float4 GetMapObjPos();


protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    bool IsFlying = true;
    bool IsChangedAnim = false;

    int Recovery = 50;
    int Blue = RGB(0, 0, 255);
    int Magenta = RGB(255, 0, 255);

    float MoveSpeed = 50.0f;                                //속력
    float Gravity = 500.0f;                                 //중력 크기

    std::string DirString = "Right_";                       //낙하할 때 방향

    float4 ObjScale = { 60.0f, 60.0f };
    float4 MoveDir = float4::Zero;                          //오브젝트 이동용 벡터

    GameEngineRender* MapObjRender = nullptr;               //object Render
    GameEngineCollision* MapObjCol = nullptr;				//Map Object Collision

    GameEngineImage* ColImage = nullptr;

    void SetCurPlayer();                                    //CurPlayer세팅함수
    void GravityApplied(float _DeltaTime);                  //중력적용
    float4 PullUp(float4 _NextPos, float _DeltaTime);       //중력에 의해 하강하는 위치값을 땅으로 끌어올림
    bool IsGround();                                        //현재 있는 위치가 땅인지 확인하는 함수

    void RecoveryCheck();
};

