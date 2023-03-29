#pragma once
#include "MapObject.h"

// Ό³Έν :
class Drum : public MapObject
{
public:
	// constrcuter destructer
	Drum();
	~Drum();

	// delete Function
	Drum(const Drum& _Other) = delete;
	Drum(Drum&& _Other) noexcept = delete;
	Drum& operator=(const Drum& _Other) = delete;
	Drum& operator=(Drum&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    int Count = 4;


    void HitCheck();
    void AnimCheck();
};

