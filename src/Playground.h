/**
 * @file Playgroun.h
 * @ref <wotf>
 * @copyright Bern University of Applied Sciences
 *            All rights reserved Max BOEGLI, Florian Dominic BURRI, 2020.
 *
 * @author Max BOEGLI             -- <max.boegli@students.bfh.ch>
 *         Florian Dominic BURRI  -- <floriandominic.burri@students.bfh.ch>
 *
 * @date 21-06-2020
 *
 * @brief Class that represents the playground of the game
 *
 * The playground class represents the playground of the game. It
 * will initialize the playground with the function eden(). It does also
 * simulate interactions in the world. The class playground is a abstract class.
 * The CLIPlayground class implements the Playground Class and provides a function
 * to visualize the world in the command line.
 */


#ifndef SRC_PLAYGROUND_H_
#define SRC_PLAYGROUND_H_

#include <ostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <string>

#include <typeinfo>

#include "Living.h"
#include "GameEvaluation.h"

// virtual class
class Playground {
public:
	Playground();
	virtual ~Playground(){ }
	void eden();
	void next();
	std::shared_ptr<Living> getObject(Coordinate position);
	virtual std::ostream &display(std::ostream &os);
protected:
	World_t world;
	World_t nextWorld;
	std::shared_ptr<GameEvaluation> evaluator;
};

class CLIPlayground : public Playground {
public:
	std::ostream &display(std::ostream &os) override;
private:
	std::ostream &separating_line(std::ostream &os);
};

#endif /* SRC_PLAYGROUND_H_ */
