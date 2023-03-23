#include "WeaponSheep.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>

WeaponSheep::WeaponSheep()
{
}

WeaponSheep::~WeaponSheep()
{
}

void WeaponSheep::Start()
{
	WeaponSheepInit();
}

void WeaponSheep::Update(float _DeltaTime)
{				
	SheepFalling(_DeltaTime);

    CheckMoveAngle();

	if (GameEngineInput::IsDown("Shoot"))
	{
		isShoot = true;
	}

	if(isShoot == true)
	{
		SheepWalking(_DeltaTime);
	}

}		
		
void WeaponSheep::Render(float _DeltaTime)
{			
	if (true == GameEngineInput::IsDown("ChangePlayer"))
	{
		ResetWeapon();
	}
}			
			
void WeaponSheep::ResetWeapon()
{
	SetCurPlayer();
	isShoot = false;
	isSet = false;
}

void WeaponSheep::WeaponSheepInit()
{
	SetCurPlayer();

	WeaponRender = CreateRender("SheepWalkRight.bmp", static_cast<int>(WormsRenderOrder::Weapon));
	WeaponCollision = CreateCollision(static_cast<int>(WormsCollisionOrder::Weapon));

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

	SetPos({ 500, 0 });

	WeaponRender->SetPosition({0, -10});
	WeaponRender->SetScale({ 60, 60 });
	WeaponRender->Off();

	WeaponCollision->SetPosition(WeaponRender->GetPosition());
	WeaponCollision->SetScale(WeaponRender->GetScale());
	WeaponCollision->Off();

	WeaponName = "Sheep";

	WeaponRender->CreateAnimation({ .AnimationName = "SheepMoveRight", .ImageName = "SheepWalkRight.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	WeaponRender->CreateAnimation({ .AnimationName = "SheepMoveLeft", .ImageName = "SheepWalkLeft.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	
	//ExplosionAnimation = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
	//ExplosionAnimation->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End = 8, .InterTime = 0.03f , .Loop = false });
	//ExplosionAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
	//ExplosionAnimation->SetScale({ 100, 100 });
	//ExplosionAnimation->Off();

	Gravity = 0.0f; //임시 설정값
	//GravityAccel = 0.0f; //임시 설정값

	MoveSpeed = 1500.0f; //임시 설정값

	//EffectGravity = true;
	//isAnimation = true;
	//isBlocked = true;
	//isTarget = false;

	TimeCount = 0;
}

void WeaponSheep::SheepFalling(float _DeltaTime)
{

	if (RGB(0, 0, 255) != MapCollision->GetPixelColor(GetPos() + float4::Down, RGB(0, 0, 255)))
	{
		MoveDir += float4::Down * _DeltaTime + float4{0, Gravity};
		Gravity += 2.0f * _DeltaTime;

		isOnMap = false;
	}
	else
	{
		Gravity = 0;
		isOnMap = true;
	}	

	SetMove(MoveDir);

	MoveDir = float4::Zero;
}

void WeaponSheep::SheepWalking(float _DeltaTime)
{
	if(isSet == false)
	{
		WeaponRender->On();
		SetPos(CurPlayer->GetPos());

		if (CurPlayer->GetPlayerDir() == float4::Right)
		{
			isDirRight = true;
		}
		else if (CurPlayer->GetPlayerDir() == float4::Left)
		{
			isDirRight = false;
		}

		isSet = true;
	}

	float4 NextPos = { 0,0 };

	if (isDirRight == true)
	{
		NextPos = GetPos() + float4::Right * 100.0f * _DeltaTime + float4::Up * 10.0f;
		WeaponRender->ChangeAnimation("SheepMoveRight");
	}
	else if (isDirRight == false)
	{
		NextPos = GetPos() + float4::Left * 100.0f * _DeltaTime + float4::Up * 10.0f;
		WeaponRender->ChangeAnimation("SheepMoveLeft");
	}

	if (RGB(0, 0, 255) != MapCollision->GetPixelColor(NextPos, RGB(0, 0, 255)))
	{
		SetPos(NextPos - float4::Up * 10.0f);
	}
	else if(RGB(0, 0, 255) == MapCollision->GetPixelColor(NextPos, RGB(0, 0, 255)))
	{

		if (RGB(0, 0, 255) != MapCollision->GetPixelColor(NextPos + float4::Up * 10.0f, RGB(0, 0, 255)))
		{
			SetPos(NextPos);
		}
	}

    if (isDirRight == true && RightMoveAngle < 240)
    {
        isDirRight = false;
    }
    else if (isDirRight == false && LeftMoveAngle > 300)
    {
         isDirRight = true;
    }
}


void WeaponSheep::CheckMoveAngle()
{
    float4 PlayerLeftPos = { GetPos().x - 5, GetPos().y };
    float4 PlayerRightPos = { GetPos().x + 5, GetPos().y };

    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(PlayerLeftPos, RGB(0, 0, 0)))
    {
        while (true)
        {
            PlayerLeftPos = { PlayerLeftPos.x, PlayerLeftPos.y - 1 };

            if (RGB(0, 0, 255) != MapCollision->GetPixelColor(PlayerLeftPos, RGB(0, 0, 0)))
            {
                break;
            }
        }
    }

    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(PlayerRightPos, RGB(0, 0, 0)))
    {
        while (true)
        {
            PlayerRightPos = { PlayerRightPos.x, PlayerRightPos.y - 1 };

            if (RGB(0, 0, 255) != MapCollision->GetPixelColor(PlayerRightPos, RGB(0, 0, 0)))
            {
                break;
            }
        }

    }

    float4 LeftAngleVector = GetPos() - PlayerLeftPos;
    LeftMoveAngle = LeftAngleVector.NormalizeReturn().GetAnagleDeg();

    float4 RightAngleVector = GetPos() - PlayerRightPos;
    RightMoveAngle = RightAngleVector.NormalizeReturn().GetAnagleDeg();
}