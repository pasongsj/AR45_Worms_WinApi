#include "WeaponShotgun.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>

WeaponShotgun::WeaponShotgun()
{
}

WeaponShotgun::~WeaponShotgun()
{
}

void WeaponShotgun::Start()
{
	WeaponName = "Shotgun";
	EffectGravity = false;
	isAnimation = false;
	isBlocked = true;
	isTarget = false;

	MoveSpeed = 600.0f;
	//float Gravity = 0.0f;
	//float Timer = 0.0f;
	//float WindPower = 0.0f;
	//float Dmg = 0.0f;
	//float Charge = 0.0f;

	Dir = float4{ 1,0 }.NormalizeReturn();
	//float4 PlayerPos = float4::Zero;
	BombScale = float4{ 100,100 };
	//float4 Scale = float4::Zero;	

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");
	//WeaponShotgunInit();
	//SetPos({50, 400});
}
void WeaponShotgun::Update(float _DeltaTime)
{
	if (nullptr == WeaponCollision)
	{
		WeaponShotgunInit();
		float4 PlayerPos = (GetLevel()->GetActors(WormsRenderOrder::Player))[0]->GetPos();// 임시 index0 PlayerPos
		SetPos(PlayerPos - float4{ 0, 30 });
	}
	

	WeaponMove(_DeltaTime);

	if (true == CheckCollision() && nullptr == BombRender)
	{
		
		BombRender = CreateRender(WormsRenderOrder::Weapon);
		BombRender->SetImage("TempBomb.bmp");
		BombRender->SetPosition(WeaponCollision->GetPosition());
		BombRender->SetScale(BombScale);

		BombCollision = CreateCollision(WormsRenderOrder::Weapon);
		BombCollision->SetPosition(WeaponCollision->GetPosition());
		BombCollision->SetScale(BombScale);

		WeaponCollision->Off();
	}


}

void WeaponShotgun::WeaponMove(float _DeltaTime)
{
	if (true == EffectGravity)
	{

	}
	else
	{
		WeaponCollision->SetMove(Dir * _DeltaTime * MoveSpeed);
	}
}
void WeaponShotgun::Render(float _DeltaTime)
{

}

void WeaponShotgun::WeaponShotgunInit()
{
	// ShotGun은 랜더이미지가 존재하지 않음
	WeaponCollision = CreateCollision(WormsRenderOrder::Weapon);
	WeaponCollision->SetScale({ 25,25 });



}

bool WeaponShotgun::CheckCollision()
{
	// 플레이어를 맞춘 경우
	if (nullptr != WeaponCollision && true == WeaponCollision->Collision({ .TargetGroup = static_cast<int>(WormsRenderOrder::Player), .TargetColType = CollisionType::CT_Rect, .ThisColType = CollisionType::CT_CirCle }))
	{
		return true;
	}


	// 맵과 충돌하는 경우
	if (nullptr == MapCollision)
	{
		MsgAssert("콜리전 이미지가 설정되지 않았습니다.");
		return false;
	}
	if (RGB(0, 0, 255) == MapCollision->GetPixelColor(WeaponCollision->GetPosition(), RGB(0, 0, 255))) // - 콜리전 맵 위치 수정 필요
	{
		int a = 0;

		return true;
	}

	//임시 타이머
	if (GetLiveTime() >= 5.0f)
	{
		return true;
	}

	// 스테이지 밖으로 나가는 경우 - 추가 필요

	return false;

}