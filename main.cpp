#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <regex>
#include <stdlib.h>
#include <time.h>

int maxLineLen;
int sleepNS;
bool animate;

void waitShort() {
	if(animate) {
		std::this_thread::sleep_for(
			std::chrono::nanoseconds(sleepNS));
	}
}

void waitLong() {
	if(animate) {
		std::this_thread::sleep_for(
			std::chrono::nanoseconds(400 * sleepNS));
	}
}

void printString(std::string str) {
	for(int i = 0; i < str.length(); i++) {
		std::cout << str[i] << std::flush;
		waitShort();
	}
}

void printStatement(std::string str) {
	std::vector<std::string> paragraph;
	std::istringstream iss(str);
	for(std::string s; iss >> s; ) {
		paragraph.push_back(s);
	}
	
	int i = 0;
	int lineLen = 0;
	do {
		lineLen += paragraph[i].length() + 1;
		if(lineLen > maxLineLen) {
			lineLen = 0;
			std::cout << std::endl;
		}
		printString(paragraph[i] + " ");
	} while(++i < paragraph.size());
	waitLong();
	std::cout << std::endl;
}

void printParagraph(std::string* strings, int numStrings) {
	for(int i = 0; i < numStrings; i++) {
		printStatement(strings[i]);
	}
	std::cout << std::endl;
}

int getInt() {
	std::cout << ">" << std::flush;
	int num;
	try {
		std::cin >> num;
	} catch(...) {
		return -1;
	}
	std::cin.clear();
	std::cin.ignore(100, '\n');
	return num;
}

std::string getString() {
	std::cout << "#" << std::flush;
	std::string str;
	try {
		getline(std::cin, str);
	} catch(...) {
		return "";
	}
	std::cin.clear();
	for (auto & c: str) c = toupper(c);
	return str;
}

//regex gave me dumb errors. :<
bool isValidCourse(std::string str) {
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

int main() {
	srand(time(NULL));
	
	std::ifstream data ("data.txt");
	std::string str;
	int numDialogues;
	
	data >> maxLineLen >> sleepNS >> animate >> numDialogues;
	
	std::string** text = new std::string*[numDialogues];
	int* sizes = new int[numDialogues];
	
	for(int i = 0; i < numDialogues; i++) {
		int numStatements;
		data >> numStatements;
		getline(data, str);//goto next line
		sizes[i] = numStatements;
		
		text[i] = new std::string[numStatements];
		std::cout << &text[i] << std::endl;
		for(int j = 0; j < numStatements; j++) {
			getline(data, str);
			text[i][j] = str;
			std::cout << text[i][j] << std::endl;
		}
	}
	
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
	
	std::string* departments = new std::string[numCourses];
	int* courses = new int[numCourses];
	
	for(int i = 0; i < numCourses; i++) {
		std::string raw = getString();
		while(!isValidCourse(raw)) {
			printStatement(text[9][1]);
			raw = getString();
		}
		
		std::istringstream is(raw);
		std::string str;
		int val;
		is >> str;
		is >> val;
		departments[i] = str;
		courses[i] = val;
	}
	
	for(int i = 0; i < numCourses; i++) {
		std::cout << departments[i] << " " << courses[i] << std::endl;
	}
	
	return 0;
}