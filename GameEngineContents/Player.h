#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	IDLE,
	MOVE,
};

// 설명 : 플레이어 클래스
class GameEngineImage;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetColImage(const std::string_view& _Name);

	void SetIsMyTurn(bool _Value)
	{
		IsMyTurn = _Value;
	}

	bool GetIsMyTurn()
	{
		return IsMyTurn;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;  //애니메이션 렌더러
	GameEngineCollision* BodyCollision = nullptr; //공격 받았는지 여부를 확인하기 위한 콜리전

	bool IsMyTurn = false; //내 턴인지 체크

	//플레이어의 방향에 따라 다른 애니메이션을 하게끔 
	void DirCheck(const std::string_view& _AnimationName);

	//이동 관련
	std::string DirString = "Right_"; //방향

	float4 MoveDir = float4::Zero; //플레이어의 이동 벡터

	float MoveSpeed = 50.0f;
	float Gravity = 300.0f;

	void GravityApplied();
	void MoveCalculation(float _DeltaTime);
	float4 PullUpCharacter(float4 _NextPos, float _DeltaTime); //플레이어가 colimage상 아래로 들어가 있다면,MoveDir을 위로 끌어올림

	GameEngineImage* ColImage = nullptr; //이동 등에 사용될 colimage

	//플레이어 스테이트 관련	
	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	//플레이어의 현재 상태
	PlayerState StateValue = PlayerState::IDLE;

	void IdleStart();
	void IdleUpdate(float _DeltatTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltatTime);
	void MoveEnd();

	//기본 스테이트 관련 함수
	//void Start();
	//void Update(float _DeltatTime);
	//void End();
};

