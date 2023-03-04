#include "player.h"

player::player(std::string playerName){
	name = playerName;
	totalMoney = 0;
	currentMoney = 0;
}

int player::returnCurrentMoney(){
	return currentMoney;
}

int player::returnTotalMoney(){
	return totalMoney;
}

std::string player::returnName(){
	return name;
}

void player::updateTotalMoney(int amount){
	totalMoney += amount;
}

void player::updateCurrentMoney(int amount){
	currentMoney += amount;
}

void player::currentMoneyReset(){
	currentMoney = 0;
}