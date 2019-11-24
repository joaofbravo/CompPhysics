#include <iostream>

using namespace std;

int main() {
    int n, m; 

    cout << "Enter integers: " << flush;
    cin >> n >> m ;

    if (n>m){ 
        int buf = m;
        m = n;
        n = buf;
    }

    cout << "This program adds the square of all integers between " << n << " and " << m << endl;

    int sumi = 0;
    double sumd = 0.;

    for (int i=n; i<=m; i++) 
    {
        sumi += i*i;
        sumd += (double)i * (double)i;
    }

    cout << "Result (with integers) = " << sumi << endl;
    cout << "Result (with doubles) = " << sumd << endl;
}
