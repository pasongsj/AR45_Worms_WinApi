#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

class Player;
class GameEngineImage;
class Weapon :public GameEngineActor
{
public:


	static std::map<std::string, Weapon*> AllWeapons;
	// constrcuter destructer
	Weapon();
	~Weapon();

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;


	bool IsWeaponDone() // 무기사용이 끝났는지 
	{
		return isWeaponDone;
	}

	bool IsFiring() // 지금 발사중인지 bool값
	{
		return isFire;
	}

	int GetWeaponNumber()
	{
		return WeaponNumber;
	}

    std::string GetWeaponName()
    {
        return WeaponName;
    }

	//virtual void ResetWeapon() {};
protected:

	//
	bool isFire = false;							// 발사중인지 체크
	bool isWeaponDone = false;

	// 카메라 이동과 관련된 것
	float4 PrevCamPos = float4::Zero;
	float4 CurPlayerPos = float4::Zero;
	float4 LerpCamPos = float4::Zero;
	float fLerpRatio = 0.f;
	float fLerpSpeed = 2.f;


    float MinKnockBackPower = 0.0f;
    float MaxKnockBackPower = 0.0f;

	float MoveSpeed = 0.0f;							// 무기속력
	float Gravity = 0.0f;							// 중력

    float Dmg = 0.0f;   //삭제 예정
    float MinDmg = 0.0f;
	float MaxDmg = 0.0f;								// 폭발데미지(거리비례인지 체크필요)
	float Charge = 0.0f;							// 차지게이지

	// GlobalValue에서 가져올 것
	float fWindSpeed = 0.f;
	int fWindPhase = 0;

	float4 Dir = float4::Zero;						// 무기 진행 방향
	//float4 PlayerPos = float4::Zero;				// 플레이어 위치 ---> 지울거
	float BombScale = 0.0f;				// 폭발 범위

	int WeaponNumber = 0;							// 무기 이름에 해당하는 Number
	std::string WeaponName;							// 무기 이름

	GameEngineImage* MapCollision = nullptr;		//충돌맵


	Player* CurPlayer = nullptr;
	float Timer = 0.0f;								// 타이머

	float4 ScreenSize = { 0,0 };
	//GameEngineRender* AimingLine = nullptr;
	virtual void Init() {};
	virtual bool CheckCollision(GameEngineCollision* _Col); // 가상화 삭제여부 추후 고민

	float4 CheckCollisionSide(GameEngineCollision* _Col);
	float4 GetShootDir();
    
    // Shoot  Key와 관련된 커맨드
    bool DownShoot();
	bool PressShoot();
    bool UpShoot();
	float GetChargeTime();

	bool isEndCharging();
	void SetCurPlayer();
	bool AttackPlayer(GameEngineCollision* _Col,bool _AttackSelf = true);
    void AttackPlayerGun(GameEngineCollision* _Col, float _Distance);

    void ExplosionEffectInit(float _CircleDiameter);

	//virtual void Charging();
	virtual void Firing(float _Deltatime) {}; // 날아가는거, 


    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineRender* PootTextAnimation = nullptr;

	
private:

	bool isRightDir = true;
	float Height = 0.0f;


};

//타겟, 방향, 랜더, 콜리전, movespeed, 중력값, 중력 영향, 크기, 
//이름, 애니메이션, 타이머, count, 지형 통과여부, 바람수치, 
//폭발스케일, 데미지, 플레이어위치, 게이지

