#pragma once
#include <stack>
#include <queue>
#include <list>
#include <iostream>
#include <string>
#include "Elem.h"
using namespace std;

class Postfix_calc
{
private: 
	string input;
	list<Elem> parsed_data;
	stack<Elem> stack;
	queue<Elem> queue;
	void parser();
	void get_postfix();
	void calc();
public:
	void start(string _input);
	double get_result();
	void clear();
};