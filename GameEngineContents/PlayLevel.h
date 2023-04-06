#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include <vector>
#include <list>


#include "GlobalValue.h"

struct Wind
{
	float	WindPower	= 30.f;
	int		WindPhase	= 0;
	float	MaxWind		= 1.19f;
	float	WindResult	= 0.f;
	float	WindTime	= 0.f;
};
// Ό³Έν :
class Player;
class PlayLevel : public GameEngineLevel
{
public:
	
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;


    GameEngineSoundPlayer BgmPlayer;



    void SetLevelSetting(LevelSetting _set)
    {
        LevelSet = _set;
    }
    LevelSetting GetLevelSetting()
    {
       return LevelSet;
    }

    inline bool IsDebugTextModeOn()
    {
        return IsDebugTextMode;
    }
	
    int GetGameSet()
    {
        if (true == bWin)
        {
            return 1;
        }
        if (true== bDraw)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }

    void SetGridRandomPos(float _Interval);

    float4 GetGridRandPos();

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}

private:
	int iPlayerNumber = -1;
    std::list<float4> listRandPos;
	std::vector<Player*> vecAllPlayer;
    std::vector<std::string_view> vecPlayerUIImage;

	bool bCamMove = false;
    std::vector<bool> vecTurnEnd;
	float4 PrevCamPos = float4::Zero;
	float4 CurPlayerPos = float4::Zero;
	float4 LerpCamPos = float4::Zero;
	float fLerpRatio = 0.f;
	float fLerpSpeed = 2.f;
	float fCamMoveSpeed = 500.f;

    bool IsDebugTextMode = false;

	float4 ScreenSize = float4::Zero;
    void SetUIImage();
    void SoundLoad();
	void ImageLoad();
	void KeyLoad();
	void CreateLeaf(float _DeltaTime);

	void PlayerChange(float _DeltaTime);
	void MoveCamForMouse(float _DeltaTime);
    bool DamageAnimCheck();


    void Win(float _DeltaTime);
    void Draw(float _DeltaTime);

    void GameSetCheck();

    bool bWin = false;
    bool bDraw = false;
    bool isLoadingOff = false;
    bool ismusicOn = false;
    float fWinTime = 0.f;
    float fAnimTime = 0.f;

    LevelSetting LevelSet = {};

	Wind AddWind;

};


