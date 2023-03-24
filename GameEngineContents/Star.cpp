#include "Star.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
Star::Star()
{
}

Star::~Star()
{
}

void Star::Start()
{
    star = CreateRender("ScatterStar2.bmp", WormsMainTitle::Star);
    star->SetPosition({ 0,0 });
    star->SetScale({32,32});


}

void Star::Update(float _DeltaTime)
{
    MoveDir = { 1,1 };

    SetMove(MoveDir * _DeltaTime * 300);

    if (GetPos().y > 1000)
    {
        this->Death();
    }

}
