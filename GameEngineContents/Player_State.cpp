#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>

void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

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

    if (CurWeapon != nullptr && true == IsMyTurn && StateCalTime >= 2.0f)
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

    if (StateCalTime > 0.05f)
    {
        MoveDir = float4::Zero;
        ChangeState(PlayerState::IDLE);
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
}
void Player::JumpUpdate(float _DeltatTime)
{
    if (true == IsGround && StateCalBool == false && StateCalTime > 0.3f)
    {
        ChangeState(PlayerState::IDLE);
        return;
    }

    StateCalTime += _DeltatTime;

    float testvalue = 0.5f;

    if (true == UpPixelCheck)
    {
        MoveDir = { 0, (-MoveDir.y) };
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
        MoveDir = { (-MoveDir.x * testvalue), (-MoveDir.y * testvalue) };
    }


	if (true == AnimationRender->IsAnimationEnd() && true == StateCalBool)
	{
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

    if (StateCalTime >= 1.0f && true == StateCalBool2)
    {
        std::string AnimationName = "FlyDown";
        std::string AnimationText = AnimationDir.data() + AnimationName;
        AnimationRender->ChangeAnimation(AnimationText);

        StateCalBool2 = false;
    }
}
void Player::JumpEnd()
{
    MoveDir = float4::Zero;
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

//void Player::EquipWeaponStart()
//{
//    //현재 무기 애니메이션으로 변경
//}
//void Player::EquipWeaponUpdate(float _DeltatTime)
//{
//
//}
//void Player::EquipWeaponEnd()
//{
//    //장비한 무기 애니메이션용 각도 리셋
//}