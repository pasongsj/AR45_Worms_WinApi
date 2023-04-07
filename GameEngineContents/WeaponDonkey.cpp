#include "WeaponDonkey.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MapModifier.h"
#include "SmokeSparkEffect.h"
#include "Player.h"

WeaponDonkey::WeaponDonkey()
{
}

WeaponDonkey::~WeaponDonkey()
{
}

void WeaponDonkey::Start()
{
    WeaponName = "Donkey";
    Gravity = 4.0f;
    MoveSpeed = 1000;
    Dir = float4::Down;
    //BombScale = 22;

    //MaxDmg = 10;
    //MinDmg = 3;
    //MaxKnockBackPower = 22;
    //MinKnockBackPower = 22;

    MapCollision = GameEngineResources::GetInst().ImageFind("MapCity_Ground.bmp"); // 수정 필요 : Level or Map엑터에서 가져와야함

    WeaponNumber = static_cast<int>(WeaponNum::Donkey);

    DonkeyInit();
    MarkerInit();
    ExplosionEffectInit(DonkeyCollision->GetScale().x + 20);

    if (GameEngineInput::IsKey("LeftMouseClick") == false)
    {
        GameEngineInput::CreateKey("LeftMouseClick", VK_LBUTTON);
    }
}
void WeaponDonkey::Update(float _DeltaTime)
{
    if (nullptr == CurPlayer)
    {
        SetCurPlayer();
    }
    if (false == isFire)
    {
        if (GameEngineInput::IsDown("LeftMouseClick") == true)
        {
            SetTarget();
            isSettedTarget = true;
        }
        if (true == isSettedTarget && GameEngineInput::IsDown("Shoot") == true )
        {
            DonkeyRender->On();
            DonkeyCollision->On();
            Marker->Off();
            isFire = true;
        }
    }

    else // true == isFire
    {
        //CurPlayer->ChangePlayerAnimation("Idle");
        Firing(_DeltaTime);
    }

}

void WeaponDonkey::Firing(float _DeltaTime)
{
    /*float4 CamPos = float4::Zero.Lerp(GetLevel()->GetCameraPos(), DonkeyRender->GetActorPlusPos() - GameEngineWindow::GetScreenSize().half(), _DeltaTime * 100);
    GetLevel()->SetCameraPos(CamPos);*/

    CheckAnimationDone();
    Dir.y += Gravity * _DeltaTime;
    float4 MoveVec = Dir * MoveSpeed * _DeltaTime;

    float4 CheckCol = Check4Side(DonkeyCollision, DonkeyCollision->GetActorPlusPos());
    DonkeyRender->SetMove(MoveVec);
    DonkeyCollision->SetMove(MoveVec);
    if (DonkeyCollision->GetActorPlusPos().y >= 1300)
    {
        if (DonkeyRender->GetActorPlusPos().y > 1600)
        {
            isWeaponDone = true;
        }
        return;
    }
    if (CheckCol.AddAllVec() > 0 && Dir.y > 0 || (1300  < DonkeyCollision->GetActorPlusPos().y && DonkeyCollision->GetActorPlusPos().y < 1310))
    {
        DonkeyRender->SetMove(-MoveVec);
        DonkeyCollision->SetMove(-MoveVec);
        Dir.y = -abs(Dir.y) * 0.8f;

        MapModifier::MainModifier->CreateRect(DonkeyCollision->GetActorPlusPos(), DonkeyCollision->GetScale().ix()+ 10, DonkeyCollision->GetScale().iy()+20);
        MapModifier::MainModifier->CreateHole(DonkeyCollision->GetActorPlusPos() + float4(0,120), DonkeyCollision->GetScale().ix() + 20);
        

        SmokeSparkEffect* Smoke = GetLevel()->CreateActor<SmokeSparkEffect>();
        Smoke->SetPos(DonkeyCollision->GetActorPlusPos() + float4(0, 120));
        Smoke->CreateSmokeSpark(18, 0, DonkeyCollision->GetScale().x, 2.0f);

        // Poot 애니메이션
        ExplosionCircle->SetPosition(DonkeyCollision->GetPosition() + float4(0, 120));
        ExplosionCircle->On();
        ExplosionCircle->ChangeAnimation("Explosion", 0);
        //ExplosionCircle->SetScale({ BombScale,BombScale });

        ExplosionElipse->SetPosition(DonkeyCollision->GetPosition() + float4(0, 120));
        ExplosionElipse->On();
        ExplosionElipse->ChangeAnimation("ExplosionElipse", 0);
        //ExplosionElipse->SetScale({ BombScale,BombScale });

        PootTextAnimation->SetPosition(DonkeyCollision->GetPosition() + float4(0, 120));
        PootTextAnimation->On();
        PootTextAnimation->ChangeAnimation("Poot", 0);
        
    }



}

void WeaponDonkey::CheckAnimationDone()
{
    if (true == ExplosionCircle->IsAnimationEnd())
    {
        ExplosionCircle->Off();
        ExplosionCircle->ChangeAnimation("Idle");
    }
    if (true == ExplosionElipse->IsAnimationEnd())
    {
        ExplosionElipse->Off();
        ExplosionElipse->ChangeAnimation("Idle");
    }
    if (true == PootTextAnimation->IsAnimationEnd())
    {
        PootTextAnimation->Off();
        PootTextAnimation->ChangeAnimation("Idle");
    }
}



void WeaponDonkey::SetTarget()
{
    TargetPos = GetLevel()->GetMousePosToCamera();
    Marker->SetPosition(TargetPos);
    Marker->ChangeAnimation("MarkerOn");
    Marker->On();

    DonkeyRender->SetPosition(float4(TargetPos.x, -200));
    DonkeyCollision->SetPosition(float4(TargetPos.x, -200));
}

void WeaponDonkey::DonkeyInit()
{
    DonkeyRender = CreateRender("Donkey.bmp",WormsRenderOrder::Weapon);
    DonkeyRender->SetScaleToImage();

    DonkeyCollision = CreateCollision(WormsCollisionOrder::Weapon);
    DonkeyCollision->SetScale(DonkeyRender->GetScale());

    DonkeyRender->Off();
    DonkeyCollision->Off();

}
void WeaponDonkey::MarkerInit()
{
    Marker = CreateRender("Marker.bmp", WormsRenderOrder::Weapon);
    Marker->SetScale({ 60, 60 });

    Marker->CreateAnimation({ .AnimationName = "MarkerOn",.ImageName = "Marker.bmp",.Start = 0,.End = 9,.InterTime = 0.05f ,. Loop = true });
    Marker->Off();
}