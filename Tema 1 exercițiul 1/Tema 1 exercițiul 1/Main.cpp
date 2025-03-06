#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

bool Verification(const std::string& message) {
	if (message.size() % 7 != 0)
		return 0;

	for (const char& character : message)
	{
		if (character != '0' && character != '1')
			return 0;
	}
	return 1;
}

std::string WrongExpression(const std::string& message, const int& position) {
	std::string wrongMessage = message;
	if (message[position] == '0')
		wrongMessage[position] = '1';
	else wrongMessage[position] = '0';
	return wrongMessage;
}

std::vector<std::vector<char>> ToMatrix(const std::string& message) {
	int size = message.size() / 7, i, j, index = 0, onesOnLine, onesOnColumn, lastLine = 0, lastColumn = 0, k = 0;
	std::vector<std::vector<char>> matrix(size + 1, std::vector<char>(8));
	std::string copy = message;

	for (i = 0; i < size;i++) {
		for (j = 0; j < 7;j++) {
			matrix[i][j] = copy[index];
			index++;
		}
	}

	for (i = 0;i < size;i++) {
		onesOnLine = 0;
		for (j = 0;j < 7;j++) {
			if (matrix[i][j] == '1')
				onesOnLine++;
		}
	    matrix[i][7] = (onesOnLine % 2) ? '1' : '0';
	}

	for (j = 0;j < 7;j++) {
		onesOnColumn = 0;
		for (i = 0;i < size;i++) {
			if (matrix[i][j] == '1')
				onesOnColumn++;
		}
		matrix[size][j] = (onesOnColumn % 2) ? '1' : '0';
	}
	
	for (i = 0; i < size; i++) {
		if (matrix[i][6] == '1')
			lastLine++;
	}

	for (j = 0; j < 7; j++) {
		if (matrix[size - 1][j] == '1')
			lastColumn++;
	}

	matrix[size][7] = ((lastColumn % 2) || (lastLine % 2)) ? '1' : '0';

	return matrix;
}

void ShowMatrix(const std::vector<std::vector<char>>& matrix) {
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < 7; j++)
		{
			std::cout << matrix[i][j] << " ";

			if (j == 5)
				std::cout << "| ";
		}

		std::cout << '\n';

		if (i == matrix.size() - 2)
			std::cout << std::string(7 * 2 + 2, '-') << '\n';
	}
}

std::pair<int, int> IdentifyWrongPosition(const std::vector<std::vector<char>>& rightMatrix, const std::vector<std::vector<char>>& wrongMatrix) {
	int i, j;

	for (i = 0;i < rightMatrix.size();i++)
	{
		for (j = 0;j < rightMatrix[i].size();j++) {
			if (rightMatrix[i][j] != wrongMatrix[i][j]) {
				return {i, j};
			}
		}
	}
	
	return { -1, -1 };
}

std::string FinalExpression(const std::vector<std::vector<char>>& rightMatrix) {
	int i, j;
	std::string finalMessage = "";

	for (i = 0; i < rightMatrix.size();i++) {
		for (j = 0;j < rightMatrix[i].size();j++) {
			finalMessage += rightMatrix[i][j];
		}
	}

	return finalMessage;
}

int main()
{
	std::string message, wrongMessage;
	int position, i;
	std::vector<std::vector<char>> rightMatrix, wrongMatrix;
	std::pair<int, int> corruptedPosition;

	std::cout << "Please enter the correct message: ";
	std::cin >> message;
	if (!Verification(message) || message.empty())
    {
		while (!Verification(message) || message.empty())
		{
			std::cout << "\nPlease enter a valid message." << '\n';
			std::cin >> message;
		}
	}
	std::cout << "\nThe message is valid." << '\n';
	std::cout << "\nThe resulted matrix:" << '\n';
	rightMatrix = ToMatrix(message);
	ShowMatrix(rightMatrix);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, static_cast<int>(message.size()) - 1);
	position = distrib(gen);

	std::cout << "The generated position is: " << position << '\n';

	wrongMessage = WrongExpression(message, position);
	std::cout << "\nThis is the wrong expression: " << wrongMessage << '.' << '\n';
	std::cout << "\nThe matrix for the wrong expression:\n";
	wrongMatrix = ToMatrix(wrongMessage);
	ShowMatrix(wrongMatrix);

	corruptedPosition = IdentifyWrongPosition(rightMatrix, wrongMatrix);
	if (corruptedPosition.first != -1 && corruptedPosition.second != -1) {
		std::cout << "\nThe corrupted position is the bit " << wrongMatrix[corruptedPosition.first][corruptedPosition.second] <<" at the position ["  << corruptedPosition.first << ", " << corruptedPosition.second << "].\n";;
	}
	std::cout << "The final message is: " << FinalExpression(rightMatrix) << '.';
	return 0;
}