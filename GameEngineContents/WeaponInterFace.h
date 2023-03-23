#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include <GameEngineCore/Button.h>
class WeaponInterFace : public GameEngineActor
{
public:
	static WeaponInterFace* Interface;
	static GameEngineLevel* Value;

	// constrcuter destructer
	WeaponInterFace();
	~WeaponInterFace();
	// delete Function
	WeaponInterFace(const WeaponInterFace& _Other) = delete;
	WeaponInterFace(WeaponInterFace&& _Other) noexcept = delete;
	WeaponInterFace& operator=(const WeaponInterFace& _Other) = delete;
	WeaponInterFace& operator=(WeaponInterFace&& _Other) noexcept = delete;
	
	
	
protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _Time) override;

private:

	GameEngineRender* WaeponInterface = nullptr;
	
	GameEngineRender* bazooka = nullptr;
	GameEngineRender* cluster = nullptr;
	GameEngineRender* grenade = nullptr;
	GameEngineRender* shotgun = nullptr;



	float4 MoveDir = float4::Zero;
	std::vector<Button*> ButtonManager;
	bool InterfaceMove = true;
};