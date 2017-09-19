#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>

#define p 5
#define MAXDEG 20
using namespace std;

int d3[4], d5[6];
int field5[3126][5], field3[126][3];
int check5[3126], check3[126];

int mod(int a, int b)
{
    if(b < 0)
        return mod(-a, -b);
    int answer = a%b;
    if(answer < 0)
        answer += b;
    return answer;
}

int findinverse(int num, int modulus)
{
    int tempinv = 1;
    while(tempinv < modulus)
    {
        if(mod((tempinv * num), modulus) == 1)
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
    if((i < n) && (a[i] != 0))
        cout<<" + "<<a[i]<<"x^"<<i;
    cout<<endl;
}

int poly_div(int g[], int degreeG, int h[], int degreeH)
{
	degreeG++;
	degreeH++;
	int i, j, t = findinverse(h[degreeH - 1], p);
	int r[20], q[20];
    for(i=0; i < degreeG; i++)
        r[i] = g[i];

    for(i = degreeG - degreeH; i >= 0; i--)
    {
        q[i] = t * r[i + degreeH - 1];
        for(j=0; j<degreeH; j++)
            r[i+j] = r[i+j] - (q[i] * h[j]);
    }

    for(i=0; i<=(degreeG - degreeH); i++)
        q[i] = mod(q[i], p);

    for(i=0; i<=(degreeH - 2); i++)
	{    
		r[i] = mod(r[i], p);
		if(r[i] != 0)
		    return 1;
	}
    return 0;
}

int *return_poly_div(int g[], int degreeG, int h[], int degreeH)
{
	degreeG++;
	degreeH++;
	int i, j, t = findinverse(h[degreeH - 1], p);
	int *r = new int[degreeG];
	int q[20];

    for(i=0; i < degreeG; i++)
        r[i] = g[i];

    for(i = degreeG - degreeH; i >= 0; i--)
    {
        q[i] = t * r[i + degreeH - 1];
        for(j=0; j<degreeH; j++)
            r[i+j] = r[i+j] - (q[i] * h[j]);
    }

    for(i=0; i<=(degreeG - degreeH); i++)
        q[i] = mod(q[i], p);

    for(i=0; i<=(degreeH - 2); i++)
	{    
		r[i] = mod(r[i], p);
	}
    return r;
}

void irr_poly_3(int it[], int degree, int it1[], int d2[][3], int j)
{
	int i;
	for(it[degree] = 1; it[degree] < p; it[degree]++)
	{
		for(it[degree - 1] = 0; it[degree - 1] < p; it[degree - 1]++)
		{
			for(it[degree - 2] = 1; it[degree - 2] < p; it[degree - 2]++)
			{
				for(it[degree - 3] = 0; it[degree - 3] < p; it[degree - 3]++)
				{
					int flag = 0;
					for(it1[1] = 1; it1[1] < p; it1[1]++)
					{	
						for(it1[0] = 0; it1[0] < p; it1[0]++)
						{				
							if(poly_div(it, degree, it1, 1) == 0)
							{
								flag = 1;
								break;
							}
						}
						if(flag == 1)
							break;
					}
					if(flag == 1)
						continue;
					for(i = 0; i < j; i++)
					{
						if(poly_div(it, degree, d2[i], 2) == 0)
							break;
					}
					if(i == j)
					{
						for(i = 0; i <= degree; i++)
							d3[i] = it[i];
						display(it, degree + 1);
						return;
					}
				}
			}
		}
	}
}

void irr_poly_5(int it[], int degree, int it1[], int d2[][3], int j)
{
	int i;
	for(it[degree] = 1; it[degree] < p; it[degree]++)
	{
		for(it[degree - 1] = 0; it[degree - 1] < p; it[degree - 1]++)
		{
			for(it[degree - 2] = 0; it[degree - 2] < p; it[degree - 2]++)
			{
				for(it[degree - 3] = 0; it[degree - 3] < p; it[degree - 3]++)
				{
					for(it[degree - 4] = 0; it[degree - 4] < p; it[degree - 4]++)
					{
						for(it[degree - 5] = 1; it[degree - 5] < p; ++it[degree - 5])
						{
							int flag = 0;
							for(it1[1] = 1; it1[1] < p; it1[1]++)
							{	
								for(it1[0] = 0; it1[0] < p; it1[0]++)
								{				
									if(poly_div(it, degree, it1, 1) == 0)
									{
										flag = 1;
										break;
									}
								}
								if(flag == 1)
									break;
							}
							if(flag == 1)
								continue;

							for(i = 0; i < j; i++)
							{
								if(poly_div(it, degree, d2[i], 2) == 0)
								{	
									break;
								}
							}
							if(i == j)
							{
								for(i = 0; i <= degree; i++)
									d5[i] = it[i];
								display(it, degree + 1);
								return;
							}
						}
					}
				}
			}
		}
	}
}

void generate_field_3()
{
	int i, j, k, l=0;
	for(i = 0; i < p; i++)
	{
		for(j = 0; j < p; j++)
		{
			for(k = 0; k < p; k++)
			{
				field3[l][2] = i;
				field3[l][1] = j;
				field3[l][0] = k;
				l++;
			}
		}
	}
}

void generate_field_5()
{
	int i, j, k, l=0, m, n;
	for(i = 0; i < p; i++)
	{
		for(j = 0; j < p; j++)
		{
			for(k = 0; k < p; k++)
			{
				for(m = 0; m < p; m++)
				{
					for(n = 0; n < p; n++)
					{
						field5[l][4] = i;
						field5[l][3] = j;
						field5[l][2] = k;
						field5[l][1] = m;
						field5[l][0] = n;
						l++;
					}
				}
				
			}
		}
	}
}

int *multiply(int A[], int B[], int m, int n)
{
	m++;
	n++;
   	int *prod = new int[m+n-1];
 
   	for (int i = 0; i < m + n - 1; i++)
    	prod[i] = 0;

   	for (int i = 0; i < m; i++)
   	{
   	    for (int j = 0; j < n; j++)
        	prod[i+j] += mod((A[i] * B[j]), p);
   	}

   	for (int i = 0; i < m + n - 1; i++)
   		prod[i] = mod(prod[i], p);
 
   	return prod;
}

int find_generator()
{
	int i, j;
	for(i = 5; i < 125; i++)
	{
		int *temp, *temp2, degree;
		for(j = 2; j >= 0; j--)
			if(field3[i][j] != 0)
				break;

		degree = j;
		if(degree == 0)
			continue;

		temp = multiply(field3[i], field3[i], degree, degree);
		temp2 = temp;
		if(2*degree >= 3)
		{				
			temp2 = return_poly_div(temp, degree + degree, d3, 3);
			
			free(temp);
			temp = temp2;
		}

		for(j = 0; j < 125; j++)
			check3[j] = 0;
		int degree2;
		check3[temp[2] * 25 + temp[1] * 5 + temp[0]]++;

		for(j = 2; j < 124; j++)
		{
			for(degree2 = 3; degree2 >= 0; degree2--)
				if(temp[degree2] != 0)
					break;
			temp2 = multiply(field3[i], temp, degree, degree2);
			free(temp);
			temp = temp2;
			if(degree + degree2 >= 3)
			{
				temp2 = return_poly_div(temp, degree + degree2, d3, 3);
				free(temp);
				temp = temp2;
				degree2 = 3;
			}

			if(check3[temp[2] * 25 + temp[1] * 5 + temp[0]] == 1)
				break;
			check3[temp[2] * 25 + temp[1] * 5 + temp[0]]++;
		}
		if(j == 124)
			return i;
	}
	return 0;
}

int main()
{
	int pr = 125, i, j = 0, k, l, m, it[10], it1[2];

	int d2[100][3], degree = 2;

	for(it[degree] = 1; it[degree] < p; it[degree]++)
	{
		for(it[degree - 1] = 0; it[degree - 1] < p; it[degree - 1]++)
		{
			for(it[degree - 2] = 0; it[degree - 2] < p; it[degree - 2]++)
			{
				int flag = 0;
				for(it1[1] = 1; it1[1] < p; it1[1]++)
				{	
					for(it1[0] = 0; it1[0] < p; it1[0]++)
					{				
						if(poly_div(it, degree, it1, 1) == 0)
						{
							flag = 1;
							break;
						}
					}
				}
				if(flag == 0)
				{
					for(i = 0; i <= degree; i++)
					{
						d2[j][i] = it[i];
					}
					j++;
				}
			}
		}
	}

	// for(i = 0; i < j; i++)
	// 	display(d2[i], degree + 1);

	generate_field_5();
	generate_field_3();

	char choice;
	cout<<"p is 5.\nPrint F1? (y/n): ";
	cin>>choice;
	cout<<endl;
	if(choice == 'Y' || choice == 'y')
	{
		// cout<<"Yes";
		for(i = 0; i < 125; i++)
			display(field3[i], 3);
	}

	cout<<"\n\n\n\nPrint F2? (y/n): ";
	cin>>choice;
	cout<<endl;
	if(choice == 'Y' || choice == 'y')
	{
		// cout<<"Yes";
		for(i = 0; i < 3125; i++)
			display(field5[i], 5);
	}

	cout<<"\nIrreducible polynomial of order 3 for F1:\nf3(x) = ";
	degree = 3;
	irr_poly_3(it, degree, it1, d2, j);

	cout<<"\nIrreducible polynomial of order 5 for F2:\nf5(x) = ";
	degree = 5;
	irr_poly_5(it, degree, it1, d2, j);

	int index = find_generator();
	cout<<"\nOne such generator of F1 can be: ";
	display(field3[index], 3);

	srand(time(NULL));

	cout<<"\nThree pairs of units of F2 found using f5(x) as irreducible polynomial are: \n";

	int pair;
	for(i = 0; i < 3; i++)
	{
		pair = 10 + (rand() % 20);
		cout<<"\nPair #"<<i+1<<": \n";
		
		for(m = 4; m >= 0; m--)
			if(field5[pair][m] != 0)
				break;
		degree = m;

		display(field5[pair], degree + 1);
		int *temp, *temp2, degree2;
		for(m = 1; m < 3125; m++)
		{
			for(l = 4; l >= 0; l--)
				if(field5[m][l] != 0)
					break;
			degree2 = l;
			temp = multiply(field5[pair], field5[m], degree, degree2);
			if(degree + degree2 >= 5)
			{
				temp2 = return_poly_div(temp, degree2 + degree, d5, 5);
				free(temp);
				temp = temp2;
			}
			for(l = 4; l >= 0; l--)
			{
				if(l == 0)
				{
					if(temp[l] != 1)
						break;
				}
				else
				{
					if(temp[l] != 0)
						break;
				}
			}
			if(l == -1)
			{

				display(field5[m], degree2 + 1);
				break;
			}
		}
	}


	return 0;
}