#include "PlayerDynamite.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MapModifier.h"
#include "ContentsEnums.h"
#include "Player.h"

PlayerDynamite::PlayerDynamite() 
{
}

PlayerDynamite::~PlayerDynamite() 
{
}

void PlayerDynamite::Start()
{
    std::string CircleImageName = "circle50.bmp";
    std::string ElipseImageName = "Elipse50.bmp";

    int CircleFrame = 8;
    int ElipseeFrame = 19;

    ExplosionCircle = CreateRender(CircleImageName, WormsRenderOrder::Weapon);
    ExplosionCircle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = CircleImageName, .Start = 0, .End = CircleFrame, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->CreateAnimation({ .AnimationName = "Idle", .ImageName = CircleImageName, .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->SetScale({100, 100});

    ExplosionCircle->ChangeAnimation("Idle");
    ExplosionCircle->Off();

    ExplosionElipse = CreateRender(ElipseImageName, WormsRenderOrder::Weapon);
    ExplosionElipse->CreateAnimation({ .AnimationName = "ExplosionElipse", .ImageName = ElipseImageName, .Start = 0, .End = ElipseeFrame, .InterTime = 0.03f , .Loop = false });
    ExplosionElipse->CreateAnimation({ .AnimationName = "Idle", .ImageName = ElipseImageName, .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionElipse->SetScale({ 150, 150 });

    ExplosionElipse->ChangeAnimation("Idle");
    ExplosionElipse->Off();

    AttackCollision = CreateCollision(WormsCollisionOrder::Weapon);
    AttackCollision->SetScale(ExplosionCircle->GetScale());
}

void PlayerDynamite::ExplosionDynamite(float4 _Pos)
{
    SetPos(_Pos);

    //ExplosionCircle->SetPosition(_Pos);
    //ExplosionElipse->SetPosition(_Pos);

    ExplosionCircle->ChangeAnimation("Explosion");
    ExplosionElipse->ChangeAnimation("ExplosionElipse");
    ExplosionCircle->On();
    ExplosionElipse->On();

    //구멍 만들기
    MapModifier::MainModifier->CreateHole(GetPos(), static_cast<int>(ExplosionCircle->GetScale().x));

    //플레이어 공격하기
    AttackPlayer();

    //사운드
    GameEngineSoundPlayer Sound = GameEngineResources::GetInst().SoundPlayToControl("Explosion1.wav");
    Sound.LoopCount(1);
}

void PlayerDynamite::Update(float _DeltaTime)
{
    if (true == ExplosionElipse->IsAnimationEnd())
    {
        Death();
    }

}

void PlayerDynamite::AttackPlayer()
{
    std::vector<GameEngineCollision*> CollisionList;

    int Radius = static_cast<int>(ExplosionCircle->GetScale().x);
    float MaxDmg = 40.0f;
    float MinDmg = 20.0f;

    float MinKnockBackPower = 5.0f;
    float MaxKnockBackPower = 30.0f;

    if (AttackCollision != nullptr && true == AttackCollision->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
    {
        for (int i = 0; i < CollisionList.size(); i++)
        {
            Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());

            if (ColPlayer->GetPlayerState() == PlayerState::FlyAway || ColPlayer->GetPlayerState() == PlayerState::FacePlant) // 임시 예외 처리 코드
            {
                continue;
            }

            float4 Distance = ColPlayer->GetPos() - AttackCollision->GetActorPlusPos(); //폭발 구점

            float Ratio = Distance.Size() / Radius;
            if (Ratio <= 0)
            {
                Ratio = 0;
            }
            else if (Ratio >= 1)
            {
                Ratio = 1;
            }

            int proportional_dmg = static_cast<int>(MaxDmg * (1 - Ratio) + MinDmg * (Ratio));
            float proportional_power = MaxKnockBackPower * (1 - Ratio) + MinKnockBackPower * (Ratio);
            Distance.Normalize();
            //              거리 비례데미지,    날라가는 방향,   거리 비례 날라가는 세기 
            ColPlayer->Damaged(proportional_dmg, Distance, proportional_power);
        }
    }
}