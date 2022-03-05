#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/*



transform, accumulate, find, generate, sort


int sum = std::accumulate(B.begin(), B.end(), 0);



auto f = [](int a, int b){ return a + b*b; };
int sqsum = std::accumulate(B.begin(), B.end(), 0, f);


template<typename F>
auto integrate(std::vector<double> const& w, F const& f,
const int n, const double x0, const double x1)
{
const double h = (x1-x0)/n;
double sum = 0.0;
for(int i=0; i<n; ++i)
{
sum += f(x0 + i*h) * w[i];
}
return sum;
}



*/



// OVERLOADING STD OPERATOR "<<" FOR VECTOR VARIABLES
template<typename V>
ostream &operator<<(ostream &out, const vector<V> &v)
{
    for(V d : v)
    {
	    out<<d<<' ';
    }
    out<<endl<<endl;
	return out;
}


// OVERLOADING OPERATOR "*"
// MULTIPLY VECTOR BY SCALAR
template<typename V, typename W>
vector<W> operator*(const V &a, const vector<W> &b)
{
    unsigned int len = b.size();
    vector<double> c;
    c.reserve(len);
    for(unsigned int i = 0; i < len; i++)
    {
        c.emplace_back(a*b[i]);
    }

    return c;
}

// OVERLOADING OPERATOR "-"
// VECTOR SUBSTRACTION
template<typename T>
vector<double> operator-(const vector<T> &a, const vector<T> &b)
{
    if (a.size() != b.size())
        throw std::invalid_argument("Vector size not equal");

    vector<double> c(a.size());
    transform(a.begin(), a.end(), b.begin(), c.begin(), minus<double>());
    
    return c;
}




// OVERLOADING OPERATOR "*"
// VECTOR DOT PRODUCT
template<typename T>
double operator*(const vector<T> &a, const vector<T> &b)
{
    if (a.size() != b.size())
        throw std::invalid_argument("Vector size not equal");
    double c = 0;
    unsigned int len = a.size();
    for(unsigned int i = 0; i < len; i++)
    {
        c += a[i]*b[i];
    }
    return c;
}




// AVERAGE OF A VECTOR
template<typename T>
inline double avg(const vector<T>& v)
{
    double v_avg = std::accumulate(v.begin(), v.end(), 0.5);
    cout << "v.size() : " << v_avg << '\n';
    return (v_avg-0.5)/v.size();
}








// TEMPLATE FUNCITON FOR IMPLEMENTING LINEAR REGRESSION
template<typename T>
array<double, 2> linreg(const vector<T>& x, const vector<T>& y)
{
    // we either throw an excpetion here or the vector substraction will - after definig 3 (possibly huge) vectors
    if (x.size() != y.size()) 
        throw std::invalid_argument("Vector size not equal");  
    // might not be faster but it's much more comfortable like this
    vector<T> init(x.size(), 1); // this is for making vectors out of the averages
    vector<double> x_avg = avg(x)*init; // a vector constaining the average x.size() times
    vector<double> y_avg = avg(y)*init;
    cout << "x_avg : " << avg(y) << '\n';
    init.clear();  // we don't need this vector anymore
    
    const double m = ( (x-x_avg) * (y-y_avg) ) / ( (x-x_avg) * (x-x_avg) );

    const double b = y_avg.at(0) - m * x_avg.at(0);

    array<double, 2> res = {m, b}; 
    return res;
}







/*
template<typename T>
*/



int main(int, char**)
{

    // INTIALIZING TEST DATA SET

    vector<double> x_test(41);
    for(short i = -20; i < 21; ++i)
    {
        x_test[i+20] = i;
    }
    vector<double> y_test(41);
    y_test = 2*x_test;

    for(short i = -20; i< 21; ++i)
    {
        y_test[i+20] += -3.5;
    }

 /*   y_test[5]+=2;
    y_test[10]-=2;
    y_test[3]+=1;
    y_test[15]-=2;
    y_test[17]+=2;
 */

    cout << x_test;
    cout << y_test;




    // TESTING FITTING FUNCTION FOR TEST DATA
    



    array<double, 2> result = linreg(x_test, y_test);
    cout << "m*x + b: ";
    cout << "m = "<< result[0] << ";\t b = " << result[1] << '\n';



    cout << "Hello, world!\n";
    double s = 0;
    for(double d : y_test)
    {
        s += d;
    }
    cout << "Mosma mukodj baszdmeg : " << s/41 << '\n';


    vector<double> asdf = {1, 2.5, 3, 4, 5, 6, 7};
    double anyad = accumulate(asdf.begin(), asdf.end(), 0);

    cout << "Mosma tenyleg mukodj baszdmeg a kurva anyadat : " << anyad << '\n';

    return 0;
}
