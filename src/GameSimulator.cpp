/**
 * @file GameSimulator.cpp
 * @ref <wotf>
 * @copyright Bern University of Applied Sciences
 *            All rights reserved Max BOEGLI, Florian Dominic BURRI, 2020.
 *
 * @author Max BOEGLI             -- <max.boegli@students.bfh.ch>
 *         Florian Dominic BURRI  -- <floriandominic.burri@students.bfh.ch>
 *
 * @date 21-06-2020
 *
 * @brief The game simulator simulates the World of the Fittest game.
 *
 * The GameSimulator class will create, run and display a World of the Fittest game.
 * The simulation speed can be chosen with the setSpeed function.
 */



#include "GameSimulator.h"

using namespace std::chrono_literals;

GameSimulator::GameSimulator() :
		updateTime{5000},
		playground{std::make_shared<CLIPlayground>()} {

}

void GameSimulator::setSpeed(Speed speed){
	switch (speed){
	case Speed::VERY_SLOW:
		updateTime = 5000;
		break;
	case Speed::SLOW:
		updateTime = 2000;
		break;
	case Speed::MEDIUM:
		updateTime = 500;
		break;
	case Speed::FAST:
		updateTime = 200;
		break;
	case Speed::VERY_FAST:
		updateTime = 50;
		break;
	}
}

void GameSimulator::reset(){
	playground->eden();
}

void GameSimulator::start(){
	while(true){
		playground->display(std::cout);
		playground->next();
		std::this_thread::sleep_for(std::chrono::milliseconds(updateTime));
	}
}

void GameSimulator::next(){
	playground->display(std::cout);
	playground->next();
}
