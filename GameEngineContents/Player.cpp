#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());

	//키 설정이 안되어있으면 키 설정( 플레이어가 여러명 일 경우를 대비하여 키 설정이 없으면 설정함 ) 
	if (GameEngineInput::IsKey("MoveLeft") == false)
	{
		//캐릭터 이동 및 행동
		GameEngineInput::CreateKey("MoveLeft", 'A');
		GameEngineInput::CreateKey("MoveRight", 'D');
	}

	ChangeState(PlayerState::IDLE);
}

void Player::Update(float _DeltaTime)
{
	MoveDir = float4::Zero; //매 프레임마다 MoveDir 초기화

	MoveCalculation(_DeltaTime);
	UpdateState(_DeltaTime);
}

void Player::MoveCalculation(float _DeltaTime)
{
	SetMove(MoveDir * _DeltaTime);
}

void Player::Render(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	//위치 확인용
	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}