#include <iostream>
#include <limits>

using namespace std;

int main()
{
	cout << "Int: \t\tMínimo " << numeric_limits<int>::min() << 
	" \t Máximo " << numeric_limits<int>::max() << endl;

	cout << "Unsigned int: \tMínimo " << numeric_limits<unsigned int>::min() << 
	" \t\t Máximo " << numeric_limits<unsigned int>::max() << endl; 
	
	cout << "Float: \t\tMínimo " << numeric_limits<float>::min() << 
	" \t Máximo " << numeric_limits<float>::max() << endl;
	
	cout << "Double: \tMínimo " << numeric_limits<double>::min() << 
	" \t Máximo " << numeric_limits<double>::max() << endl << endl;

	return 0;
}