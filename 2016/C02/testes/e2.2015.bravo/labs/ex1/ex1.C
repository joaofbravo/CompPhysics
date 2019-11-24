#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int a=0, b=0, c=0, x=0;

    if(argc!=3)
    {
        cout<<"Insert 2 numbers: '<a> <b>'"<<endl;
        return -1;
    }

    a= atoi(argv[1]);  
    b= atoi(argv[2]);

    if(b < a){
        c=a;
        a=b;
        b=c;
    }

    while(a<=b){
        x +=a;
        a++;
    }

    cout << "The result is: " << x << endl;

    return 0;
}