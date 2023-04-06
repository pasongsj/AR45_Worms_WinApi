#include "Button.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
Button::Button() 
{
	State = ButtonState::Release;
}

Button::~Button() 
{
}


void Button::SetTargetCollisionGroup(int _PointTargetGroup)
{
	PointTargetGroup = _PointTargetGroup;
	if (nullptr == ButtonCollision)
	{
		ButtonCollision = CreateCollision(PointTargetGroup);
	}
}


void Button::Start()
{
	ButtonRender = CreateRender();
	ButtonCollision = CreateCollision();
    ButtonCollision->SetDebugRenderType(CollisionType::CT_Rect);
}

void Button::SetRenderOrder(int _Value)
{
	ButtonRender->SetOrder(_Value);
}

void Button::SetScale(float4 _Scale)
{
	Scale = _Scale;
	ButtonCollision->SetScale(Scale);
}

void Button::SetCollisionOrder(int _Order)
{
	ButtonCollision->SetOrder(_Order);


}

void Button::Update(float _DeltaTime)
{
   
    test = false;
    Hover = false;

	State = ButtonState::Release;

	if (true != ButtonCollision->Collision({ .TargetGroup = PointTargetGroup, .TargetColType = CollisionType::CT_Point,.ThisColType = CT_Rect }))
	{
		State = ButtonState::Release;
	}


	if (true == ButtonCollision->Collision({ .TargetGroup = PointTargetGroup, .TargetColType = CollisionType::CT_Point,.ThisColType = CT_Rect }))
	{
        test = true;
		if (true == GameEngineInput::IsUp("EngineMouseLeft") && (nullptr != ClickPtr|| ClickPtrEnum != nullptr))
		{
			
            if (ClickPtrEnum!=nullptr)
            {
                ClickPtrEnum(this, iEnum);

                GameEngineResources::GetInst().SoundPlay("CursorSelect.wav");
            }
            else
            {
			    ClickPtr(this);
            }
		}
		else if (true == GameEngineInput::IsFree("EngineMouseLeft"))
		{
			State = ButtonState::Hover;
		}
		else if (true == GameEngineInput::IsPress("EngineMouseLeft"))
		{
			State = ButtonState::Press;
		}
	}

	switch (State)
	{
	case ButtonState::Release:
        HoverCount = 0;
		CurImageName = ReleaseImageName;
		ButtonRender->SetImage(ReleaseImageName);
		if (-1 != ReleaseIndex)
		{
			ButtonRender->SetFrame(ReleaseIndex);
		}
		ButtonRender->SetScale(Scale);
		break;
	case ButtonState::Press:
		CurImageName = PressImageName;
		ButtonRender->SetImage(PressImageName);
		if (-1 != PressIndex)
		{
			ButtonRender->SetFrame(PressIndex);
		}
		ButtonRender->SetScale(Scale);
		break;
	case ButtonState::Hover:

	{
        Hover = true;
		float4 MousePoisition = GameEngineWindow::GetMousePosition();
		float4 ActorPos = ButtonCollision->GetActorPlusPos();
        ++HoverCount;
        if (1== HoverCount)
        {
            GameEngineResources::GetInst().SoundPlay("LoadingTick.wav");
        }
		

		CurImageName = HoverImageName;
		ButtonRender->SetImage(HoverImageName);
		if (-1 != HoverIndex)
		{
			ButtonRender->SetFrame(HoverIndex);
		}
		ButtonRender->SetScale(Scale);
		break;
	}
	default:
		break;
	}
}

void Button::setting(const std::string_view& _ReleaseName, const std::string_view& _HoverName, const std::string_view& _PressName, float4 _Pos, float4 _Scale, int _Order, bool _EffectCam)
{
	SetReleaseImage(_ReleaseName);
	SetHoverImage(_HoverName);
	SetPressImage(_PressName);
	SetPos(_Pos);
	Button::SetScale(_Scale);
	SetRenderOrder(_Order);
	ButtonRender->SetEffectCamera(_EffectCam);
}