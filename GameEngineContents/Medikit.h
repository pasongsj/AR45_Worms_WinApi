#pragma once
#include "MapObject.h"

// 설명 :
class Medikit : public MapObject
{
public:
	// constrcuter destructer
	Medikit();
	~Medikit();

	// delete Function
	Medikit(const Medikit& _Other) = delete;
	Medikit(Medikit&& _Other) noexcept = delete;
	Medikit& operator=(const Medikit& _Other) = delete;
	Medikit& operator=(Medikit&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;

private:
    bool IsChangedAnim = false;                                //처음 생성되서 낙하산으로 하강하고 땅에 닿았다면 그 이후로는 애니메이션을 변경하지 않음
    bool IsPlaySound = false;

    int Recovery = 50;

    std::string DirString = "Right_";                          //낙하할 때 방향

    void DirCheck(const std::string_view& _AnimationName);     //애니메이션 방향 체크 및 변경

    void RecoveryCheck();                                      //Player와 충돌하면 체력 회복

    bool IsWindApplied();                                      //공중에 있다면 바람의 영향을 적용

};

