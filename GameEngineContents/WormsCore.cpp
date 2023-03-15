#include "WormsCore.h"

#include "CenterLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

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
	CreateLevel<PlayLevel>("Play");
	ChangeLevel("Center");
}

WormsCore::~WormsCore() 
{
}

