#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MouseObject : public GameEngineActor
{
public:
	// constrcuter destructer
	MouseObject();
	~MouseObject();

	// delete Function
	MouseObject(const MouseObject& _Other) = delete;
	MouseObject(MouseObject&& _Other) noexcept = delete;
	MouseObject& operator=(const MouseObject& _Other) = delete;
	MouseObject& operator=(MouseObject&& _Other) noexcept = delete;

public:
	/*inline GameEngineRender* GetMouseRender() 
	{
		return MouseRender;
	}*/

	inline GameEngineCollision* GetMouseCollision()
	{
		return MouseCollision;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//GameEngineRender* MouseRender = nullptr;
	GameEngineCollision* MouseCollision = nullptr;

};

