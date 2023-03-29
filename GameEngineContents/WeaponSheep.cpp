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
    DebrisInit();
    PrevTime = clock();
}
void WeaponSheep::Update(float _DeltaTime)
{		
    Timer();

    if (isShoot == true && GameEngineInput::IsDown("Shoot"))
    {
        Explosion();
    }

    //앞뒤 경사각 수시로 기록
    CheckMoveAngle();
    
	if (GameEngineInput::IsDown("Shoot"))
	{
		isShoot = true;
	}

	if(isShoot == true && isExplosion == false)
	{
        SheepMove(_DeltaTime);
	}

    if (isExplosion == true)
    {
        DebrisAnimation(_DeltaTime);
    }

    ExplosionAnimationOff();
    CameraUpdate(_DeltaTime);
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

    ExplosionEffectInit();

	Gravity = 0.0f; //임시 설정값
    BombScale = 50.0f;
    Dmg = 50;
	MoveSpeed = 200.0f; //임시 설정값
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
    MapModifier::MainModifier->CreateHole(GetPos(), BombScale);
    WeaponRender->Off();
    WeaponCollision->Off();
    
    ExplosionCircle->On();
    ExplosionCircle->ChangeAnimation("Explosion", 0);

    ExplosionElipse->On();
    ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);

    PootTextAnimation->On();
    PootTextAnimation->ChangeAnimation("Poot", 0);

    DamageToPlayer();

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

void WeaponSheep::Timer()
{
    CurTime = clock();

    TimeCount = (CurTime - PrevTime) / 1000.0f;

    PrevTime = CurTime;
}

void WeaponSheep::CameraUpdate(float _DeltaTime)
{
    if (isShoot == false)
    {
        GetLevel()->SetCameraPos(CurPlayer->GetPos() - ScreenSize.half());
        return;
    }


    if (isExplosion == false)
    {
        GetLevel()->SetCameraPos(GetPos() - ScreenSize.half());
    }
    else if(isExplosion == true)
    {
        CameraTimeCount += TimeCount;

        if (CameraTimeCount >= 2.0f && fLerpRatio < 1)
        {
            CurPlayerPos = CurPlayer->GetPos();
            PrevCamPos = GetLevel()->GetCameraPos();
            fLerpRatio += _DeltaTime * fLerpSpeed;
            GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
        }
        else if (fLerpRatio >= 1 && CameraTimeCount >= 4.0f)
        {
            isWeaponDone = true;
        }
    }
}


void WeaponSheep::DebrisAnimation(float _DeltaTime)
{
    if (isDebrisSet == false)
    {
        for (int i = 0; i < Sparks.size(); i++)
        {
            float X = GameEngineRandom::MainRandom.RandomFloat(-20, 20);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-20, 20);

            Sparks[i]->SetPosition(float4{X,Y});
            Sparks[i]->ChangeAnimation("Spark");
            Sparks[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SparksDir.push_back(Dir);
        }

        for (int i = 0; i < Smokes.size(); i++)
        {
            float X = GameEngineRandom::MainRandom.RandomFloat(-40, 40);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-40, 40);

            Smokes[i]->SetPosition(float4{ X,Y });
            Smokes[i]->ChangeAnimation("Smoke");
            Smokes[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SmokesDir.push_back(Dir);
        }

        isDebrisSet = true;

    }
    else
    {
        for (int i = 0; i < Sparks.size(); i++)
        {
            Sparks[i]->SetMove(SparksDir[i] * 150.0f * _DeltaTime + float4{ 0, DebrisGravity } *_DeltaTime);
        }

        DebrisGravity += 250.0f * _DeltaTime;

        for (int i = 0; i < Smokes.size(); i++)
        {
            //Smokes[i]->SetMove(SmokesDir[i] * 25.0f * _DeltaTime);
            if (Smokes[i]->IsAnimationEnd() == true)
            {
                Smokes[i]->Off();
            }
        }
    }
}

void WeaponSheep::DebrisInit()
{
    for (int i = 0; i < 9; i++)
    {
        GameEngineRender* Smoke = CreateRender("Smoke100.bmp", WormsRenderOrder::Weapon);
        Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "Smoke100.bmp", .Start = 0, .End = 27, .InterTime = 0.03f , .Loop = false });
        Smoke->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Smoke100.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Smoke->SetScale({ 134, 134 });
        Smoke->Off();

        Smokes.push_back(Smoke);
    }

    for (int i = 0; i < 10; i++)
    {
        GameEngineRender* Spark = CreateRender("Spark1.bmp", WormsRenderOrder::Weapon);
        Spark->CreateAnimation({ .AnimationName = "Spark", .ImageName = "Spark1.bmp", .Start = 0, .End = 31, .InterTime = 0.1f , .Loop = false });
        Spark->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Spark1.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Spark->SetScale({ 60, 60 });
        Spark->Off();

        Sparks.push_back(Spark);
    }
}

void WeaponSheep::DamageToPlayer()
{
    std::vector<GameEngineCollision*> CollisionPlayer;

    MapModifier::MainModifier->SetModifierColScale({ 50, 50 });
    GameEngineCollision* HoleCollision = MapModifier::MainModifier->GetModifierCollision();

    if (true == HoleCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionPlayer))
    {
        for (int i = 0; i < CollisionPlayer.size(); i++)
        {
            Player* ColPlayer = dynamic_cast<Player*>(CollisionPlayer[i]->GetActor());
            float4 Dir = ColPlayer->GetPos() - MapModifier::MainModifier->GetModifierCollision()->GetActorPlusPos();
            Dir.Normalize();

            ColPlayer->Damaged(Dmg, Dir, 50);
        }
    }
}

void WeaponSheep::ExplosionAnimationOff()
{
    if (isExplosion == true)
    {
        if (ExplosionCircle->IsAnimationEnd() == true)
        {
            ExplosionCircle->ChangeAnimation("Idle");
            ExplosionCircle->Off();
        }

        if (ExplosionElipse->IsAnimationEnd() == true)
        {
            ExplosionElipse->ChangeAnimation("Idle");
            ExplosionElipse->Off();
        }

        if (PootTextAnimation->IsAnimationEnd() == true)
        {
            PootTextAnimation->ChangeAnimation("Idle");
            PootTextAnimation->Off();
        }
    }
}

void WeaponSheep::SheepMove(float _DeltaTime)
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