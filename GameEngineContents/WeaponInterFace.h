#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include <GameEngineCore/Button.h>
#include <GameEngineCore/NumberRenderObject.h>

class Player;
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
	
    static int HomingMissileCount;
    static int GrenadeCount;
    static int ClusterBombCount;
    static int ShotgunCount;
    static int HandgunCount;
    static int UziCountCount;
    static int MinigunCount;
    static int SheepCount;
    static int AirStrikeCount;
    static int TorchCount;
    static int CarpetBomb;
   
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
    GameEngineRender* firepnch = nullptr;
    GameEngineRender* drill = nullptr;
    GameEngineRender* CarpetUI = nullptr;
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
    Button* FireFunch = nullptr;
    Button* Drill = nullptr;
    Button* Carpet = nullptr;


  
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
    NumberRenderObject CarpetNumber;
    

  

    Player* CurPlayer = nullptr;

	float4 MoveDir = float4::Zero;
	std::vector<Button*> ButtonManager;
	bool InterfaceMove = true;
};