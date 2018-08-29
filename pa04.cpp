/* Sample tester
 * We've included vector below to show you how your types should behave.
 * You can use that for debugging.
 * As in the assignment description, if you use the std::vector for your submitted code,
 * you will get a 0.
 */

#include "BigInteger.h"
#include "MyVector.h"

template <typename T>
void print_vector(MyVector<T> v)
{
  int j = 0;
  for(auto i = 0; i < v.size(); i++)
    {
        cout << v[j];
        j++;
    }
}

int main()
{
	
    MyVector<int> v;

    cout << v.size() << endl;
    v.push_back(4000);
    cout << v.at(0) << endl;
    cout << v.capacity() << endl;
    v.reserve(10);
    cout << v.capacity() << endl;
    v.push_back(200);
    v.push_back(100);
    v.insert(v.begin(), 3);
    v.insert(v.end(), 20);
	
	cout << "\nOperator= test\n";
	MyVector<int> newVector(v);
	cout << v << endl;
	cout << newVector << endl;
	
	newVector.clear();
	newVector = v;
	cout << newVector << endl;

    int j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        cout << v.at(j) << endl;
        j++;
    }
    
    j = 0;
    for(auto i = 0; i < v.size(); i++)
    {
        cout << v[j] << endl;
        j++;
    }
    
	
    std::string init_string("-8675309");

    BigInteger my_big_int(init_string);
	
	cout << "\nBIG INT INBOUND!!" << endl;
	cout << my_big_int.to_string() << "\n";

    BigInteger another_big_int = my_big_int;
	cout << "Another Big Int: " << another_big_int.to_string() << endl;
    
	init_string = "-5733150142";
	BigInteger yet_another_big_int(init_string);
	cout << "Yet another.... " << yet_another_big_int.to_string() << endl;
    
    my_big_int = another_big_int + yet_another_big_int;
	cout << "\nAdd those two: " << my_big_int.to_string() << endl;

    my_big_int = another_big_int - yet_another_big_int;
	cout << "Sub those two: " << my_big_int.to_string() << endl;
  
    return 0;
}

