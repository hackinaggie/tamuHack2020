#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "section.h"

class Course {
	string department;
	int num;
	vector<Section> sections;

public:
	Course() : department(""), num(0), sections({}) {}

	const string& getDepartment() const {
		return department;
	}

	void setDepartment(const string &department) {
		this->department = department;
	}

	const int getNum() const {
		return num;
	}

	void setNum(const int n) {
		num = n;
	}

	vector<Section>& getSections() {
		return sections;
	}

	void setSection(const vector<Section> &section) {
		this->sections = section;
	}

	void addSection( Section sec) {
		this->sections.push_back(sec);
	}
};


#endif



