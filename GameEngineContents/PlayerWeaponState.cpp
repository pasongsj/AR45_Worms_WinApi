#include "Player.h"
#include "Weapon.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineInput.h>
void Player::EquipWeaponStart()
{
    if (nullptr == CurWeapon || CurWeapon->GetWeaponNumber() == static_cast<int>(WeaponNum::None))
    {
        return;
    }
    std::string _Name = CurWeapon->GetWeaponName() + "On";
    DirCheck(_Name);
    //switch (WeaponNumber)
    //{
    //case static_cast<int>(WeaponNum::Uzi):
    //{
    //    DirCheck("UziOn");
    //    break;
    //}
    //case static_cast<int>(WeaponNum::Grenade):
    //{
    //    DirCheck("GrenadeOn");
    //    break;
    //}
    //case static_cast<int>(WeaponNum::ClusterBomb):
    //{
    //    DirCheck("ClusterBombOn"); // 딜레이 업데이트 필요
    //    break;
    //}
    //default:
    //    break;
    //}
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
    if (true == CurWeapon->IsWeaponDone())
    {
        ChangeState(PlayerState::IDLE);
        return;
    }


}
void Player::EquipWeaponEnd()
{
    std::string _Name = CurWeapon->GetWeaponName() + "Off";
    DirCheck(_Name);
    //int WeaponNumber = CurWeapon->GetWeaponNumber();

    //switch (WeaponNumber)
    //{
    //case static_cast<int>(WeaponNum::Uzi):
    //{
    //    DirCheck("UziOff"); // 딜레이 업데이트 필요
    //    break;
    //}
    //case static_cast<int>(WeaponNum::Grenade):
    //{
    //    DirCheck("GrenadeOff"); // 딜레이 업데이트 필요
    //    break;
    //}
    //case static_cast<int>(WeaponNum::ClusterBomb):
    //{
    //    DirCheck("ClusterBombOff"); // 딜레이 업데이트 필요
    //    break;
    //}
    //default:
    //    break;
    //}
    //장비한 무기 애니메이션용 각도 리셋
}