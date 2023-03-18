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
	Weapon() ;
	~Weapon();

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;

	float4 GetShootDir();
	bool PressShoot();
	bool isEndCharging();
	void TimeCounting();
	void SetCurPlayer();
	virtual void ResetWeapon() {};
	virtual bool CheckCollision(GameEngineCollision* _Col = nullptr);
protected:

	//
	bool EffectGravity = true;						// 중력영향
	bool isAnimation = false;						// 애니메이션
	bool isBlocked = false;							// 지형 통과여부
	bool isTarget = false;							// 타겟 설정 여부

	float MoveSpeed = 0.0f;							// 무기속력
	float Gravity = 0.0f;							// 중력
	float GravityAccel = 0.0f;						// 중력가속도
	float WindPower = 0.0f;							// 바람세기
	float Dmg = 0.0f;								// 폭발데미지(거리비례인지 체크필요)
	float Charge = 0.0f;							// 차지게이지

	float4 Dir = float4::Zero;						// 무기 진행 방향
	float4 PlayerPos = float4::Zero;				// 플레이어 위치
	float4 BombScale = float4::Zero;				// 폭발 범위
	//float4 Scale = float4::Zero;					// 랜더스케일

	std::string WeaponName;							// 무기 이름

	GameEngineImage* MapCollision = nullptr;		//충돌맵

	GameEngineRender* WeaponRender = nullptr;		//렌더
	GameEngineCollision* WeaponCollision = nullptr;	//콜리전

	Player* CurPlayer = nullptr;

	float PrevTime = 0.0f;
	float CurTime = 0.0f;
	float Timer = 0.0f;								// 타이머
	float TimeCount = 0.0f;		

	GameEngineRender* AimingLine = nullptr;

private:

	float Height = 0.0f;
	bool isRightDir = true;

		
};

//타겟, 방향, 랜더, 콜리전, movespeed, 중력값, 중력 영향, 크기, 
//이름, 애니메이션, 타이머, count, 지형 통과여부, 바람수치, 
//폭발스케일, 데미지, 플레이어위치, 게이지

