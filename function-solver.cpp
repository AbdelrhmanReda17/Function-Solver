#include <iostream>

using namespace std;

double cube (double n) {
    return n * n * n;
}
double second (double d) {
    return d * d - 5 * d - 4;
}
double fun (double d) {
    return d * d - 3 * d - 4;
}

class Function
{
public:
    virtual double evaluateAt(double value) = 0;

};
class SimpleFunction:Function
{
public:
    double (*first_function)(double);

    SimpleFunction(double (*f)(double))
    {
        first_function = f;
    }
    virtual double evaluateAt(double value)
    {
        value = ( first_function(value) );
        return value;
    }
};
class CompositeFunction:Function
{

public:
    double (*first_function)(double);
    double (*second_function)(double);
    CompositeFunction( double (*f)(double) , double (*s)(double) )
    {
         first_function = f;
         second_function = s;
    }
    virtual double evaluateAt(double value)
    {
        value = ( first_function( second_function(value) ) );
        return value;
    }
};
class DerivativeFunction:Function
{
public:
    double x;
    double (*func)(double);
    DerivativeFunction(double (*f)(double) , double dl)
    {
        x = dl;
        func = f;
    }
    virtual double evaluateAt( double value )
    {
        return ( (func(value+x) - func (value - x)) / (2 * x) );
    }
};


int main(){
    SimpleFunction f31 ( [](double n) -> double { return n * n; } );
    cout << f31.evaluateAt(6);
    CompositeFunction f1(cube, second);
    cout << f1.evaluateAt(5) << endl;
    DerivativeFunction f2(second, 5);
    cout << f2.evaluateAt(5) << endl;
}