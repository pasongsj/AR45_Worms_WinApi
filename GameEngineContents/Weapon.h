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


	float MoveSpeed = 0.0f;							// 무기속력
	float Gravity = 0.0f;							// 중력
	float Dmg = 0.0f;								// 폭발데미지(거리비례인지 체크필요)
	float Charge = 0.0f;							// 차지게이지

	// GlobalValue에서 가져올 것
	float fWindSpeed = 0.f;
	int fWindPhase = 0;

	float4 Dir = float4::Zero;						// 무기 진행 방향
	//float4 PlayerPos = float4::Zero;				// 플레이어 위치 ---> 지울거
	int BombScale = 0;				// 폭발 범위

	WeaponNum WeaponNumber;							// 무기 이름에 해당하는 Number
	std::string WeaponName;							// 무기 이름

	GameEngineImage* MapCollision = nullptr;		//충돌맵

	//GameEngineRender* WeaponRender = nullptr;		//렌더
	//GameEngineCollision* WeaponCollision = nullptr;	//콜리전

	Player* CurPlayer = nullptr;
	float Timer = 0.0f;								// 타이머
	float PrevTime = 0.0f;
	float CurTime = 0.0f;
	float TimeCount = 0.0f;		
	float TimeCount_2 = 0.0f;

	//GameEngineRender* AimingLine = nullptr;
	virtual void Init() {};
	virtual bool CheckCollision(GameEngineCollision* _Col); // 가상화 삭제여부 추후 고민

	float GetChargeTime();
	float4 CheckCollisionSide(GameEngineCollision* _Col);
	float4 GetShootDir();
	bool PressShoot();
	bool isEndCharging();
	void TimeCounting();
	void SetCurPlayer();

	//virtual void Charging();
	virtual void Firing(float _Deltatime) {}; // 날아가는거, 


private:

	bool isRightDir = true;
	float Height = 0.0f;


};

//타겟, 방향, 랜더, 콜리전, movespeed, 중력값, 중력 영향, 크기, 
//이름, 애니메이션, 타이머, count, 지형 통과여부, 바람수치, 
//폭발스케일, 데미지, 플레이어위치, 게이지

