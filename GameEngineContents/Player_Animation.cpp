#include "Player.h"

void Player::CreateAnimation()
{
    //애니메이션
    {
        //좌측
        AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName = "IdleLeft.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_Move", .ImageName = "WalkLeft.bmp", .Start = 0, .End = 14, .InterTime = 0.03f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_JumpReady", .ImageName = "JumpReadyLeft.bmp", .Start = 0, .End = 9, .InterTime = 0.03f, .Loop = false});
        AnimationRender->CreateAnimation({ .AnimationName = "Left_FlyUp", .ImageName = "FlyupLeft.bmp", .Start = 0, .End = 1, .InterTime = 0.03f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_FlyDown", .ImageName = "FlydownLeft.bmp", .Start = 0, .End = 1, .InterTime = 0.03f });
    }
    {
        //우측
        AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle", .ImageName = "IdleRight.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_Move", .ImageName = "WalkRight.bmp", .Start = 0, .End = 14, .InterTime = 0.03f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_JumpReady", .ImageName = "JumpReadyRight.bmp", .Start = 0, .End = 9, .InterTime = 0.03f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_FlyUp", .ImageName = "FlyupRight.bmp", .Start = 0, .End = 1, .InterTime = 0.03f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_FlyDown", .ImageName = "FlydownRight.bmp", .Start = 0, .End = 1, .InterTime = 0.03f });
    }
}