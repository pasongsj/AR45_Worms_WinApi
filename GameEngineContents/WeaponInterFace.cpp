#include "WeaponInterFace.h"
#include "ContentsEnums.h"
#include <functional>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "WeaponBazooka.h"
#include "WeaponGrenade.h"
#include "WeaponClusterBomb.h"
#include "WeaponShotgun.h"
#include "MouseObject.h"
#include "PlayLevel.h"

#include "Player.h"
#include "GlobalValue.h"

WeaponInterFace*WeaponInterFace::Interface;
GameEngineLevel* WeaponInterFace::Value;

//void asas(Button* a) // 수정 전 코드
void asas(Button*a, int _Enum) // int를 받는 함수를 넣을수 있게 새로 만들어서 가능
{
    WeaponNum eNum = static_cast<WeaponNum>(_Enum);

	Player* CurPlayer = GlobalValue::gValue.GetPlayer();
	//if (CurPlayer->GetCurWeapon()->GetName() == "B")
	//{
	//	return;
	//}
	if (CurPlayer->GetCurWeapon() != nullptr)
	{
		CurPlayer->GetCurWeapon()->Death();

	}

    switch (eNum)
    {
    case WeaponNum::None:
        break;
    case WeaponNum::Bazooka: 
    //{
    //    Weapon* NewWeapon = WeaponInterFace::Value->CreateActor<WeaponBazooka>();
    //    CurPlayer->SetCurWeapon(NewWeapon);
    //}
        break;
    case WeaponNum::HomingMissile:
    {
        int a = 0;
    }
        break;
    case WeaponNum::Grenade: 
    {
        Weapon* NewWeapon = WeaponInterFace::Value->CreateActor<WeaponGrenade>();
        CurPlayer->SetCurWeapon(NewWeapon);
    }
        break;
    case WeaponNum::ClusterBomb:
    {
        Weapon* NewWeapon = WeaponInterFace::Value->CreateActor<WeaponClusterBomb>();
        CurPlayer->SetCurWeapon(NewWeapon);
    }
        break;
    case WeaponNum::Shotgun:
    {
        Weapon* NewWeapon = WeaponInterFace::Value->CreateActor<WeaponShotgun>();
        CurPlayer->SetCurWeapon(NewWeapon);
    }
        break;
    case WeaponNum::Handgun:
        break;
    case WeaponNum::Uzi:
        break;
    case WeaponNum::Minigun:
        break;
    case WeaponNum::Sheep:
        break;
    case WeaponNum::AirStrike:
        break;
    default:
        break;
    }
        
	/*if (CurWeapon == nullptr)
	{
		GameEngineActor* Weapon = WeaponInterFace::Value->CreateActor<WeaponBazooka>();
	}
	Gmsf::dsds()
	int a = 1;*/
	
}
void avvv(Button* a)
{
	WeaponInterFace::Value->CreateActor<WeaponGrenade>();

}



WeaponInterFace::WeaponInterFace()
{
}


WeaponInterFace::~WeaponInterFace()
{
}

void WeaponInterFace::test()
{
	WeaponBazooka* A = GetLevel()->CreateActor<WeaponBazooka>();
}

void WeaponInterFace::Start()
{
	Interface = this;
	MouseObject* MouseObjectInst = GetLevel()->CreateActor<MouseObject>(2); //마우스 오브젝트 생성
	
	if (false == GameEngineInput::IsKey("RightClock"))
	{
		GameEngineInput::CreateKey("RightClock", VK_RBUTTON);
		
	}
	WeaponInterFace::Value = GetLevel();
	
	// 위에 인터페이스 

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
        button->SetEnum(WeaponNum::Bazooka); //SetEnum으로 새로만든 ButtonCallbackEnum에 Enum세팅되게끔만들기.
		ButtonManager.push_back(button);
        button->SetClickCallBackEnum(asas);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
        button->SetEnum(WeaponNum::HomingMissile);
		ButtonManager.push_back(button);
        button->SetClickCallBackEnum(asas);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
        button->SetEnum(WeaponNum::Grenade);
		ButtonManager.push_back(button);
        button->SetClickCallBackEnum(asas);

	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
        button->SetEnum(WeaponNum::ClusterBomb);
        ButtonManager.push_back(button);
        button->SetClickCallBackEnum(asas);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
        button->SetEnum(WeaponNum::Shotgun);
        ButtonManager.push_back(button);
        button->SetClickCallBackEnum(asas);
	}

	// 2번쨰 인터페이스 

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
	    //button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
	    //button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}



	{
		WaeponInterface = CreateRender(5);
		WaeponInterface->SetImage("weaponSheet.Bmp");
		WaeponInterface->SetPosition({ 1370,740 });
		WaeponInterface->SetScale({ 180, 400 });
		WaeponInterface->EffectCameraOff();
		WaeponInterface->On();
	}
	
	
}

void WeaponInterFace::Update(float _DeltaTime)
{
	

	if(true == GameEngineInput::IsDown("RightClock") && InterfaceMove ==true)
	{
		MoveDir = float4::Left * 300;
		

	}

	if (true == GameEngineInput::IsDown("RightClock") && InterfaceMove == false)
	{
		MoveDir = float4::Right * 300;
	}
	
	


	if (GetPos().x < -180 && InterfaceMove == true)
	{
		MoveDir = { 0,0 };
		InterfaceMove = false;
	}
	if (GetPos().x > 0 && InterfaceMove == false)
	{
		MoveDir = { 0,0 };
		InterfaceMove = true;
	}

	for (size_t i = 0; i < ButtonManager.size(); i++)
	{
		ButtonManager[i]->SetMove(MoveDir * _DeltaTime);
	}

	SetMove(MoveDir*_DeltaTime);
}

void WeaponInterFace::Render(float _Time)
{
	
}

