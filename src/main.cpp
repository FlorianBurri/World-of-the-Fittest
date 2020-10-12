/**
 * @file main.cpp
 * @ref <wotf>
 * @copyright Bern University of Applied Sciences
 *            All rights reserved Max BOEGLI, Florian Dominic BURRI, 2020.
 *
 * @author Max BOEGLI             -- <max.boegli@students.bfh.ch>
 *         Florian Dominic BURRI  -- <floriandominic.burri@students.bfh.ch>
 *
 * @date 21-06-2020
 *
 * @brief Starting Point of the Project.
 *
 * Starting Point of the Project.
 */


#include "main.h"

int main() {
	GameSimulator game = GameSimulator();
	game.setSpeed(Speed::VERY_SLOW);
	game.start();
}
