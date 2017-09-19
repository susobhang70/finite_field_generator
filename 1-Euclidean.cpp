#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int a, b, c;
    cout<<"Enter two numbers greater than 0: ";
    cin>>a>>b;
    if(b > a)
        swap(a, b);
    while(b != 0)
    {
        c = a%b;
        a = b;
        b = c;
    }
    cout<<"The GCD is "<<a<<endl;
    return 0;
}
