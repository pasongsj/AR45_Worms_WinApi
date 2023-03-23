
#include <functional>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "WeaponInterFace.h"
#include "ContentsEnums.h"
#include "PlayLevel.h"
#include "GlobalValue.h"
#include "MouseObject.h"
#include "Player.h"

#include "WeaponBazooka.h"
#include "WeaponGrenade.h"
#include "WeaponClusterBomb.h"
#include "WeaponShotgun.h"


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


WeaponInterFace::WeaponInterFace()
{
}


WeaponInterFace::~WeaponInterFace()
{
}


void WeaponInterFace::Start()
{
	//Interface = this;
	
	
	if (false == GameEngineInput::IsKey("RightClock"))
	{
		GameEngineInput::CreateKey("RightClock", VK_RBUTTON);
		
	}
	WeaponInterFace::Value = GetLevel();
	MouseObject* MouseObjectInst = GetLevel()->CreateActor<MouseObject>();
	
	// 1번쨰 인터페이스 
	
	// 바주카 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
        button->SetEnum(WeaponNum::Bazooka); //SetEnum으로 새로만든 ButtonCallbackEnum에 Enum세팅되게끔만들기.
		ButtonManager.push_back(button);
        button->SetClickCallBackEnum(asas);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
	}

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
        ButtonManager.push_back(button);   
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,586 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
        button->SetEnum(WeaponNum::Shotgun);
        ButtonManager.push_back(button);
        button->SetClickCallBackEnum(asas);
	}

	// 2번쨰 인터페이스 

	// 초록폭탄 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		button->SetEnum(WeaponNum::Shotgun);
		ButtonManager.push_back(button);
	//	button->SetClickCallBack(asas);
	}
	// 빨간폭탄 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
	//	button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
	    //button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
	    //button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,615 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}

	//3번째 인터페이스 

	// 샷건 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,644 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
	//	button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,644 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,644 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,644 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,644 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	// 4번쨰 인퍼페이스 

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,673 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,673 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,673 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,673 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,673 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	// 5번쨰 인터페이스 

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,702 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,702 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,702 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,702 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,702 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}

	// 6번쨰 인퍼페이스 

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,731 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,731 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,731 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,731 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,731 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}

	// 7번쨰 인퍼페이스 

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,760 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,760 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,760 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,760 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,760 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	// 8번쨰 인터페이스 

	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,789 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,789 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,789 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,789 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,789 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	// 9번쨰 인터페이스 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,818 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,818 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,818 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,818 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,818 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	// 10번쨰 인터페이스 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,847 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,847 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,847 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,847 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,847 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	// 11번쨰 인터페이스 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,876 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,876 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,876 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,876 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,876 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	// 12번쨰 인터페이스 
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1327,905 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(asas);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1357,905 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack(avvv);
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1387,905 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1415,905 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
		//button->SetClickCallBack();
		ButtonManager.push_back(button);
	}
	{
		Button* button = GetLevel()->CreateActor<Button>();
		button->setting("WeaponIcon.bmp", "2020.bmp", "2020.bmp", { 1444,905 }, { 26,27 }, static_cast<int>(WormsRenderOrder::WeaPonInterFace), false);
		button->SetTargetCollisionGroup(static_cast<int>(WormsCollisionOrder::WeaPonInterFace));
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

	{
		bazooka = CreateRender(9);
		bazooka->SetImage("bazookaUI.Bmp");
		bazooka->SetPosition({ 1327,586 });
		bazooka->SetScale({ 32, 32 });
		bazooka->EffectCameraOff();
		bazooka->On();
	}
	{
		cluster = CreateRender(9);
		cluster->SetImage("clusterUI.Bmp");
		cluster->SetPosition({ 1357,615 });
		cluster->SetScale({ 32, 32 });
		cluster->EffectCameraOff();
		cluster->On();
	}
	{
		grenade = CreateRender(9);
		grenade->SetImage("grenadeUI.Bmp");
		grenade->SetPosition({ 1327,615 });
		grenade->SetScale({ 32, 32 });
		grenade->EffectCameraOff();
		grenade->On();
	}
	{
		shotgun = CreateRender(9);
		shotgun->SetImage("shotgunUI.Bmp");
		shotgun->SetPosition({ 1327,644 });
		shotgun->SetScale({ 32, 32 });
		shotgun->EffectCameraOff();
		shotgun->On();
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

