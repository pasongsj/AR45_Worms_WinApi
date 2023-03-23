#include "MouseObject.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
MouseObject::MouseObject() 
{
}

MouseObject::~MouseObject() 
{
}

void MouseObject::Start() 
{
//	MouseRender = CreateRender();
	MouseCollision = CreateCollision(WormsCollisionOrder::WeaPonInterFace);

	/*if (nullptr == MouseRender)
	{
		MsgAssert("랜더러가 만들어지지 않았습니다.");
	}*/

	if (nullptr == MouseCollision)
	{
		MsgAssert("콜리전이 만들어지지 않았습니다.");
	}
}

void MouseObject::Update(float _DeltaTime) 
{
	SetPos(GetLevel()->GetMousePos());
}