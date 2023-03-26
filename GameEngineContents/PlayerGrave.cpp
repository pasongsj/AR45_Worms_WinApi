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

void PlayerGrave::Update(float _DeltaTime)
{

    GravePixelCheck();
    DirCheck();
    GravityApplied(_DeltaTime);
    MoveCalculation(_DeltaTime);
}

void PlayerGrave::SetPlayerGrave(const std::string_view& _GraveImage, GameEngineImage* _ColImage, float4 PlayerPos)
{
    SetPos(PlayerPos);
    
    ColImage = _ColImage;

    MoveDir += float4::Up * 150.0f;

    JumpTime = 0;

    AnimationRender = CreateRender(WormsRenderOrder::Player);
    AnimationRender->CreateAnimation({ .AnimationName = "Idle", .ImageName = _GraveImage, .Start = 0, .End = 19, .InterTime = 0.05f });
    AnimationRender->SetScale({ 60, 60 });
    AnimationRender->ChangeAnimation("Idle");
}

void PlayerGrave::MoveCalculation(float _DeltaTime)
{
    float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
    NextPos = PullUpObject(NextPos, _DeltaTime);

    if (true == DownPixelCheck && JumpTime >= 3)
    {
        return;
    }

    SetMove(MoveDir * _DeltaTime);
}

float4 PlayerGrave::PullUpObject(float4 _NextPos, float _DeltaTime)
{
    if (RGB(0, 0, 255) != ColImage->GetPixelColor(_NextPos, RGB(0, 0, 255)))
    {
        return _NextPos;
    }

    float4 NextMoveDir = MoveDir;

    while (true)
    {
        MoveDir.y -= 1;

        _NextPos = GetPos() + MoveDir * _DeltaTime;

        if (RGB(0, 0, 255) == ColImage->GetPixelColor(_NextPos, RGB(0, 0, 255)))
        {
            continue;
        }

        return _NextPos;
    }
}

void PlayerGrave::GravityApplied(float _DeltaTime)
{
    MoveDir += (float4::Down * 300.0f * _DeltaTime);
}

void PlayerGrave::GravePixelCheck()
{
    float4 UpPixel = { GetPos().x , GetPos().y - 20 };
    float4 DownPixel = { GetPos().x , GetPos().y + 1 };

    if (RGB(0, 0, 255) == ColImage->GetPixelColor(UpPixel, RGB(0, 0, 0)))
    {
        UpPixelCheck = true;
    }
    else
    {
        UpPixelCheck = false;
    }

    if (RGB(0, 0, 255) == ColImage->GetPixelColor(DownPixel, RGB(0, 0, 0)))
    {
        DownPixelCheck = true;
    }
    else
    {
        DownPixelCheck = false;
    }
}

void PlayerGrave::DirCheck()
{
    if (JumpTime >= 3)
    {
        return;
    }

    if (MoveDir.y > 0.1f)
    {
        CurrentDir = GraveDir::Down;
    }
    else
    {
        CurrentDir = GraveDir::Up;
    }

    if (GraveDir::Up == CurrentDir)
    {
        if (true == UpPixelCheck)
        {
            MoveDir = { MoveDir.x, MoveDir.y * - 0.5f };
            CurrentDir = GraveDir::Down;
        }
    }
    else
    {
        if (true == DownPixelCheck)
        {
            MoveDir = { MoveDir.x, MoveDir.y * - 0.5f };
            CurrentDir = GraveDir::Up;
            ++JumpTime;
        }
    }


}