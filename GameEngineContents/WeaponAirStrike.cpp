#include "WeaponAirStrike.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "MapModifier.h"

#include <cmath>

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

WeaponAirStrike::WeaponAirStrike()
{
}

WeaponAirStrike::~WeaponAirStrike()
{
}

void WeaponAirStrike::Start()
{
	WeaponAirStrikeInit();
    DebrisInit();
    MarkerInit();
}

void WeaponAirStrike::Update(float _DeltaTime)
{
    if (CurPlayer->GetPlayerState() == PlayerState::IDLE)
    {
        CurPlayer->ChangePlayerAnimation("AirStrikeOn");
    }

	Attack(_DeltaTime);
    DebrisAnimation(_DeltaTime);
    ExplosionAnimationOff();
	CameraUpdate(_DeltaTime);
}

void WeaponAirStrike::Render(float _DeltaTime)
{

}

void WeaponAirStrike::WeaponAirStrikeInit()
{
	SetCurPlayer();
	Airplane = CreateRender("Airplane.bmp", WormsRenderOrder::Weapon);
	Airplane->SetScaleToImage();
	Airplane->Off();

	MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

	ScreenSize = GameEngineWindow::GetScreenSize();

	WeaponNumber = static_cast<int>(WeaponNum::AirStrike);

    BombScale = 50;
    Dmg = 50;

    WeaponName = "AirStrike";

    MissileNum = 5;
    MissileList.reserve(MissileNum);

    ExplosionEffectInit();
 
}

void WeaponAirStrike::Attack(float _DeltaTime)
{
	if (GameEngineInput::IsKey("LeftMouseClick") == false)
	{
		GameEngineInput::CreateKey("LeftMouseClick", VK_LBUTTON);
	}

	if (GameEngineInput::IsDown("LeftMouseClick") == true)
	{
		SetAirPlanePos();
	}

	AirPlaneMove(_DeltaTime);

	if (isHideAirPlane == true && MissileList.size() == 0)
	{
		SetMissiles();
	}

	else if (isHideAirPlane == true && MissileList.size() > 0)
	{
		Firing(_DeltaTime);
	}

	Explosion();
}

void WeaponAirStrike::SetAirPlanePos()
{
	TargetPos = GetLevel()->GetMousePosToCamera();

	AirPlaneStartPos.x = TargetPos.x;
	AirPlaneStartPos.y = -200.0f;

	if (AirPlaneStartPos.x > CurPlayer->GetPos().x)
	{
		isMoveRight = true;
        Airplane->SetImage("AirPlaneRight.bmp");
	}
	else
	{
		isMoveRight = false;
        Airplane->SetImage("AirPlane.bmp");
	}

	if (isMoveRight == true)
	{
		AirPlaneStartPos.x -= 700.0f;
	}
	else
	{
		AirPlaneStartPos.x += 700.0f;
	}

	Airplane->SetPosition(AirPlaneStartPos);
    Marker->SetPosition(TargetPos);
    Marker->ChangeAnimation("MarkerOn");
    Marker->On();
}

void WeaponAirStrike::AirPlaneMove(float _DeltaTime)
{
    if (GameEngineInput::IsDown("Shoot"))
    {
        Airplane->On();
        Marker->Off();
        isFire = true;
    }

	if (Airplane->IsUpdate() == true)
	{
		if (isMoveRight == true)
		{
			Airplane->SetMove(float4::Right * 600.0f * _DeltaTime);
		}

		else
		{
			Airplane->SetMove(float4::Left * 600.0f * _DeltaTime);
		}
	}

	float MovePos = Airplane->GetPosition().x - AirPlaneStartPos.x;
	
	if (abs(MovePos) > 500.0f)
	{
		Airplane->Off();
		isHideAirPlane = true;
	}
}

void WeaponAirStrike::Firing(float _DeltaTime)
{
	Gravity += 0.01f * _DeltaTime;
	
	if(Dir == float4{0,0})
	{
		Dir = TargetPos - MiddleMissileStartPos;
		Dir.Normalize();


		for (int i = 0; i < MissileList.size(); i++)
		{
			MissileList[i]->On();
		}
	}

	Dir += float4{0, Gravity};

	for (int i = 0; i < MissileList.size(); i++)
	{
		MissileList[i]->SetMove(Dir * 400.0f * _DeltaTime + float4{0, Gravity * _DeltaTime});
		MissileCollisionList[i]->SetMove(Dir * 400.0f * _DeltaTime + float4{ 0, Gravity * _DeltaTime });
	}

	CurPos = MissileList[MissileNum / 2]->GetPosition();

	for (int i = 0; i < MissileList.size(); i++)
	{
		MissileList[i]->SetAngle(-Dir.GetAnagleDeg());
	}

}

void WeaponAirStrike::SetMissiles()
{
	float4 AirPlanePos = Airplane->GetPosition();
    float MissileXpos = 0.0f;

    if (isMoveRight == true)
    {
        MissileXpos = -150.0f;
    }
    else
    {
        MissileXpos = 150.0f;
    }

	for (int i = 0; i < MissileNum; i++)
	{
		MissileList.push_back(CreateRender("AirMissile.bmp", WormsRenderOrder::Weapon));
		MissileList[i]->SetRotFilter("AirMissileRot.bmp");
		MissileList[i]->SetScaleToImage();
		MissileList[i]->SetPosition(AirPlanePos - float4{ MissileXpos, -50 });
		MissileList[i]->Off();

		MissileCollisionList.push_back(CreateCollision(WormsCollisionOrder::Weapon));
		MissileCollisionList[i]->SetScale({ 30, 30 });
		MissileCollisionList[i]->SetPosition(MissileList[i]->GetPosition());

		if (isMoveRight == true)
		{
			MissileXpos += 75.0f;
		}
		else
		{
			MissileXpos -= 75.0f;
		}
	}

	MiddleMissileStartPos = MissileList[MissileNum / 2]->GetPosition();
}

void WeaponAirStrike::Explosion()
{
	for (int i = 0; i < MissileCollisionList.size(); i++)
	{
		if (MissileCollisionList[i]->GetPosition().y > 0 && MissileCollisionList[i]->IsUpdate() == true && CheckCollision(MissileCollisionList[i]) == true)
		{
			MapModifier::MainModifier->CreateHole(MissileCollisionList[i]->GetActorPlusPos(), BombScale);
			MissileCollisionList[i]->Off();
			MissileList[i]->Off();

            DebrisSet(i);
            ExplosionAnimation(i);
            DamageToPlayer();
		}
	}
}

void WeaponAirStrike::CameraUpdate(float _DeltaTime)
{
	if (Airplane->IsUpdate() == true)
	{
        float4 AirPlanePos = Airplane->GetActorPlusPos();
        PrevCamPos = GetLevel()->GetCameraPos();
        fLerpRatio += _DeltaTime * fLerpSpeed;
        GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, AirPlanePos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
	}
	else if (MissileList.size() >= 3 && MissileList[2]->IsUpdate() == true)
	{
		GetLevel()->SetCameraPos(MissileList[2]->GetActorPlusPos() - ScreenSize.half());

        PrevCamPos = { 0, 0 };
        fLerpRatio = 0.0f;
	}


    for (int i = 0; i < MissileNum; i++)
    {
        if (isDebrisSetList[i] == false)
        {
            return;
        }
    }

    TimeCounting();

    if (TimeCount >= 3.0f && fLerpRatio < 1)
    {
        CurPlayerPos = CurPlayer->GetPos();
        PrevCamPos = GetLevel()->GetCameraPos();
        fLerpRatio += _DeltaTime * fLerpSpeed;
        GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
    }

    if (fLerpRatio >= 1)
    {
        CurPlayer->ChangePlayerAnimation("AirStrikeOff");
        isWeaponDone = true;
    }

}



void WeaponAirStrike::DebrisSet(int MissileIndex)
{
    if(isDebrisSetList[MissileIndex] == false)
    {
        for (int i = MissileIndex * 9; i < (MissileIndex + 1) * 9; i++)
        {

            float X = GameEngineRandom::MainRandom.RandomFloat(-40, 40);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-40, 40);

            Smokes[i]->SetPosition(MissileList[MissileIndex]->GetPosition() + float4{ X,Y });
            Smokes[i]->ChangeAnimation("Smoke");
            Smokes[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SmokesDir[i] = Dir;
        }

        for (int i = MissileIndex * 10; i < (MissileIndex + 1) * 10; i++)
        {
            float X = GameEngineRandom::MainRandom.RandomFloat(-20, 20);
            float Y = GameEngineRandom::MainRandom.RandomFloat(-20, 20);

            Sparks[i]->SetPosition(MissileList[MissileIndex]->GetPosition() + float4{ X,Y });
            Sparks[i]->ChangeAnimation("Spark");
            Sparks[i]->On();

            float4 Dir = float4{ X,Y };
            Dir.Normalize();

            SparksDir[i] = Dir;
        }

        isDebrisSetList[MissileIndex] = true;
    }
}

void WeaponAirStrike::DebrisInit()
{
    for (int i = 0; i < MissileNum * 9; i++)
    {
        GameEngineRender* Smoke = CreateRender("Smoke100.bmp", WormsRenderOrder::Weapon);
        Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "Smoke100.bmp", .Start = 0, .End = 27, .InterTime = 0.03f , .Loop = false });
        Smoke->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Smoke100.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Smoke->SetScale({ 134, 134 });
        Smoke->Off();

        Smokes.push_back(Smoke);
        SmokesDir.push_back({ 0, 0 });
    }

    for (int i = 0; i < MissileNum * 10; i++)
    {
        GameEngineRender* Spark = CreateRender("Spark1.bmp", WormsRenderOrder::Weapon);
        Spark->CreateAnimation({ .AnimationName = "Spark", .ImageName = "Spark1.bmp", .Start = 0, .End = 31, .InterTime = 0.05f , .Loop = false });
        Spark->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Spark1.bmp", .Start = 0, .End = 0, .InterTime = 0.05f , .Loop = false });
        Spark->SetScale({ 60, 60 });
        Spark->Off();

        Sparks.push_back(Spark);
        SparksDir.push_back({ 0, 0 });
    }

    for (int i = 0; i < MissileNum; i++)
    {
        isDebrisSetList.push_back(false);
        DebrisGravityList.push_back(0);
    }
}

void WeaponAirStrike::DebrisAnimation(float _DeltaTime)
{
    for (int i = 0; i < MissileNum; i++)
    {
        if (isDebrisSetList[i] == false)
        {
            continue;
        }

        else
        {
            for (int Index = i * 10; Index < (i + 1) * 10; Index++)
            {
                Sparks[Index]->SetMove(SparksDir[Index] * 150.0f * _DeltaTime + float4{ 0, DebrisGravityList[i] } *_DeltaTime);
            }

            DebrisGravityList[i] += 250.0f * _DeltaTime;

            for (int Index = i * 9; Index < (i+1) * 9; Index++)
            {
                if (Smokes[Index]->IsAnimationEnd() == true)
                {
                    Smokes[Index]->Off();
                }
            }
        }
    }
}

void WeaponAirStrike::TimeCounting()
{
    if (isTimeSet == false)
    {
        PrevTime = clock();
        isTimeSet = true;
    }

    CurTime = clock();

    TimeCount += (CurTime - PrevTime) / 1000;

    PrevTime = CurTime;
}

void WeaponAirStrike::DamageToPlayer()
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

            ColPlayer->Damaged(Dmg, Dir, 100);
        }
    }
}

void WeaponAirStrike::ExplosionEffectInit()
{

    for (int i = 0; i < MissileNum; i++)
    {
        GameEngineRender* Circle = CreateRender("circle50.bmp", WormsRenderOrder::Weapon);
        Circle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp", .Start = 0, .End = 8, .InterTime = 0.05f , .Loop = false });
        Circle->CreateAnimation({ .AnimationName = "Idle", .ImageName = "circle50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
        Circle->SetScale({ 100, 100 });

        Circle->ChangeAnimation("Idle");
        Circle->Off();

        ExplosionCircleList.push_back(Circle);

        GameEngineRender* Elipse = CreateRender("Elipse50.bmp", WormsRenderOrder::Weapon);
        Elipse->CreateAnimation({ .AnimationName = "ExplosionElipse", .ImageName = "Elipse50.bmp", .Start = 0, .End = 19, .InterTime = 0.03f , .Loop = false });
        Elipse->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Elipse50.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
        Elipse->SetScale({ 150, 150 });

        Elipse->ChangeAnimation("Idle");
        Elipse->Off();

        ExplosionElipseList.push_back(Elipse);

        GameEngineRender* PootText = CreateRender("Poot.bmp", WormsRenderOrder::Weapon);
        PootText->CreateAnimation({ .AnimationName = "Poot", .ImageName = "Poot.bmp", .Start = 0, .End = 17, .InterTime = 0.02f , .Loop = false });
        PootText->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Poot.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
        PootText->SetScale({ 70, 70 });

        PootText->ChangeAnimation("Idle");
        PootText->Off();

        PootTextAnimationList.push_back(PootText);
    }
}

void WeaponAirStrike::ExplosionAnimation(int _Index)
{
    ExplosionCircleList[_Index]->SetPosition(MissileList[_Index]->GetPosition());
    ExplosionCircleList[_Index]->On();
    ExplosionCircleList[_Index]->ChangeAnimation("Explosion", 0);

    ExplosionElipseList[_Index]->SetPosition(MissileList[_Index]->GetPosition());
    ExplosionElipseList[_Index]->On();
    ExplosionElipseList[_Index]->ChangeAnimation("ExplosionElipse", 0);

    PootTextAnimationList[_Index]->SetPosition(MissileList[_Index]->GetPosition());
    PootTextAnimationList[_Index]->On();
    PootTextAnimationList[_Index]->ChangeAnimation("Poot", 0);
}

void WeaponAirStrike::ExplosionAnimationOff()
{
    for (int i = 0; i < MissileNum; i++)
    {
        if (ExplosionCircleList[i]->IsAnimationEnd() == true)
        {
            ExplosionCircleList[i]->Off();
        }

        if (ExplosionElipseList[i]->IsAnimationEnd() == true)
        {
            ExplosionElipseList[i]->Off();
        }

        if (PootTextAnimationList[i]->IsAnimationEnd() == true)
        {
            PootTextAnimationList[i]->Off();
        }
    }
}

void WeaponAirStrike::MarkerInit()
{
    Marker = CreateRender("Marker.bmp", WormsRenderOrder::Weapon);
    Marker->SetScale({ 60, 60 });

    Marker->CreateAnimation({ .AnimationName = "MarkerOn",.ImageName = "Marker.bmp",.Start = 0,.End = 9,.InterTime = 0.05 ,. Loop = true });
    Marker->Off();
}