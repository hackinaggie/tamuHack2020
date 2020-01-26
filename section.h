#ifndef SECTION_H_
#define SECTION_H_

#include "types.h"

class Section {
	int crn;
	int sNum;
	vector<Type> types;

public:
	Section() : crn(0), sNum(0), types({}) {}
	const int getCrn() const {
		return crn;
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

	void print() {
		cout << "   CRN: " << getCrn() << ", Sec Number: " << getNum() << endl;
		for(Type t : types) {
			t.print();
		}
	}
};


#endif /* SECTION_H_ */
