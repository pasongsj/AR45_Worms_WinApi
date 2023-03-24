#include "Player.h"
#include "Weapon.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineInput.h>
void Player::EquipWeaponStart()
{
    int WeaponNumber = CurWeapon->GetWeaponNumber();

    switch (WeaponNumber)
    {
    case static_cast<int>(WeaponNum::Uzi):
    {
        DirCheck("UziOn");
        break;
    }
    default:
        break;
    }
    //현재 무기 애니메이션으로 변경
}
void Player::EquipWeaponUpdate(float _DeltatTime)
{

    { // 움직임 체크
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
    }



}
void Player::EquipWeaponEnd()
{
    int WeaponNumber = CurWeapon->GetWeaponNumber();

    switch (WeaponNumber)
    {
    case static_cast<int>(WeaponNum::Uzi):
    {
        DirCheck("UziOff"); // 딜레이 업데이트 필요
        break;
    }
    default:
        break;
    }
    //장비한 무기 애니메이션용 각도 리셋
}