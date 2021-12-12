#include <bits/stdc++.h>
#include <math.h>
#include "testlib.h"
using namespace std;
#include<time.h>

int main()
{
    //srand(time(NULL));
    int n, i,ns,np;
    printf("Enter number of points : \n");
    cin>>n;
    printf("Enter number of lines the points should roughly lie on : \n");
    cin>>ns;
    np = n/ns;
    int slopes[ns], inter[ns];
    int nump[ns];
    for(i = 0; i<ns; i++)
    nump[i] = np;
    if(n%ns != 0)
    {
        if(n%ns > np)
        nump[ns-1] = n%ns;
        else
        nump[ns-1] = np+n%ns;
    }
    for(i = 0; i<ns; i++)
    {
        slopes[i] = rnd.next(-9,9);
        inter[i] = rnd.next(-19,19);
    }
    //for(i = 0;i<ns; i++)
    //cout<<inter[i]<<"\n";
    fstream input;
    int y;
    input.open("test.txt",ios::out);
    input<<n<<"\n";
    i = 1;
    for(int j = 0; j<ns; j++)
    {
        for(int k = 0; k<nump[j];k++)
        {
            y = slopes[j]*i + inter[j] + rnd.next(-5,5);
            input<<i<<" "<<y<<"\n";
            i++;
        }
    }
    input.close();
    return 0;
}
