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

	const string& getLecType() const {
		return lecType;
	}

	const string& getDays() const {
		return days;
	}

	void setStartTime(const int startTime) {
		this->startTime = startTime;
	}

	void print(){
		cout << "      Lecture Type: " << getLecType() << ", Days: "<< getDays() << ", Start Time: " << getStartTime()<< ", End Time: " << getEndTime() << endl;
	}
};


#endif /* TYPES_H_ */
