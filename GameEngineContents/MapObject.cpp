#include "MapObject.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
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
   /* MapObjRender = CreateRender(WormsRenderOrder::MapObject);
    MapObjRender->SetImage("mcrate1.bmp");
    MapObjRender->SetScaleToImage();
    MapObjRender->SetPosition({350, 600});*/

    MapObjCol = CreateCollision(static_cast<int>(WormsCollisionOrder::MapObject));
    MapObjCol->SetDebugRenderType(CT_Rect);
}

void MapObject::Update(float _DeltaTime)
{

}
