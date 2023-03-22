#include "WeaponInterFace.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
WeaponInterFace::WeaponInterFace()
{
}

WeaponInterFace::~WeaponInterFace()
{
}


void WeaponInterFace::Start()
{
	int a = 0;
	if (false == GameEngineInput::IsKey("RightClock"))
	{
		GameEngineInput::CreateKey("RightClock", VK_RBUTTON);
		
	}
	Button*A  = GetLevel()->CreateActor<Button>();
	A -> setting("2020.bmp", "weaponSheet.bmp", "2020.bmp", { 500,500 }, { 100,100 }, static_cast<int>(5), false);
	b.push_back(A);
	{
		WaeponInterface = CreateRender(2);
		WaeponInterface->SetImage("weaponSheet.Bmp");
		WaeponInterface->SetPosition({ 1370,740 });
		WaeponInterface->SetScale({ 180, 400 });
		WaeponInterface->EffectCameraOff();
		WaeponInterface->On();
	}
	{
		WeaponInterFaceCollision = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision->SetPosition({ 1200,400 });
		WeaponInterFaceCollision->SetScale({ 20, 20 });	
	}
	{
		WeaponInterFaceCollision2 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision2->SetPosition({ 1200,400 });
		WeaponInterFaceCollision2->SetScale({ 20, 20 });
	}
	{
		WeaponInterFaceCollision3 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision3->SetPosition({ 1370,740 });
		WeaponInterFaceCollision3->SetScale({ 180, 400 });
	}
	{
		WeaponInterFaceCollision4 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision4->SetPosition({ 1370,740 });
		WeaponInterFaceCollision4->SetScale({ 180, 400 });
	}
	{
		WeaponInterFaceCollision5 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision5->SetPosition({ 1370,740 });
		WeaponInterFaceCollision5->SetScale({ 180, 400 });
	}
	{
		WeaponInterFaceCollision6 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision6->SetPosition({ 1370,740 });
		WeaponInterFaceCollision6->SetScale({ 180, 400 });
	}
	{
		WeaponInterFaceCollision7 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision7->SetPosition({ 1370,740 });
		WeaponInterFaceCollision7->SetScale({ 180, 400 });
	}
	{
		WeaponInterFaceCollision8 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision8->SetPosition({ 1370,740 });
		WeaponInterFaceCollision8->SetScale({ 180, 400 });
	}
	{
		WeaponInterFaceCollision9 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision9->SetPosition({ 1370,740 });
		WeaponInterFaceCollision9->SetScale({ 180, 400 });
	}
	{
		WeaponInterFaceCollision10 = CreateCollision(WormsRenderOrder::WeaPonInterFace);
		WeaponInterFaceCollision10->SetPosition({ 1370,740 });
		WeaponInterFaceCollision10->SetScale({ 180, 400 });
	}


	

	
}

void WeaponInterFace::Update(float _DeltaTime)
{
	GameEngineWindow::GetMousePosition();

	
	
	//NewCharBtn
	/*Button* NewCharBtn = GetLevel()->CreateActor<Button>();
	NewCharBtn->setting(_Name.second, _Name.second, _Name.second, { 0,0 }, BtnScale, static_cast<int>(VSRenderOrder::LastUI), false);
	NewCharBtn->GetButtonRender()->SetImage(_Name.second);
	NewCharBtn->GetButtonRender()->EffectCameraOn();
	Items[_Name.first] = (NewCharBtn);
	NewCharBtn->Off();*/


	WeaponInterFaceCollision->SetPosition({ GetLevel()->GetCameraPos().x+ 1325,GetLevel()->GetCameraPos().y+ 585 });
	
	WeaponInterFaceCollision2->SetPosition({ GetLevel()->GetCameraPos().x + 1355,GetLevel()->GetCameraPos().y + 585 });
		


	if (InterfaceMove == true)
	{
		

	}

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


	SetMove(MoveDir*_DeltaTime);
}

void WeaponInterFace::Render(float _Time)
{
	WeaponInterFaceCollision->DebugRender();
	WeaponInterFaceCollision2->DebugRender();
}

