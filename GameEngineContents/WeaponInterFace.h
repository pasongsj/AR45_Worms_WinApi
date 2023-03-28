#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include <GameEngineCore/Button.h>
#include <GameEngineCore/NumberRenderObject.h>
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
    void NumberManager();
	
	
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
    GameEngineRender* HomingMissileUI = nullptr;
    GameEngineRender* HandgunUI = nullptr;
    GameEngineRender* UziUI = nullptr;
    GameEngineRender* MinigunUI = nullptr;
    GameEngineRender* SheepUI = nullptr;
    GameEngineRender* AirStrikeUI = nullptr;
    GameEngineRender* TorchUI = nullptr;
    GameEngineRender* X = nullptr;

    Button* Bazooka = nullptr;
    Button* HomingMissile = nullptr;
    Button* Grenade = nullptr;
    Button* ClusterBomb = nullptr;
    Button* Shotgun = nullptr;
    Button* Handgun = nullptr;
    Button* Uzi = nullptr;
    Button* Minigun = nullptr;
    Button* Sheep = nullptr;
    Button* AirStrike = nullptr;
    Button* Torch = nullptr;
  
    NumberRenderObject HomingMissileNumber;
    NumberRenderObject GrenadeNummber;
    NumberRenderObject ClusterBombNumber;
    NumberRenderObject ShotgunNumber;
    NumberRenderObject HandgunNumber;
    NumberRenderObject UziNummber;
    NumberRenderObject MinigunNumber;
    NumberRenderObject SheepNumber;
    NumberRenderObject AirStrikeNumber;
    NumberRenderObject TorchNumber;

    int HomingMissileCount = 3;
    int GrenadeCount = 3;
    int ClusterBombCount = 3;
    int ShotgunCount = 3;
    int HandgunCount = 3;
    int UziCountCount = 3;
    int MinigunCount = 3;
    int SheepCount = 3;
    int AirStrikeCount = 3;
    int TorchCount = 3;




	float4 MoveDir = float4::Zero;
	std::vector<Button*> ButtonManager;
	bool InterfaceMove = true;
};