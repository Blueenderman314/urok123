#pragma once
#include <iostream>
#include <string>
using namespace std;

enum Datatype{left_bracket, right_bracket, number, operation, function, constant};

struct Elem
{
	string data;
	Datatype datatype;
	Elem(string _data, Datatype _datatype)
	{
		data = _data; datatype = _datatype;
	}
};