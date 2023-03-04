#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include "player.h"

std::string generatePuzzle(std::string fileName);
std::string generateBlanks(std::string phrase);
std::vector<int> generateWheel();

bool buyVowel(player& p, std::string puzzle, std::string& currentSol){
	std::string guess;
	bool badGuess = true;
	do{
			std::cout<<"Enter a vowel: ";
			std::cin>>guess;
			if((tolower(guess[0]) == 'a' || tolower(guess[0]) == 'e' || tolower(guess[0]) == 'i' || tolower(guess[0]) == 'o' || tolower(guess[0]) == 'u') && guess.size() == 1){
				badGuess = false;
			}
		}while(badGuess);

		badGuess = true;
		for(int i = 0; i <puzzle.size(); ++i){
			if(tolower(guess[0]) == puzzle.at(i)){
				currentSol.at(i) = puzzle.at(i);
				badGuess = false;
			}
		}
		p.updateCurrentMoney(-250);
		std::cout<<std::endl;
		return badGuess;
}

bool spin(player& p, std::string puzzle, std::string& currentSol){
	std::vector<int> wheel= generateWheel();
	std::minstd_rand mt(std::chrono::system_clock::now().time_since_epoch().count());
	int randomNumber = mt() % wheel.size();
	bool badGuess = true;
	std::string guess;
	int wheelResult = wheel.at(randomNumber); 
		do{
			std::cout<<"Wheel: $"<<wheelResult<<std::endl;
			std::cout<<"Enter a consonant: ";
			std::cin>>guess;
			if(tolower(guess[0]) != 'a' && tolower(guess[0]) != 'e' && tolower(guess[0]) != 'i' && tolower(guess[0]) != 'o' && tolower(guess[0]) != 'u' && guess.size() == 1){
				badGuess = false;
			}
		}while(badGuess);
		badGuess = true;
		for(int i = 0; i <puzzle.size(); ++i){
			if(tolower(guess[0]) == puzzle.at(i)){
				currentSol.at(i) = puzzle.at(i);
				p.updateCurrentMoney(wheelResult);
				badGuess = false;
			}
		}
		std::cout<<std::endl;
		return badGuess;
	}

bool turn(player& p, std::string puzzle, std::string& currentSol){
	bool badGuess = false;
	std::string guess;

	while(!badGuess){
		std::cout<<p.returnName() << std::endl;
		std::cout<<"Current Money: $"<<p.returnCurrentMoney()<<std::endl;
		std::cout<<currentSol <<std::endl;

		int wheelResult;
		bool valid = true;
		std::cout<<"Enter a 'v' to buy a vowel, 's' to solve, or anything else to spin: ";
		do{
			std::cin>>guess;
			valid = true;
			if(guess == "v" && p.returnCurrentMoney() < 250){
				std::cout<<"Not enough money to buy a vowel" <<std::endl;
				std::cout<<"Try again: ";
				valid = false;
			}
		}while(!valid);
		
		

		if(guess == "v"){
			badGuess = buyVowel(p, puzzle, currentSol);
		}
		else{
			badGuess = spin(p, puzzle, currentSol);
		}
		

		if(currentSol == puzzle){
			return true;
		}
	}
	return false;
}

std::vector<int> generateWheel(){
	std::vector<int> wheel;
	for(int i = 100; i <= 1000; i+=100){
		wheel.push_back(i);
		wheel.push_back(i);
	}
	return wheel;
}

void game(std::string file, std::vector<player>& players){
	std::string puzzle = generatePuzzle(file);
	std::string currentSol = generateBlanks(puzzle);
	bool solved = false;
	int pnum = 0;
	while(!solved){
		solved = turn(players.at(pnum), puzzle, currentSol);
		if(solved){
			break;
		}
		pnum++;
		if(pnum == 3){
			pnum = 0;
		}
	}
	std::cout<<std::endl;
	std::cout<<players.at(pnum).returnName() << " Won This Round!" << std::endl;
	players.at(pnum).updateTotalMoney(players.at(pnum).returnCurrentMoney());

	std::cout<<"Scores!" <<std::endl;
	for(int i = 0; i < players.size(); ++i){
		std::cout<<players.at(i).returnName() << ": $" << players.at(i).returnTotalMoney() <<std::endl;
		players.at(i).currentMoneyReset();
	}
	std::cout<<std::endl;
}

int main(int argc, char**argv) {
	std::string tempName;
	std::vector<player> players;
	std::cout<<"Enter a Name for Player 1: ";
	std::cin>>tempName;
	players.push_back(player(tempName));
	std::cout<<"Enter a Name for Player 2: ";
	std::cin>>tempName;
	players.push_back(player(tempName));
	std::cout<<"Enter a Name for Player 3: ";
	std::cin>>tempName;
	std::cout<<std::endl;
	players.push_back(player(tempName));

  game(argv[1], players);
} 

std::string generatePuzzle(std::string fileName){
  std::string word;
  std::ifstream wordFile;
  std::vector<std::string> words;
  wordFile.open(fileName);

  while(wordFile >> word){
    words.push_back(word);
  }

  std::minstd_rand mt(std::chrono::system_clock::now().time_since_epoch().count());
  do{
    int randomNumber = mt() % words.size();
    word = words.at(randomNumber);
  }while(word.size() <= 0);

  wordFile.close();
  return word;
}

std::string generateBlanks(std::string phrase){
	std::string currentSol = phrase;
	for(int i = 0; i < phrase.size(); ++i){
		if(tolower(phrase.at(i)) >= 'a' || tolower(phrase.at(i)) <= 'z'){
			currentSol.at(i) = '_';
		}
	}
	return currentSol;
}