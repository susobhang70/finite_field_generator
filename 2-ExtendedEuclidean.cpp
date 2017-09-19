#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int r, rd, s = 1, sd = 0, t = 0, td = 1, q, rdd, sdd, tdd;
    cout<<"Enter two numbers greater than or equal to 0: ";
    cin>>r>>rd;
    if(rd > r)
        swap(r,rd);
    cout<<r<<" "<<rd<<endl;

    while(rd != 0)
    {
        q = r / rd;
        rdd = r % rd;
        r = rd;
        rd = rdd;
        sdd = s - (sd * q);
        tdd = t - (td * q);
        s = sd;
        t = td;
        sd = sdd;
        td = tdd;
    }

    cout<<"Result: "<<r<<" "<<s<<" "<<t<<endl;
    return 0;
}
