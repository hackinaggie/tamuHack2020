#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <regex>
#include <stdlib.h>
#include <time.h>

using namespace std;

#include "course.h"
#include "section.h"
#include "types.h"


int maxLineLen;
int sleepNS;
bool animate;

void waitShort() {
	if(animate) {
		this_thread::sleep_for(
			chrono::nanoseconds(sleepNS));
	}
}

void waitLong() {
	if(animate) {
		this_thread::sleep_for(
			chrono::nanoseconds(400 * sleepNS));
	}
}

void printString(string str) {
	for(int i = 0; i < str.length(); i++) {
		cout << str[i] << flush;
		waitShort();
	}
}

void printStatement(string str) {
	vector<string> paragraph;
	istringstream iss(str);
	for(string s; iss >> s; ) {
		paragraph.push_back(s);
	}
	
	int i = 0;
	int lineLen = 0;
	do {
		lineLen += paragraph[i].length() + 1;
		if(lineLen > maxLineLen) {
			lineLen = 0;
			cout << endl;
		}
		printString(paragraph[i] + " ");
	} while(++i < paragraph.size());
	waitLong();
	cout << endl;
}

void printParagraph(string* strings, int numStrings) {
	for(int i = 0; i < numStrings; i++) {
		printStatement(strings[i]);
	}
	cout << endl;
}

int getInt() {
	cout << ">" << flush;
	int num;
	try {
		cin >> num;
	} catch(...) {
		return -1;
	}
	cin.clear();
	cin.ignore(100, '\n');
	return num;
}

string getString() {
	cout << "#" << flush;
	string str;
	try {
		getline(cin, str);
	} catch(...) {
		return "";
	}
	cin.clear();
	for (auto & c: str) c = toupper(c);
	return str;
}

//regex gave me dumb errors. :<
bool isValidCourse(string str) {
	if(str.length() != 8) return false;
	for(int i = 0; i < 4; i++) {
		if(!isupper(str[i])) return false;
	}
	if(!isspace(str[4])) return false;
	for(int i = 5; i < 8; i++) {
		if(!isdigit(str[i])) return false;
	}
	return true;
}

// Loads all the data from the selected department
Course loadCourse(string department, int courseNum) {

	ifstream ifs("data/" + department + ".dat");
		if (!ifs.is_open()) {
			cout << "Unable to open file"<< department << endl;
			exit(2);
		}

	string str;
	string name;
	int numSections;
	ifs >> numSections;
	getline(ifs, str);
	
	Course course;

	for(int i = 0; i < numSections; i++) {
		Section s;
		
		int crn, cNum, sNum;
		
		ifs >> crn >> str >> cNum;
		ifs.ignore(1, ',');
		ifs >> sNum;
		ifs.ignore(1, ',');
		getline(ifs, name);
		//cout << crn << cNum << sNum << name << endl;
		
		//38993,ENGR 101,500,ENERGY RSRCE USE IMPRTCE
		//reads something similar to this...
		
		bool found = (cNum == courseNum);
		if(found) {
			s.setName(name);
			s.setNum(sNum);
			s.setCrn(crn);
		}
		
		int numTypes;
		ifs >> numTypes;
		getline(ifs, str);

		for(int j = 0; j < numTypes; j++) {
			if(!found) {getline(ifs, str); continue;}
			//Lecture,M,1240,1330
			//reads something similar to this...
			
			Type t;
			
			string lecType;
			string days;
			int sTime, eTime;
			
			getline(ifs, lecType, ',');
			getline(ifs, days, ',');
			ifs >> sTime;
			ifs.ignore(1, ',');
			ifs >> eTime;
			getline(ifs, str);
			
			t.setLecType(lecType);
			t.setDays(days);
			t.setStartTime(sTime);
			t.setEndTime(eTime);
			
			s.addType(t);

		}
		
		if(found) course.addSection(s);
	}
	
	course.setDepartment(department);
	course.setNum(courseNum);
	return course;
}


vector<Course> getCourses(string* departments, int* courses, int count) {
	
	vector<Course> courseList;

	for (int i = 0; i < count; i++) {
		Course c = loadCourse(departments[i], courses[i]);
		if(c.getSections().size() != 0)
			courseList.push_back(c);
	}

	return courseList;
}

bool isTypeConflict(Type a, Type b) {
	string aDay = a.getDays();
	string bDay = b.getDays();
	
	bool commonDay = false;
	for(char c : aDay) {
		if(commonDay) break;
		commonDay = bDay.find(c) != string::npos;
	}
	if(commonDay) {
		int aS = a.getStartTime();
		int aE = a.getEndTime();
		int bS = b.getStartTime();
		int bE = b.getEndTime();
		return max(aS, bS) <= min(aE, bE);
	}
	return false;
}

bool isSectionConflict(Section a, Section b) {
	if(a.getCrn() == b.getCrn()) return true;
	for(Type ta : a.getTypes()) {
		for(Type tb : b.getTypes()) {
			if(isTypeConflict(ta, tb)) return true;
		}
	}
	return false;
}

vector<vector<Section>> getScheduleList(vector<Course> courses) {
	vector<vector<Section>> unorderedMap;
	vector<vector<Section>> scheduleList;
	
	for(Course c : courses) {
		unorderedMap.push_back(c.getSections());
	}
	
	int size = unorderedMap.size();
	int* factors = new int[size];
	int factorial = 1;
	
	for(int i = 0; i < size; i++) {
		factors[i] = factorial;
		factorial *= unorderedMap[i].size();
	}
	bool conflict;
	for(int count = 0; count < factorial; count++) {
		int* indexes = new int[size];
		conflict = false;
		for(int i = 0; i < size; i++) {
			if(conflict) break;
			indexes[i] = (count / factors[i]) % unorderedMap[i].size();
			for(int checkConflict = 0; checkConflict < i; checkConflict++) {
				conflict = isSectionConflict(unorderedMap[checkConflict][indexes[checkConflict]], unorderedMap[i][indexes[i]]);
			}
		}
		if(!conflict) {
			vector<Section> schedule;
			for(int i = 0; i < size; i++) {
				schedule.push_back(unorderedMap[i][indexes[i]]);
			}
			scheduleList.push_back(schedule);
		}
		
		delete[] indexes;
	}
	
	delete[] factors;
	return scheduleList;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	
	ifstream data ("data/dialogue.txt");
	string str;
	int numDialogues;
	
	data >> maxLineLen >> sleepNS >> animate >> numDialogues;
	if(argc > 1) animate = (argv[1][0] == '1');
	
	string** text = new string*[numDialogues];
	int* sizes = new int[numDialogues];
	
	for(int i = 0; i < numDialogues; i++) {
		int numStatements;
		data >> numStatements;
		getline(data, str);//goto next line
		sizes[i] = numStatements;
		
		text[i] = new string[numStatements];
		for(int j = 0; j < numStatements; j++) {
			getline(data, str);
			text[i][j] = str;
		}
	}
	
	for(int i = 0; i < 100; i++) cout << endl;
	
	printParagraph(text[1], sizes[1]);
	
	int responses[5];
	for(int i = 0; i < 5; i++) {
		int size = sizes[i + 2];
		printParagraph(text[i + 2], size);
		
		int num = getInt();
		while(num < 1 || num >= size) {
			printStatement(text[0][rand() % sizes[0]]);
			num = getInt();
		}
		responses[i] = num;
	}
	
	printParagraph(text[7], sizes[7]);
	
	int numCourses = getInt();
	while(numCourses < 1 || numCourses > 7) {
		if(numCourses < 1) {
			printStatement(text[8][0]);
		} else {
			printStatement(text[8][6]);
		}
		numCourses = getInt();
	}
	switch(numCourses) {
		case 1: printStatement(text[8][1]); break;
		case 2: printStatement(text[8][2]); break;
		case 3: printStatement(text[8][3]); break;
		case 4:
		case 5: printStatement(text[8][4]); break;
		case 6:
		case 7: printStatement(text[8][5]); break;
	};
	
	printStatement(text[9][0]);
	
	string* departments = new string[numCourses];
	int* courses = new int[numCourses];
	
	for(int i = 0; i < numCourses; i++) {
		string raw = getString();
		while(!isValidCourse(raw)) {
			printStatement(text[9][1]);
			raw = getString();
		}
		
		istringstream is(raw);
		string str;
		int val;
		is >> str;
		is >> val;
		departments[i] = str;
		courses[i] = val;
	}
	
	vector<Course> courseList = getCourses(departments, courses, numCourses);
	
	vector<vector<Section>> scheduleList = getScheduleList(courseList);
	
	if(scheduleList.size() == 0) {
		printStatement(text[10][0]);
	} else {
		printStatement(text[10][1] + " " + to_string(scheduleList.size()) + " " + text[10][2]);
		printStatement(text[10][3]);
		int randSchedule = rand() % scheduleList.size();
		vector<Section> schedule = scheduleList[randSchedule];
		for(int i = 0; i < schedule.size(); i++) {
			Section s = schedule[i];
			Course c = courseList[i];
			
			printStatement("CRN " + to_string(s.getCrn()));
			printStatement(c.getDepartment() + " " + to_string(c.getNum()) + "-" + to_string(s.getNum()) + ":" + s.getName());
			for(Type t : s.getTypes()) {
				printStatement("   Type: " + t.getLecType() + ", Days: " + t.getDays() + ", " + t.getStartTimeString() + " to " + t.getEndTimeString());
			}
		}
	}
	
	return 0;
}