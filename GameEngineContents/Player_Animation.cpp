#include "Player.h"

void Player::CreateAnimation()
{
    //애니메이션
    {
        AnimationRender->CreateAnimation({ .AnimationName = "FacePlant", .ImageName = "FacePlant.bmp", .Start = 0, .End = 48, .InterTime = 0.05f });
    }
    {
        //좌측
        AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName = "IdleLeft.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_Move", .ImageName = "WalkLeft.bmp", .Start = 0, .End = 14, .InterTime = 0.03f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_JumpReady", .ImageName = "JumpReadyLeft.bmp", .Start = 0, .End = 9, .InterTime = 0.03f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_FlyUp", .ImageName = "FlyupLeft.bmp", .Start = 0, .End = 1, .InterTime = 0.05f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_FlyLink", .ImageName = "FlyLinkLeft.bmp", .Start = 0, .End = 6, .InterTime = 0.05f,  .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_FlyDown", .ImageName = "FlydownLeft.bmp", .Start = 0, .End = 1, .InterTime = 0.05f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_Die", .ImageName = "DieLeft.bmp", .Start = 0, .End = 59, .InterTime = 0.05f });
        AnimationRender->CreateAnimation({ .AnimationName = "Left_Win", .ImageName = "WinLeft.bmp", .Start = 0, .End = 13, .InterTime = 0.05f });
    }
    {
        //우측
        AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle", .ImageName = "IdleRight.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_Move", .ImageName = "WalkRight.bmp", .Start = 0, .End = 14, .InterTime = 0.03f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_JumpReady", .ImageName = "JumpReadyRight.bmp", .Start = 0, .End = 9, .InterTime = 0.03f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_FlyUp", .ImageName = "FlyupRight.bmp", .Start = 0, .End = 1, .InterTime = 0.05f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_FlyLink", .ImageName = "FlyLinkRight.bmp", .Start = 0, .End = 6, .InterTime = 0.05f,  .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_FlyDown", .ImageName = "FlydownRight.bmp", .Start = 0, .End = 1, .InterTime = 0.05f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_Die", .ImageName = "DieRight.bmp", .Start = 0, .End = 59, .InterTime = 0.05f });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_Win", .ImageName = "WinRight.bmp", .Start = 0, .End = 13, .InterTime = 0.05f });
    }


    //바주카                            
    {  
        AnimationRender->CreateAnimation({ .AnimationName = "Left_bazookaAim", .ImageName = "bazAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 1000.0f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_bazookaAim", .ImageName = "bazAimRight.bmp",.Start = 0, .End = 31, .InterTime = 1000.0f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_bazookaOff", .ImageName = "bazOffLeft.bmp",.Start = 0, .End = 6, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_bazookaOff", .ImageName = "bazOffRight.bmp", .Start = 0, .End = 6, .InterTime = 0.05f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_bazookaOn", .ImageName = "bazOnLeft.bmp", .Start = 0, .End = 7, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_bazookaOn", .ImageName = "bazOnRight.bmp", .Start = 0, .End = 7, .InterTime = 0.05f, .Loop = false });
    }

    //양
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_SheepOff", .ImageName = "SheepOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.025f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_SheepOff", .ImageName = "SheepOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.025f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_SheepOn", .ImageName = "SheepOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.025f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_SheepOn", .ImageName = "SheepOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.025f, .Loop = false });
    }

    //에어스트라이크
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_AirStrikeOff", .ImageName = "AirStrikeOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_AirStrikeOff", .ImageName = "AirStrikeOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_AirStrikeOn", .ImageName = "AirStrikeOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_AirStrikeOn", .ImageName = "AirStrikeOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    }

    //호밍미사일
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_HomingAim", .ImageName = "HomingAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 1000.0f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_HomingAim", .ImageName = "HomingAimRight.bmp",.Start = 0, .End = 31, .InterTime = 1000.0f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_HomingOff", .ImageName = "HomingOffLeft.bmp",.Start = 0, .End = 6, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_HomingOff", .ImageName = "HomingOffRight.bmp",.Start = 0, .End = 6, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_HomingOn", .ImageName = "HomingOnLeft.bmp",.Start = 0, .End = 6, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_HomingOn", .ImageName = "HomingOnRight.bmp", .Start = 0, .End = 6, .InterTime = 0.05f, .Loop = false });
    }

    //그레네이드 ( 수류탄 )
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_GrenadeAim", .ImageName = "GrenadeAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_GrenadeAim", .ImageName = "GrenadeAimRight.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_GrenadeOff", .ImageName = "GrenadeOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_GrenadeOff", .ImageName = "GrenadeOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_GrenadeOn", .ImageName = "GrenadeOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_GrenadeOn", .ImageName = "GrenadeOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    }

    //토치
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_TorchFire", .ImageName = "TorchFireLeft.bmp",.Start = 0, .End = 14, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_TorchFire", .ImageName = "TorchFireRight.bmp",.Start = 0, .End =14, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_TorchOff", .ImageName = "TorchOffLeft.bmp",.Start = 0, .End = 14, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_TorchOff", .ImageName = "TorchOffRight.bmp",.Start = 0, .End = 14, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_TorchOn", .ImageName = "TorchOnLeft.bmp",.Start = 0, .End = 14, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_TorchOn", .ImageName = "TorchOnRight.bmp", .Start = 0, .End = 14, .InterTime = 0.05f, .Loop = false });
    }

    //우지
    {
        AnimationRender->CreateAnimation({.AnimationName = "Left_UziFire", .ImageName = "UziFireLeft.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({.AnimationName = "Right_UziFire", .ImageName = "UziFireRight.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });
       
        AnimationRender->CreateAnimation({ .AnimationName = "Left_UziAim", .ImageName = "UziAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_UziAim", .ImageName = "UziAimRight.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });
       
        AnimationRender->CreateAnimation({.AnimationName = "Left_UziOff", .ImageName = "UziOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({.AnimationName = "Right_UziOff", .ImageName = "UziOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({.AnimationName = "Left_UziOn", .ImageName = "UziOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({.AnimationName = "Right_UziOn", .ImageName = "UziOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    }

    // 클러스터 폭탄
    { 
        //AnimationRender->CreateAnimation({ .AnimationName = "Left_ClusterBombFire", .ImageName = "ClusterBombFireLeft.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });
        //AnimationRender->CreateAnimation({ .AnimationName = "Right_ClusterBombFire", .ImageName = "ClusterBombFireRight.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_ClusterBombAim", .ImageName = "ClusterBombAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_ClusterBombAim", .ImageName = "ClusterBombAimRight.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_ClusterBombOff", .ImageName = "ClusterBombOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_ClusterBombOff", .ImageName = "ClusterBombOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_ClusterBombOn", .ImageName = "ClusterBombOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_ClusterBombOn", .ImageName = "ClusterBombOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    }

    // 권총(핸드건)
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_HandgunFire", .ImageName = "HandgunFireLeft.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_HandgunFire", .ImageName = "HandgunFireRight.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_HandgunAim", .ImageName = "HandgunAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_HandgunAim", .ImageName = "HandgunAimRight.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_HandgunOff", .ImageName = "HandgunOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_HandgunOff", .ImageName = "HandgunOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_HandgunOn", .ImageName = "HandgunOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_HandgunOn", .ImageName = "HandgunOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    }

    // 미니건
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_MinigunFire", .ImageName = "MinigunFireLeft.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_MinigunFire", .ImageName = "MinigunFireRight.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_MinigunAim", .ImageName = "MinigunAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_MinigunAim", .ImageName = "MinigunAimRight.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_MinigunOff", .ImageName = "MinigunOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_MinigunOff", .ImageName = "MinigunOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_MinigunOn", .ImageName = "MinigunOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_MinigunOn", .ImageName = "MinigunOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    }

    // 샷건
    {
        AnimationRender->CreateAnimation({ .AnimationName = "Left_ShotgunFire", .ImageName = "ShotgunFireLeft.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_ShotgunFire", .ImageName = "ShotgunFireRight.bmp",.Start = 0, .End = 31, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_ShotgunAim", .ImageName = "ShotgunAimLeft.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_ShotgunAim", .ImageName = "ShotgunAimRight.bmp",.Start = 0, .End = 31, .InterTime = 1000, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_ShotgunOff", .ImageName = "ShotgunOffLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_ShotgunOff", .ImageName = "ShotgunOffRight.bmp",.Start = 0, .End = 9, .InterTime = 0.1f, .Loop = false });

        AnimationRender->CreateAnimation({ .AnimationName = "Left_ShotgunOn", .ImageName = "ShotgunOnLeft.bmp",.Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
        AnimationRender->CreateAnimation({ .AnimationName = "Right_ShotgunOn", .ImageName = "ShotgunOnRight.bmp", .Start = 0, .End = 9, .InterTime = 0.05f, .Loop = false });
    }
}