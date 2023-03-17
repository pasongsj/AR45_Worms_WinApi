#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnums.h"

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	AnimationRender = CreateRender(WormsRenderOrder::Player);
	AnimationRender->SetScale({ 60, 60 });
	AnimationRender->SetPosition({ 0, -10 });
	//애니메이션
	{
		//좌측
		//CreatePlayerAnimation("Left_Idle", "IdleLeft.bmp", 0, 5, 0.1f);

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName = "IdleLeft.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move", .ImageName = "WalkLeft.bmp", .Start = 0, .End = 14, .InterTime = 0.1f });
	}
	{
		//우측
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle", .ImageName = "IdleRight.bmp", .Start = 0, .End = 5, .InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move", .ImageName = "WalkRight.bmp", .Start = 0, .End = 14, .InterTime = 0.1f });

	}

	//콜리전
	{
		BodyCollision = CreateCollision(WormsCollisionOrder::Player);
		BodyCollision->SetMove({ 0, -10 });
		BodyCollision->SetScale({ 30 , 30 });
	}

	//키 설정이 안되어있으면 키 설정( 플레이어가 여러명 일 경우를 대비하여 키 설정이 없으면 설정함 ) 
	if (GameEngineInput::IsKey("MoveLeft") == false)
	{
		//캐릭터 이동 및 행동
		GameEngineInput::CreateKey("MoveRight", 'D');
		GameEngineInput::CreateKey("MoveLeft", 'A');
	}

	ChangeState(PlayerState::IDLE);
}

void Player::SetColImage(const std::string_view& _Name)
{
	ColImage = GameEngineResources::GetInst().ImageFind(_Name.data());
}

void Player::Update(float _DeltaTime)
{
	MoveDir = float4::Zero; //매 프레임마다 MoveDir 초기화
	
	if (true == IsMyTurn) //내 턴일때만 스테이트 변경
	{
		UpdateState(_DeltaTime);
	}
	GravityApplied();
	MoveCalculation(_DeltaTime);

}

void Player::GravityApplied()
{
	MoveDir += (float4::Down * Gravity);
}

void Player::MoveCalculation(float _DeltaTime)
{
	float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
	NextPos = PullUpCharacter(NextPos, _DeltaTime);

	SetMove(MoveDir * _DeltaTime);
}

float4 Player::PullUpCharacter(float4 _NextPos, float _DeltaTime)
{
	if (RGB(0, 0, 255) != ColImage->GetPixelColor(_NextPos, RGB(0, 0, 255)))
	{
		return _NextPos;
	}

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


void Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	if (GameEngineInput::IsPress("MoveLeft"))
	{
		DirString = "Left_";
	}
	else if (GameEngineInput::IsPress("MoveRight"))
	{
		DirString = "Right_";
	}

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}

void Player::CreatePlayerAnimation(const std::string_view& _AnimationName, const std::string_view& _ImageName, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	AnimationRender->CreateAnimation({ .AnimationName = _AnimationName, .ImageName = _ImageName, .Start = _StartFrame, .End = _EndFrame, .InterTime = _InterTime, .Loop = _Loop });
}
void Player::ChangePlayerAnimation(const std::string_view& _AnimationName)
{
	DirCheck(_AnimationName);
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
