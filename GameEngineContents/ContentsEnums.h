#pragma once

enum class WormsRenderOrder
{
	IntroBackGround,
	Intro,
	BackGround,
	Map,
	Wave,
	Player,
	Weapon,
	UI,
	WeaPonInterFace,

};
enum class WormsTitle
{
	IntroBackGround,
	Intro,
	WhiteBackGround,
	Write
};
enum class WormsCollisionOrder
{
	Player,
	Weapon,
	MapModifier,
	WeaPonInterFace
};

enum class WeaponNum
{
	None,				//무기없음
	Bazooka,			//F1
    HomingMissile,      //F1
	Grenade,			//F2
	ClusterBomb,
	Shotgun,			//F3
	Handgun,
	Uzi,
	Minigun,
	Sheep,				//F5
	AirStrike,			//F6
    Torch,              //F7

};