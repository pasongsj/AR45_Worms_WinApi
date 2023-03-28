#pragma once
#include <vector>

class Player;
class PlayLevel;

class GlobalValue
{
public:
	static GlobalValue gValue;

	Player* GetPlayer()
	{
		return pCurPlayer;
	}

	void SetPlayer(Player* _pCurPlayer)
	{
		pCurPlayer = _pCurPlayer;
	}

    std::vector<Player*> GetAllPlayer() const
    {
        return vecAllPlayerG;
    }

    void SetAllPlayer(std::vector<Player*> _pAllPlayer)
    {
        vecAllPlayerG = _pAllPlayer;
    }

	float GetWindSpeed() const
	{
		return fWindSpeed;
	}

	void SetWindSpeed(float _fWindSpeed)
	{
		fWindSpeed = _fWindSpeed;
	}

	int GetWindPhase() const
	{
		return fWindPhase;
	}

	void SetWindPhase(int _fWindPhase)
	{
		fWindPhase = _fWindPhase;
	}

    PlayLevel* GetPlayLevel() const
    {
        return pPlayLevel;
    }

    void SetPlayLevel(PlayLevel* _pPlayLevel)
    {
        pPlayLevel = _pPlayLevel;
    }

    void SetWeapon(int _Value);

    void SetWeapon(enum class WeaponNum _Value)
    {
        SetWeapon(static_cast<int>(_Value));
    }

private:
	Player* pCurPlayer = nullptr;
    std::vector<Player*> vecAllPlayerG;
	float fWindSpeed = 0.f;
	int fWindPhase = 0;

    PlayLevel* pPlayLevel = nullptr;
};



struct LevelSetting
{
    float fTime  = 15.f;
    int iPlayerHp = 100;
    int iPlayerNum = 2;
    int iTurnRandom = 0;
    bool bDeathMatch = false;
    bool bMousePosPlayerSet = false;
};