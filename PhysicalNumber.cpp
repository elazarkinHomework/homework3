/*
 * PhysicalNumber.cpp
 *
 *  Created on: Apr 2, 2019
 *      Author: elazar
 */

#include "PhysicalNumber.h"

#include <math.h>

namespace ariel {

const Unit PhysicalNumber::LenghtMeasure::s_friendsOrdBig2Small[] = {Unit::KM, Unit::M, Unit::CM, Unit::MM};
const double PhysicalNumber::LenghtMeasure::s_scalesRelatedSmallest[] = {1000000.0, 1000.0, 10.0, 1.0};

const Unit PhysicalNumber::WeightMeasure::s_friendsOrdBig2Small[] = {Unit::TON, Unit::KG, Unit::G};
const double PhysicalNumber::WeightMeasure::s_scalesRelatedSmallest[] = {1000000.0, 1000.0, 1.0};

const Unit PhysicalNumber::TimeMeasure::s_friendsOrdBig2Small[] = {Unit::HOUR, Unit::MIN, Unit::SEC};
const double PhysicalNumber::TimeMeasure::s_scalesRelatedSmallest[] = {3600.0, 60.0, 1.0};

const PhysicalNumber::UnitsScalesLookUpTable PhysicalNumber::IMeasure::s_unitsScalesLookUpTable;

const PhysicalNumber::IMeasure::CreateIfContainMeasureFunction *PhysicalNumber::IMeasure::s_createIfContainMeasureFunctions[] =
{
	&PhysicalNumber::LenghtMeasure::createIfContainMeasure,
	&PhysicalNumber::WeightMeasure::createIfContainMeasure,
	&PhysicalNumber::TimeMeasure::createIfContainMeasure
};

const PhysicalNumber::UnitsScalesLookUpTable::LockOnFriendsUnitsAndScalesFunction *PhysicalNumber::UnitsScalesLookUpTable::s_lockOnFriendsUnitsAndScalesFunction[] =
{
	&PhysicalNumber::LenghtMeasure::LockOnFriendsUnitsAndScales,
	&PhysicalNumber::WeightMeasure::LockOnFriendsUnitsAndScales,
	&PhysicalNumber::TimeMeasure::LockOnFriendsUnitsAndScales
};

PhysicalNumber::UnitsScalesLookUpTable::UnitsScalesLookUpTable()
{
	int FUNCTIONS_SIZE = sizeof(s_lockOnFriendsUnitsAndScalesFunction)/sizeof(PhysicalNumber::UnitsScalesLookUpTable::LockOnFriendsUnitsAndScalesFunction *);

	for(int i = 0; i < FUNCTIONS_SIZE; i++)
	{
		Unit *unitPtr = NULL;
		double *scalePtr = NULL;
		int amount = 0;

		s_lockOnFriendsUnitsAndScalesFunction[i](&unitPtr, &scalePtr, amount);

		for(int j = 0; j < amount; j++)
		{
			m_lookUpTable[unitPtr[j]] = scalePtr[j];
		}
	}
}

PhysicalNumber::PhysicalNumber(double value, Unit type)
{
	m_value = value;
	m_measure = IMeasure::generateMeasure(type);
}

PhysicalNumber::~PhysicalNumber()
{
	if(m_measure != NULL)
	{
		delete[] m_measure;
	}
}

// TODO
// TODO
// TODO check friend measures before operation!
// TODO
// TODO

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& another)
{
	double result = IMeasure::toSmallestUnit(m_value, m_measure->unit()) + IMeasure::toSmallestUnit(another.m_value, another.m_measure->unit());
	double fixedResult = result;
	Unit fixedMeasureType;

	m_measure->smallestResultToBestCompact(fixedResult, fixedMeasureType);

	return PhysicalNumber(fixedResult, fixedMeasureType);
}

PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber&another)
{
	double result = IMeasure::toSmallestUnit(m_value, m_measure->unit()) - IMeasure::toSmallestUnit(another.m_value, another.m_measure->unit());
	double fixedResult = result;
	Unit fixedMeasureType;

	m_measure->smallestResultToBestCompact(fixedResult, fixedMeasureType);

	return PhysicalNumber(fixedResult, fixedMeasureType);
}

PhysicalNumber PhysicalNumber::operator-()
{
	double result = -IMeasure::toSmallestUnit(m_value, m_measure->unit());
	double fixedResult = result;
	Unit fixedMeasureType;

	m_measure->smallestResultToBestCompact(fixedResult, fixedMeasureType);

	return PhysicalNumber(fixedResult, fixedMeasureType);
}

PhysicalNumber& PhysicalNumber::operator +=(const PhysicalNumber&another)
{
	double result = IMeasure::toSmallestUnit(m_value, m_measure->unit()) + IMeasure::toSmallestUnit(another.m_value, another.m_measure->unit());
	double fixedResult = result;
	Unit fixedMeasureType;

	m_measure->smallestResultToBestCompact(fixedResult, fixedMeasureType);

	m_value = fixedResult;
	m_measure->updateType(fixedMeasureType);

	return *this;
}

PhysicalNumber::IMeasure::IMeasure(Unit u)
{
	m_unit = u;
}

Unit PhysicalNumber::IMeasure::unit()
{
	return m_unit;
}

bool PhysicalNumber::IMeasure::isFriend(const Unit *friendsList, int listSize, Unit u)
{
	for(int i = 0; i < listSize; i++)
	{
		if(friendsList[i] == u)
		{
			return true;
		}
	}
	return false;
}

PhysicalNumber::LenghtMeasure::LenghtMeasure(Unit u):IMeasure(u){}

PhysicalNumber::IMeasure* PhysicalNumber::LenghtMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friendsOrdBig2Small, sizeof(s_friendsOrdBig2Small)/sizeof(Unit), u))
	{
		return new PhysicalNumber::LenghtMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::LenghtMeasure::LockOnFriendsUnitsAndScales(Unit **units, double **scales, int &amount)
{
	amount = sizeof(s_friendsOrdBig2Small)/sizeof(Unit);
	units[0] = (Unit *) s_friendsOrdBig2Small;
	scales[0] = (double *) s_scalesRelatedSmallest;
}

void PhysicalNumber::LenghtMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out[0] = (Unit *)s_friendsOrdBig2Small;
	amount = sizeof(s_friendsOrdBig2Small)/sizeof(Unit);
}

PhysicalNumber::WeightMeasure::WeightMeasure(Unit u):IMeasure(u){}

PhysicalNumber::IMeasure* PhysicalNumber::WeightMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friendsOrdBig2Small, sizeof(s_friendsOrdBig2Small)/sizeof(Unit), u))
	{
		return new WeightMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::WeightMeasure::LockOnFriendsUnitsAndScales(Unit **units, double **scales, int &amount)
{
	amount = sizeof(s_friendsOrdBig2Small)/sizeof(Unit);
	units[0] = (Unit *) s_friendsOrdBig2Small;
	scales[0] = (double *) s_scalesRelatedSmallest;
}

void PhysicalNumber::WeightMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out[0] = (Unit *)s_friendsOrdBig2Small;
	amount = sizeof(s_friendsOrdBig2Small)/sizeof(Unit);
}

PhysicalNumber::TimeMeasure::TimeMeasure(Unit u):IMeasure(u){}

PhysicalNumber::IMeasure* PhysicalNumber::TimeMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friendsOrdBig2Small, sizeof(s_friendsOrdBig2Small)/sizeof(Unit), u))
	{
		return new TimeMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::TimeMeasure::LockOnFriendsUnitsAndScales(Unit **units, double **scales, int &amount)
{
	amount = sizeof(s_friendsOrdBig2Small)/sizeof(Unit);
	units[0] = (Unit *) s_friendsOrdBig2Small;
	scales[0] = (double *) s_scalesRelatedSmallest;
}

void PhysicalNumber::TimeMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out[0] = (Unit *)s_friendsOrdBig2Small;
	amount = sizeof(s_friendsOrdBig2Small)/sizeof(Unit);
}

PhysicalNumber::IMeasure* PhysicalNumber::IMeasure::generateMeasure(Unit u)
{
	IMeasure* ret = NULL;

	int FUNCTIONS_SIZE = sizeof(s_createIfContainMeasureFunctions)/sizeof(PhysicalNumber::IMeasure::CreateIfContainMeasureFunction *);

	int functionsIndex = 0;

	while(functionsIndex < FUNCTIONS_SIZE && (ret=s_createIfContainMeasureFunctions[functionsIndex](u)) == NULL)
	{
		functionsIndex++;
	}

	return ret;
}

void PhysicalNumber::IMeasure::updateType(Unit u)
{
	// TODO test if u is friend
	m_unit = u;
}

double PhysicalNumber::IMeasure::toSmallestUnit(double value, Unit unit)
{
	return value*s_unitsScalesLookUpTable[unit];
}

void PhysicalNumber::IMeasure::smallestResultToBestCompact(double &value, Unit &unit)
{
	Unit *unitsPtr = NULL;
	int amount = 0;
	int bestIndex;

	lockOnFriendsMeasures(&unitsPtr, amount);

	bestIndex = amount - 1;

	while(bestIndex > 0 && fabs(value/s_unitsScalesLookUpTable[unitsPtr[bestIndex-1]]) > 1.0)
	{
		bestIndex--;
	}

	unit = unitsPtr[bestIndex];
	value /= s_unitsScalesLookUpTable[unitsPtr[bestIndex]];
}

}  // namespace ariel
