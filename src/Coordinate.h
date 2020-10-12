/**
 * @file Cordinate.h
 * @ref <wotf>
 * @copyright Bern University of Applied Sciences
 *            All rights reserved Max BOEGLI, Florian Dominic BURRI, 2020.
 *
 * @author Max BOEGLI             -- <max.boegli@students.bfh.ch>
 *         Florian Dominic BURRI  -- <floriandominic.burri@students.bfh.ch>
 *
 * @date 21-06-2020
 *
 * @brief Simple Coordinate Class.
 *
 */


#ifndef SRC_COORDINATE_H_
#define SRC_COORDINATE_H_

struct Coordinate {
public:
	Coordinate() : x{0}, y{0} { }
	Coordinate(unsigned int x, unsigned int y) : x{x}, y{y} { }
	unsigned int x;
	unsigned int y;
};

#endif /* SRC_COORDINATE_H_ */
