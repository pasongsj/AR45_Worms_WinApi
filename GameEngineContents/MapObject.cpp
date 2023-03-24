#include "MapObject.h"
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Map.h"
#include "MapModifier.h"
#include "ContentsEnums.h"
MapObject::MapObject() 
{
}

MapObject::~MapObject() 
{
}

void MapObject::Start()
{
    //MapRender »ý¼º
    MapObjRender = CreateRender(WormsRenderOrder::MapObject);
    MapObjRender->SetImage("TrachCan.bmp");
    MapObjRender->SetPosition(GetPos());
    MapObjRender->SetScaleToImage();
}

void MapObject::Update(float _DeltaTime)
{

}