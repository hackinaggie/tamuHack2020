/*
 * types.h
 *
 *  Created on: Jan 25, 2020
 *      Author: Joao Pedro
 */

#ifndef TYPES_H_
#define TYPES_H_


class Type {
	string lecType;
	string days;
	int startTime;
	int endTime;

public:
	Type() : lecType(""), days(""), startTime(0), endTime(0) {}
	const int getEndTime() const {
		return endTime;
	}

	void setDays(const string &days) {
		this->days = days;
	}


	void setLecType(const string &lecType) {
		this->lecType = lecType;
	}

	void setEndTime(const int endTime) {
		this->endTime = endTime;
	}

	const int getStartTime() const {
		return startTime;
	}
	
	const string militarytoStandard(int mil) {
		string suffix = "am";
		if(mil >= 1200) suffix = "pm";
		if(mil >= 1300) mil -= 1200;
		int hour = mil / 100;
		int min = mil % 100;
		return to_string(hour) + ":" + to_string(min) + suffix;
	}
	
	const string getStartTimeString() {
		return militarytoStandard(startTime);
	}
	
	const string getEndTimeString() {
		return militarytoStandard(endTime);
	}

	const string& getLecType() const {
		return lecType;
	}

	const string& getDays() const {
		return days;
	}

	void setStartTime(const int startTime) {
		this->startTime = startTime;
	}
};


#endif /* TYPES_H_ */
