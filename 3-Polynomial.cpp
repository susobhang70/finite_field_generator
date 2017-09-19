#include <iostream>
#include <cstdlib>

#define MAXDEG 20
using namespace std;

int r[MAXDEG], q[MAXDEG], g[MAXDEG], h[MAXDEG];

int mod(int a, int b)
{
    if(b < 0)
        return mod(-a, -b);
    int answer = a%b;
    if(answer < 0)
        answer += b;
    return answer;
}

int findinverse(int num, int p)
{
    int tempinv = 1;
    while(tempinv < p)
    {
        if(mod((tempinv * num), p) == 1)
            return tempinv;
        else
            tempinv++;
    }
    return 0;
}

void display(int a[], int n)
{
    int i = 0;
    cout<<a[i];
    for(i = 1; i<n-1; i++)
        if(a[i]!=0)
            cout<<" + "<<a[i]<<"x^"<<i;
    if(i < n && a[i] != 0)
        cout<<" + "<<a[i]<<"x^"<<i<<endl;
    cout<<endl;
}


int main()
{
    int degreeG, degreeH, p, i, j;

    cout<<"Enter prime p for Zp: ";
    cin>>p;
    cout<<"Degree of polynomial with bigger degree: ";
    cin>>degreeG;
    cout<<"Degree of other polynomial: ";
    cin>>degreeH;

    degreeG++;
    degreeH++;

    cout<<"Enter coefficients of higher degree polynomial starting from lowest order x's coefficient: ";
    for(i = 0; i < degreeG; i++)
        cin>>g[i];
    cout<<"Enter coefficients of other polynomial starting from lowest order coefficient: ";
    for(i = 0; i < degreeH; i++)
        cin>>h[i];

    cout<<"The polynomials are:\ng(x) = ";
    display(g, degreeG);

    cout<<"h(x) = ";
    display(h, degreeH);

    int t = findinverse(h[degreeH - 1], p);
    // cout<<"The inverse of "<<h[degreeH - 1]<<" in Z sub "<<p<<" is "<<t<<endl;


    for(i = 0; i < degreeG; i++)
        r[i] = g[i];

    for(i = degreeG - degreeH; i >= 0; i--)
    {
        q[i] = t * r[i + degreeH - 1];
        for(j=0; j<degreeH; j++)
            r[i+j] = r[i+j] - (q[i] * h[j]);
    }

    cout<<"The polynomials q, r such that g = hq + r are:\n";

    for(i = 0; i <= (degreeG - degreeH); i++)
        q[i] = mod(q[i], p);

    for(i = 0; i <= (degreeH - 2); i++)
        r[i] = mod(r[i], p);

    cout<<"q(x) = ";
    display(q, degreeG - degreeH + 1);
    cout<<"r(x) = ";
    display(r, degreeH - 1);

    return 0;
}
