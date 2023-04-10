#include "WeaponCarpetBomb.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "GlobalValue.h"
#include "MapModifier.h"
#include "Map.h"

#include <ctime>

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <gameenginePlatform/GameengineInput.h>

WeaponCarpetBomb::WeaponCarpetBomb()
{
}

WeaponCarpetBomb::~WeaponCarpetBomb()
{
    for (int i = 0; i < CarpetList.size(); i++)
    {
        delete CarpetList[i];
        CarpetList[i] = nullptr;
    }
}

void WeaponCarpetBomb::Start()
{
    CarpetInit();
    MarkerInit();

    if (GameEngineInput::IsKey("LeftMouseClick") == false)
    {
        GameEngineInput::CreateKey("LeftMouseClick", VK_LBUTTON);
    }
}

void WeaponCarpetBomb::Update(float _DeltaTime)
{

    Timer();

    if(GameEngineInput::IsDown("LeftMouseClick") == true && isFire == false)
    {
        SetTarget();
        SetTruck();
        //TruckRender->On();      
    }

    if (GameEngineInput::IsDown("Shoot") == true && isFire == false)
    {
        isFire = true;
        TruckRender->On();   
        Marker->Off();
    }

    if(ExplosionEndCount < 5)
    {
        Firing(_DeltaTime);
    }
    else if (ExplosionEndCount == 5)
    {
        CameraWaitCount += TimeCount;

        if (CameraWaitCount >= 1.0f && fLerpRatio < 1)
        {
            CurPlayerPos = CurPlayer->GetPos();
            PrevCamPos = GetLevel()->GetCameraPos();
            fLerpRatio += _DeltaTime * fLerpSpeed;
            GetLevel()->SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - GameEngineWindow::GetScreenSize().half(), fLerpRatio));
        }
        else if (fLerpRatio >= 1)
        {
            TurnChangeCount += TimeCount;

            if(TurnChangeCount >= 0.5f)
            {
                isWeaponDone = true;
            }
        }
    }

    CameraUpdate();
    SparkMove(_DeltaTime);
}

void WeaponCarpetBomb::Render(float _DeltaTime)
{
    //HDC _hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

    //float4 CamPos = GetLevel()->GetCameraPos();
    //for (int i = 0; i < CarpetList.size(); i++)
    //{
    //    if(CarpetList[i]->CarpetRender->IsUpdate() == true)
    //    {
    //        Rectangle(_hdc, CarpetList[i]->CarpetCollision->GetActorPlusPos().x - 15 - CamPos.x,
    //            CarpetList[i]->CarpetCollision->GetActorPlusPos().y - 15 - CamPos.y,
    //            CarpetList[i]->CarpetCollision->GetActorPlusPos().x + 15 - CamPos.x,
    //            CarpetList[i]->CarpetCollision->GetActorPlusPos().y + 15 - CamPos.y);
    //    }
    //}
}

void WeaponCarpetBomb::CarpetInit()
{
    CarpetList.reserve(5);
    SparkList.reserve(100);
    GravityList.reserve(100);
    DirList.reserve(100);

    for (int i = 0; i < CarpetList.capacity(); i++)
    {
        Carpet* NewCarpet = new Carpet();

        NewCarpet->CarpetRender = CreateRender("Carpet.bmp", WormsRenderOrder::Weapon);
        NewCarpet->CarpetRender->SetScale({ 60, 60 });
        NewCarpet->CarpetRender->CreateAnimation({ .AnimationName = "Roll", .ImageName = "carpet.bmp",.Start = 0, .End = 9, .InterTime = 0.05f });
        NewCarpet->CarpetRender->ChangeAnimation("Roll");
        NewCarpet->CarpetRender->Off();

        NewCarpet->CarpetCollision = CreateCollision(WormsCollisionOrder::Weapon);
        NewCarpet->CarpetCollision->SetScale({30, 30});

        CarpetList.push_back(NewCarpet);
    }

    SetCurPlayer();

    Gravity = 500.0f;
    MinDmg = 10;
    MaxDmg = 25;

    MinKnockBackPower = 10.0f;
    MaxKnockBackPower = 20.0f;

    BombScale = 100.0f;
    std::string Name = Map::MainMap->GetColMapName();
    MapCollision = GameEngineResources::GetInst().ImageFind(Name);

    TruckRender = CreateRender("CarpetTruckLeft.bmp", WormsRenderOrder::Weapon);
    TruckRender->SetScale({ 100, 100 });
    TruckRender->CreateAnimation({ .AnimationName = "TruckLeft", .ImageName = "CarpetTruckLeft.bmp",.Start = 0, .End = 3, .InterTime = 0.05f});
    TruckRender->CreateAnimation({ .AnimationName = "TruckRight", .ImageName = "CarpetTruckRight.bmp",.Start = 0, .End = 3, .InterTime = 0.05f});

    TruckRender->Off();

    MoveSpeed = 600.0f;

    WeaponName = "Carpet";
    WeaponNumber = static_cast<int>(WeaponNum::Carpet);
}

void WeaponCarpetBomb::MarkerInit()
{
    Marker = CreateRender("Marker.bmp", WormsRenderOrder::Weapon);
    Marker->SetScale({ 60, 60 });

    Marker->CreateAnimation({ .AnimationName = "MarkerOn",.ImageName = "Marker.bmp",.Start = 0,.End = 9,.InterTime = 0.05f ,. Loop = true });
    Marker->Off();
}

void WeaponCarpetBomb::SetTarget()
{
    GameEngineResources::GetInst().SoundPlay("JUSTYOUWAIT.wav");
    TargetPos = GetLevel()->GetMousePosToCamera();

    Marker->SetPosition(TargetPos);
    Marker->ChangeAnimation("MarkerOn");
    Marker->On();

}

void WeaponCarpetBomb::SetTruck()
{
    TruckStartPos.x = TargetPos.x;
    TruckStartPos.y = -200.0f;

    if (TruckStartPos.x > CurPlayer->GetPos().x)
    {
        isMoveRight = true;
        TruckRender->ChangeAnimation("TruckRight");
        Dir = float4::Right;
    }
    else
    {
        isMoveRight = false;
        TruckRender->ChangeAnimation("TruckLeft");
        Dir = float4::Left;
    }

    if (isMoveRight == true)
    {
        TruckStartPos.x -= 700.0f;
    }
    else
    {
        TruckStartPos.x += 700.0f;
    }

    TruckRender->SetPosition(TruckStartPos);
}


void WeaponCarpetBomb::Firing(float _DeltaTime)
{
    if (isFire == false)
    {
        return;
    }

    TruckMove(_DeltaTime);

    if (isHideTruck == true)
    {
        DropCarpet(_DeltaTime);
    }
}

void WeaponCarpetBomb::TruckMove(float _DeltaTime)
{
    float MovePos = TruckRender->GetPosition().x - TruckStartPos.x;

    if(isTruckSoundOn == false)
    {
        GameEngineResources::GetInst().SoundPlay("Airstrike.wav");
        isTruckSoundOn = true;
    }

    if (abs(MovePos) > 2000.0f)
    {
        TruckRender->Off();
        return;
    }
    else if (abs(MovePos) > 500.0f)
    {
        isHideTruck = true;
    }

    if (TruckRender->IsUpdate() == true)
    {
        if (isMoveRight == true)
        {
            TruckRender->SetMove(float4::Right * 1500.0f * _DeltaTime);
        }

        else
        {
            TruckRender->SetMove(float4::Left * 1500.0f * _DeltaTime);
        }
    }

}

void WeaponCarpetBomb::DropCarpet(float _DeltaTime)
{

    if (isCarpetSet == false)
    {
        SetCarpet();
        isCarpetSet = true;
    }


    for (int i = 0; i < CarpetList.size(); i++)
    {
        if (CarpetList[i]->PrevPos == float4{ 0, 0 })
        {
            CarpetList[i]->PrevPos = CarpetList[i]->CarpetRender->GetActorPlusPos();
        }

        if (CarpetList[i]->MoveDir == float4{ 0, 0 })
        {
            CarpetList[i]->MoveDir = Dir;
        }

        float wind = GlobalValue::gValue.GetWindSpeed();

        CarpetList[i]->Gravity += CarpetList[i]->GravityAccel * _DeltaTime;

        CarpetList[i]->CarpetRender->SetMove(CarpetList[i]->MoveDir * CarpetList[i]->MoveSpeed * _DeltaTime + float4{ wind * _DeltaTime, CarpetList[i]->Gravity });
        CarpetList[i]->CarpetCollision->SetMove(CarpetList[i]->MoveDir * CarpetList[i]->MoveSpeed * _DeltaTime + float4{ wind * _DeltaTime, CarpetList[i]->Gravity });
        
        CarpetList[i]->CurPos = CarpetList[i]->CarpetRender->GetActorPlusPos();

        CarpetList[i]->RotDir = CarpetList[i]->CurPos - CarpetList[i]->PrevPos;
        CarpetList[i]->RotDir.Normalize();

        CarpetList[i]->PrevPos = CarpetList[i]->CurPos;

        if(CheckCollision(CarpetList[i]->CarpetCollision) == true)
        {
            Explosion(CarpetList[i]);
            DamageToPlayer(i);
        }
    }

}

void WeaponCarpetBomb::SetCarpet()
{
    float4 TruckPos = TruckRender->GetActorPlusPos();
    float CarpetXpos = 0.0f;

    if (isMoveRight == true)
    {
        CarpetXpos = -100.0f;
    }
    else
    {
        CarpetXpos = +100.0f;
    }

    for (int i = 0; i < CarpetList.size(); i++)
    {
        CarpetList[i]->CarpetRender->On();

        CarpetList[i]->CarpetRender->SetPosition(TruckPos - float4{ CarpetXpos, -50 });

        CarpetList[i]->CarpetCollision->SetPosition(CarpetList[i]->CarpetRender->GetPosition());

        if (isMoveRight == true)
        {
            CarpetXpos += 50.0f;
        }
        else
        {
            CarpetXpos -= 50.0f;
        }
    }
}

void WeaponCarpetBomb::Explosion(Carpet* _Carpet)
{
    if (_Carpet->BounceCount < 0)
    {
        return;
    }

    else if (_Carpet->BounceCount == 1)
    {
        MakeSmoke(_Carpet->CarpetRender->GetActorPlusPos());
        MakeSpark(_Carpet->CarpetRender->GetActorPlusPos());

        MapModifier::MainModifier->CreateHole(_Carpet->CarpetCollision->GetActorPlusPos(), BombScale);

        _Carpet->CarpetRender->Off();
        _Carpet->CarpetCollision->Off();
        _Carpet->BounceCount--;
        ExplosionAnimation(_Carpet->CarpetRender->GetActorPlusPos());
        GameEngineResources::GetInst().SoundPlay("Explosion3.wav");
        
        ExplosionEndCount++;

        return;
    }

    else if(_Carpet->BounceCount > 1)
    {
        MakeSmoke(_Carpet->CarpetRender->GetActorPlusPos());
        MakeSpark(_Carpet->CarpetRender->GetActorPlusPos());

        float RandomXdir = GameEngineRandom::MainRandom.RandomFloat(-0.5, 0.5);
        float RandomYdir = GameEngineRandom::MainRandom.RandomFloat(-1.0, 0.0);

        MapModifier::MainModifier->CreateHole(_Carpet->CarpetCollision->GetActorPlusPos(), BombScale);
        _Carpet->MoveDir = -_Carpet->RotDir + float4{ RandomXdir , RandomYdir };
        Dir.Normalize();

        _Carpet->Gravity = 0.0f;
        _Carpet->BounceCount--;
        _Carpet->MoveSpeed = 400.0f;
        _Carpet->GravityAccel = 15.0f;

        ExplosionAnimation(_Carpet->CarpetRender->GetActorPlusPos());
        GameEngineResources::GetInst().SoundPlay("Explosion1.wav");
    }
}

void WeaponCarpetBomb::Timer()
{
    CurTime = static_cast<float>(clock());

    TimeCount = (CurTime - PrevTime) / 1000.0f;

    PrevTime = CurTime;
}

void WeaponCarpetBomb::ExplosionAnimation(float4 _Pos)
{
    GameEngineRender* ExplosionCircle = CreateRender(WormsRenderOrder::Weapon);
    ExplosionCircle->SetScale({ 100, 100 });
    ExplosionCircle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp",.Start = 0, .End = 8, .InterTime = 0.05f, .Loop = false});
    ExplosionCircle->SetPosition(_Pos);
    ExplosionCircle->ChangeAnimation("Explosion");

    GameEngineRender* ExplosionElipse = CreateRender(WormsRenderOrder::Weapon);
    ExplosionElipse->SetScale({ 150, 150 });
    ExplosionElipse->CreateAnimation({ .AnimationName = "Elipse", .ImageName = "Elipse75.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    ExplosionElipse->SetPosition(_Pos);
    ExplosionElipse->ChangeAnimation("Elipse");

    GameEngineRender* Poot = CreateRender(WormsRenderOrder::Weapon);
    Poot->SetScale({ 70, 70 });
    Poot->CreateAnimation({ .AnimationName = "Poot", .ImageName = "Poot.bmp",.Start = 0, .End = 17, .InterTime = 0.05f, .Loop = false });
    Poot->SetPosition(_Pos);
    Poot->ChangeAnimation("Poot");
}

void WeaponCarpetBomb::CameraUpdate()
{
    if (isHideTruck == false && TruckRender->IsUpdate() == true)
    {
        GetLevel()->SetCameraPos(TruckRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());
    }
    else if(isHideTruck == true && CarpetList[2]->CarpetRender->IsUpdate() == true)
    {
        GetLevel()->SetCameraPos(CarpetList[2]->CarpetRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half());
    }
}

void WeaponCarpetBomb::DamageToPlayer(int _Index)
{
    GameEngineCollision* HoleCollision = CreateCollision(WormsCollisionOrder::Weapon);
    HoleCollision->SetScale({ BombScale, BombScale });
    HoleCollision->SetPosition(CarpetList[_Index]->CarpetCollision->GetActorPlusPos());

    AttackPlayer(HoleCollision);
}

void WeaponCarpetBomb::MakeSmoke(float4 _pos)
{
    for (int i = 0; i < 9; i++)
    {
        GameEngineRender* Smoke = CreateRender(WormsRenderOrder::Weapon);

        Smoke->CreateAnimation({ .AnimationName = "Smoke", .ImageName = "Smoke100.bmp", .Start = 0, .End = 27, .InterTime = 0.03f , .Loop = false });
        Smoke->SetScale({ 134, 134 });

        float X = GameEngineRandom::MainRandom.RandomFloat(-40, 40);
        float Y = GameEngineRandom::MainRandom.RandomFloat(-40, 40);

        Smoke->SetPosition(_pos + float4{ X,Y });
        Smoke->ChangeAnimation("Smoke");
        Smoke->On();
    }
}

void WeaponCarpetBomb::MakeSpark(float4 _pos)
{
    for (int i = 0; i < 5; i++)
    {
        GameEngineRender* Spark = CreateRender(WormsRenderOrder::Weapon);

        Spark->CreateAnimation({ .AnimationName = "Spark", .ImageName = "Spark1.bmp", .Start = 0, .End = 31, .InterTime = 0.05f , .Loop = false });
        Spark->SetScale({ 60, 60 });

        float X = GameEngineRandom::MainRandom.RandomFloat(-40, 40);
        float Y = GameEngineRandom::MainRandom.RandomFloat(-40, 40);

        Spark->SetPosition(_pos + float4{ X,Y });
        Spark->ChangeAnimation("Spark");
        Spark->On();

        SparkList.push_back(Spark);
        GravityList.push_back(0);

        float4 SparkDir = float4{ X, Y };
        SparkDir.Normalize();

        DirList.push_back(SparkDir);
    }
}

void  WeaponCarpetBomb::SparkMove(float _DeltaTime)
{

    float Wind = GlobalValue::gValue.GetWindSpeed();


    //DirList µµ ÇÊ¿ä
    for (int i = 0; i < SparkList.size(); i++)
    {
        SparkList[i]->SetMove(DirList[i] * 200.0f * _DeltaTime + float4{0,  GravityList[i]} *_DeltaTime);
        GravityList[i] += 5.0f;
    }
}