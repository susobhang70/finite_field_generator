#include <iostream>
#include <cstdlib>

#define MAXDEG 20
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

int polynomial_division(int g[], int degk, int h[], int degl, int arrq[], int &degquo, int arrr[], int &degrem, int p)
{
    int i,j;

    int t = findinverse(h[degl-1],p);

    for(i=0; i<degk; i++)
        arrr[i] = g[i];
    
    for(i=degk - degl; i>=0; i--){
        arrq[i] = t*arrr[i+degl-1];
        for(j=0; j<degl; j++)
            arrr[i+j] = arrr[i+j] - (arrq[i] * h[j]);
    }

    for(i=0; i<=(degk - degl); i++)
        arrq[i] = mod(arrq[i], p);

    for(i=0; i<=(degl - 2); i++)
        arrr[i] = mod(arrr[i], p); //arrr[i] % p;

    degquo = degk - degl + 1;
    degrem = (degl - 2 + 1);
}

void multiply(int A[], int B[], int m, int n,int prod[], int p)
{
   //int *prod = new int[m+n-1];

   // Initialize the porduct polynomial
   for (int i = 0; i<m+n-1; i++)
     prod[i] = 0;

   // Multiply two polynomials term by term

   // Take ever term of first polynomial
    for (int i=0; i<m; i++)
    {
     // Multiply the current term of first polynomial
     // with every term of second polynomial.
        for (int j=0; j<n; j++)
            prod[i+j] += A[i]*B[j];
    }

    for (int i = 0; i<m+n-1; i++)
        prod[i] = mod(prod[i], p);

    return;
}

void display(int a[], int n)
{
    int i = 0;
    cout<<a[i];
    for(i = 1; i<n-1; i++)
        if(a[i]!=0)
            cout<<" + "<<a[i]<<"x^"<<i;
    if((i < n) && (a[i] != 0))
        cout<<" + "<<a[i]<<"x^"<<i<<endl;
    cout<<endl;
}

int main()
{
    int degquo = 0,degrem = 0, degreeG, degreeH, p, i, j, degsdd = 1, degsd = 1, degtdd = 1, degtd = 1, degs=0, degt=0, degprod1=0, degprod2=0;
    cout<<"Enter value of p in Z sub p where p is prime: ";
    cin>>p;
    cout<<"Degree of polynomial with bigger degree: ";
    cin>>degreeG;
    cout<<"Degree of other polynomial: ";
    cin>>degreeH;
    degreeG++;
    degreeH++;

    int quo[MAXDEG], rem[MAXDEG], g[MAXDEG], h[MAXDEG], sdd[MAXDEG], sd[MAXDEG], tdd[MAXDEG], td[MAXDEG], s[MAXDEG], t[MAXDEG], prod1[MAXDEG], prod2[MAXDEG];
    cout<<"Enter coefficients of higher degree polynomial starting from lowest order coefficient: ";
    for(i = 0; i < degreeG; i++)
        cin>>g[i];
    cout<<"Enter coefficients of other polynomial starting from lowest order coefficient: ";
    for(i = 0; i < degreeH; i++)
        cin>>h[i];

    cout<<"The polynomials are:\ng(x) = ";
    display(g, degreeG);

    cout<<"h(x) = ";
    display(h, degreeH);

    for(i = 0; i < MAXDEG; i++)
    {
        sdd[i] = 0;
        tdd[i] = 0;
    }

    for(i = 0; i < degsdd; i++)
    {
        sdd[0] = 1;
        sd[0] = 0;
        tdd[0] = 0;
        td[0] = 1;
    }

    int old;

    while((h[0] % p) != 0)
    {
        old = h[0] % p;
        polynomial_division(g, degreeG, h, degreeH, quo, degquo, rem, degrem, p);

        for(i = 0 ; i < degreeH; i++)
            g[i] = h[i];

        degreeG = degreeH;

        for(i = 0; i < degrem; i++)
            h[i] = rem[i];

        degreeH = degrem;

        if(old == (h[0] % p))
        {
            cout<<"This algorithm doesn't work for gcd = 1\n";
            exit(EXIT_SUCCESS);
        }

        multiply(quo, sd, degquo, degsd, prod1, p);
        degprod1 = degquo + degsd - 1;
        multiply(quo, td, degquo, degtd, prod2, p);
        degprod2 = degquo + degtd - 1;

        for(i = 0; i < max(degsdd, degprod1); i++)
            s[i] = sdd[i] - prod1[i];

        degs = max(degsdd, degprod1);

        for(i = 0; i < max(degtdd, degprod2); i++)
            t[i] = tdd[i] - prod2[i];

        degt = max(degtdd, degprod2);

        for(i = 0; i < MAXDEG; i++)
        {
            sdd[i] = 0;
            tdd[i] = 0;
            prod1[i] = 0;
            prod2[i] = 0;
        }

        for(i = 0; i < degsd; i++)
            sdd[i] = sd[i];
        degsdd = degsd;

        for(i = 0; i < degtd; i++)
            tdd[i] = td[i];
        degtdd = degtd;

        for(i = 0; i < degs; i++)
            sd[i] = s[i];
        degsd = degs;

        for(i = 0; i < degt; i++)
            td[i] = t[i];
        degtd = degt;

    }

    int temp = findinverse(g[degreeG-1], p);

    for(i = 0; i < degreeG; i++)
    {
        g[i] = g[i] * temp;
        g[i] = mod(g[i], p);
    }

    for(i = 0; i < degsdd; i++)
    {
        sdd[i] = sdd[i] * temp;
        sdd[i] = mod(sdd[i], p);
    }

    for(i = 0; i < degtdd; i++)
    {
        tdd[i] = tdd[i] * temp;
        tdd[i] = mod(tdd[i], p);
    }

    cout<<"d = gs + ht and d, s and t are:\n"<<endl;
    cout<<"d(x) = ";
    display(g, degreeG);

    cout<<"s(x) = ";
    display(sdd, degsdd);

    cout<<"t(x) = ";
    display(tdd, degtdd);

    return 0;
}
