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


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;


	//플레이어 스테이트 관련
	PlayerState StateValue = PlayerState::IDLE;

	//플레이어의 이동방향
	float4 MoveDir = float4::Zero;

	//이동 관련 함수
	void MoveCalculation(float _DeltaTime);

	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	GameEngineImage* ColImage = nullptr; //이동 등에 사용될 colimage

	//기본 스테이트 관련 함수
	//void Start();
	//void Update(float _DeltatTime);
	//void End();
};

