#pragma once

#include <GameEngineCore/GameEngineActor.h>
enum class TiTleState
{
	Title,
	TitleStop
};

class TitleBack : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBack();
	~TitleBack();

	// delete Function
	TitleBack(const TitleBack& _Other) = delete;
	TitleBack(TitleBack&& _Other) noexcept = delete;
	TitleBack& operator=(const TitleBack& _Other) = delete;
	TitleBack& operator=(TitleBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:

	GameEngineRender* InTro = nullptr;
	GameEngineRender* BackDrop = nullptr;
	GameEngineRender* InTroBackGround = nullptr;
	GameEngineRender* TitleLogo = nullptr;
	GameEngineRender* TitleAnimation = nullptr;
	GameEngineRender* TitleAnimationStop = nullptr;
	GameEngineRender* WhiteBackGround = nullptr;

	GameEngineRender* A = nullptr;
	GameEngineRender* R = nullptr;
	GameEngineRender* M = nullptr;
	GameEngineRender* A1 = nullptr;
	GameEngineRender* G = nullptr;
	GameEngineRender* E = nullptr;
	GameEngineRender* D = nullptr;
	GameEngineRender* D1 = nullptr;
	GameEngineRender* O = nullptr;
	GameEngineRender* N = nullptr;


	float IntroLogTime = 0;
	float IntroLogColor = 0;
	float AnimatonCheck = 0; 
	float AnimationWhiteTime = 0; 
	float WhiteColor = 0;
	bool IntroCheck = false;
	bool TitleCheck = false;

};

