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
	string startTime;
	string endTime;

public:
	Type() : lecType(""), days(""), startTime(""), endTime("") {}
	const string& getEndTime() const {
		return endTime;
	}

	void setDays(const string &days) {
		this->days = days;
	}


	void setLecType(const string &lecType) {
		this->lecType = lecType;
	}

	void setEndTime(const string &endTime) {
		this->endTime = endTime;
	}

	const string& getStartTime() const {
		return startTime;
	}

	const string& getLecType() const {
		return lecType;
	}

	const string& getDays() const {
		return days;
	}

	void setStartTime(const string &startTime) {
		this->startTime = startTime;
	}

	void print(){
		cout<< "	Lecture Type: " << getLecType() << ", Days: "<< getDays() << ", Start Time: " << getStartTime()
				<< ", End Time: " << getEndTime() << endl;
	}
};


#endif /* TYPES_H_ */
