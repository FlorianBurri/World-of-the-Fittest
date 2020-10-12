/**
 * @file Playground.cpp
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

#include "Playground.h"


Playground::Playground() {
	this->eden();
	evaluator = std::make_shared<GameEvaluation>(world);
}

void Playground::eden(){
	// initialize random number generator
	std::mt19937 gen((unsigned)std::time(NULL)); //Standard mersenne_twister_engine seeded with current time
	std::uniform_real_distribution<> dis(0., 1.0);
	std::uniform_int_distribution<> grassHeightDis(1, 5);

	for (unsigned int row = 0; row < EDGE_LENGTH_GAME_BOARD + 2; ++row){
		for (unsigned int column = 0; column < EDGE_LENGTH_GAME_BOARD + 2 ; ++column){
			float randomNumb = dis(gen);


			if (row==0 or row==EDGE_LENGTH_GAME_BOARD + 1
					or column==0 or column==EDGE_LENGTH_GAME_BOARD+1){
				std::shared_ptr<Living> liv {new Empty(Coordinate(row,column))};
				world[row][column] = liv;
			}

			else if (randomNumb < 0.4){
				// random grass height
				unsigned int height = grassHeightDis(gen);
				world[row][column] = std::make_shared<Grass>(Coordinate(row,column), height);
			}
			else if (randomNumb < 0.6){
				world[row][column] = std::make_shared<M_Rabbit>(Coordinate(row,column));
			}
			else if (randomNumb < 0.8){
				world[row][column] = std::make_shared<F_Rabbit>(Coordinate(row,column));
			}
			else if (randomNumb < 0.85){
				world[row][column] = std::make_shared<M_Fox>(Coordinate(row,column));
			}
			else if (randomNumb < 0.9){
				world[row][column] = std::make_shared<F_Fox>(Coordinate(row,column));
			}
			else{
				world[row][column] = std::make_shared<Empty>(Coordinate(row,column));
			}

		}
	}
	nextWorld = world;
}

std::ostream &Playground::display(std::ostream &os){
	return os << "Playground::display" << std::endl;
}

void Playground::next(){
	for (unsigned int row = 1; row < EDGE_LENGTH_GAME_BOARD + 1; ++row){
		for (unsigned int column = 1; column < EDGE_LENGTH_GAME_BOARD + 1 ; ++column){
			std::shared_ptr<Living> newLiv {world[row][column]->next(world)};
			nextWorld[row][column] = newLiv;
		}
		std::cout<<std::endl;
	}
	world = nextWorld;
}

std::shared_ptr<Living> Playground::getObject(Coordinate position){
	if(position.x >= EDGE_LENGTH_GAME_BOARD or position.y >= EDGE_LENGTH_GAME_BOARD){
		std::cout << "Position for object out of range";
		return 0;
	}
	return world[position.x + 1][position.y + 1];
}

// implement CLI visualisation

std::ostream &CLIPlayground::separating_line(std::ostream &os){
	for (unsigned int i=0; i < EDGE_LENGTH_GAME_BOARD; i++){
			os << "\u2540\u2500\u2500\u2500\u2500";
		}
		return os << "\u2540" << std::endl;
}

std::ostream &CLIPlayground::display(std::ostream &os){
	os << "  " << std::endl;
	this->separating_line(os);
	for (unsigned int row = 1; row < EDGE_LENGTH_GAME_BOARD + 1; ++row){
		for (unsigned int column = 1; column < EDGE_LENGTH_GAME_BOARD + 1 ; ++column){
			os << "\u2502" ;
			world[row][column]->display(std::cout);
		}
		os << "\u2502" << std::endl;
		this->separating_line(os);
	}
	evaluator->displayStats(os);
	return os;
}

