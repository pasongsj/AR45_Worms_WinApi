#include "Weapon.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "GlobalValue.h"
#include <time.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>


std::map<std::string, Weapon*> Weapon::AllWeapons;

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}


float4 Weapon::GetShootDir()
{
	float4 ReturnDir = float4::Zero;

	if (GameEngineInput::IsPress("WeaponUp") && -5.7 < Height)
	{
		Height -= 0.05f;
	}
	else if (GameEngineInput::IsPress("WeaponDown") && 5.7 > Height)
	{
		Height += 0.05f;
	}

	if (nullptr == CurPlayer)
	{
		MsgAssert("현재 플레이어를 찾을 수 없습니다.");
	}

	float4 PlayerDir = CurPlayer->GetPlayerDir();

	if (float4::Left == PlayerDir)
	{
		if (isRightDir == true)
		{
			Height = 0.0f;
		}

		isRightDir = false;
	}
	else if (float4::Right == PlayerDir)
	{
		if (isRightDir == false)
		{
			Height = 0.0f;
		}

		isRightDir = true;
	}

	ReturnDir.y = Height;
	ReturnDir.x = static_cast<float>(isRightDir ? 1 : -1);

	return ReturnDir.NormalizeReturn();

}

bool Weapon::DownShoot()
{
    if (GameEngineInput::IsDown("Shoot")) 
    {
        return true;
    }
    return false;
}

bool Weapon::PressShoot()
{
    if (GameEngineInput::IsPress("Shoot")) 
    {
        return true;
    }
	return false;
}

bool Weapon::UpShoot()
{
    if (GameEngineInput::IsUp("Shoot"))
    {
        return true;
    }
    return false;
}

bool Weapon::isEndCharging()
{
	if (GameEngineInput::IsUp("Shoot"))
	{
		return true;
	}

	if (true)
	{
		//return true;
	}

	return false;
}



void Weapon::SetCurPlayer() // 수정완료
{
	Player* tmpPlayer = GlobalValue::gValue.GetPlayer();
	if (tmpPlayer != CurPlayer)
	{
		CurPlayer = tmpPlayer;
        GetShootDir();
	}

	if (nullptr == CurPlayer)
	{
		MsgAssert("CurPlayer가 nullptr입니다.");
	}
    // 임시로 PlyaerState 체크하기 위해 생성 -> 무기 변경시 적용해주는 내용
    if (nullptr == CurPlayer->GetCurWeapon())
    {
        CurPlayer->SetCurWeapon(this);
    }
}

bool Weapon::CheckCollision(GameEngineCollision* _Col)
{
	if (nullptr == _Col)
	{
		MsgAssert("체크할 콜리전이 없습니다.");
	}

	// 플레이어 체크
	std::vector<GameEngineCollision*> CollisionList;

	if (_Col != nullptr && true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
	{
		for (int i = 0; i < CollisionList.size(); i++)
		{
			Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());

			if (ColPlayer->GetIsMyTurn() == false)
			{
				return true;
			}
		}
	}

    if (true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Drum), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }))
    {
        return true;
    }


	// 맵체크
	else if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos(), RGB(0, 0, 255)) && _Col->GetActorPlusPos().y > 0 && _Col->GetActorPlusPos().x > 0) //맵에 닿으면 사라짐
	{
		return true;
	}
	// 맵 밖으로 나갔는지 체크
    float4 _Pos = _Col->GetPosition();
    if (!(-640 <= _Pos.x && _Pos.x < 4480 && -743 <= _Pos.y && _Pos.y < 1310))
    {
        return true;
    }

	return false;
}

float Weapon::GetChargeTime()
{
	return GameEngineInput::GetPressTime("Shoot");
}


float4 Weapon::CheckSide(float4 _Vec)
{
    _Vec.Normalize();
    float _X = _Vec.x;
    float _Y = _Vec.y;
    float4 ReturnNull = float4::Null;
    if (_X > 0)
    {
        ReturnNull.x = 1;
    }
    else if (_X < 0)
    {
        ReturnNull.y = 1;
    }

    if (_Y > 0)
    {
        ReturnNull.z = 1;
    }
    else if (_Y < 0)
    {
        ReturnNull.w = 1;
    }

    if (abs(_X) + 0.5f < abs(_Y))
    {
        ReturnNull.x = 0;
        ReturnNull.y = 0;
    }
    else if (abs(_X) > abs(_Y) + 0.5f)
    {
        ReturnNull.z = 0;
        ReturnNull.w = 0;
    }
    return ReturnNull;


    //if (abs(_X) + 0.5f < abs(_Y))
    //{
    //    if (_Y > 0)
    //    {
    //        return float4{ 0,0,1,0 };
    //        //return static_cast<int>(WeaponCollisionCheck::DOWN);
    //    }
    //    else
    //    {
    //        return float4{ 0,0,0,1 };
    //        //return static_cast<int>(WeaponCollisionCheck::UP);
    //    }
    //}

    //if (_X > 0)
    //{
    //    if (abs(_X) > abs(_Y) + 0.5f)
    //    {
    //        return float4{ 1,0,0,0 };
    //        //return static_cast<int>(WeaponCollisionCheck::RIGHT);
    //    }
    //    else
    //    {
    //        if (_Y > 0)
    //        {
    //            return float4{ 1,0,1,0 };
    //            //return static_cast<int>(WeaponCollisionCheck::DOWNRIGHT);
    //        }
    //        else
    //        {
    //            return float4{ 1,0,0,1 };
    //            //return static_cast<int>(WeaponCollisionCheck::UPRIGHT);
    //        }
    //    }
    //}
    //else if (_X < 0)
    //{
    //    if (abs(_X) > abs(_Y) + 0.5f)
    //    {
    //        return static_cast<int>(WeaponCollisionCheck::LEFT);
    //    }
    //    else
    //    {
    //        if (_Y > 0)
    //        {
    //            return static_cast<int>(WeaponCollisionCheck::DOWNLEFT);
    //        }
    //        else
    //        {
    //            return static_cast<int>(WeaponCollisionCheck::UPLEFT);
    //        }
    //    }
    //}
    //return static_cast<int>(WeaponCollisionCheck::ALL);

}

float4 Weapon::CheckCollisionSide(GameEngineCollision* _Col)
{
    float4 ReturnValue = float4::Zero;

    // 맵 밖으로 나갔는지 체크
    float4 _Pos = _Col->GetActorPlusPos(); // 값 확인 필요함.
    if (!(-640 <= _Pos.x && _Pos.x < 5600 && -743 <= _Pos.y && _Pos.y < 1300))
    {
        Timer = 0;
        return float4::Up;
    }


    std::vector<GameEngineCollision*> CollisionList;
    float CheckScale = _Col->GetScale().hx();

    if (true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
    {
        for (int i = 0; i < CollisionList.size(); i++)
        {
            Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());
            if (CurPlayer == ColPlayer)
            {
                continue;
            }
            float4 Range = (ColPlayer->GetPos() - GetPos());
            if (abs(Range.y) < abs(Range.x))
            {
                ReturnValue.y += 1;
            }
            else if (Range.x > 0)
            {
                ReturnValue.x += 1;
            }
            else
            {
                ReturnValue.x -= 1;
            }
            return ReturnValue;

        }
    }

    CollisionList.clear();
    if (true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Drum), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
    {
        float4 Range = (CollisionList.back()->GetActorPlusPos() - GetPos());
        return Range;
    }


    // 30 30 20,40
    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ CheckScale }, RGB(255, 0, 255)) &&
        RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ -CheckScale }, RGB(255, 0, 255)) &&
        RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ 0,CheckScale }, RGB(255, 0, 255)))
    {
        return float4::Up;
    }

    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ CheckScale }, RGB(255, 0, 255)))
    {
        ReturnValue.x += 1;
    }
    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ -CheckScale }, RGB(255, 0, 255)))
    {
        ReturnValue.x -= 1;
    }
    if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_Col->GetActorPlusPos() + float4{ 0,CheckScale }, RGB(255, 0, 255)))
    {
        ReturnValue.y += 1;
    }

    return ReturnValue;
}



float4 Weapon::Check4Side(GameEngineCollision* _Col, float4 _NextPos)
{

    // 맵 밖으로 나갔는지 체크
    float4 _Pos = _Col->GetActorPlusPos(); // 값 확인 필요함.
    if (!(-640 <= _Pos.x && _Pos.x < 5600 && -743 <= _Pos.y && _Pos.y < 1300))
    {
        Timer = -1;
        return float4{1,1,1,1};
    }


	std::vector<GameEngineCollision*> CollisionList;

	if (true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
	{
        /*float4 Range = (CollisionList.back()->GetActorPlusPos() - GetPos());
        return CheckSide(Range);*/
        for (int i = 0; i < CollisionList.size(); i++)
        {
            Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());
            if (CurPlayer == ColPlayer)
            {
                continue;
            }
            float4 Range = (ColPlayer->GetPos() - GetPos());
            return CheckSide(Range);
        }
            
	}


    CollisionList.clear();
    if (true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Drum), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
    {
        float4 Range = (CollisionList.back()->GetActorPlusPos() - GetPos());
        return CheckSide(Range);
    }

    float4 RetrunValue = float4::Null;
    bool N = false, S = false, E = false, W = false;
    float CheckScale = _Col->GetScale().hx();
	// 30 30 20,40
    if ( // 콜리전이 발생함
        RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ CheckScale }, RGB(255, 0, 255)) ||
        RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ -CheckScale }, RGB(255, 0, 255)) ||
        RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ 0,CheckScale }, RGB(255, 0, 255)) ||
        RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ 0,-CheckScale }, RGB(255, 0, 255))
        )
    {
        if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ CheckScale }, RGB(255, 0, 255))) // 동
        {
            RetrunValue.x = 1;
        }
        if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ -CheckScale }, RGB(255, 0, 255))) // 서
        {
            RetrunValue.y = 1;
        }
        if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ 0,CheckScale }, RGB(255, 0, 255))) // 남
        {
            RetrunValue.z = 1;
        }
        if (RGB(0, 0, 255) == MapCollision->GetPixelColor(_NextPos + float4{ 0,-CheckScale }, RGB(255, 0, 255))) // 북
        {
            RetrunValue.w = 1;
        }
    }
    if (RetrunValue.AddAllVec() > 0)
    {
        int a = 0;
    }
    return RetrunValue;

        //if (true == S)
        //{
        //    if (true == N)
        //    {
        //        return static_cast<int>(WeaponCollisionCheck::ALL);
        //    }
        //    else if (true == E)
        //    {
        //        return static_cast<int>(WeaponCollisionCheck::DOWNRIGHT);
        //    }
        //    else if (true == W)
        //    {
        //        return static_cast<int>(WeaponCollisionCheck::DOWNLEFT);
        //    }
        //    return static_cast<int>(WeaponCollisionCheck::DOWN);
        //}
        //else if (true == N)
        //{
        //    if (true == E)
        //    {
        //        return static_cast<int>(WeaponCollisionCheck::UPRIGHT);
        //    }
        //    else if (true == W)
        //    {
        //        return static_cast<int>(WeaponCollisionCheck::UPLEFT);
        //    }
        //    return static_cast<int>(WeaponCollisionCheck::UP);
        //}
        //else if (true == E)
        //{
        //    return static_cast<int>(WeaponCollisionCheck::RIGHT);
        //}
        //else if (true == W)
        //{
        //    return static_cast<int>(WeaponCollisionCheck::LEFT);
        //}
    //}

    //return static_cast<int>(WeaponCollisionCheck::ZERO);
    
}


bool Weapon::AttackPlayer(GameEngineCollision* _Col, bool _AttackSelf) // 값 확인 필요함
{                   // 폭발 CollisionScale설정 필요                                   :_Col->SetScale({ static_cast<float>(BombScale * 2) });
                    // _Col->GetActorPlusPos()가 정확한 폭발 위치가 되게 설정 필요

    int HitCnt = 0;
	if (nullptr == _Col)
	{
		MsgAssert("체크할 콜리전이 없습니다.");
	}

	// 플레이어 체크
	std::vector<GameEngineCollision*> CollisionList;

    int Radius = static_cast<int>(BombScale);

	if (_Col != nullptr && true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
	{
		for (int i = 0; i < CollisionList.size(); i++)
		{
			Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());
            if (_AttackSelf == false && ColPlayer == CurPlayer)
            {
                continue;
            }
            if (ColPlayer->GetPlayerState() == PlayerState::FlyAway || ColPlayer->GetPlayerState() == PlayerState::FacePlant) // 임시 예외 처리 코드
            {
                continue;
            }
            float4 Distance = ColPlayer->GetPos() - _Col->GetActorPlusPos(); //폭발 구점

            float Ratio = Distance.Size() / Radius;
            if (Ratio <= 0)
            {
                Ratio = 0;
            }
            else if (Ratio >= 1)
            {
                Ratio = 1;
            }

            int proportional_dmg = static_cast<int>(MaxDmg * (1 - Ratio) + MinDmg * (Ratio));
            float proportional_power = MaxKnockBackPower * (1 - Ratio) + MinKnockBackPower * (Ratio);
            Distance.Normalize();
            //              거리 비례데미지,    날라가는 방향,   거리 비례 날라가는 세기 
            ColPlayer->Damaged(proportional_dmg, Distance, proportional_power);

		    //여기서 Dmg 는 최대 데미지, KnockBackPower은 최대 넉백 파워를 이야기함

            ++HitCnt;
        }
	}
    if (HitCnt > 0)
    {
        return true;
    }
    return false;
}


// Gun류 무기는 폭발 위치가 아닌 플레이어가 발사한 거리 반비례 데미지이므로
void Weapon::AttackPlayerGun(GameEngineCollision* _Col, float _refDistance)
{                   // 폭발 CollisionScale설정 필요
                    // _Col->GetActorPlusPos()가 정확한 폭발 위치가 되게 설정 필요

    if (nullptr == _Col)
    {
        MsgAssert("체크할 콜리전이 없습니다.");
    }

    // 플레이어 체크
    std::vector<GameEngineCollision*> CollisionList;

    if (_Col != nullptr && true == _Col->Collision({ .TargetGroup = static_cast<int>(WormsCollisionOrder::Player), .TargetColType = CollisionType::CT_CirCle, .ThisColType = CollisionType::CT_CirCle }, CollisionList))
    {
        for (int i = 0; i < CollisionList.size(); i++)
        {
            Player* ColPlayer = dynamic_cast<Player*>(CollisionList[i]->GetActor());
            //if (ColPlayer == CurPlayer) // Gun은 본인에게 데미지를 주지 않음?? 주더라?
            //{
            //    continue;
            //}
            float4 Distance = _Col->GetActorPlusPos() - GetPos(); //폭발 구점

            float Ratio = Distance.Size() / _refDistance; // 일정 길이 이상으로 넘어가면 값 고정
            if (Ratio <= 0)
            {
                Ratio = 0;
            }
            else if (Ratio >= 1)
            {
                Ratio = 1;
            }

            int proportional_dmg = static_cast<int>(MaxDmg * (1 - Ratio) + MinDmg * Ratio); // 가까울수록 높은 데미지
            float proportional_power = MaxKnockBackPower * (1 - Ratio) + MinKnockBackPower * Ratio;
            Distance.Normalize();

            //              거리 비례데미지,    날라가는 방향,   거리 비례 날라가는 세기 
            if(ColPlayer->GetIsMyTurn() == false)
            {
                ColPlayer->Damaged(proportional_dmg, Distance, proportional_power);
            }
            //여기서 Dmg 는 최대 데미지, KnockBackPower은 최대 넉백 파워를 이야기함
        }
    }
}


void Weapon::ExplosionEffectInit(float _CircleDiameter)
{
    //디폴트
    std::string CircleImageName = "circle25.bmp";
    std::string ElipseImageName = "Elipse50.bmp";

    int CircleFrame = 7;
    int ElipseeFrame = 19;

    //크기에 따라 변화
    if (_CircleDiameter >= 100)
    {
        CircleImageName = "circle50.bmp";
        CircleFrame = 8;

        ElipseImageName = "Elipse75.bmp";
        ElipseeFrame = 9;
    }
    else if (_CircleDiameter >= 150)
    {
        CircleImageName = "circle75.bmp";
        CircleFrame = 3;

        ElipseImageName = "Elipse100.bmp";
        ElipseeFrame = 9;
    }
    else if (_CircleDiameter >= 200)
    {
        CircleImageName = "circle100.bmp";
        CircleFrame = 3;

        ElipseImageName = "Elipse100.bmp";
        ElipseeFrame = 9;
    }

    ExplosionCircle = CreateRender(CircleImageName, WormsRenderOrder::Weapon);
    ExplosionCircle->CreateAnimation({ .AnimationName = "Explosion", .ImageName = CircleImageName, .Start = 0, .End = CircleFrame, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->CreateAnimation({ .AnimationName = "Idle", .ImageName = CircleImageName, .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionCircle->SetScale({ _CircleDiameter , _CircleDiameter });

    ExplosionCircle->ChangeAnimation("Idle");
    ExplosionCircle->Off();

    ExplosionElipse = CreateRender(ElipseImageName, WormsRenderOrder::Weapon);
    ExplosionElipse->CreateAnimation({ .AnimationName = "ExplosionElipse", .ImageName = ElipseImageName, .Start = 0, .End = ElipseeFrame, .InterTime = 0.03f , .Loop = false });
    ExplosionElipse->CreateAnimation({ .AnimationName = "Idle", .ImageName = ElipseImageName, .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    ExplosionElipse->SetScale({ _CircleDiameter * 1.5f , _CircleDiameter * 1.5f });

    ExplosionElipse->ChangeAnimation("Idle");
    ExplosionElipse->Off();

    PootTextAnimation = CreateRender("Poot.bmp", WormsRenderOrder::Weapon);
    PootTextAnimation->CreateAnimation({ .AnimationName = "Poot", .ImageName = "Poot.bmp", .Start = 0, .End = 17, .InterTime = 0.02f , .Loop = false });
    PootTextAnimation->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Poot.bmp", .Start = 0, .End = 1, .InterTime = 0.05f , .Loop = false });
    PootTextAnimation->SetScale({ 70 , 70 });

    PootTextAnimation->ChangeAnimation("Idle");
    PootTextAnimation->Off();

}