#include "fib.h"

// fib(n) = fib(n-1)+ fib(n-2)
int fib(int n)
{
    int i;
    int an_1,an_2,an;

    an_1 = 1;
    an_2 = 0;
    an = an_1 + an_2 ;
    
    for(i=1;i< n;i++){
	an=an_1+an_2;
	an_2=an_1;
	an_1=an;
    }
    return an;
}

