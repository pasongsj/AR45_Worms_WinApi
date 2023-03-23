#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP,
    EQUIPWEAPON,
};

enum class PlayerAngleDir
{
    Left,
    Right,
};

// 설명 : 플레이어 클래스
class Weapon;
class GameEngineImage;
class PlayerHPUI;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();
	int a = 0;
	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetColImage(const std::string_view& _Name);

	void SetIsMyTurn(bool _Value);

	bool GetIsMyTurn()
	{
		return IsMyTurn;
	}

	void SetCurWeapon(Weapon* _Weapon)
	{
		CurWeapon = _Weapon;
	}

	Weapon* GetCurWeapon()
	{
		return CurWeapon;
	}

    int GetPlayerHP()
    {
        return PlayerHP;
    }

	void CreatePlayerAnimation(const std::string_view& _AnimationName, const std::string_view& _ImageName, int _StartFrame, int _EndFrame, float _InterTime, bool Loop = true); //외부(무기)에서 플레이어의 애니메이션을 만들 수 있게끔 
	void ChangePlayerAnimation(const std::string_view& _AnimationName, int _CurIndex = 0); //플레이어 애니메이션 변경
	void SetPlayerAnimationFrame(int _Frame); // 조준 상태일 때 프레임을 고정
	void GetDamaged(int _Damage); //플레이어가 데미지를 받는 함수

	//플레이어 상태를 받아옴
	PlayerState GetPlayerState()
	{
		return StateValue;
	}

	bool IsPlayerAnimationEnd();

	void SetCanIMove(bool _Value)
	{
		CanIMove = _Value;
	}

	// 무기에서 현재 플레이어의 방향을 가지고 오는 메서드 
	float4 GetPlayerDir() 
	{
		if ("Right_" == DirString)
		{
			return float4::Right;
		}
		else
		{
			return float4::Left;
		}
	}

	//플레이어 UI의 이미지들을 특정지어주는 메서드
	void SetHPUI(const std::string_view& _HPNumberImage, const std::string_view& _NametagImage, const std::string_view& _ArrowImage);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Test(); //테스트용 함수
	
	bool CanIMove = true;

    void CreateAnimation();
	GameEngineRender* AnimationRender = nullptr;  //애니메이션 렌더러
	GameEngineCollision* BodyCollision = nullptr; //공격 받았는지 여부를 확인하기 위한 콜리전

	//플레이어 UI관련 (HP, 화살표이미지)
	PlayerHPUI* HPUI; //플레이어 HP를 보여줄 넘버 렌더러 
	int PlayerHP = 100;
	float GetDamagedTime = 0.0f;
	std::string_view PlayerHPNumberImageStringView; //플레이어의 HPNumberImage 이름
	
    void CheckTurn();
	bool IsMyTurn = false; //내 턴인지 체크

	//플레이어의 방향에 따라 다른 애니메이션을 하게끔 
	void DirCheck(const std::string_view& _AnimationName, int _CurIndex = 0);

	//이동 관련
	std::string DirString = "Right_"; //방향
	float4 MoveDir = float4::Zero; //플레이어의 이동 벡터
	bool IsGround = true; //플레이어의 지면 여부
	void IsGroundCheck();
	std::string_view AnimationDir = "";
    void MoveCalculation(float _DeltaTime);
    bool NextPosWallCheck(float4 _NextPos);

    bool ReturnCanIMove(PlayerAngleDir _Dir);
	void SetMoveAngle(); 	//이동시 플레이어의 좌우의 픽셀을 체크하여, 앵글을 넣음
	float LeftMoveAngle = 0.0f; 
	float RightMoveAngle = 0.0f; 
    const float AngleLimit = 15.0f; //각도 제한용 상수

	float MoveSpeed = 50.0f;
	float Gravity = 50.0f;

	void GravityApplied();

	float4 PullUpCharacter(float4 _NextPos, float _DeltaTime); //플레이어가 colimage상 아래로 들어가 있다면,MoveDir을 위로 끌어올림

	GameEngineImage* ColImage = nullptr; //이동 등에 사용될 colimage

	//플레이어 스테이트 관련	
	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

    float StateCalTime = 0.0f; //스테이트 내에서 시간 계산이 필요할 때
    bool StateCalBool = true;

	//플레이어의 현재 상태
	PlayerState StateValue = PlayerState::IDLE;

	void IdleStart();
	void IdleUpdate(float _DeltatTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltatTime);
	void MoveEnd();

	Weapon* CurWeapon = nullptr;
	
	void JumpStart();
	void JumpUpdate(float _DeltatTime);
	void JumpEnd();

    void EquipWeaponStart();
    void EquipWeaponUpdate(float _DeltatTime);
    void EquipWeaponEnd();

	//기본 스테이트 관련 함수
	//void Start();
	//void Update(float _DeltatTime);
	//void End();
};

