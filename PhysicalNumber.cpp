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
	printf("IMeasure Constructor\n");
	m_unit = u;
}

bool PhysicalNumber::IMeasure::isFriend(const Unit *friendsList, int listSize, Unit u)
{
	for(int i = 0; i < listSize; i++)
	{
		printf("check %d expect %d listSize=%d\n", friendsList[i], u, listSize);
		if(friendsList[i] == u)
		{
			return true;
		}
	}
	return false;
}

PhysicalNumber::LenghtMeasure::LenghtMeasure(Unit u):IMeasure(u)
{
	printf("LenghtMeasure Constructor\n");
}

PhysicalNumber::IMeasure* PhysicalNumber::LenghtMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		printf("create LenghtMeasure\n");
		return new PhysicalNumber::LenghtMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::LenghtMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out = (Unit **)&s_friends;
	amount = sizeof(s_friends)/sizeof(Unit);
}

PhysicalNumber::IMeasure* PhysicalNumber::WeightMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		printf("create WeightMeasure\n");
		return new WeightMeasure(u);
	}
	return NULL;
}

void PhysicalNumber::WeightMeasure::lockOnFriendsMeasures(Unit **out, int &amount)
{
	out = (Unit **)&s_friends;
	amount = sizeof(s_friends)/sizeof(Unit);
}

PhysicalNumber::IMeasure* PhysicalNumber::TimeMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		printf("create TimeMeasure\n");
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

	fprintf(stdout, "generateMeasure: FUNCTIONS_SIZE = %d\n", FUNCTIONS_SIZE);

	while(functionsIndex < FUNCTIONS_SIZE && (ret=s_createIfContainMeasureFunctions[functionsIndex](u)) == NULL)
	{
		fprintf(stdout, "generateMeasure: %d/%d\n", functionsIndex, FUNCTIONS_SIZE);
		functionsIndex++;
	}

	fprintf(stdout, "generateMeasure: finish\n");

	return ret;
}

}  // namespace ariel
