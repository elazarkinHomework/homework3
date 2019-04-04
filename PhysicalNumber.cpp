/*
 * PhysicalNumber.cpp
 *
 *  Created on: Apr 2, 2019
 *      Author: elazar
 */

#include "PhysicalNumber.h"

namespace ariel {

const Unit PhysicalNumber::LenghtMeasure::s_friends[] = {Unit::KM, Unit::M, Unit::CM, Unit::MM};

const Unit PhysicalNumber::WeightMeasure::s_friends[] = {Unit::TON, Unit::KG, Unit::G};

const Unit PhysicalNumber::TimeMeasure::s_friends[] = {Unit::HOUR, Unit::MIN, Unit::SEC};

const PhysicalNumber::IMeasure::CreateIfContainMeasureFunction *PhysicalNumber::IMeasure::s_createIfContainMeasureFunctions[] =
{
	&PhysicalNumber::LenghtMeasure::createIfContainMeasure,
	&PhysicalNumber::WeightMeasure::createIfContainMeasure,
	&PhysicalNumber::TimeMeasure::createIfContainMeasure
};

PhysicalNumber::PhysicalNumber(double value, Unit type)
{
	m_measure = IMeasure::generateMeasure(type);
}

PhysicalNumber::~PhysicalNumber()
{
	if(m_measure != NULL)
	{
		delete[] m_measure;
	}
}

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber&)
{
	//TODO
	return PhysicalNumber(0.0, Unit::M);
}

PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber&)
{
	//TODO
	return PhysicalNumber(0.0, Unit::M);
}

PhysicalNumber PhysicalNumber::operator-()
{
	//TODO
	return PhysicalNumber(0.0, Unit::M);
}

PhysicalNumber& PhysicalNumber::operator +=(const PhysicalNumber&)
{
	//TODO
	return *this;
}

PhysicalNumber::IMeasure::IMeasure(Unit u)
{
	m_unit = u;
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
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		return new PhysicalNumber::LenghtMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::LenghtMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out = (Unit **)&s_friends;
	amount = sizeof(s_friends)/sizeof(Unit);
}

PhysicalNumber::WeightMeasure::WeightMeasure(Unit u):IMeasure(u){}

PhysicalNumber::IMeasure* PhysicalNumber::WeightMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		return new WeightMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::WeightMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out = (Unit **)&s_friends;
	amount = sizeof(s_friends)/sizeof(Unit);
}

PhysicalNumber::TimeMeasure::TimeMeasure(Unit u):IMeasure(u){}

PhysicalNumber::IMeasure* PhysicalNumber::TimeMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		return new TimeMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::TimeMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out = (Unit **)&s_friends;
	amount = sizeof(s_friends)/sizeof(Unit);
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

}  // namespace ariel
