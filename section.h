#ifndef SECTION_H_
#define SECTION_H_

#include "types.h"

class Section {
	string crn;
	string sNum;
	vector<Type> types;

public:
	Section() : crn(""), sNum(""), types({}) {}
	const string& getCrn() const {
		return crn;
	}

	void setCrn(const string &crn) {
		this->crn = crn;
	}

	vector<Type>& getTypes() {
		return types;
	}

	void setSection(const vector<Type> &types) {
		this->types = types;
	}

	const string& getNum() const {
		return sNum;
	}

	void setNum(const string &num) {
		sNum = num;
	}

	void addType( Type typ) {
		this->types.push_back(typ);
	}

	void print(){
		cout << "    CRN: " << getCrn() << ", Sec Number: " << getNum() << endl;
	}
};


#endif /* SECTION_H_ */
