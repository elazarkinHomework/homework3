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

		static const LockOnFriendsUnitsAndScalesFunction *s_lockOnFriendsUnitsAndScalesFunction[];

	public:
		UnitsScalesLookUpTable();

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

		static bool isFriend(const Unit *friendsList, int listSize, Unit u);

		static IMeasure *generateMeasure(Unit u);

		static double toSmallestUnit(double value, Unit unit);

	public:
		typedef IMeasure*(CreateIfContainMeasureFunction)(Unit u);

	private:
		static const CreateIfContainMeasureFunction *s_createIfContainMeasureFunctions[];
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

	PhysicalNumber operator+(const PhysicalNumber&);
	PhysicalNumber operator-(const PhysicalNumber&);
	PhysicalNumber operator-();
	PhysicalNumber& operator+=(const PhysicalNumber&);

	bool operator<(const PhysicalNumber&){return false;}
	bool operator<=(const PhysicalNumber&){return false;}
	bool operator>(const PhysicalNumber&){return false;}
	bool operator>=(const PhysicalNumber&){return false;}
	bool operator==(const PhysicalNumber&){return false;}

	friend std::ostream& operator<<(std::ostream& out, const PhysicalNumber& pn)
	{
		out << pn.m_value << "[" << pn.m_measure->unit() << "]";
		return out;
	}

	friend std::istream& operator>>(std::istream& in, const PhysicalNumber&)
	{
		return in;
	}
};

}  // namespace ariel
#endif /* PHYSICALNUMBER_H_ */
