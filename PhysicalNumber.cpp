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

PhysicalNumber::IMeasure* PhysicalNumber::LenghtMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		printf("create LenghtMeasure\n");
		//return new LenghtMeasure(u);
	}
	return NULL;
}

PhysicalNumber::IMeasure* PhysicalNumber::WeightMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		printf("create WeightMeasure\n");
		//return new WeightMeasure(u);
	}
	return NULL;
}

PhysicalNumber::IMeasure* PhysicalNumber::TimeMeasure::createIfContainMeasure(Unit u)
{
	if(isFriend(s_friends, sizeof(s_friends)/sizeof(Unit), u))
	{
		printf("create TimeMeasure\n");
		//return new TimeMeasure(u);
	}
	return NULL;
}

PhysicalNumber::IMeasure* PhysicalNumber::IMeasure::generateMeasure(Unit u)
{
	IMeasure* ret = NULL;

	int FUNCTIONS_SIZE = sizeof(s_createIfContainMeasureFunctions)/sizeof(PhysicalNumber::IMeasure::CreateIfContainMeasureFunction *);

	int functionsIndex = 0;

	fprintf(stdout, "generateMeasure: FUNCTIONS_SIZE = %d\n", FUNCTIONS_SIZE);

	while((ret=s_createIfContainMeasureFunctions[functionsIndex](u)) == NULL && functionsIndex < FUNCTIONS_SIZE)
	{
		fprintf(stdout, "generateMeasure: %d/%d\n", functionsIndex, FUNCTIONS_SIZE);
		functionsIndex++;
	}

	fprintf(stdout, "generateMeasure: finish\n");

	return ret;
}

}  // namespace ariel
