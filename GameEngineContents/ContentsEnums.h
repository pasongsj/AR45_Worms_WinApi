#pragma once

enum class WormsRenderOrder
{
	IntroBackGround,
	Intro,
	BackGround,
	Map,
	Wave,
    MapObject,
	Player,
	Weapon,
	UI,
	WeaPonInterFace,
    WeaPonUI,
    Cusor,

};
enum class WormsTitle
{
	IntroBackGround,
	Intro,
	WhiteBackGround,
	Write,
    Finish
};
enum class WormsMainTitle
{
    BackGround,
    Star,
    Select,
    BlackBackGround,
    Cusor,

};
enum class WormsCollisionOrder
{
	Player = 100,
	Weapon,
    MapObject,
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