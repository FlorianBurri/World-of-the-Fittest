/**
 * @file Living.h
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

#ifndef SRC_LIVING_H_
#define SRC_LIVING_H_

#include <ostream>
#include <string>
#include <memory>
#include <iostream>
#include <random>
#include <ctime>

#include "properties.h"
#include "Coordinate.h"

class Living;
class Empty;

enum class Role { EMPTY=0, DEAD_GRASS, GRASS, M_RABBIT, F_RABBIT ,M_FOX, F_FOX, MAX_LIVING};
static const int n_species = static_cast<int>(Role::MAX_LIVING);

// custom data types
using World_t = std::array<std::array<std::shared_ptr<Living>, EDGE_LENGTH_GAME_BOARD +2>, EDGE_LENGTH_GAME_BOARD +2>;
using SpeciesCount_t = std::array<int, n_species>;

class Living {
public:
	Living(Coordinate inputPosition, Role inputKind);
	virtual ~Living(){ }
	Role who() const;
	virtual std::ostream &display(std::ostream &os);
	virtual std::shared_ptr<Living> next(const World_t &world);
protected:
	void neighborhood(const World_t &world, SpeciesCount_t &result) const;
	Coordinate position;
	Role kind;
};

class Empty: public Living {
public:
	Empty(Coordinate inputPosition):
		Living(inputPosition, Role::EMPTY){ }
	~Empty(){ }
	std::ostream &display(std::ostream &os) override;
	std::shared_ptr<Living> next(const World_t &world) override;
};

class DeadGrass: public Living {
public:
	DeadGrass(Coordinate inputPosition):
		Living(inputPosition, Role::DEAD_GRASS), age{0} { }
	DeadGrass(Coordinate inputPosition, unsigned int age):
		Living(inputPosition, Role::DEAD_GRASS), age{age} { }
	~DeadGrass(){ }
	std::ostream &display(std::ostream &os) override;
	std::shared_ptr<Living> next(const World_t &world) override;
protected:
	unsigned int age;
};

class Grass: public Living {
public:
	Grass(Coordinate inputPosition):
		Living(inputPosition, Role::GRASS), height{1} { }
	Grass(Coordinate inputPosition, unsigned int height):
			Living(inputPosition, Role::GRASS), height{height} { }
	~Grass(){ }
	std::ostream &display(std::ostream &os) override;
	std::shared_ptr<Living> next(const World_t &world) override;
protected:
	unsigned int height;
};

class Rabbit: public Living {
public:

	Rabbit(Coordinate inputPosition, Role inputKind):
			Living(inputPosition, inputKind), age{0}, foodlessCycles{0} { }
	Rabbit(Coordinate inputPosition,  Role inputKind, unsigned int age, unsigned int foodlessCycles):
			Living(inputPosition, inputKind), age{age}, foodlessCycles{foodlessCycles} { }

	virtual ~Rabbit(){ }
	std::shared_ptr<Living> next(const World_t &playground) override;
protected:
	virtual std::shared_ptr<Living> newSelf();
	unsigned int age;
	unsigned int foodlessCycles;
};

class M_Rabbit: public Rabbit {
public:
        M_Rabbit(Coordinate inputPosition):
        		Rabbit(inputPosition, Role::M_RABBIT) { }
        M_Rabbit(Coordinate inputPosition, unsigned int age, unsigned int foodlessCycles):
                Rabbit(inputPosition, Role::M_RABBIT, age , foodlessCycles) { }
        ~M_Rabbit(){ }
        std::ostream &display(std::ostream &os) override;
protected:
        std::shared_ptr<Living> newSelf() override;
};

class F_Rabbit: public Rabbit {
public:
	F_Rabbit(Coordinate inputPosition):
			Rabbit(inputPosition, Role::F_RABBIT) { }
	F_Rabbit(Coordinate inputPosition, unsigned int age, unsigned int foodlessCycles):
			Rabbit(inputPosition, Role::F_RABBIT, age , foodlessCycles) { }
	~F_Rabbit(){ }
	std::ostream &display(std::ostream &os) override;
protected:
	std::shared_ptr<Living> newSelf() override;
};

class Fox: public Living {
public:
	Fox(Coordinate inputPosition, Role inputKind):
			Living(inputPosition, inputKind), age{0}, foodlessCycles{0} { }
	Fox(Coordinate inputPosition, Role inputKind,  unsigned int age, unsigned int foodlessCycles):
			Living(inputPosition, inputKind), age{age}, foodlessCycles{foodlessCycles} { }
	virtual ~Fox(){ }
	std::shared_ptr<Living> next(const World_t &playground) override;
protected:
	virtual std::shared_ptr<Living> newSelf();
	unsigned int age;
	unsigned int foodlessCycles;
};

class M_Fox: public Fox {
public:
	M_Fox(Coordinate inputPosition):
			Fox(inputPosition, Role::M_FOX) { }
	M_Fox(Coordinate inputPosition, unsigned int age, unsigned int foodlessCycles):
			Fox(inputPosition, Role::M_FOX, age, foodlessCycles) { }
	~M_Fox(){ }
	std::ostream &display(std::ostream &os) override;
protected:
	virtual std::shared_ptr<Living> newSelf() override;
};

class F_Fox: public Fox {
public:
	F_Fox(Coordinate inputPosition):
			Fox(inputPosition, Role::F_FOX) { }
	F_Fox(Coordinate inputPosition, unsigned int age, unsigned int foodlessCycles):
			Fox(inputPosition, Role::F_FOX, age, foodlessCycles) { }
	~F_Fox(){ }
	std::ostream &display(std::ostream &os) override;
protected:
	virtual std::shared_ptr<Living> newSelf() override;
};

#endif /* SRC_LIVING_H_ */
