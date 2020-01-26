#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "section.h"

class Course {
	string name;
	string department;
	string num;
	vector<Section> sections;

public:
	Course() : name(""), department(""), num(""), sections({}) {}

	const string& getDepartment() const {
		return department;
	}

	void setDepartment(const string &department) {
		this->department = department;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string &name) {
		this->name = name;
	}

	const string& getNum() const {
		return num;
	}

	void setNum(const string &num) {
		this->num = num;
	}

	vector<Section>& getSection() {
		return sections;
	}

	void setSection(const vector<Section> &section) {
		this->sections = section;
	}

	void addSection( Section sec) {
		this->sections.push_back(sec);
	}

	void print(){
		cout << "Name: "<< getName() << ", Department: " << getDepartment() << ", Num: "<< getNum() << endl;
	}
};


#endif



