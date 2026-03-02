#include <iostream>

using namespace std;

int calc_pow(int input, int n)
{
    if (n % 2 == 1 && n != 1)
    {
        n=n-1;
        return input*calc_pow(input,n/2) * calc_pow(input,n/2);
    }else if(n % 2 == 0)
    {
        return calc_pow(input,n/2) * calc_pow(input,n/2);
    }else
    {
        return input;
    }
    
}

int main()
{
    int input,n;
    cout<< "input a num and n"<< endl;
    cin>>input;
    cin>>n;
    int result = calc_pow(input, n);
    cout<<"input^n = "<< result<< endl;
    cout<< "input anykey"<< endl;
    cin>>input;
    return 0;
}