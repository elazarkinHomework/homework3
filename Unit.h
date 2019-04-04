/*
 * Unit.h
 *
 *  Created on: Apr 2, 2019
 *      Author: elazar
 */

#ifndef UNIT_H_
#define UNIT_H_

#include <ostream>

namespace ariel
{

enum Unit
{
	KM = 0, M, CM, MM, HOUR, MIN, SEC, TON, KG, G
};

static const char *UnitToStringMap[] =
{
	"KM", "M", "CM", "MM", "HOUR", "MIN", "SEC", "TON", "KG", "G"
};

inline std::ostream& operator<<(std::ostream &os, Unit u)
{
	os << UnitToStringMap[u];
	return os;
}

}  // namespace ariel




#endif /* UNIT_H_ */
