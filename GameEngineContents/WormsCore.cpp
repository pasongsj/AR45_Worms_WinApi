#include "WormsCore.h"

#include "CenterLevel.h"
#include "TitleLevel.h"

void WormsCore::Start()
{
}

void WormsCore::Update()
{
}

void WormsCore::End()
{
}

WormsCore::WormsCore()
{
	CreateLevel<CenterLevel>("Center");
	CreateLevel<TitleLevel>("Title");
	ChangeLevel("Center");
}

WormsCore::~WormsCore() 
{
}

