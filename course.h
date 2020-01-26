#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "section.h"

class Course {
	string name;
	string department;
	int num;
	vector<Section> sections;

public:
	Course() : name(""), department(""), num(0), sections({}) {}

	const string& getDepartment() const {
		return department;
	}

	void setDepartment(const string &department) {
		this->department = department;
	}

	const string getName() const {
		return name;
	}

	void setName(const string str) {
		name = str;
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

	void print(){
		cout << "Name: " << getName();
		cout << ", Department: " << getDepartment();
		cout << ", Num: "<< getNum() << endl;
		for(Section s : sections) {
			s.print();
		}
	}
};


#endif



