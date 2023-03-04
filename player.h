#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class player{
	public:
	player(std::string playerName);
	int returnTotalMoney();
	int returnCurrentMoney();
	std::string returnName();

	void updateTotalMoney(int amount);
	void updateCurrentMoney(int amount);
	void currentMoneyReset();
private:
	int totalMoney;
	int currentMoney;
	std::string name;
};


#endif