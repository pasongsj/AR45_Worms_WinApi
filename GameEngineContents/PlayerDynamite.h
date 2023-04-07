#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerDynamite : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerDynamite();
	~PlayerDynamite();

	// delete Function
	PlayerDynamite(const PlayerDynamite& _Other) = delete;
	PlayerDynamite(PlayerDynamite&& _Other) noexcept = delete;
	PlayerDynamite& operator=(const PlayerDynamite& _Other) = delete;
	PlayerDynamite& operator=(PlayerDynamite&& _Other) noexcept = delete;

    void ExplosionDynamite(float4 _Pos);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    GameEngineRender* ExplosionCircle = nullptr;
    GameEngineRender* ExplosionElipse = nullptr;
    GameEngineCollision* AttackCollision = nullptr;
    
    void AttackPlayer();
};

