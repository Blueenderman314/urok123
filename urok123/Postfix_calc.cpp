#include "Postfix_calc.h"

int get_priority(string oper)
{
	if (oper == "+" || oper == "-")
	{
		return 0;
	}
	if (oper == "*" || oper == "/")
	{
		return 1;
	}
	return 2;
}

char isConst(string oper, size_t index = 0) //pi, e
{
	if (oper[index] == 'p' && oper[index + 1] == 'i') //pi
		return 2;
	else if (oper[index] == 'e') //e
		return 1;
	return 0;
}

bool isNumber(string str)
{
	if (str[0] >= '0' && str[0] <= '9')
		return true;
	if (str[0] == '-' && str[1] >= '0' && str[1] <= '9')
		return true;
	if (isConst(str))
		return true;
	return false;
}

bool isOperator(string oper, size_t index = 0, size_t ctrl = 0) // + - * / ^
{
	if (ctrl == 0 && oper[1] >= '0' && oper[1] <= '9')
		return false;
	if (oper[index] == '+' || oper[index] == '-' || oper[index] == '*' || oper[index] == '/' || oper[index] == '^')
		return true;
	return false;
}

char isFunc(string oper, size_t index = 0) //cos, sin, tg, ctg, ln, log, sqrt, abs
{
	if (oper[index] == 't' && oper[index + 1] == 'g') //tg
		return 2;
	else if (oper[index] == 'l' && oper[index + 1] == 'n') //ln
		return 2;
	else if (oper[index] == 'c' && oper[index + 1] == 'o' && oper[index + 2] == 's') //cos
		return 3;
	else if (oper[index] == 'c' && oper[index + 1] == 't' && oper[index + 2] == 'g') //ctg
		return 3;
	else if (oper[index] == 'l' && oper[index + 1] == 'o' && oper[index + 2] == 'g') //log
		return 3;
	else if (oper[index] == 's' && oper[index + 1] == 'i' && oper[index + 2] == 'n') //sin
		return 3;
	else if (oper[index] == 'a' && oper[index + 1] == 'b' && oper[index + 2] == 's') //abs
		return 3;
	else if (oper[index] == 's' && oper[index + 1] == 'q' && oper[index + 2] == 'r' && oper[index + 3] == 't') //sqrt
		return 4;
	return 0;
}


void Postfix_calc::parser()//делит выражение на составные элементы
{
	string temp;
	Datatype temp_e;

	for (size_t i = 0; i < input.size(); i++)
	{
		temp.clear();
		size_t control = 0;
		while (((input[i] >= 48 && input[i] <= 57) || (input[i] == '.')) && i < input.size()) //выделение чисел
			temp.push_back(input[i++]);
		//написать функцию которы€ провер€ет €вл€етс€ числом или нет, тут вставить проверку, если €вл€етс€ то создать элем где дата = темп, и дататайп = намбер
		if (isNumber(temp))
		{
			temp_e = number;
			this->parsed_data.push_back(Elem(temp, temp_e));
			continue;
		}
		if (isOperator(input, i, 1))
		{
			temp.push_back(input[i]);
			temp_e = operation;
			this->parsed_data.push_back(Elem(temp, temp_e));
			continue;
		}
		if (input[i] == '(')
		{
			temp.push_back(')');
			temp_e = left_bracket;
			this->parsed_data.push_back(Elem(temp, temp_e));
			continue;
		}
		if (input[i] == ')')
		{
			temp.push_back('(');
			temp_e = right_bracket;
			this->parsed_data.push_back(Elem(temp, temp_e));
			continue;
		}
		if (input[i] == ' ')
		{
			if (temp != "")
			{

			}
			continue;
		}
		try
		{
			size_t temp_2 = isFunc(input, i); //выделение функций одного аргумента
			if (temp_2)
			{
				for (size_t j = i; j < i + temp_2; j++) //вставка самой функции
					temp.push_back(input[j]);
				temp_2--;
				size_t control = 0;
				do
				{
					temp_2++;
					if (input[i + temp_2] == '(')
						control++;
					if (input[i + temp_2] == ')')
						control--;
					temp.push_back(input[i + temp_2]);
				} while (control != 0 && input.size() > i + temp_2); //вставка аргумента функции
				if (control != 0)
					throw "Incorrect input: error 4";
				temp_e = function;
				i += temp_2;
				this->parsed_data.push_back(Elem(temp, temp_e));
				continue;
			}
		}
		catch (const char* error)
		{
			cout << error << endl;
			cout << "error symbols: ";
			for (size_t j = i; j < input.size(); j++)
				cout << input[j];
			cout << endl;
			return;
		}
		try
		{
			size_t temp_2 = isConst(input, i); //выделение констант - пи и экспоненты
			if (temp_2)
			{
				for (size_t j = i; j < i + temp_2; j++)
					temp.push_back(input[j]);
				temp_e = constant;
				i += temp_2 - 1;
				this->parsed_data.push_back(Elem(temp, temp_e));
				continue;
			}
		}
		catch (const char* error)
		{
			cout << error << endl;
			cout << "error symbols: ";
			for (size_t j = i; j < input.size(); j++)
				cout << input[j];
			cout << endl;
			return;
		}
		throw "Unknown symbols";
	}
}

void Postfix_calc::get_postfix()
{
	list<Elem>::iterator it = parsed_data.begin();

	for (it; it != parsed_data.end(); it++)
	{
		if ((*it).datatype = number)
		{
			queue.push(*it);
		}
		if ((*it).datatype = operation)
		{
			if (stack.empty() || stack.top().datatype == left_bracket)
			{
				stack.push(*it);
			}
			if (stack.top().datatype == operation)
			{
				if (get_priority(stack.top().data) < get_priority((*it).data))
				{
					stack.push(*it);
				}
				else
				{
					while (get_priority(stack.top().data) > get_priority((*it).data) || ((*it).datatype != left_bracket))
					{
						queue.push(stack.top());
						stack.pop();
					}
					stack.push(*it);
				}
			}
			if ((*it).datatype == left_bracket)
			{
				stack.push(*it);
			}
			if ((*it).datatype == right_bracket)
			{
				while ((*it).datatype != left_bracket)
				{
					queue.push(stack.top());
					stack.pop();
				}
				stack.pop();
			}	
		}
	}
	while (!stack.empty())
	{
		queue.push(stack.top());
		stack.pop();
	}
}

void Postfix_calc::calc()
{

}

void Postfix_calc::start(string _input)
{
	this->input = _input;
	parser();
	get_postfix();
}

double Postfix_calc::get_result()
{
	return 0.0;
}

void Postfix_calc::clear()
{

}
