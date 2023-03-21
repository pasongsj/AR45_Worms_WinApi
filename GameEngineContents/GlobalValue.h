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

	float GetWindSpeed()
	{
		return fWindSpeed;
	}

	void SetWindSpeed(float _fWindSpeed)
	{
		fWindSpeed = _fWindSpeed;
	}

	int GetWindPhase()
	{
		return fWindPhase;
	}

	void SetWindPhase(int _fWindPhase)
	{
		fWindPhase = _fWindPhase;
	}
private:
	Player* pCurPlayer;
	float fWindSpeed = 0.f;
	int fWindPhase = 0;
};