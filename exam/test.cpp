#include "test.h"
#include <string>
#include <iostream>

Question::Question(
	std::string question,
	std::string variant1,
	std::string variant2,
	std::string variant3,
	std::string variant4,
	int correct,
	double weight
) : 
	question(question),
	weight(weight)
{
	Answer answer1, answer2, answer3, answer4;
	answer1.s = variant1;
	answer2.s = variant2;
	answer3.s = variant3;
	answer4.s = variant4;
	switch(correct) {
	case 1:
		answer1.c = true;
		answer2.c = false;
		answer3.c = false;
		answer4.c = false;
		break;
	case 2:
		answer1.c = false;
		answer2.c = true;
		answer3.c = false;
		answer4.c = false;
		break;
	case 3:
		answer1.c = false;
		answer2.c = false;
		answer3.c = true;
		answer4.c = false;
		break;
	case 4:
		answer1.c = false;
		answer2.c = false;
		answer3.c = false;
		answer4.c = true;
		break;
	default:
		answer1.c = false;
		answer2.c = false;
		answer3.c = false;
		answer4.c = false;
		break;
	}
	answers[1] = answer1;
	answers[2] = answer2;
	answers[3] = answer3;
	answers[4] = answer4;
}

double Question::check(int variant) {
	return answers[variant].c * weight;
}

std::ostream& operator<<(std::ostream& out, Question q) {
	out << q.question
		<< "\n1. "
		<< q.answers[1].s
		<< "\n2. "
		<< q.answers[2].s
		<< "\n3. "
		<< q.answers[3].s
		<< "\n4. "
		<< q.answers[4].s;
	return out;
}

double Test::take() {
	double result = 0;
	int c;
	for (auto i = questions.begin(); i != questions.end(); i++) {
		std::cout << *i << std::endl;
		std::cin >> c;
		result += i->check(c);
	}
	return result;
}

int Test::size() {
	return questions.size();
}