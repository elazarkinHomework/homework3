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
	KM = 0, M, CM, MM, HOUR, MIN, SEC, TON, KG, G, UNITS_SIZE
};

static const char *UnitToStringMap[] =
{
	"km", "m", "cm", "mm", "hour", "min", "sec", "ton", "kg", "g"
};

inline std::ostream& operator<<(std::ostream &os, Unit u)
{
	os << UnitToStringMap[u];
	return os;
}

}  // namespace ariel




#endif /* UNIT_H_ */
