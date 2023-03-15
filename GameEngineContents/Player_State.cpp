#include "Player.h"

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

	}
	case PlayerState::MOVE:
	{

	}
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
	{

	}
	case PlayerState::MOVE:
	{

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

	}
	case PlayerState::MOVE:
	{

	}
	default:
		break;
	}
}