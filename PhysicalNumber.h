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

	class IMeasure
	{
	protected:
		Unit m_unit;

		virtual void lockOnFriendsMeasures(Unit **, int &amount){}

	public:

		IMeasure(Unit u);
		static bool isFriend(const Unit *friendsList, int listSize, Unit u);

		static IMeasure *generateMeasure(Unit u);

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
		const static Unit s_friends[];

	protected:
		void lockOnFriendsMeasures(Unit **, int &amount);

	public:
		static IMeasure* createIfContainMeasure(Unit u);
	};

	class WeightMeasure : public IMeasure
	{
	public:
		WeightMeasure(Unit u);
	private:
			const static Unit s_friends[];

	protected:
			void lockOnFriendsMeasures(Unit **, int &amount);

	public:
			static IMeasure* createIfContainMeasure(Unit u);
	};

	class TimeMeasure : public IMeasure
	{
	public:
		TimeMeasure(Unit u);
	private:
			const static Unit s_friends[];

	protected:
			void lockOnFriendsMeasures(Unit **, int &amount);

	public:
			static IMeasure* createIfContainMeasure(Unit u);
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

	friend std::ostream& operator<<(std::ostream& out, const PhysicalNumber&)
	{
		return out;
	}

	friend std::istream& operator>>(std::istream& in, const PhysicalNumber&)
	{
		return in;
	}
};

}  // namespace ariel
#endif /* PHYSICALNUMBER_H_ */
