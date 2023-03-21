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

private:
	static class Player* pCurPlayer;

};

Player* GlobalValue::pCurPlayer = nullptr;
GlobalValue GlobalValue::gValue;