#include "GlobalValue.h"
#include "ContentsEnums.h"

#include "Player.h"
#include "PlayLevel.h"

#include "WeaponBazooka.h"
#include "WeaponGrenade.h"
#include "WeaponClusterBomb.h"
#include "WeaponShotgun.h"
#include "HomingMissile.h"
#include "WeaponHandgun.h"
#include "WeaponUzi.h"
#include "WeaponMinigun.h"
#include "WeaponTorch.h"
#include "WeaponSheep.h"
#include "WeaponAirStrike.h"


void GlobalValue::SetWeapon(int _Value)
{
    WeaponNum eNum = static_cast<WeaponNum>(_Value);

    if (pCurPlayer->GetCurWeapon() != nullptr)
    {
        pCurPlayer->GetCurWeapon()->Death();

    }

    switch (eNum)
    {
    case WeaponNum::None:
        break;
    case WeaponNum::Bazooka:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponBazooka>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::HomingMissile:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<HomingMissile>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::Grenade:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponGrenade>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::ClusterBomb:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponClusterBomb>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::Shotgun:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponShotgun>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::Handgun:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponHandgun>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::Uzi:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponUzi>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::Minigun:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponMinigun>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::Sheep:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponSheep>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::AirStrike:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponAirStrike>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    case WeaponNum::Torch:
    {
        Weapon* NewWeapon = pPlayLevel->CreateActor<WeaponTorch>();
        pCurPlayer->SetCurWeapon(NewWeapon);
        break;
    }

    default:
        break;
    }
}
