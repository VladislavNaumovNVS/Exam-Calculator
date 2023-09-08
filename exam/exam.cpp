#include <iostream>
#include <stack>
#include <sstream>
#include <string>
using namespace std;
bool isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}
bool isOpeningBracket(char c) {
	return (c == '(');
}
bool isClosingBracket(char c) {
	return (c == ')');
}
int getPriority(char op) {
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	return 0;
}
double executeOperation(double operand1, double operand2, char op) {
	switch (op) {
	case '+': return operand1 + operand2;
	case '-': return operand1 - operand2;
	case '*': return operand1 * operand2;
	case '/': return operand1 / operand2;
	default: return 0;
	}
}
double evaluateExpression(string expression) {
	stack<char> operators;
	stack<double> operands;
	for (int i = 0; i < expression.length(); i++) {
		char c = expression[i];
		// Пропускаем пробелы
		if (c == ' ') continue;
		// Если текущий символ - открывающаяся скобка, помещаем ее в стек символов
		if (isOpeningBracket(c)) {
			operators.push(c);
		}

		// Если текущий символ - цифра, считываем всё число и помещаем его в стек значений
		else if (isdigit(c)) {
			stringstream ss;
			ss << c;

			// Если число состоит более чем из одной цифры, считываем остальные цифры
			while (i + 1 < expression.length() && isdigit(expression[i + 1])) {
				ss << expression[i + 1];
				i++;
			}

			double number;
			ss >> number;

			operands.push(number);
		}

		// Если текущий символ - оператор
		else if (isOperator(c)) {
			// Пока на вершине стека символов находится оператор с более высоким или равным приоритетом
			// или на вершине стека находится открывающаяся скобка, выполняем операцию и добавляем результат в стек значений
			while (!operators.empty() && operators.top() != '(' && getPriority(operators.top()) >= getPriority(c)) {
				double operand2 = operands.top();
				operands.pop();

				double operand1 = operands.top();
				operands.pop();

				char op = operators.top();
				operators.pop();

				double result = executeOperation(operand1, operand2, op);

				operands.push(result);
			}

			// Помещаем текущий символ в стек символов
			operators.push(c);
		}

		// Если текущий символ - закрывающаяся скобка
		else if (isClosingBracket(c)) {
			// Выполняем операции, пока на вершине стека символов не окажется открывающаяся скобка
			while (!operators.empty() && operators.top() != '(') {
				double operand2 = operands.top();
				operands.pop();

				double operand1 = operands.top();
				operands.pop();

				char op = operators.top();
				operators.pop();

				double result = executeOperation(operand1, operand2, op);

				operands.push(result);
			}

			// Удаляем открывающуюся скобку из стека символов
			if (!operators.empty() && operators.top() == '(') {
				operators.pop();
			}
		}
	}
	// Выполняем оставшиеся операции
	while (!operators.empty()) {
		double operand2 = operands.top();
		operands.pop();

		double operand1 = operands.top();
		operands.pop();

		char op = operators.top();
		operators.pop();



		double result = executeOperation(operand1, operand2, op);
	}