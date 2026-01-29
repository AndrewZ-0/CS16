#include <iostream>
using namespace std;

int main() {
	int a, b, c, result;

	cout << "Please enter 3 numbers." << endl;
	cin >> a >> b >> c;
	
	result = 2 * (a - 4 * b) + 3 * c;

	cout << "The result of the formula is: " << result << endl;

	return 0;
}
