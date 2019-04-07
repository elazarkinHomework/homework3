/*
 * PhysicalNumber.h
 *
 *  Created on: Apr 2, 2019
 *      Author: elazar
 */

#ifndef PHYSICALNUMBER_H_
#define PHYSICALNUMBER_H_

#include "Unit.h"
#include <ostream>
#include <istream>
#include <iostream>
#include <iomanip>
#include <string.h>

namespace ariel {


class PhysicalNumber
{
private:

	double m_value;

	class UnitsScalesLookUpTable
	{
	private:
		double m_lookUpTable[Unit::UNITS_SIZE];

		typedef void (LockOnFriendsUnitsAndScalesFunction)(Unit **units, double **scales, int &amount);

		static LockOnFriendsUnitsAndScalesFunction *s_lockOnFriendsUnitsAndScalesFunction[];

	public:
		UnitsScalesLookUpTable();

		double operator[](const Unit &u) const { return m_lookUpTable[u];}

	};

	class IMeasure
	{
	private:
		static const UnitsScalesLookUpTable s_unitsScalesLookUpTable;

	protected:
		Unit m_unit;

		virtual void lockOnFriendsMeasures(Unit **, int &amount){}

	public:

		IMeasure(Unit u);

		Unit unit();

		bool checkIfUnitIsFried(Unit u);

		static bool isFriend(const Unit *friendsList, int listSize, Unit u);

		static IMeasure *generateMeasure(Unit u);

		static double toSmallestUnit(double value, Unit unit);

		void updateType(Unit u);

		/**
		 * This util function can't be static cause we call virtual method of get friends
		 * so in a practice we use m_measure object even though it not use any internal variables
		 */
		void smallestResultToBestCompact(double &value, Unit &unit);

		void smallestResultToForceFormat(double &value, const Unit unit);

	public:
		typedef IMeasure*(CreateIfContainMeasureFunction)(Unit u);

	private:
		static CreateIfContainMeasureFunction *s_createIfContainMeasureFunctions[];
	};

	class LenghtMeasure : public IMeasure
	{
	public:
		LenghtMeasure(Unit u);

	private:
		const static Unit s_friendsOrdBig2Small[];
		const static double s_scalesRelatedSmallest[];

	protected:
		void lockOnFriendsMeasures(Unit **, int &amount);

	public:
		static IMeasure* createIfContainMeasure(Unit u);

		static void LockOnFriendsUnitsAndScales(Unit **units, double **scales, int &amount);
	};

	class WeightMeasure : public IMeasure
	{
	public:
		WeightMeasure(Unit u);
	private:
			const static Unit s_friendsOrdBig2Small[];
			const static double s_scalesRelatedSmallest[];

	protected:
			void lockOnFriendsMeasures(Unit **, int &amount);

	public:
			static IMeasure* createIfContainMeasure(Unit u);

			static void LockOnFriendsUnitsAndScales(Unit **units, double **scales, int &amount);

	};

	class TimeMeasure : public IMeasure
	{
	public:
		TimeMeasure(Unit u);
	private:
			const static Unit s_friendsOrdBig2Small[];
			const static double s_scalesRelatedSmallest[];

	protected:
			void lockOnFriendsMeasures(Unit **, int &amount);

	public:
			static IMeasure* createIfContainMeasure(Unit u);

			static void LockOnFriendsUnitsAndScales(Unit **units, double **scales, int &amount);

	};

	IMeasure *m_measure;

public:
	PhysicalNumber(double value, Unit type);
	virtual ~PhysicalNumber();

	void throwIfWrongMeasures(const PhysicalNumber &another);

	PhysicalNumber operator+(const PhysicalNumber&);
	PhysicalNumber operator-(const PhysicalNumber&);
	PhysicalNumber operator-();
	PhysicalNumber& operator+=(const PhysicalNumber&);

	bool operator<(const PhysicalNumber&);
	bool operator<=(const PhysicalNumber&);
	bool operator>(const PhysicalNumber&);
	bool operator>=(const PhysicalNumber&);
	bool operator==(const PhysicalNumber&);

	friend std::ostream& operator<<(std::ostream& out, const PhysicalNumber& pn)
	{
		//out<< std::fixed << std::setw(11) << std::setprecision(3) << pn.m_value << "[" << pn.m_measure->unit() << "]";
		out<<pn.m_value << "[" << pn.m_measure->unit() << "]";
		return out;
	}

	friend std::istream& operator>>(std::istream& in, PhysicalNumber& pn)
	{
		std::string message;
		double value;
		char measure[16];
		int ret = 0;
		bool success = true;

		in >> message;

		success = (ret=sscanf(message.c_str(), "%lf[%[^]]s]", &value, measure)) == 2;

		if(success)
		{
			pn.m_value = value;

			success = false;

			for(int u = 0; u < Unit::UNITS_SIZE; u++)
			{
				if(strcmp(UnitToStringMap[u], measure) == 0)
				{
					if(pn.m_measure != NULL)
					{
						delete pn.m_measure;
						pn.m_measure = NULL;
					}
					pn.m_measure = IMeasure::generateMeasure((Unit) u);
					success = true;
					break;
				}
			}
		}

		if(!success)
		{
			fprintf
			(
				stderr,
				"Warning: used wrong format init PhysicalNumber with istream operator! (was <%s> must be <value[measure]>)\n",
				message.c_str()
			);
		}

		return in;
	}
};

}  // namespace ariel
#endif /* PHYSICALNUMBER_H_ */
