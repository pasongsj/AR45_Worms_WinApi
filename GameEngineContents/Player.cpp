#include "Player.h"

#include<iostream>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineDebug.h>

#include "GlobalValue.h"
#include "PlayerHPUI.h"
#include "PlayerGetDamagedUI.h"
#include "ContentsEnums.h"
#include "Weapon.h"
#include "PlayerGrave.h"

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
    CreateAnimation();

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
		GameEngineInput::CreateKey("Jump", 'K');

		GameEngineInput::CreateKey("TestButton", 'M');
	}

    PlayerGraveImageStringView = "Grave5.bmp";

    SetWeaponCount();

	SetHPUI("RedNumberRender.bmp", "RedNameTag.bmp", "PlayerSelectArrowRed.bmp");
	ChangeState(PlayerState::IDLE);
}

void Player::SetHPUI(const std::string_view& _HPNumberImage, const std::string_view& _NametagImage, const std::string_view& _ArrowImage) //HP 이미지 등을 세팅해주는 메서드
{
	PlayerHPNumberImageStringView = _HPNumberImage;

	HPUI = GetLevel()->CreateActor<PlayerHPUI>();
	HPUI->SetPlayerHPUI(_HPNumberImage, _NametagImage, _ArrowImage, &PlayerHP);
}

void Player::SetIsMyTurn(bool _Value)
{
	IsMyTurn = _Value;
	HPUI->SetSelectPlayerRender(_Value);

    if (WeaponNum::None == CurWeaponNum)
    {
        return;
    }

    //본인 턴이고, CurWeapon의 개수가 0이 아니라면 생성함
    if (true == _Value && WeaponCount[static_cast<int>(CurWeaponNum)] != 0)
    {
        StateCalTime = 0.0f; //플레이어 아이들 애니메이션에서 특정 시간 있다가 무기를 들게끔
        GlobalValue::gValue.SetWeapon(CurWeaponNum);
    }
}

void Player::UsingHealkit(int _Value)
{
    PlayerHP += _Value;

    if (PlayerHP >= MaxHP)
    {
        PlayerHP = MaxHP;
    }

}

void Player::SetColImage(const std::string_view& _Name)
{
	ColImage = GameEngineResources::GetInst().ImageFind(_Name.data());
}

void Player::Test()
{
	if (GameEngineInput::IsDown("TestButton") && IsMyTurn == true)
	{

        float4 TestDir = float4::Up;
        if (GameEngineInput::IsPress("MoveRight") == true)
        {
            TestDir += float4::Right;
        }
        else
        {
            TestDir += float4::Left;
        }

        float Power = 400.0f;

		Damaged(10, TestDir, Power);
        //ChangeState(PlayerState::Win);

        //UsingHealkit(50);
	}
}

void Player::CheckAlive()
{
    if (PlayerHP <= 0)
    {
        TestChangeDeadState();
    }
}

void Player::TestChangeDeadState()
{
    if (true == IsAlive)
    {
        ChangeState(PlayerState::Dead);
        IsAlive = false;
    }
}

void Player::Damaged(int _Damage, float4 _Dir, float _Power)
{
	if (DamagedTime >= 0.0f)
	{
		PlayerHP -= _Damage;
		DamagedTime = 0.0f;
		
        if (_Dir == float4::Zero)
        {
            ChangeState(PlayerState::FacePlant);
        }
        else
        {
            //이동방향을 설정
            MoveDir = _Dir.NormalizeReturn() * _Power;
            if (MoveDir.x > 0.0f)
            {
                DirString = "Right_";
            }
            else
            {
                DirString = "Left_";
            }

            ChangeState(PlayerState::FlyAway);

        }

        DisplayDamageUI(_Damage);
	}
}

void Player::DisplayDamageUI(float _Damage)
{
    PlayerGetDamagedUI* DamagedUI = GetLevel()->CreateActor<PlayerGetDamagedUI>();
    DamagedUI->SetDamagedUI(PlayerHPNumberImageStringView, _Damage);

    float4 DamagedUIPos = { HPUI->GetPos().x, HPUI->GetPos().y - 20.0f };
    DamagedUI->SetPos(DamagedUIPos);
}

void Player::CheckTurn()
{
    if (false == IsMyTurn || nullptr == CurWeapon)
    {
        return;
    }

    if (true == CurWeapon->IsWeaponDone())
    {
        SetIsMyTurn(false);
        SetCanIMove(true);

        int CurWeaponNumber = CurWeapon->GetWeaponNumber();

        if (0 == WeaponCount[CurWeaponNumber])
        {
            MsgAssert("방금 개수가 0인 무기를 사용했습니다");
        }
        else if (0 < WeaponCount[CurWeaponNumber])
        {
            WeaponCount[CurWeaponNumber] -= 1;
        }

        CurWeapon->Death();
        CurWeapon = nullptr;
    }
}

void Player::Update(float _DeltaTime)
{
    PlayerPixelCheck();
    UpdateState(_DeltaTime);
   
    MoveCalculation(_DeltaTime);
	
    CheckAlive();

    IsGroundCheck();
    CheckTurn();
    Test();

	HPUI->SetPos({GetPos().x , GetPos().y - 50.0f}); //UI 프레임마다 위치 조정
	DamagedTime += _DeltaTime; //플레이어가 한번에 여러번의 데미지를 받지않기 위한 변수
}

void Player::GravityApplied(float _DeltaTime)
{
	MoveDir += (float4::Down * Gravity * _DeltaTime);
}

void Player::MoveCalculation(float _DeltaTime)
{
	float4 NextPos = GetPos() + (MoveDir * _DeltaTime);
    
    NextPos = PullUpCharacter(NextPos, _DeltaTime);

    SetMoveAngle();

    if (true == IsGround)
    {
        //움직이는 상태가 아니면 리턴함 중력으로 인해 점점 떨어지는 버그를 수정하기 위해
        if (PlayerState::Dead == StateValue ||
            PlayerState::IDLE == StateValue ||
            PlayerState::EQUIPWEAPON == StateValue ||
            PlayerState::Win == StateValue ||
            PlayerState::StandUp == StateValue)
        {
            return;
        }
    }

    SetMove(MoveDir * _DeltaTime);

}

void Player::IsGroundCheck()
{
	float4 PlayerGroundCheckPos = { GetPos().x , GetPos().y + 1 };

	if (RGB(0, 0, 255) == ColImage->GetPixelColor(PlayerGroundCheckPos, RGB(0, 0, 0)))
	{
		IsGround = true;
	}
	else
	{
		IsGround = false;
	}
}

void Player::PlayerPixelCheck()
{
    float4 CenterPos = { GetPos().x, GetPos().y + SetMoveDIrCenterPos };						                           
    float Angle = 0.0f;

    for (; Angle < 360.0f; ++Angle)
    {
        float4 CheckPos = { 0.0f, -SetMoveDirRadius };		                                        
        CheckPos.RotaitonZDeg(-Angle);				                                        
        CheckPos += CenterPos;						                                       

        const float AngleValue = 22.5;


        if ((Angle >= 0.0f && Angle <= AngleValue) || (Angle >= 360.0f - AngleValue && Angle <= 360.0f))
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                UpPixelCheck = true;
            }
            else
            {
                UpPixelCheck = false;
            }
        }
        else if (Angle >= AngleValue && Angle <= AngleValue * 3) //좌측 상단
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                LeftUpPixelCheck = true;
            }
            else
            {
                LeftUpPixelCheck = false;
            }
        }
        else if (Angle >= AngleValue * 3 && Angle <= AngleValue * 5) // 좌측
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                LeftPixelCheck = true;
            }
            else
            {
                LeftPixelCheck = false;
            }
        }
        else if (Angle >= AngleValue * 5 && Angle <= AngleValue * 7) //좌측 하단
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                LeftDownPixelCheck = true;
            }
            else
            {
                LeftDownPixelCheck = false;
            }
        }
        else if (Angle >= AngleValue * 7 && Angle <= AngleValue * 9) //하단
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                DownPixelCheck = true;
            }
            else
            {
                DownPixelCheck = false;
            }
        }
        else if (Angle >= AngleValue * 9 && Angle <= AngleValue * 11) // 우측 하단
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                RightDownPixelCheck = true;
            }
            else
            {
                RightDownPixelCheck = false;
            }
        }
        else if (Angle >= AngleValue * 11 && Angle <= AngleValue * 13) // 우측
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                RightPixelCheck = true;
            }
            else
            {
                RightPixelCheck = false;
            }
        }
        else if (Angle >= AngleValue * 13 && Angle <= AngleValue * 15) //우측 상단
        {
            if (RGB(0, 0, 255) == ColImage->GetPixelColor(CheckPos, RGB(0, 0, 0))) //상단
            {
                RightUpPixelCheck = true;
            }
            else
            {
                RightUpPixelCheck = false;
            }
        }     
    }
}

void Player::SetMoveAngle()
{
	float4 PlayerLeftPos = { GetPos().x - 5, GetPos().y };
	float4 PlayerRightPos = { GetPos().x + 5, GetPos().y };

	if (RGB(0, 0, 255) == ColImage->GetPixelColor(PlayerLeftPos, RGB(0, 0, 0)))
	{
		while (true)
		{
			PlayerLeftPos = { PlayerLeftPos.x, PlayerLeftPos.y - 1 };

			if (RGB(0, 0, 255) != ColImage->GetPixelColor(PlayerLeftPos, RGB(0, 0, 0)))
			{
				break;
			}
		}
	}

	if (RGB(0, 0, 255) == ColImage->GetPixelColor(PlayerRightPos, RGB(0, 0, 0)))
	{
		while (true)
		{
			PlayerRightPos = { PlayerRightPos.x, PlayerRightPos.y - 1 };

			if (RGB(0, 0, 255) != ColImage->GetPixelColor(PlayerRightPos, RGB(0, 0, 0)))
			{
				break;
			}
		}

	}

	float4 LeftAngleVector = GetPos() - PlayerLeftPos;
	LeftMoveAngle = LeftAngleVector.NormalizeReturn().GetAnagleDeg();

	float4 RightAngleVector = GetPos() - PlayerRightPos;
	RightMoveAngle = RightAngleVector.NormalizeReturn().GetAnagleDeg();
}

bool Player::ReturnCanIMove(PlayerAngleDir _Dir)
{
    if (PlayerAngleDir::Left == _Dir)
    {
        if ((LeftMoveAngle <= 1.0f && LeftMoveAngle >= -1.0f) || LeftMoveAngle >= 270 + AngleLimit)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if ((RightMoveAngle <= 181.0f && RightMoveAngle >= 179.0f) || RightMoveAngle <= 270 - AngleLimit)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

float4 Player::PullUpCharacter(float4 _NextPos, float _DeltaTime)
{
    float4 ColImageScale = ColImage->GetImageScale();

    if (_NextPos.x < 0 || _NextPos.x >ColImageScale.x || _NextPos.y < 0 || _NextPos.y > ColImageScale.y)
    {
        return _NextPos;
    }

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



void Player::SetMoveDirWithAngle(WallCheckDir _Dir)
{
    if ("Left_" == DirString)
    {
        switch (_Dir)
        {
        case WallCheckDir::LeftUpBoth:
        {
            MoveDir = { -MoveDir.x , -MoveDir.y };
            break;
        }
        case WallCheckDir::LeftDownBoth:
        {
            MoveDir = { -MoveDir.x , -MoveDir.y };
            break;
        }
        case WallCheckDir::Up:
        {
            MoveDir = { MoveDir.x , -MoveDir.y };
            break;
        }
        case WallCheckDir::LeftUp:
        {
            MoveDir = { (-MoveDir.x), (MoveDir.y) };
            break;
        }
        case WallCheckDir::Left:
        {
            MoveDir = { (-MoveDir.x), (MoveDir.y) };
            break;
        }
        case WallCheckDir::LeftDown:
        {
            MoveDir = { (-MoveDir.x), (MoveDir.y) };
            break;
        }
        case WallCheckDir::Down:
        {
            MoveDir = { (MoveDir.x), (-MoveDir.y) };
            break;
        }

        }
    }
    else if ("Right_" == DirString)
    {
        switch (_Dir)
        {
        case WallCheckDir::RightUpBoth:
        {
            MoveDir = { -MoveDir.x , -MoveDir.y };
            break;
        }
        case WallCheckDir::RightDownBoth:
        {
            MoveDir = { -MoveDir.x , -MoveDir.y };
            break;
        }
        case WallCheckDir::Up:
        {
            MoveDir = { MoveDir.x , -MoveDir.y };
            break;
        }
        case WallCheckDir::RightUp:
        {
            MoveDir = { (-MoveDir.x ), (MoveDir.y ) };
            break;
        }
        case WallCheckDir::Right:
        {
            MoveDir = { (-MoveDir.x), (MoveDir.y) };
            break;
        }
        case WallCheckDir::RightDown:
        {
            MoveDir = { (-MoveDir.x), (MoveDir.y) };
            break;
        }
        case WallCheckDir::Down:
        {
            MoveDir = { (MoveDir.x), (-MoveDir.y) };
            break;
        }
        }
    }

    if (MoveDir.x > 0.0f)
    {
        DirString = "Right_";
    }
    else
    {
        DirString = "Left_";
    }
}

bool Player::GetPlayerWallCheck(WallCheckDir _Dir)  //현재 그 방향이 벽과 맞닿아 있는지를 가져옴 
{
    float Radius = 5.0f;
    float Angle = 0.0f;

    float4 CenterPos = { GetPos().x, GetPos().y - 4.0f };


    switch (_Dir)
    {
    case WallCheckDir::Up:
    {
        for (; Angle < 360.0f; ++Angle)
        {
            float4 CheckPos = { 0.0f, -Radius };
            CheckPos.RotaitonZDeg(Angle);
            CheckPos += CenterPos;
            int Value = 0;
        }
        break;
    }
    case WallCheckDir::Down:
    {
        break;
    }
    case WallCheckDir::Left:
    {
        break;
    }
    case WallCheckDir::Right:
    {
        break;
    }
    case WallCheckDir::LeftUp:
    {
        break;
    }
    case WallCheckDir::LeftDown:
    {
        break;
    }
    case WallCheckDir::RightUp:
    {
        break;
    }
    case WallCheckDir::RightDown:
    {
        break;
    }
    }


    return true;
}


void Player::DirCheck(const std::string_view& _AnimationName, int _CurIndex)
{
    std::string PrevDirString = DirString;

    if (PlayerState::EQUIPWEAPON == StateValue)
    {
        AnimationRender->ChangeAnimation(DirString + _AnimationName.data(), _CurIndex, true);
    }
    else
    {
        AnimationRender->ChangeAnimation(DirString + _AnimationName.data(), _CurIndex);
    }

    if (true == IsMyTurn)
    {
        if (GameEngineInput::IsDown("MoveLeft"))
        {
            DirString = "Left_";
        }

        if (GameEngineInput::IsDown("MoveRight"))
        {
            DirString = "Right_";
        }
    }

    if (PrevDirString != DirString)
    {
        AnimationRender->ChangeAnimation(DirString + _AnimationName.data(), _CurIndex, true);
    }
}

void Player::CreatePlayerAnimation(const std::string_view& _AnimationName, const std::string_view& _ImageName, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop)
{
	AnimationRender->CreateAnimation({ .AnimationName = _AnimationName, .ImageName = _ImageName, .Start = _StartFrame, .End = _EndFrame, .InterTime = _InterTime, .Loop = _Loop });
}

void Player::ChangePlayerAnimation(const std::string_view& _AnimationName, int _CurIndex)
{
	DirCheck(_AnimationName, _CurIndex);
}

void Player::SetPlayerAnimationFrame(int _Frame)
{
	AnimationRender->SetAnimationFrame(_Frame);
}

void Player::Render(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

  /*  float Angle = 0.0f;
    float4 CenterPos = { GetPos().x, GetPos().y + SetMoveDIrCenterPos };

    for (; Angle < 90.0f; ++Angle)
    {
        float4 CheckPos = { 0.0f, -SetMoveDirRadius };
        CheckPos.RotaitonZDeg(-Angle);
        CheckPos += CenterPos;
        float4 CameraCheckPos = CheckPos - GetLevel()->GetCameraPos();

        Rectangle(DoubleDC,
            CameraCheckPos.ix() - 1,
            CameraCheckPos.iy() - 1,
            CameraCheckPos.ix() + 1,
            CameraCheckPos.iy() + 1
        );
    }
*/

	//위치 확인용
	//Rectangle(DoubleDC,
	//	ActorPos.ix() - 5,
	//	ActorPos.iy() - 5,
	//	ActorPos.ix() + 5,
	//	ActorPos.iy() + 5
	//);

	if (true == IsMyTurn)
	{
		std::string PlayerLeftAngle = "PlayerLeftAngle = ";
		PlayerLeftAngle = PlayerLeftAngle + std::to_string(LeftMoveAngle);
		GameEngineLevel::DebugTextPush(PlayerLeftAngle);

		std::string PlayerRightAngle = "PlayerRightAngle = ";
		PlayerRightAngle = PlayerRightAngle + std::to_string(RightMoveAngle);
		GameEngineLevel::DebugTextPush(PlayerRightAngle);

		std::string PlayerIsGround = "PlayerIsGround = ";
		PlayerIsGround = PlayerIsGround + std::to_string(IsGround);
		GameEngineLevel::DebugTextPush(PlayerIsGround);

        std::string PlayerDirString = "PlayerDirString = ";
        PlayerDirString = PlayerDirString + DirString;
        GameEngineLevel::DebugTextPush(PlayerDirString);

        //float4 NextPos = (GetPos() + MoveDir * _DeltaTime) - GetLevel()->GetCameraPos();

        float4 CenterPos = { GetPos().x, GetPos().y + SetMoveDIrCenterPos };

        float Angle = 0.0f;

       /* for (; Angle < 360.0f; ++Angle)
        {
            float4 CheckPos = { 0.0f, -SetMoveDirRadius };
            CheckPos.RotaitonZDeg(-Angle);
            CheckPos += CenterPos;
            float4 CheckImagePos = CheckPos - GetLevel()->GetCameraPos();


            const float AngleValue = 22.5;

            Rectangle(DoubleDC,
                CheckImagePos.ix() - 1,
                CheckImagePos.iy() - 1,
                CheckImagePos.ix() + 1,
                CheckImagePos.iy() + 1
            );

        }*/


        //Rectangle(DoubleDC,
        //    NextPos.ix() - 5,
        //    NextPos.iy() - 5,
        //    NextPos.ix() + 5,
        //    NextPos.iy() + 5
        //);
    /*    float4 PlayerLeftPixel = { GetPos().x - 10.0f, GetPos().y - 11.0f };
        float4 PlayerRightPixel = { GetPos().x + 10.0f, GetPos().y - 11.0f };
        float4 PlayerUpPixel = { GetPos().x , GetPos().y - 21.0f };
        float4 PlayerDownPixel = { GetPos().x , GetPos().y + 1.0f };
        float4 PlayerLeftUpPixel = { GetPos().x - 8.0f, GetPos().y - 19.0f };
        float4 PlayerRightUpPixel = { GetPos().x + 8.0f, GetPos().y - 19.0f };
        float4 PlayerLeftDownPixel = { GetPos().x - 8.0f, GetPos().y - 2.0f };
        float4 PlayerRightDownPixel = { GetPos().x + 8.0f, GetPos().y - 2.0f };

        PlayerLeftPixel -= GetLevel()->GetCameraPos();
        PlayerRightPixel -= GetLevel()->GetCameraPos();
        PlayerUpPixel -= GetLevel()->GetCameraPos();
        PlayerDownPixel -= GetLevel()->GetCameraPos();
        PlayerLeftUpPixel -= GetLevel()->GetCameraPos();
        PlayerRightUpPixel -= GetLevel()->GetCameraPos();
        PlayerLeftDownPixel -= GetLevel()->GetCameraPos();
        PlayerRightDownPixel -= GetLevel()->GetCameraPos();

        Rectangle(DoubleDC,
            PlayerLeftPixel.ix() - 1,
            PlayerLeftPixel.iy() - 1,
            PlayerLeftPixel.ix() + 1,
            PlayerLeftPixel.iy() + 1
        );
        Rectangle(DoubleDC,
            PlayerRightPixel.ix() - 1,
            PlayerRightPixel.iy() - 1,
            PlayerRightPixel.ix() + 1,
            PlayerRightPixel.iy() + 1
        );
        Rectangle(DoubleDC,
            PlayerUpPixel.ix() - 1,
            PlayerUpPixel.iy() - 1,
            PlayerUpPixel.ix() + 1,
            PlayerUpPixel.iy() + 1
        );
        Rectangle(DoubleDC,
            PlayerDownPixel.ix() - 1,
            PlayerDownPixel.iy() - 1,
            PlayerDownPixel.ix() + 1,
            PlayerDownPixel.iy() + 1
        );

        Rectangle(DoubleDC,
            PlayerLeftUpPixel.ix() - 1,
            PlayerLeftUpPixel.iy() - 1,
            PlayerLeftUpPixel.ix() + 1,
            PlayerLeftUpPixel.iy() + 1
        );
        Rectangle(DoubleDC,
            PlayerRightUpPixel.ix() - 1,
            PlayerRightUpPixel.iy() - 1,
            PlayerRightUpPixel.ix() + 1,
            PlayerRightUpPixel.iy() + 1
        );
        Rectangle(DoubleDC,
            PlayerLeftDownPixel.ix() - 1,
            PlayerLeftDownPixel.iy() - 1,
            PlayerLeftDownPixel.ix() + 1,
            PlayerLeftDownPixel.iy() + 1
        );
        Rectangle(DoubleDC,
            PlayerRightDownPixel.ix() - 1,
            PlayerRightDownPixel.iy() - 1,
            PlayerRightDownPixel.ix() + 1,
            PlayerRightDownPixel.iy() + 1
        );*/

        if (nullptr != CurWeapon)
        {
            std::string PlayerCurWeapon = "PlayerCurWeapon = ";
            PlayerCurWeapon = PlayerCurWeapon + std::to_string(CurWeapon->GetWeaponNumber());
            GameEngineLevel::DebugTextPush(PlayerCurWeapon);
        }

        std::string PlayerStateText = "PlayerState = ";

        switch (StateValue)
        {
        case PlayerState::IDLE:
            PlayerStateText = PlayerStateText + "IDLE 상태";
            break;
        case PlayerState::MOVE:
            PlayerStateText = PlayerStateText + "MOVE 상태";
            break;
        case PlayerState::JUMP:
            PlayerStateText = PlayerStateText + "JUMP 상태";
            break;
        case PlayerState::EQUIPWEAPON:
            PlayerStateText = PlayerStateText + "EQUIPWEAPON 상태";
            break;
        default:
            PlayerStateText = PlayerStateText + "UNKNOWN 상태";
            break;
        }
        GameEngineLevel::DebugTextPush(PlayerStateText);

        std::string LeftPixelCheckString = "LeftPixelCheck = ";
        LeftPixelCheckString = LeftPixelCheckString + std::to_string(LeftPixelCheck);
        GameEngineLevel::DebugTextPush(LeftPixelCheckString);

        std::string RightPixelCheckString = "RightPixelCheck = ";
        RightPixelCheckString = RightPixelCheckString + std::to_string(RightPixelCheck);
        GameEngineLevel::DebugTextPush(RightPixelCheckString);

        std::string UpPixelCheckString = "UpPixelCheck = ";
        UpPixelCheckString = UpPixelCheckString + std::to_string(UpPixelCheck);
        GameEngineLevel::DebugTextPush(UpPixelCheckString);

        std::string DownPixelCheckString = "DownPixelCheck = ";
        DownPixelCheckString = DownPixelCheckString + std::to_string(DownPixelCheck);
        GameEngineLevel::DebugTextPush(DownPixelCheckString);

        std::string LeftUpPixelCheckString = "LeftUpPixelCheck = ";
        LeftUpPixelCheckString = LeftUpPixelCheckString + std::to_string(LeftUpPixelCheck);
        GameEngineLevel::DebugTextPush(LeftUpPixelCheckString);

        std::string RightUpPixelCheckString = "RightUpPixelCheck = ";
        RightUpPixelCheckString = RightUpPixelCheckString + std::to_string(RightUpPixelCheck);
        GameEngineLevel::DebugTextPush(RightUpPixelCheckString);

        std::string LeftDownPixelCheckString = "LeftDownPixelCheck = ";
        LeftDownPixelCheckString = LeftDownPixelCheckString + std::to_string(LeftDownPixelCheck);
        GameEngineLevel::DebugTextPush(LeftDownPixelCheckString);

        std::string RightDownPixelCheckString = "RightDownPixelCheck = ";
        RightDownPixelCheckString = RightDownPixelCheckString + std::to_string(RightDownPixelCheck);
        GameEngineLevel::DebugTextPush(RightDownPixelCheckString);
	}

}

void Player::PlayerDead()
{
    Off();
    HPUI->Off();
    SetGraveObject(PlayerGraveImageStringView);
}

void Player::SetGraveObject(const std::string_view& _GraveImage)
{
    PlayerGrave* GraveObject = GetLevel()->CreateActor<PlayerGrave>();
    GraveObject->SetPlayerGrave(_GraveImage, ColImage ,GetPos());
}

bool Player::IsPlayerAnimationEnd()
{
	return AnimationRender->IsAnimationEnd();
}

//enum class WeaponNum
//{
//    None,				//무기없음
//    Bazooka,			//F1
//    HomingMissile,      //F1
//    Grenade,			//F2
//    ClusterBomb,
//    Shotgun,			//F3
//    Handgun,
//    Uzi,
//    Minigun,
//    Sheep,				//F5
//    AirStrike,			//F6
//    Torch,              //F7
//    Drill,              //F7
//    WeaponCount        //Enum 개수 확인하기위한 Count (마지막에 있어야 함)
//};


void Player::SetCurWeapon(Weapon* _Weapon)
{
    CurWeapon = _Weapon;
    CurWeaponNum = static_cast<WeaponNum>(_Weapon->GetWeaponNumber());
}

// -1 : 무제한, 0 : 없음, 나머지 개수 
void Player::SetWeaponCount()
{
    WeaponCount.reserve(static_cast<size_t>(WeaponNum::WeaponCount));

    WeaponCount.push_back(-1);
    WeaponCount.push_back(-1);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(-1);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(3);
    WeaponCount.push_back(-1);
}

void Player::SetPlayerState(PlayerState _State)
{
    ChangeState(_State);
}