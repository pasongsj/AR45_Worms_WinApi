#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Weapon.h"

void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;
    PrevStateValue = PrevState;

	//상태가 변했을 때, 끝날 때 필요한 코드, 시작할 때 필요한 코드를 출력하기 위함
	switch (NextState)
	{
	case PlayerState::IDLE:
	{
		IdleStart();
		break;
	}
	case PlayerState::MOVE:
	{
		MoveStart();
		break;
	}
	case PlayerState::JUMP:
	{
		JumpStart();
		break;
	}
    case PlayerState::EQUIPWEAPON:
    {
        EquipWeaponStart();
        break;
    }
    case PlayerState::Dead:
    {
        DeadStart();
        break;
    }
    case PlayerState::Win:
    {
        WinStart();
        break;
    }
    case PlayerState::FlyDown:
    {
        FlyDownStart();
        break;
    }
    case PlayerState::FacePlant:
    {
        FacePlantStart();
        break;
    }
    case PlayerState::FlyAway:
    {
        FlyAwayStart();
        break;
    }
    case PlayerState::Sliding:
    {
        SlidingStart();
        break;
    }
    case PlayerState::StandUp:
    {
        StandUpStart();
        break;
    }
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
	{
		IdleEnd();
		break;
	}
	case PlayerState::MOVE:
	{
		MoveEnd();
		break;
	}
	case PlayerState::JUMP:
	{
		JumpEnd();
		break;
	}
    case PlayerState::EQUIPWEAPON:
    {
        EquipWeaponEnd();
        break;
    }
    case PlayerState::Dead:
    {
        DeadEnd();
        break;
    }
    case PlayerState::Win:
    {
        WinEnd();
        break;
    }
    case PlayerState::FlyDown:
    {
        FlyDownEnd();
        break;
    }
    case PlayerState::FacePlant:
    {
        FacePlantEnd();
        break;
    }
    case PlayerState::FlyAway:
    {
        FlyAwayEnd();
        break;
    }
    case PlayerState::Sliding:
    {
        SlidingEnd();
        break;
    }
    case PlayerState::StandUp:
    {
        StandUpEnd();
        break;
    }
	default:
		break;
	}
}

void Player::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
	{
		IdleUpdate(_DeltaTime);
		break;
	}
	case PlayerState::MOVE:
	{
		MoveUpdate(_DeltaTime);
		break;
	}
	case PlayerState::JUMP:
	{
		JumpUpdate(_DeltaTime);
		break;
	}
    case PlayerState::EQUIPWEAPON:
    {
        EquipWeaponUpdate(_DeltaTime);
        break;
    }
    case PlayerState::Dead:
    {
        DeadUpdate(_DeltaTime);
        break;
    }
    case PlayerState::Win:
    {
        WinUpdate(_DeltaTime);
        break;
    }
    case PlayerState::FlyDown:
    {
        FlyDownUpdate(_DeltaTime);
        break;
    }
    case PlayerState::FacePlant:
    {
        FacePlantUpdate(_DeltaTime);
        break;
    }
    case PlayerState::FlyAway:
    {
        FlyAwayUpdate(_DeltaTime);
        break;
    }
    case PlayerState::Sliding:
    {
        SlidingUpdate(_DeltaTime);
        break;
    }
    case PlayerState::StandUp:
    {
        StandUpUpdate(_DeltaTime);
        break;
    }
	default:
		break;
	}
}

void Player::IdleStart()
{
	DirCheck("Idle");
    StateCalTime = 0.0f;
    StateCalTime2 = 0.0f; //IsGround == false 인 상태로 지낸 시간
    StateCalValue = 0.0f; //IsGround == false가 됐을때 y값
    MoveDir = float4::Zero;
}
void Player::IdleUpdate(float _DeltaTime)
{
    GravityApplied(_DeltaTime);

    StateCalTime += _DeltaTime;

    if (true == AnimationRender->IsAnimationEnd())
    {
        DirCheck("Idle");
    }

    if (true == IsGround)
    {
        StateCalTime2 = 0.0f;

        MoveDir = float4::Zero;
    }

    if (false == IsGround )
    {
        StateCalTime2 += _DeltaTime;
        StateCalValue = GetPos().y;
    }

    if (StateCalTime2 >= 0.3f)
    {
        ChangeState(PlayerState::FlyDown);
    }

	if (GameEngineInput::IsPress("MoveLeft") && GameEngineInput::IsPress("MoveRight"))
	{
		return;
	}

	if (true == IsMyTurn && true == CanIMove)
	{
		if (true == GameEngineInput::IsDown("MoveLeft"))
		{
            if (true == ReturnCanIMove(PlayerAngleDir::Left))
            {
                ChangeState(PlayerState::MOVE);
                return;
            }
		}

		if (true == GameEngineInput::IsDown("MoveRight"))
		{
            if (true == ReturnCanIMove(PlayerAngleDir::Right))
            {
                ChangeState(PlayerState::MOVE);
                return;
            }
		}

		if (true == GameEngineInput::IsDown("Jump"))
		{
			ChangeState(PlayerState::JUMP);
			return;
		}
	}

    if (CurWeapon != nullptr && true == IsMyTurn && StateCalTime >= 1.0f && false == CurWeapon->IsWeaponDone())
    {
        ChangeState(PlayerState::EQUIPWEAPON);
        return;
    }

}
void Player::IdleEnd()
{

}

void Player::MoveStart()
{
    DirCheck("Move");
    StateCalTime = 0.0f;
    StateCalValue = 0.0f;
}
void Player::MoveUpdate(float _DeltaTime)
{
	//동시에 누르면 진행하지 않음
	if (GameEngineInput::IsPress("MoveLeft") && GameEngineInput::IsPress("MoveRight"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	//이동키 둘중에 하나도 눌려있지 않으면 Idle상태로
	if (GameEngineInput::IsPress("MoveLeft") == false && GameEngineInput::IsPress("MoveRight") == false)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

    if (false == IsGround)
    {
        MoveDir.y = 0.0f;
        StateCalTime += _DeltaTime;
    }
    else
    {
        StateCalTime = 0.0f;
    }

    DirCheck("Move");

    if (StateCalTime > 0.05f)
    {
        StateCalValue = GetPos().y;
        ChangeState(PlayerState::FlyDown);
        return;
    }

    if (GameEngineInput::IsPress("MoveLeft"))
    {
        if (true == ReturnCanIMove(PlayerAngleDir::Left))
        {
            MoveDir = float4::Left * MoveSpeed;
            MoveDir += float4::Down * Gravity;
        }
        else
        {
            ChangeState(PlayerState::IDLE);
            return;
        }
    }

    if (GameEngineInput::IsPress("MoveRight"))
    {
        if (true == ReturnCanIMove(PlayerAngleDir::Right))
        {
            MoveDir = float4::Right * MoveSpeed;
            MoveDir += float4::Down * Gravity;
        }
        else
        {
            ChangeState(PlayerState::IDLE);
            return;
        }
    }
    

	
}
void Player::MoveEnd()
{

}

void Player::JumpStart()
{
	AnimationDir = DirString;

	std::string AnimationName = "JumpReady";
	std::string AnimationText = AnimationDir.data() + AnimationName;
	AnimationRender->ChangeAnimation(AnimationText);
  
    StateCalTime = 0.0f;
    StateCalBool = true;
    StateCalBool2 = true;
    StateCalBool3 = true;
    StateCalValue = 0.0f;
}
void Player::JumpUpdate(float _DeltaTime)
{
    if (StateCalBool == false && MoveDir.Size() <= 5.0f)
    {
        ChangeState(PlayerState::IDLE);
        return;
    }

    if (StateCalValue < GetPos().y)
    {
        StateCalValue = GetPos().y;
    }

    if (false == IsGround)
    {
        StateCalBool3 = false;
    }

    StateCalTime += _DeltaTime;

    float testvalue = 0.5f;

    if (true == AnimationRender->IsAnimationEnd() && true == StateCalBool)
    {
        //점프를 시작하려 할때, 상단 픽셀이 comlimage와 맞닿아 있다면,
        if (true == UpPixelCheck)
        {
            ChangeState(PlayerState::IDLE);
            return;
        }

        DownPixelCheck = false;

        if ("Right_" == DirString)
        {
            if (true == RightPixelCheck)
            {
                ChangeState(PlayerState::IDLE);
                return;
            }
            MoveDir += (float4::Up + float4::Right) * JumpForce;
        }
        else
        {
            if (true == LeftPixelCheck)
            {
                ChangeState(PlayerState::IDLE);
                return;
            }
            MoveDir += (float4::Up + float4::Left) * JumpForce;
        }

        std::string AnimationName = "FlyUp";
        std::string AnimationText = AnimationDir.data() + AnimationName;
        AnimationRender->ChangeAnimation(AnimationText);

        StateCalBool = false;
    }

    if (StateCalBool == false && false == StateCalBool3)
    {
        GravityApplied(_DeltaTime);

        if (true == LeftPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Left);
            MoveDir *= 0.8f;
        }
        else if (true == RightPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Right);
            MoveDir *= 0.8f;
        }
        else if (true == DownPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Down);
            MoveDir *= 0.8f;
        }
        else if (true == LeftUpPixelCheck)
        {
            if (true == UpPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::LeftUpBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::LeftUp);
            }
            MoveDir *= 0.8f;
        }
        else if (true == RightUpPixelCheck)
        {
            if (true == RightUpPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::RightUpBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::RightUp);
            }
            MoveDir *= 0.8f;
        }
        else if (true == UpPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Up);
            MoveDir *= 0.8f;
        }

        else if (true == LeftDownPixelCheck)
        {
            if (true == DownPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::LeftDownBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::LeftDown);

            }
            MoveDir *= 0.8f;
        }
        else if (true == RightDownPixelCheck)
        {
            if (true == DownPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::RightDownBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::RightDown);
            }
            MoveDir *= 0.8f;
        }
    }

    if (StateCalTime >= 0.7f && true == StateCalBool2)
    {
        std::string AnimationName = "FlyLink";
        std::string AnimationText = AnimationDir.data() + AnimationName;
        AnimationRender->ChangeAnimation(AnimationText);

        StateCalBool2 = false;
    }

    if (AnimationRender->IsAnimationEnd() && false == StateCalBool2)
    {
        ChangeState(PlayerState::FlyDown);
        return;
    }
}
void Player::JumpEnd()
{

}

void Player::DeadStart()
{
    AnimationDir = DirString;

    std::string AnimationName = "Die";
    std::string AnimationText = AnimationDir.data() + AnimationName;
    AnimationRender->ChangeAnimation(AnimationText);
}

void Player::DeadUpdate(float _DeltaTime)
{
    MoveDir = float4::Zero;

    if (AnimationRender->IsAnimationEnd())
    {
        PlayerDead();
    }
}

void Player::DeadEnd()
{

}

void Player::WinStart()
{
    AnimationDir = DirString;

    std::string AnimationName = "Win";
    std::string AnimationText = AnimationDir.data() + AnimationName;
    AnimationRender->ChangeAnimation(AnimationText);
}

void Player::WinUpdate(float _DeltatTime)
{
    MoveDir = float4::Zero;
}

void Player::WinEnd()
{

}

void Player::FlyDownStart()
{
    AnimationDir = DirString;

    std::string AnimationName = "FlyDown";
    std::string AnimationText = AnimationDir.data() + AnimationName;
    AnimationRender->ChangeAnimation(AnimationText);
}

void Player::FlyDownUpdate(float _DeltaTime)
{
    float testvalue = 0.5f;

    GravityApplied(_DeltaTime);

    //이후 거리에 따라 낙사 데미지 추가
    float Value = abs(StateCalValue - GetPos().y);

    if (PlayerState::JUMP == PrevStateValue)
    {
        if (true == DownPixelCheck || true == RightDownPixelCheck || true == LeftDownPixelCheck)
        {
            if (Value >= 50.0f)
            {
                //이후 데미지 받음
                ChangeState(PlayerState::Sliding);
                return;
            }
            else
            {
                ChangeState(PlayerState::IDLE);
                return;
            }
        }
    }
    else if (PlayerState::MOVE == PrevStateValue || PlayerState::IDLE == PrevStateValue)
    {
        MoveDir.x = 0.0f;

        if (true == DownPixelCheck || true == RightDownPixelCheck || true == LeftDownPixelCheck)
        {
            if (Value >= 50.0f)
            {
                //데미지 받음
                ChangeState(PlayerState::FacePlant);
                return;
            }
            else
            {
                ChangeState(PlayerState::IDLE);
                return;
            }
        }
    }

}

void Player::FlyDownEnd()
{
}

void Player::FacePlantStart()
{
    AnimationRender->ChangeAnimation("FacePlant");
}

void Player::FacePlantUpdate(float _DeltaTime)
{
    if (AnimationRender->IsAnimationEnd())
    {
        ChangeState(PlayerState::IDLE);
        return;
    }
}

void Player::FacePlantEnd()
{

}


void Player::FlyAwayStart()
{
    AnimationDir = DirString;

    std::string AnimationName = "FlyAway";
    std::string AnimationText = AnimationDir.data() + AnimationName;
    AnimationRender->ChangeAnimation(AnimationText);

    StateCalTime = 0.0f;
    StateCalTime2 = 0.0f;
    StateCalBool = false;
}

void Player::FlyAwayUpdate(float _DeltaTime)
{
    if (DownPixelCheck == false)
    {
        StateCalBool = true;
    }

    float testvalue = 0.5f;

    if (StateCalBool == true)
    {
        GravityApplied(_DeltaTime);

        if (true == LeftPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Left);
            MoveDir *= 0.8f;

            ChangeState(PlayerState::Sliding);
            return;
        }
        else if (true == RightPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Right);
            MoveDir *= 0.8f;

            ChangeState(PlayerState::Sliding);
            return;
        }
        else if (true == DownPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Down);
            MoveDir *= 0.8f;

            ChangeState(PlayerState::Sliding);
            return;
        }
        else if (true == LeftUpPixelCheck)
        {
            if (true == UpPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::LeftUpBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::LeftUp);
            }
            MoveDir *= 0.8f;

            ChangeState(PlayerState::Sliding);
            return;
        }
        else if (true == RightUpPixelCheck)
        {
            if (true == RightUpPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::RightUpBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::RightUp);
            }


            MoveDir *= 0.8f;

            ChangeState(PlayerState::Sliding);
            return;
        }
        else if (true == UpPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::Up);
            MoveDir *= 0.8f;
        }

        else if (true == LeftDownPixelCheck)
        {
            if (true == DownPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::LeftDownBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::LeftDown);

            }
            MoveDir *= 0.8f;

            ChangeState(PlayerState::Sliding);
            return;
        }
        else if (true == RightDownPixelCheck)
        {
            if (true == DownPixelCheck)
            {
                SetMoveDirWithAngle(WallCheckDir::RightDownBoth);
            }
            else
            {
                SetMoveDirWithAngle(WallCheckDir::RightDown);
            }
            MoveDir *= 0.8f;

            ChangeState(PlayerState::Sliding);
            return;
        }
    }

    StateCalTime += _DeltaTime;
    StateCalTime2 += _DeltaTime;
}

void Player::FlyAwayEnd()
{
}

void Player::SlidingStart()
{
    AnimationDir = DirString;

    std::string AnimationName = "Slide";
    std::string AnimationText = AnimationDir.data() + AnimationName;
    AnimationRender->ChangeAnimation(AnimationText);

    StateCalTime = 0.0f;
}

void Player::SlidingUpdate(float _DeltaTime)
{
    GravityApplied(_DeltaTime);

    StateCalTime += _DeltaTime;

    float FrictionValue = 0.7f;

    //하단 픽셀들중 하나가 닿아있고, movedir의 속도가 줄어있다면,
    if (MoveDir.Size() <= 20.0f && (true == DownPixelCheck || true == LeftDownPixelCheck || true == RightDownPixelCheck))
    {
        ChangeState(PlayerState::StandUp);
        return;
    }

    if (true == LeftPixelCheck)
    {
        SetMoveDirWithAngle(WallCheckDir::Left);
        MoveDir *= FrictionValue;
    }
    else if (true == RightPixelCheck)
    {
        SetMoveDirWithAngle(WallCheckDir::Right);
        MoveDir *= FrictionValue;
    }
    else if (true == DownPixelCheck)
    {
        SetMoveDirWithAngle(WallCheckDir::Down);
        
        MoveDir = { MoveDir.x * FrictionValue , MoveDir.y * (FrictionValue * 1 / 2) };
       
    }
    else if (true == LeftUpPixelCheck)
    {
        if (true == UpPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::LeftUpBoth);
        }
        else
        {
            SetMoveDirWithAngle(WallCheckDir::LeftUp);
        }
        MoveDir *= FrictionValue;
    }
    else if (true == RightUpPixelCheck)
    {
        if (true == RightUpPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::RightUpBoth);
        }
        else
        {
            SetMoveDirWithAngle(WallCheckDir::RightUp);
        }
        MoveDir *= FrictionValue;
    }
    else if (true == UpPixelCheck)
    {
        SetMoveDirWithAngle(WallCheckDir::Up);
        MoveDir *= FrictionValue;
    }

    else if (true == LeftDownPixelCheck)
    {
        if (true == DownPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::LeftDownBoth);
        }
        else
        {
            SetMoveDirWithAngle(WallCheckDir::LeftDown);

        }
        MoveDir *= FrictionValue;
    }
    else if (true == RightDownPixelCheck)
    {
        if (true == DownPixelCheck)
        {
            SetMoveDirWithAngle(WallCheckDir::RightDownBoth);
        }
        else
        {
            SetMoveDirWithAngle(WallCheckDir::RightDown);
        }
        MoveDir *= FrictionValue;
    }
}

void Player::SlidingEnd()
{

}

void Player::StandUpStart()
{
    AnimationDir = DirString;

    std::string AnimationName = "StandUp";
    std::string AnimationText = AnimationDir.data() + AnimationName;
    AnimationRender->ChangeAnimation(AnimationText);
}

void Player::StandUpUpdate(float _DeltaTime)
{
    GravityApplied(_DeltaTime);

    if (AnimationRender->IsAnimationEnd())
    {
        ChangeState(PlayerState::IDLE);
        return;
    }
}

void Player::StandUpEnd()
{

}