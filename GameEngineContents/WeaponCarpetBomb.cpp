#include "WeaponCarpetBomb.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "GlobalValue.h"
#include "MapModifier.h"

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

    Firing(_DeltaTime);

}

void WeaponCarpetBomb::Render(float _DeltaTime)
{

}

void WeaponCarpetBomb::CarpetInit()
{
    CarpetList.reserve(5);

    for (int i = 0; i < CarpetList.capacity(); i++)
    {
        Carpet* NewCarpet = new Carpet();

        NewCarpet->CarpetRender = CreateRender("Carpet.bmp", WormsRenderOrder::Weapon);
        NewCarpet->CarpetRender->SetScale({ 60, 60 });
        NewCarpet->CarpetRender->Off();

        NewCarpet->CarpetCollision = CreateCollision(WormsCollisionOrder::Weapon);
        NewCarpet->CarpetCollision->SetScale({30, 30});

        CarpetList.push_back(NewCarpet);
    }

    SetCurPlayer();

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp");

    TruckRender = CreateRender("CarpetTruckLeft.bmp", WormsRenderOrder::Weapon);
    TruckRender->SetScale({ 100, 100 });
    TruckRender->CreateAnimation({ .AnimationName = "TruckLeft", .ImageName = "CarpetTruckLeft.bmp",.Start = 0, .End = 3, .InterTime = 0.1f});
    TruckRender->CreateAnimation({ .AnimationName = "TruckRight", .ImageName = "CarpetTruckRight.bmp",.Start = 0, .End = 3, .InterTime = 0.1f});

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

    if(isHideTruck == false)
    {
        TruckMove(_DeltaTime);
    }

    if (isHideTruck == true)
    {
        DropCarpet(_DeltaTime);
    }
}

void WeaponCarpetBomb::TruckMove(float _DeltaTime)
{
    if (TruckRender->IsUpdate() == true)
    {
        if (isMoveRight == true)
        {
            TruckRender->SetMove(float4::Right * 600.0f * _DeltaTime);
        }

        else
        {
            TruckRender->SetMove(float4::Left * 600.0f * _DeltaTime);
        }
    }

    float MovePos = TruckRender->GetPosition().x - TruckStartPos.x;

    if (abs(MovePos) > 500.0f)
    {
        TruckRender->Off();
        isHideTruck = true;
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

        CarpetList[i]->Gravity += CarpetList[i]->GravityAccel * _DeltaTime;

        CarpetList[i]->CarpetRender->SetMove(Dir * CarpetList[i]->MoveSpeed * _DeltaTime + float4{ CarpetList[i]->Wind * _DeltaTime, CarpetList[i]->Gravity });
        CarpetList[i]->CarpetCollision->SetMove(Dir * CarpetList[i]->MoveSpeed * _DeltaTime + float4{ CarpetList[i]->Wind * _DeltaTime, CarpetList[i]->Gravity });
        
        CarpetList[i]->CurPos = CarpetList[i]->CarpetRender->GetActorPlusPos();

        CarpetList[i]->Dir = CarpetList[i]->CurPos - CarpetList[i]->PrevPos;
        CarpetList[i]->Dir.Normalize();

        CarpetList[i]->PrevPos = CarpetList[i]->CurPos;

        if(CheckCollision(CarpetList[i]->CarpetCollision) == true)
        {
            Explosion(CarpetList[i]);
        }
    }

}

void WeaponCarpetBomb::SetCarpet()
{
    float4 TruckPos = TruckRender->GetActorPlusPos();
    float CarpetXpos = 0.0f;

    if (isMoveRight == true)
    {
        CarpetXpos = -150.0f;
    }
    else
    {
        CarpetXpos = +150.0f;
    }

    for (int i = 0; i < CarpetList.size(); i++)
    {
        CarpetList[i]->CarpetRender->On();

        CarpetList[i]->CarpetRender->SetPosition(TruckPos - float4{ CarpetXpos, -50 });

        CarpetList[i]->CarpetCollision->SetPosition(CarpetList[i]->CarpetRender->GetPosition());

        if (isMoveRight == true)
        {
            CarpetXpos += 75.0f;
        }
        else
        {
            CarpetXpos -= 75.0f;
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
        MapModifier::MainModifier->CreateHole(_Carpet->CarpetCollision->GetActorPlusPos(), 100.0f);

        _Carpet->CarpetRender->Off();
        _Carpet->CarpetCollision->Off();
        _Carpet->BounceCount--;
        ExplosionAnimation(_Carpet->CarpetRender->GetActorPlusPos());

        return;
    }

    else if(_Carpet->BounceCount > 1)
    {
        MapModifier::MainModifier->CreateHole(_Carpet->CarpetCollision->GetActorPlusPos(), 100.0f);
        Dir = -_Carpet->Dir;
        Dir.Normalize();

        _Carpet->Gravity = 0.0f;
        _Carpet->BounceCount--;
        _Carpet->MoveSpeed = 750.0f;
        _Carpet->GravityAccel = 10.0f;
        //_Carpet->Wind = GlobalValue::gValue.GetWindSpeed();
        _Carpet->Wind = 120.0f;

        ExplosionAnimation(_Carpet->CarpetRender->GetActorPlusPos());
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
    GameEngineRender* Explosion = CreateRender(WormsRenderOrder::Weapon);
    Explosion->SetScale({ 100, 100 });
    Explosion->CreateAnimation({ .AnimationName = "Explosion", .ImageName = "circle50.bmp",.Start = 0, .End = 8, .InterTime = 0.05f, .Loop = false});
    Explosion->SetPosition(_Pos);
    Explosion->ChangeAnimation("Explosion");

}