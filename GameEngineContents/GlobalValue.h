#pragma once

class Player;
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
private:
	Player* pCurPlayer;
    std::vector<Player*> vecAllPlayerG;
	float fWindSpeed = 0.f;
	int fWindPhase = 0;
};