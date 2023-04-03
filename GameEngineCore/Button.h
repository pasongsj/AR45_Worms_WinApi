#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRender.h"

enum class ButtonState
{
	Release, // 안눌렸다.
	Press, // 눌렸다.
	Hover, // 나를 누를수 있는 녀석이 위에서 맴돌고 있다.
};

// 설명 :
class GameEngineRender;
class Button : public GameEngineActor
{
public:
	// constrcuter destructer
	Button();
	~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

	void SetRenderOrder(int _Value);

	void SetScale(float4 _Scale);

	void SetClickCallBack(void(*_ClickPtr)(Button* _Btn))
	{
		ClickPtr = _ClickPtr;
	}
    void SetClickCallBackEnum(void(*_ClickPtrEnum)(Button* _Btn,int _Enum))
    {
        ClickPtrEnum = _ClickPtrEnum;
    }


	void SetTargetCollisionGroup(int _PointTargetGroup);

	void SetButtonCollisionType(CollisionType _ButtonCollisionType)
	{
		ButtonCollisionType = _ButtonCollisionType;
	}

	void SetHoverImage(const std::string_view& _Name, int _HoverIndex = -1)
	{
		HoverImageName = _Name;
		HoverIndex = _HoverIndex;
	}
	void SetReleaseImage(const std::string_view& _Name, int _ReleaseIndex = -1)
	{
		ReleaseImageName = _Name;
		ReleaseIndex = _ReleaseIndex;
	}
	void SetPressImage(const std::string_view& _Name, int _PressIndex = -1)
	{
		PressImageName = _Name;
		PressIndex = _PressIndex;
	}

	GameEngineRender* GetButtonRender() 
	{
		return ButtonRender;
	}

	GameEngineCollision* GetButtonCollision() 
	{
		return ButtonCollision;
	}

	ButtonState GetState() 
	{
		return State;
	}

	int GetHoverIndex() 
	{
		return HoverIndex;
	}

	int GetReleaseIndex() 
	{
		return ReleaseIndex;
	}

	int GetPressIndex()
	{
		return PressIndex;
	}
    bool GetTest()
    {
        return test;
    }
    bool GetHover()
    {
        return Hover;
    }
	void SetCollisionOrder(int _Order);

	float4 GetScale() 
	{
		return Scale;
	}

    template<typename ENUM>
    void SetEnum(ENUM _Enum)
    {
        iEnum = static_cast<int>(_Enum);
    }

	void setting(const std::string_view& _ReleaseName, const std::string_view& _HoverName, const std::string_view& _PressName,
		float4 _Pos, float4 _Scale, int _Order, bool _EffectCam); 

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
    int HoverCount =0;
	GameEngineRender* ButtonRender = nullptr;
	GameEngineCollision* ButtonCollision = nullptr;
	int PointTargetGroup = 0;
	CollisionType ButtonCollisionType = CollisionType::CT_Rect;
	void(*ClickPtr)(Button* _Btn) = nullptr;
    void(*ClickPtrEnum)(Button* _Btn,int _Enum) = nullptr;
    bool test = false;
    bool Hover = false;
    int iEnum = 0;
	float4 Scale;
	ButtonState State;
	std::string CurImageName;
	std::string HoverImageName;
	int HoverIndex = -1;
	std::string ReleaseImageName;
	int ReleaseIndex = -1;
	std::string PressImageName;
	int PressIndex = -1;

};

