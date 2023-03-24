#include "WeaponSheep.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"

#include <cmath>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

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
    if (isShoot == true && GameEngineInput::IsDown("Shoot"))
    {
        Explosion();
    }

    if (CurPlayer->GetPlayerState() == PlayerState::IDLE)
    {
        if(isShoot == false)
        {
            CurPlayer->ChangePlayerAnimation("SheepOn");
        }
    }

    //앞뒤 경사각 수시로 기록
    CheckMoveAngle();
    
	if (GameEngineInput::IsDown("Shoot"))
	{
		isShoot = true;
	}

	if(isShoot == true && isExplosion == false)
	{

        if (isJump == true)
        {
            SheepJump(_DeltaTime);
        }
        else
        {
            SheepWalking(_DeltaTime);
        }
	}

    CameraUpdate(_DeltaTime);

    //if(isExplosion == true)
    //{
    //    DebrisMove(_DeltaTime);
    //}
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
	
    ScreenSize = GameEngineWindow::GetScreenSize();
	//ExplosionAnimation = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
	//ExplosionAnimation->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End = 8, .InterTime = 0.03f , .Loop = false });
	//ExplosionAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
	//ExplosionAnimation->SetScale({ 100, 100 });
	//ExplosionAnimation->Off();

	Gravity = 0.0f; //임시 설정값

	MoveSpeed = 200.0f; //임시 설정값

	TimeCount = 0;
}

void WeaponSheep::SheepFalling(float _DeltaTime)
{

	if (RGB(0, 0, 255) != MapCollision->GetPixelColor(GetPos() + float4::Down, RGB(0, 0, 255)))
	{
		Gravity += 300.0f * _DeltaTime;
		MoveDir += float4{0, Gravity}*_DeltaTime;

		isOnMap = false;
	}
	else
	{
        for (int i = 0; ; i++)
        {
            MoveDir += {0, -1};

            if (RGB(0, 0, 255) != MapCollision->GetPixelColor(GetPos() + MoveDir, RGB(0, 0, 255)))
            {
                break;
            }
        }

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

        CurPlayer->ChangePlayerAnimation("SheepOff");

		isSet = true;
	}

	float4 NextPos = { 0,0 };

	if (isDirRight == true)
	{
		NextPos = GetPos() + float4::Right * MoveSpeed * _DeltaTime;
		WeaponRender->ChangeAnimation("SheepMoveRight");
	}
	else if (isDirRight == false)
	{
		NextPos = GetPos() + float4::Left * MoveSpeed * _DeltaTime;
		WeaponRender->ChangeAnimation("SheepMoveLeft");
	}


	if (RGB(0, 0, 255) != MapCollision->GetPixelColor(NextPos, RGB(0, 0, 255)))
	{
		SetPos(NextPos);
        SheepFalling(_DeltaTime);
	}
	else if(RGB(0, 0, 255) == MapCollision->GetPixelColor(NextPos, RGB(0, 0, 255)))
	{
        if (true == CanIMove())
        {
            SetPos(NextPos);
            SheepFalling(_DeltaTime);
        }
        else
        {
            isDirRight = !isDirRight;
        }
	}

    if(isOnMap == true)
    {
        int Num = GameEngineRandom::MainRandom.RandomInt(0, 10);

        if (Num == 0)
        {
            isJump = true;
        }
    }
}


void WeaponSheep::CheckMoveAngle()
{
    float4 SheepLeftPos = { GetPos().x - 5, GetPos().y };
    float4 SheepRightPos = { GetPos().x + 5, GetPos().y };

    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(SheepLeftPos, RGB(0, 0, 0)))
    {
        while (true)
        {
            SheepLeftPos = { SheepLeftPos.x, SheepLeftPos.y - 1 };

            if (RGB(0, 0, 255) != MapCollision->GetPixelColor(SheepLeftPos, RGB(0, 0, 0)))
            {
                break;
            }
        }
    }

    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(SheepRightPos, RGB(0, 0, 0)))
    {
        while (true)
        {
            SheepRightPos = { SheepRightPos.x, SheepRightPos.y - 1 };

            if (RGB(0, 0, 255) != MapCollision->GetPixelColor(SheepRightPos, RGB(0, 0, 0)))
            {
                break;
            }
        }

    }

    float4 LeftAngleVector = GetPos() - SheepLeftPos;
    LeftMoveAngle = LeftAngleVector.NormalizeReturn().GetAnagleDeg();

    float4 RightAngleVector = GetPos() - SheepRightPos;
    RightMoveAngle = RightAngleVector.NormalizeReturn().GetAnagleDeg();
}

bool WeaponSheep::CanIMove()
{
   
    if (isDirRight == false)
    {
        if ((LeftMoveAngle <= 1.0f && LeftMoveAngle >= -1.0f) || LeftMoveAngle >= 270 + 30)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if ((RightMoveAngle <= 181.0f && RightMoveAngle >= 179.0f) || RightMoveAngle <= 270 - 30)
        {
            return true;
        }
        else
        {
            return false;
        }
    }  
}

void WeaponSheep::Explosion()
{
    MapModifier::MainModifier->CreateHole(GetPos(), 50);
    WeaponRender->Off();
    WeaponCollision->Off();

    //for(int i =0; i<15; i++)
    //{
    //    CreateDebris();
    //}

    isExplosion = true;
}

void WeaponSheep::SheepJump(float _DeltaTime)
{
    if (isSet == false)
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

        CurPlayer->ChangePlayerAnimation("SheepOff");

        isSet = true;
    }

    float4 NextPos;
    JumpGravity += 500.0f * _DeltaTime;

    if (isDirRight == true)
    {
        NextPos = GetPos() + float4{ MoveSpeed, -MoveSpeed + JumpGravity } *_DeltaTime;
        WeaponRender->ChangeAnimation("SheepMoveRight");
    }
    else if (isDirRight == false)
    {
        NextPos = GetPos() + float4{ -MoveSpeed, -MoveSpeed + JumpGravity } *_DeltaTime;
        WeaponRender->ChangeAnimation("SheepMoveLeft");
    }

    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(NextPos, RGB(0, 0, 255)))
    {
        isJump = false;
        JumpGravity = 0;
    }
    else
    {
        SetPos(NextPos);
    }
}

void WeaponSheep::TimeCounting(float *TimeCount)
{
    if (*TimeCount == 0)
    {
        PrevTime = clock() - 1;
    }

    CurTime = clock();

    *TimeCount += (CurTime - PrevTime) / 1000.0f;

    PrevTime = CurTime;
}

void WeaponSheep::CameraUpdate(float _DeltaTime)
{
    if (isExplosion == false)
    {
        GetLevel()->SetCameraPos(GetPos() - ScreenSize.half());
    }
    else if(isExplosion == true)
    {
        TimeCounting(&TimeCount);

        if (TimeCount >= 2.0f && fLerpRatio < 1)
        {
            CurPlayerPos = CurPlayer->GetPos();
            PrevCamPos = GetLevel()->GetCameraPos();
            fLerpRatio += _DeltaTime * fLerpSpeed;
            GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
        }
        else if (fLerpRatio >= 1)
        {
            isWeaponDone = true;
        }
    }
}

//void WeaponSheep::DebrisMove(float _DeltaTime)
//{
//
//    DebrisGravity += 50.0f * _DeltaTime;
//
//    for(int i = 0; i< 15; i++)
//    {
//        
//        if (DebrisCountList[i] < 0)
//        {
//            DebrisList[i]->Off();
//            continue;
//        }
//
//        DebrisList[i]->SetMove((DebrisDirList[i] * DebrisMoveSpeed + float4{0, DebrisGravity}) * _DeltaTime );
//
//        if (RGB(0, 0, 255) == MapCollision->GetPixelColor(DebrisList[i]->GetActorPlusPos(), RGB(0, 0, 255)))
//        {
//            MapModifier::MainModifier->CreateHole(DebrisList[i]->GetActorPlusPos(), DebrisList[i]->GetScale().x);
//            DebrisCountList[i]--;
//        }
//
//    }
//
//    MoveCount++;
//}
//
//void WeaponSheep::CreateDebris()
//{
//    DebrisMoveSpeed = 100.0f;
//    GameEngineRender* Debris = CreateRender("fire.bmp", WormsRenderOrder::Weapon);
//    float Scale = GameEngineRandom::MainRandom.RandomInt(2, 10);
//    Debris->SetScale({ Scale ,Scale });
//
//    float Xdir = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
//    float Ydir = GameEngineRandom::MainRandom.RandomFloat(0.3, 1);
//
//    int Count = GameEngineRandom::MainRandom.RandomInt(1, 3);
//    
//    DebrisList.push_back(Debris);
//    DebrisDirList.push_back({ Xdir , Ydir });
//    DebrisCountList.push_back(Count);
//
//}