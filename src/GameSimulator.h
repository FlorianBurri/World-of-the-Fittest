/**
 * @file GameSimulator.h
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


#ifndef SRC_GAMESIMULATOR_H_
#define SRC_GAMESIMULATOR_H_

#include <chrono>
#include <thread>

#include "Playground.h"


enum class Speed { VERY_SLOW=0, SLOW, MEDIUM, FAST, VERY_FAST};

class GameSimulator {
public:
	GameSimulator();
	void setSpeed(Speed speed);
	void reset();
	void start();
	void next();
protected:
	unsigned int updateTime; // in milliseconds
	std::shared_ptr<Playground> playground;
};

#endif /* SRC_GAMESIMULATOR_H_ */
