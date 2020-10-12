/**
 * @file GameEvaluation.cpp
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

#include "GameEvaluation.h"

std::ostream &GameEvaluation::displayStats(std::ostream &os){
	int n_empty{0};
	int n_grass{0};
	int n_dead_grass{0};
	int n_m_rabbit{0};
	int n_f_rabbit{0};
	int n_m_fox{0};
	int n_f_fox{0};

	for (unsigned int row = 1; row < EDGE_LENGTH_GAME_BOARD + 1; ++row){
		for (unsigned int column = 1; column < EDGE_LENGTH_GAME_BOARD + 1 ; ++column){
			switch(world[row][column]->who()){
			case Role::EMPTY:
				n_empty += 1;
				break;
			case Role::DEAD_GRASS:
				n_dead_grass += 1;
				break;
			case Role::GRASS:
				n_grass += 1;
				break;
			case Role::M_RABBIT:
				n_m_rabbit += 1;
				break;
			case Role::F_RABBIT:
				n_f_rabbit += 1;
				break;
			case Role::M_FOX:
				n_m_fox += 1;
				break;
			case Role::F_FOX:
				n_f_fox += 1;
				break;
			case Role::MAX_LIVING:
				break;
			}
		}
	}
	os << "\t\tMale\tFemale\tTotal" << std::endl;
	os << "empty\t\t\t\t" << n_empty << std::endl;
	os << "dead Grass\t\t\t" << n_dead_grass << std::endl;
	os << "Grass\t\t\t\t" << n_grass << std::endl;
	os << "Rabbits\t\t" << n_m_rabbit << "\t" << n_f_rabbit << "\t" << (n_m_rabbit + n_f_rabbit) << std::endl;
	os << "Foxes\t\t" << n_m_fox << "\t" << n_f_fox << "\t" << (n_m_fox + n_f_fox) << std::endl;

	return os;
}

