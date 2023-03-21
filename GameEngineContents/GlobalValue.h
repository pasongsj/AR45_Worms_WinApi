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

	float GetWindPower()
	{
		return fWindPower;
	}

	void SetWindPower(float _fWindPower)
	{
		fWindPower = _fWindPower;
	}

private:
	Player* pCurPlayer;
	float fWindPower = 0.f;
};