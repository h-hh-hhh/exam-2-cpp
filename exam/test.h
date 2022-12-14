#pragma once
#include <vector>
#include <map>
#include <string>

class Question {
public:
	Question(
		std::string question, 
		std::string variant1, 
		std::string variant2, 
		std::string variant3, 
		std::string variant4, 
		int correct, 
		double weight
	);

	double check(int variant);
	friend std::ostream& operator<<(std::ostream& out, Question q);
protected:
	struct Answer { 
		std::string s;
		bool c;
	};
	std::string question;
	std::map<int, Answer> answers;
	double weight;
};

std::ostream& operator<<(std::ostream& out, Question q);

class Test {
public:
	Test() {}
	double take();
	int size();
	bool operator<(const Test& other) const {
		return this->id < other.id;
	}
	int id;
protected:
	std::vector<Question> questions;
};