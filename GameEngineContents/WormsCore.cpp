#include "WormsCore.h"


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
	CreateLevel<TitleLevel>("Title");
	ChangeLevel("Title");
}

WormsCore::~WormsCore() 
{
}

