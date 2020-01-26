#ifndef SECTION_H_
#define SECTION_H_

#include "types.h"

class Section {
	int crn;
	int sNum;
	string name;
	vector<Type> types;

public:
	Section() : crn(0), sNum(0), name(""), types({}) {}
	const int getCrn() const {
		return crn;
	}
	
	void setName(const string& name) {
		this->name = name;
	}
	
	const string& getName() const {
		return name;
	}

	void setCrn(const int crn) {
		this->crn = crn;
	}

	vector<Type>& getTypes() {
		return types;
	}

	void setSection(const vector<Type> &types) {
		this->types = types;
	}

	const int getNum() const {
		return sNum;
	}

	void setNum(const int num) {
		sNum = num;
	}

	void addType(Type typ) {
		this->types.push_back(typ);
	}
};


#endif /* SECTION_H_ */
