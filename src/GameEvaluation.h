/**
 * @file GameEvaluation.h
 * @ref <wotf>
 * @copyright Bern University of Applied Sciences
 *            All rights reserved Max BOEGLI, Florian Dominic BURRI, 2020.
 *
 * @author Max BOEGLI             -- <max.boegli@students.bfh.ch>
 *         Florian Dominic BURRI  -- <floriandominic.burri@students.bfh.ch>
 *
 * @date 21-06-2020
 *
 * @brief Class used to evaluate a given playground.
 *
 * The GameEvaluation class requires a pointer to a World_t object. The displayStats()
 * function will give out some statistics about the world in the given output stream.
 */


#ifndef SRC_GAMEEVALUATION_H_
#define SRC_GAMEEVALUATION_H_

#include "Living.h"

class GameEvaluation {
public:
	GameEvaluation(const World_t &world) : world{world} { };
	std::ostream &displayStats(std::ostream &os);
protected:
	const World_t &world;
private:
	GameEvaluation(); // not used
};

#endif /* SRC_GAMEEVALUATION_H_ */
