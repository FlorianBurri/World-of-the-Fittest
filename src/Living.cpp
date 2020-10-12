/**
 * @file Living.cpp
 * @ref <wotf>
 * @copyright Bern University of Applied Sciences
 *            All rights reserved Max BOEGLI, Florian Dominic BURRI, 2020.
 *
 * @author Max BOEGLI             -- <max.boegli@students.bfh.ch>
 *         Florian Dominic BURRI  -- <floriandominic.burri@students.bfh.ch>
 *
 * @date 21-06-2020
 *
 * @brief Series of classes that represent living things in the world.
 *
 * This file includes a series of classes that represent living things in the world.
 * Those living things interact with each other. All implemented classes
 * inherit from the abstract class Living.
 */

#include <memory>
#include "Living.h"

// Implementing class Living:

Living::Living(Coordinate inputPosition, Role inputKind){
	position = inputPosition;
	kind = inputKind;
};

Role Living::who() const{
	return kind;
}

void Living::neighborhood(const World_t &world, SpeciesCount_t &result) const {
	result[static_cast<int>(Role::EMPTY)] = 0;
	result[static_cast<int>(Role::DEAD_GRASS)] = 0;
	result[static_cast<int>(Role::GRASS)] = 0;
    result[static_cast<int>(Role::M_RABBIT)] = 0;
    result[static_cast<int>(Role::F_RABBIT)] = 0;
    result[static_cast<int>(Role::M_FOX)] = 0;
    result[static_cast<int>(Role::F_FOX)] = 0;
	for (int row = -1; row <= 1; ++row)
		for (int column = - 1; column <= 1 ; ++column)
			result[static_cast<int>(world[position.x + row][position.y + column]->who())]++;
}

std::ostream &Living::display(std::ostream &os){
	return os << "<Living>" << std::endl;
}

std::shared_ptr<Living> Living::next(const World_t &world){
	return std::make_shared<Empty>(position);
}


// Implementing class Empty:
std::shared_ptr<Living> Empty::next(const World_t &world){
	// initialize random number generator
	std::mt19937 gen((unsigned)std::time(NULL)); //Standard mersenne_twister_engine seeded with current time
	std::uniform_int_distribution<> dis(0, 1);

	SpeciesCount_t neighbor_count{0};
	neighborhood(world, neighbor_count);
	if ((neighbor_count[static_cast<int>(Role::M_RABBIT)] > 0)
			and (neighbor_count[static_cast<int>(Role::F_RABBIT)] > 0)) {
		if(dis(gen) == 0){
			return std::make_shared<M_Rabbit>(position);
		}
		else {
			return std::make_shared<F_Rabbit>(position);
		}
	}
	else if ((neighbor_count[static_cast<int>(Role::M_FOX)] > 0)
			and (neighbor_count[static_cast<int>(Role::F_FOX)] > 0)) {
		if(dis(gen) == 0){
			return std::make_shared<M_Fox>(position);
		}
		else {
			return std::make_shared<F_Fox>(position);
		}
	}
	else if (neighbor_count[static_cast<int>(Role::GRASS)] > 0) {
		return std::make_shared<Grass>(position);
	}
	else {
		return std::make_shared<Empty>(position);
	}

}

std::ostream &Empty::display(std::ostream &os){
	return os << "    ";
}

// Implementing class DeadGrass:
std::shared_ptr<Living> DeadGrass::next(const World_t &world){
	if (age >= 0) {
		// return empty
		return std::make_shared<Empty>(position);
	}
	else {
		return std::make_shared<DeadGrass>(position, age+1);
	}
}


std::ostream &DeadGrass::display(std::ostream &os){
	return os << " xx ";
}


// Implementing class Grass:
std::shared_ptr<Living> Grass::next(const World_t &world){
	SpeciesCount_t neighbor_count{0};
	neighborhood(world, neighbor_count);

	int new_height = height;
	// Grow grass
	if (neighbor_count[static_cast<int>(Role::GRASS)] > 1) {
		new_height += 2;
	}
	else {
		new_height += 1;
	}
	if (new_height > 5) {
		new_height = 5;
	}

	// Grass eaten by rabbits:
    int m_rabbits { neighbor_count[static_cast<int>(Role::M_RABBIT)] };
    int f_rabbits { neighbor_count[static_cast<int>(Role::F_RABBIT)] };
    new_height -= m_rabbits;
    new_height -= f_rabbits;

	if (new_height <= 0) {
		// plant is death
		return std::make_shared<DeadGrass>(position);;
	}
	else {
		return std::make_shared<Grass>(position, new_height);
	}
}


std::ostream &Grass::display(std::ostream &os){
	switch(height){
	case 1:
		os << " |  ";
		break;
	case 2:
		os << " || ";
		break;
	case 3:
		os << " |||";
		break;
	case 4:
		os << "||||";
		break;
	case 5:
		os << "||||";
		break;
	}
	return os;
}

// Implementing class Rabbit
std::shared_ptr<Living> Rabbit::next(const World_t &world){
	SpeciesCount_t neighbor_count{0};
	neighborhood(world, neighbor_count);
	age += 1;

	if (neighbor_count[static_cast<int>(Role::GRASS)] == 0){
		foodlessCycles += 1;
	}
	else {
		foodlessCycles = 0;
	}

	// count foxes in neighborhood
	int n_fox = neighbor_count[static_cast<int>(Role::M_FOX)];
	n_fox += neighbor_count[static_cast<int>(Role::F_FOX)];

	if ((n_fox > 0) or (age > LIFESPAN_RABBIT) or (foodlessCycles > 1)){
		return std::make_shared<Empty>(position);
	}
	else {
		return newSelf();
	}
}

std::shared_ptr<Living> Rabbit::newSelf(){
	return std::make_shared<Empty>(position);
}

std::ostream &M_Rabbit::display(std::ostream &os){
	return os << " R\u2642 ";
}

std::shared_ptr<Living> M_Rabbit::newSelf(){
	return std::make_shared<M_Rabbit>(position, age, foodlessCycles);
}

std::ostream &F_Rabbit::display(std::ostream &os){
	return os << " R\u2640 ";
}
std::shared_ptr<Living> F_Rabbit::newSelf(){
	return std::make_shared<F_Rabbit>(position, age, foodlessCycles);
}

// Implementing class M_Fox
std::shared_ptr<Living> Fox::next(const World_t &world){
	SpeciesCount_t neighbor_count{0};
	neighborhood(world, neighbor_count);
	age += 1;

	// count foxes in neighborhood
	unsigned int n_fox = neighbor_count[static_cast<int>(Role::M_FOX)];
	n_fox += neighbor_count[static_cast<int>(Role::F_FOX)];

	if ((neighbor_count[static_cast<int>(Role::F_RABBIT)] == 0)
			and (neighbor_count[static_cast<int>(Role::M_RABBIT)] == 0)){
		foodlessCycles += 1;
	}
	else {
		foodlessCycles = 0;
	}

	if ((age > LIFESPAN_FOX)
			or (foodlessCycles > 1)
			or (n_fox > MAX_POPULATION_FOX)){
		return std::make_shared<Empty>(position);;
	}
	else {
		return newSelf();
	}
}

std::shared_ptr<Living> Fox::newSelf(){
	return std::make_shared<Empty>(position);
}

std::ostream &M_Fox::display(std::ostream &os){
	return os << " F\u2642 ";
}

std::shared_ptr<Living> M_Fox::newSelf(){
	return std::make_shared<M_Fox>(position, age, foodlessCycles);
}

std::ostream &F_Fox::display(std::ostream &os){
	return os << " F\u2640 ";
}

std::shared_ptr<Living> F_Fox::newSelf(){
	return std::make_shared<F_Fox>(position, age, foodlessCycles);
}

