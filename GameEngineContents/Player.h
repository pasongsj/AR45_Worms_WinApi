#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

#include "ContentsEnums.h"

enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP,
    EQUIPWEAPON,

    Dead,
    Win,

    FlyDown,
    FacePlant,

    Damaged,

    FlyAway,
    Sliding,
    StandUp,

};

enum class PlayerAngleDir
{
    Left,
    Right,
};

enum class WallCheckDir
{
    Up,
    Down,
    Left,
    Right,
    LeftUp, //좌측 상단
    LeftDown, //좌측 하단
    RightUp, //우측 상단
    RightDown, //우측 하단
    LeftUpBoth,
    LeftDownBoth,
    RightUpBoth,
    RightDownBoth
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

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetColImage(const std::string_view& _Name);

	void SetIsMyTurn(bool _Value);

    void SetHP(int _Hp)
    {
        PlayerHP = _Hp;
        MaxHP = _Hp;
    }

	bool GetIsMyTurn()
	{
		return IsMyTurn;
	}

    void SetCurWeapon(Weapon* _Weapon);

	Weapon* GetCurWeapon()
	{
		return CurWeapon;
	}

    int GetPlayerHP()
    {
        return PlayerHP;
    }

    void SetPlayerState(PlayerState _State);

    void DisplayDamageUI(float _Damage); //데미지 UI를 띄우는 함수
	void CreatePlayerAnimation(const std::string_view& _AnimationName, const std::string_view& _ImageName, int _StartFrame, int _EndFrame, float _InterTime, bool Loop = true); //외부(무기)에서 플레이어의 애니메이션을 만들 수 있게끔 
	void ChangePlayerAnimation(const std::string_view& _AnimationName, int _CurIndex = 0); //플레이어 애니메이션 변경
	void SetPlayerAnimationFrame(int _Frame); // 조준 상태일 때 프레임을 고정
	void Damaged(int _Damage, float4 _Dir = float4::Zero, float _Power = 0); //플레이어가 데미지를 받는 함수

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

    bool GetIsAlive()
    {
        return IsAlive;
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

    std::vector<int> GetPlayerWeaponCount()
    {
        return WeaponCount;
    }

    void UsingHealkit(int _Value);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Test(); //테스트용 함수
    
    void CreateAnimation();
	GameEngineRender* AnimationRender = nullptr;  //애니메이션 렌더러
	GameEngineCollision* BodyCollision = nullptr; //공격 받았는지 여부를 확인하기 위한 콜리전

    void PlaySoundOnce(const std::string_view& _Text);
    void RandomDamagedSound();

    //플레이어 스테이터스 관련 (HP,움직일 수 있는지,생존여부)
    bool CanIMove = true;
    int PlayerHP = 100;
    int MaxHP = 100;
    bool IsAlive = true;
    void CheckAlive();
    void TestChangeDeadState();

    void CheckTurn();
    bool IsMyTurn = false; //내 턴인지 체크

    Weapon* CurWeapon = nullptr; //현재 무기
    WeaponNum CurWeaponNum = WeaponNum::None;

    void PlayerDead(); //플레이어 죽은 이후 실행하는 함수
    void SetGraveObject(const std::string_view& _GraveImage);
    std::string_view PlayerGraveImageStringView;

	//플레이어 UI관련 (HP, 화살표이미지)
	PlayerHPUI* HPUI = nullptr; //플레이어 HP를 보여줄 넘버 렌더러 
	float DamagedTime = 0.0f;
	std::string_view PlayerHPNumberImageStringView; //플레이어의 HPNumberImage 이름
	
	//플레이어의 방향에 따라 다른 애니메이션을 하게끔 
	void DirCheck(const std::string_view& _AnimationName, int _CurIndex = 0);

	//이동 관련
	std::string DirString = "Right_"; //방향
	float4 MoveDir = float4::Zero; //플레이어의 이동 벡터
	bool IsGround = true; //플레이어의 지면 여부
	void IsGroundCheck();
	std::string AnimationDir = "";
    void MoveCalculation(float _DeltaTime);

    bool ReturnCanIMove(PlayerAngleDir _Dir);
	void SetMoveAngle(); 	//이동시 플레이어의 좌우의 픽셀을 체크하여, 앵글을 넣음
	float LeftMoveAngle = 0.0f; 
	float RightMoveAngle = 0.0f; 
    const float AngleLimit = 7.0f; //각도 제한용 상수

    const float SetMoveDirRadius = 5.0f;
    const float SetMoveDIrCenterPos = -4.0f;

    bool GetPlayerWallCheck(WallCheckDir _Dir, float _DeltaTime); //현재 그 방향이 벽과 맞닿아 있는지를 가져옴 
    void SetMoveDirWithAngle(WallCheckDir _Dir); // 공중에서 벽에 닿았을 때, MoveDir을 변경하는 함수

    void PlayerPixelCheck(float _Deltatime);
    bool LeftPixelCheck = false;
    bool RightPixelCheck = false;
    bool UpPixelCheck = false;
    bool DownPixelCheck = false;
    bool LeftUpPixelCheck = false;
    bool RightUpPixelCheck = false;
    bool LeftDownPixelCheck = false;
    bool RightDownPixelCheck = false;

	float MoveSpeed = 50.0f;
	float Gravity = 500.0f;
    float JumpForce = 200.0f;

	void GravityApplied(float _DeltaTime); //중력적용

	float4 PullUpCharacter(float4 _NextPos, float _DeltaTime); //플레이어가 colimage상 아래로 들어가 있다면,MoveDir을 위로 끌어올림

	GameEngineImage* ColImage = nullptr; //이동 등에 사용될 colimage

    void SetWeaponCount();
    std::vector<int> WeaponCount;

	//플레이어 스테이트 관련	
	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

    float StateCalTime = 0.0f; //스테이트 내에서 시간 계산이 필요할 때
    float StateCalTime2 = 0.0f;
    float StateCalTime3 = 0.0f;
    bool StateCalBool = true;
    bool StateCalBool2 = true;
    bool StateCalBool3 = true;
    float StateCalValue = 0.0f;

	//플레이어의 현재 상태
	PlayerState StateValue = PlayerState::IDLE;
    PlayerState PrevStateValue = PlayerState::IDLE;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

    void EquipWeaponStart();
    void EquipWeaponUpdate(float _DeltaTime);
    void EquipWeaponEnd();

    void DeadStart();
    void DeadUpdate(float _DeltaTime);
    void DeadEnd();

    void WinStart();
    void WinUpdate(float _DeltaTime);
    void WinEnd();

    void FlyDownStart();
    void FlyDownUpdate(float _DeltaTime);
    void FlyDownEnd();

    void FacePlantStart();
    void FacePlantUpdate(float _DeltaTime);
    void FacePlantEnd();

    void FlyAwayStart();
    void FlyAwayUpdate(float _DeltaTime);
    void FlyAwayEnd();

    void SlidingStart();
    void SlidingUpdate(float _DeltaTime);
    void SlidingEnd();

    void StandUpStart();
    void StandUpUpdate(float _DeltaTime);
    void StandUpEnd();

    void DamagedStart();
    void DamagedUpdate(float _DeltaTime);
    void DamagedEnd();

	//기본 스테이트 관련 함수
	//void Start();
	//void Update(float _DeltaTime);
	//void End();
};

