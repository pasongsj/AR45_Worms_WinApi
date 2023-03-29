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
}
void Player::IdleUpdate(float _DeltatTime)
{
    StateCalTime += _DeltatTime;

    if (true == AnimationRender->IsAnimationEnd())
    {
        DirCheck("Idle");
    }

    if (true == IsGround)
    {
        MoveDir = float4::Zero;
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
void Player::MoveUpdate(float _DeltatTime)
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
        StateCalTime += _DeltatTime;
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
    StateCalValue = 0.0f;
}
void Player::JumpUpdate(float _DeltatTime)
{
    if (true == IsGround && StateCalBool == false && StateCalTime > 0.3f)
    {
        ChangeState(PlayerState::IDLE);
        return;
    }

    if (StateCalValue < GetPos().y)
    {
        StateCalValue = GetPos().y;
    }

    StateCalTime += _DeltatTime;

    float testvalue = 0.5f;

    if (true == UpPixelCheck)
    {
        MoveDir = { MoveDir.x , (-MoveDir.y) };

    }
    else if (true == LeftPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == RightPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == LeftUpPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (-MoveDir.y * testvalue) };

    }
    else if (true == RightUpPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == RightDownPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == LeftDownPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }


	if (true == AnimationRender->IsAnimationEnd() && true == StateCalBool)
	{
        SetMove({ 0, -5 });

        IsGround = false;

        if ("Right_" == DirString)
        {
            MoveDir += (float4::Up + float4::Right) * 150.0f;
        }
        else
        {
            MoveDir += (float4::Up + float4::Left) * 150.0f;
        }
       
		std::string AnimationName = "FlyUp";
		std::string AnimationText = AnimationDir.data() + AnimationName;
		AnimationRender->ChangeAnimation(AnimationText);

        StateCalBool = false;
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

void Player::DeadUpdate(float _DeltatTime)
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

void Player::FlyDownUpdate(float _DeltatTime)
{
    float testvalue = 0.5f;

    if (true == UpPixelCheck)
    {
        MoveDir = { MoveDir.x , (-MoveDir.y) };
    }
    else if (true == LeftPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == RightPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == LeftUpPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (-MoveDir.y * testvalue) };

    }
    else if (true == RightUpPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == RightDownPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    else if (true == LeftDownPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

    }
    float Value = abs(StateCalValue - GetPos().y);

    if (PlayerState::JUMP == PrevStateValue)
    {
        if (true == IsGround)
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
    else if (PlayerState::MOVE == PrevStateValue)
    {
        MoveDir.x = 0.0f;

        if (true == IsGround)
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

void Player::FacePlantUpdate(float _DeltatTime)
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

    float4 PlayerPos = GetPos();

    SetMove({ 0, -5 });

    std::string AnimationName = "FlyAway";
    std::string AnimationText = AnimationDir.data() + AnimationName;
    AnimationRender->ChangeAnimation(AnimationText);

    StateCalTime = 0.0f;
    StateCalTime2 = 0.0f;
}

void Player::FlyAwayUpdate(float _DeltatTime)
{
    if (StateCalTime >= 0.3f)
    {
        MoveDir *= 0.97f;
        StateCalTime = 0.0f;
    }

    float testvalue = 0.5f;

    if (true == UpPixelCheck)
    {
        MoveDir = { MoveDir.x , (-MoveDir.y) };

        ChangeState(PlayerState::Sliding);
        return;
    }
    else if (true == DownPixelCheck)
    {
        MoveDir = { (MoveDir.x * testvalue), (-MoveDir.y * (testvalue - 0.2f)) };

        ChangeState(PlayerState::Sliding);
        return;
    }
    else if (true == LeftPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        ChangeState(PlayerState::Sliding);
        return;
    }
    else if (true == RightPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        ChangeState(PlayerState::Sliding);
        return;
    }
    else if (true == LeftUpPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (-MoveDir.y * testvalue) };

        ChangeState(PlayerState::Sliding);
        return;
    }
    else if (true == RightUpPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        ChangeState(PlayerState::Sliding);
        return;
    }
    else if (true == RightDownPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        ChangeState(PlayerState::Sliding);
        return;
    }
    else if (true == LeftDownPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        ChangeState(PlayerState::Sliding);
        return;
    }
 

    StateCalTime += _DeltatTime;
    StateCalTime2 += _DeltatTime;
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

void Player::SlidingUpdate(float _DeltatTime)
{
    StateCalTime += _DeltatTime;

    if (StateCalTime >= 0.3f)
    {
        MoveDir *= 0.9f;
        StateCalTime = 0.0f;
    }

    if (MoveDir.Size() <= 2.0f)
    {
        ChangeState(PlayerState::StandUp);
        return;
    }

    float testvalue = 0.5f;

    if (true == UpPixelCheck)
    {
        MoveDir = { MoveDir.x , (-MoveDir.y) };
    }
    else if (true == LeftPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        std::string AnimationName = "Slide";
        std::string AnimationText = DirString.data() + AnimationName;
        AnimationRender->ChangeAnimation(AnimationText);
    }
    else if (true == RightPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        std::string AnimationName = "Slide";
        std::string AnimationText = DirString.data() + AnimationName;
        AnimationRender->ChangeAnimation(AnimationText);
    }
    else if (true == LeftUpPixelCheck && "Left_" == DirString)
    {
        DirString = "Right_";
        MoveDir = { (-MoveDir.x * testvalue), (-MoveDir.y * testvalue) };

        std::string AnimationName = "Slide";
        std::string AnimationText = DirString.data() + AnimationName;
        AnimationRender->ChangeAnimation(AnimationText);
    }
    else if (true == RightUpPixelCheck && "Right_" == DirString)
    {
        DirString = "Left_";
        MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

        std::string AnimationName = "Slide";
        std::string AnimationText = DirString.data() + AnimationName;
        AnimationRender->ChangeAnimation(AnimationText);
    }
    else if (MoveDir.Size() >= 10.0f)
    {
        if (true == DownPixelCheck)
        {
            MoveDir = { (MoveDir.x * (testvalue - 0.2f)), (-MoveDir.y * (testvalue)) };
        }
        else if (true == RightDownPixelCheck && "Right_" == DirString)
        {
            DirString = "Left_";
            MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

            std::string AnimationName = "Slide";
            std::string AnimationText = DirString.data() + AnimationName;
            AnimationRender->ChangeAnimation(AnimationText);
        }
        else if (true == LeftDownPixelCheck && "Left_" == DirString)
        {
            DirString = "Right_";
            MoveDir = { (-MoveDir.x * testvalue), (MoveDir.y * testvalue) };

            std::string AnimationName = "Slide";
            std::string AnimationText = DirString.data() + AnimationName;
            AnimationRender->ChangeAnimation(AnimationText);
        }

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

void Player::StandUpUpdate(float _DeltatTime)
{
    if (AnimationRender->IsAnimationEnd())
    {
        ChangeState(PlayerState::IDLE);
        return;
    }
}

void Player::StandUpEnd()
{

}