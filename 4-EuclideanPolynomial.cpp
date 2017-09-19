#include <iostream>
#include <cstdlib>

#define MAXDEG 20

int g[MAXDEG], h[MAXDEG];

using namespace std;

int mod(int a, int b)
{
    if(b < 0)
        return mod(-a, -b);
    int answer = a%b;
    if(answer < 0)
        answer += b;
    return answer;
}

int find_inverse(int num, int p)
{
    int tempinv = 1;
    while(tempinv < p)
    {
        if(( mod((tempinv * num), p)) == 1)
            return tempinv;
        else
            tempinv++;
    }
    return 0;
}

int polynomial_division(int G[], int degreeG, int H[], int degreeH, int R[], int p)
{
    int i,j;
    int t = find_inverse(H[degreeH-1], p);

    int Q[MAXDEG];
    for(i = 0; i < degreeG; i++)
    {
        R[i] = G[i];
    }

    for(i = degreeG - degreeH; i >= 0; i--)
    {
        Q[i] = t * R[i + degreeH - 1];
        for(j = 0; j < degreeH; j++)
            R[i + j] = R[i + j] - (Q[i] * H[j]);
    }

    for(i=0; i<=(degreeH - 2); i++)
        R[i] = mod(R[i], p); //R[i] % p;

    return (degreeH - 2 + 1);
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

    cout<<"Enter coefficients of higher degree polynomial starting from lowest order coefficient: ";
    for(i=0; i<degreeG; i++)
        cin>>g[i];
    cout<<"Enter coefficients of other polynomial starting from lowest order coefficient: ";
    for(i=0; i<degreeH; i++)
        cin>>h[i];

    cout<<"The polynomials are:\ng(x) = ";
    display(g, degreeG);

    cout<<"h(x) = ";
    display(h, degreeH);

    int r[MAXDEG], degreeR = 0, old;
    while((h[0] % p) != 0)
    {
        old = h[0] % p;
        degreeR = polynomial_division(g, degreeG, h, degreeH, r, p);
        for(i = 0; i < degreeH; i++)
            g[i] = h[i];
        degreeG = degreeH;
        for(i = 0; i < degreeR; i++)
            h[i] = r[i];
        degreeH = degreeR;
        if(old == (h[0] % p))
        {
            cout<<"The gcd is: 1\n";
            exit(EXIT_SUCCESS);
        }
    }

    int temp = find_inverse(g[degreeG - 1],p);
    for(i = 0; i < degreeG; i++){
        g[i] = g[i] * temp;
        g[i] = mod(g[i], p);
    }

    cout<<"The gcd is: ";
    display(g, degreeG);

    return 0;
}
