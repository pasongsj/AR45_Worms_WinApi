#include "PlayerGrave.h"

#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnums.h"

PlayerGrave::PlayerGrave() 
{
}

PlayerGrave::~PlayerGrave() 
{
}

void PlayerGrave::Start()
{

}

void PlayerGrave::SetPlayerGrave(const std::string_view& _GraveImage, float4 PlayerPos)
{
    SetPos(PlayerPos);

    AnimationRender = CreateRender(WormsRenderOrder::Player);
    AnimationRender->CreateAnimation({ .AnimationName = "Idle", .ImageName = _GraveImage, .Start = 0, .End = 19, .InterTime = 0.05f });
    AnimationRender->SetScale({ 60, 60 });
    AnimationRender->ChangeAnimation("Idle");
}