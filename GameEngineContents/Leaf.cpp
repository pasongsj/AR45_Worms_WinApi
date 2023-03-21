#include "Leaf.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>

#include "ContentsEnums.h"
#include "GlobalValue.h"

Leaf::Leaf() 
{
}

Leaf::~Leaf() 
{
}

void Leaf::Start()
{
	{
		int iRand = GameEngineRandom::MainRandom.RandomInt(0,12);
		GameEngineRender* Leaf = CreateRender(WormsRenderOrder::BackGround);
		Leaf->SetScale({ 80, 48 });
		Leaf->CreateAnimation({ .AnimationName = "Leaf",.ImageName = "ScatterLeaf.bmp",.Start = 0,.End = 12});
		Leaf->ChangeAnimation("Leaf", iRand);
	}
	fRandPower = GameEngineRandom::MainRandom.RandomInt(7, 10);
}

void Leaf::Update(float _DeltaTime)
{
	MoveDir.y += fGravity * (fRandPower / 10);
	MoveDir.x += GlobalValue::gValue.GetWindPower();

	SetMove(MoveDir* _DeltaTime);
}

