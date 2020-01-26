
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "course.h"
#include "section.h"
#include "types.h"

// Given course name and number, returns reference to said course
Course search(string input, const vector<Course> &cou) {
	for(unsigned int i = 0; i < cou.size(); i++) {
		if (input == ( cou[i].getDepartment() + " " + cou[i].getNum()) ){
			return cou[i];
		}
	}
	cout << "Didnt find it" << endl;
	exit(5);
}

// Given multiple course names and numbers,  returns vectors with references to said objects
vector<Course> searchResultsMult(const vector<string>& inputNames, const vector<Course> &cou){
	vector<Course> out;
	for(unsigned int i=0; i < inputNames.size(); i++){
		out.push_back(search(inputNames[i], cou));
	}
	return out;
}

// Loads all the data from the selected department
vector<Course> &loadDepart(string depart, vector<Course> &classes) {

	ifstream ifs(depart + ".dat");
		if (!ifs.is_open()) {
			cout << "Unable to open file"<< depart << endl;
			exit(2);
		}

	int size, size2;
	string sz;
	getline(ifs, sz);
	size = stoi(sz);


	for(int i = 0; i < size; i++) {
		string line;
		getline(ifs, line);
		stringstream ss(line);
		string crn;
		getline(ss, crn, ',');
		string department;
		getline(ss, department, ' ');
		string classNumber;
		getline(ss,classNumber,',');
		string section;
		getline(ss, section, ',');
		string name;
		getline(ss, name);

		bool found = true;
		for(unsigned int z = 0; z < classes.size(); z++) {
			if (classes.back().getNum() == classNumber) {
				found = false;
			}
		}
		if (found)
			classes.push_back(Course());
		classes.back().setName(name);
		classes.back().setDepartment(department);
		classes.back().setNum(classNumber);
		classes.back().addSection(Section());
		classes.back().getSection().back().setCrn(crn);
		classes.back().getSection().back().setNum(section);

		string sz2;
		getline(ifs, sz2);
		size2 = stoi(sz2);

		for(int a = 0; a < size2; a++) {
			classes.back().getSection().back().addType(Type());
			getline(ifs, line);
			stringstream ss(line);

			string sectionType;
			getline(ss, sectionType, ',');
			classes.back().getSection().back().getTypes().back().setLecType(sectionType);

			string day;
			getline(ss, day,',');
			classes.back().getSection().back().getTypes().back().setDays(day);

			string startTime;
			getline(ss, startTime,',');
			classes.back().getSection().back().getTypes().back().setStartTime(startTime);

			string endTime;
			getline(ss, endTime);
			classes.back().getSection().back().getTypes().back().setEndTime(endTime);

		}

	}
	return classes;
}


int main() {

	vector<string> userInput;
	userInput.push_back("ENGR");
	userInput.push_back("ENGR");
	userInput.push_back("CSCE");
	userInput.push_back("MATH");

	//will populate with vectors of courses for each department
	vector<vector<Course>> mainTing;

	for (unsigned int i = 0; i < userInput.size(); i++) {
		bool load = true;
		for (unsigned int j = 0; j < i; j++) {
			if (userInput[j].compare(userInput[i]) == 0) { load = false; break; }
		}
		if (load) {
			vector <Course> temp;
			mainTing.push_back(loadDepart(userInput[i], temp));
		}
	}
	


	return 0;
}

