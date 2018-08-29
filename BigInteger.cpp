#include "BigInteger.h"

const std::string USERNAME = "ebmy83";
const std::string STUDENT_ID = "12422230";

/*~~EXCEPTION~~~*/
BigIntException Big_Ex;

void get_identity(std::string my_id[])
{
  my_id[0] = USERNAME;
  my_id[1] = STUDENT_ID;
}

//Determines if the string is a correctly input integer string
//Ex, "888665858449" is valid. Ex, "-97949330" is also valid.
bool valid_int_string(std::string & str)
{
  bool valid = true;
  int i = 0;
  
  if(str[i] == '-')
	i = 1;

  while(valid && i < str.length()){
	valid = false;
    if(str[i] >= '0' && str[i] <= '9')
	  valid = true;
	  
	i++;  
  }
  
  return valid;
	
}

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

template <typename T>
void string_to_vector(MyVector<T> & v, std::string str)
{
  //Clear the array before building	
  v.clear();
  
  //Build the integer vector
    for(int i = 0; i < str.length(); i++){
      v.push_back(str[i]); 
    }	   
}

std::string vector_to_string(MyVector<int> vect)
{
  std::string big_number;
  
  if(vect[0] == '-'){
	big_number += '-';
    for(int i = 1; i < vect.size(); i++){
      big_number += (vect[i] + '0');	  
    }
  }
  else
	for(int i = 0; i < vect.size(); i++){
      big_number += (vect[i] + '0');	  
    }
	  
  return big_number;
}

void to_valid_int(MyVector<int> & number)
{
  //Set each element to a valid integer value
  if(number[0] == '-'){
	for(int i = 1; i < number.size(); i++){
	  number[i] -= '0';
	}
  }
  else if(number[0] != '-')
    for(int i = 0; i < number.size(); i++){
	  number[i] -= '0';
	}		

}

bool greaterThan(MyVector<int> lhs, MyVector<int> rhs)
{
  bool is_greater = false;
 
  //Check is lhs[i] > rhs[i], is so then lhs is greater,
  //if not then rhs is greater. If they are equal iterate until one is greater than the other
  //if the numbers are the same then we will set lhs to greater.
  int i = 0;
 
  //Account for the '-' sign
  if(lhs[0] == '-' && rhs[0] == 0)
	i = 1;
  
  while(lhs[i] == rhs[i] && i < lhs.size()){
	i++;  
  }
	  
  if(lhs[i] > rhs[i])
	is_greater= true;	
  else if(lhs[i] = rhs[i] && i == lhs.size())
	is_greater = true;
 
  //If lhs is negative, check if rhs[0] is greater than a leading 0
  if(lhs[0] == '-' && rhs[i] != 0)
    is_greater = false;	  
  
  return is_greater;
}

MyVector<int> vectorAdd(MyVector<int> num1, MyVector<int> num2)
{
  MyVector<int> sum;
  int sum_digit;
  int carry = 0;

  //Add from right to left, both numbers should be passed in 
  //at the same length
  for(int i = num1.size()-1; i >= 0; i--){
	sum_digit = num1[i] + num2[i] + carry;
	if(sum_digit > 9){
	  sum_digit -= 10; 
	  carry = 1;
	  sum.insert(sum.begin(), sum_digit);
	}	
    else{
	  sum.insert(sum.begin(), sum_digit);
      carry = 0;
	}	  
  }
  //Add Carry to the beginning if needed
  if(carry)
   sum.insert(sum.begin(), carry);		

  return sum;	
}

MyVector<int> vectorSub(MyVector<int> num1, MyVector<int> num2)
{
  MyVector<int> diff;
  int diff_digit;
  
  if(greaterThan(num1, num2)){
	//num1 is greater so we "put it on top" so to speak
	//Subtract from right to left
	for(int i = (num1.size()-1); i >= (num1.size()-num2.size()); i--){
	  diff_digit = num1[i] - num2[i];
	  if(diff_digit < 0){
	    diff_digit += 10;
		num1[i-1] -= 1;
	  }
	  diff.insert(diff.begin(), diff_digit);  
	}
			  
  }	  
  else{
	//num2 is greater so we "put it on top"
	//Subtract from right to left
	for(int i = (num2.size()-1); i >= 0; i--){
	  diff_digit = num2[i] - num1[i];
	  if(diff_digit < 0){
	    diff_digit += 10;
		num2[i-1] -= 1;
	  }
	  diff.insert(diff.begin(), diff_digit);  
	}
		  
  }
	
  return diff;

}

/*~~~BIGINTEGER FUNCTIONS~~~*/
BigInteger::BigInteger()
{
  digit_vector.clear();	
  isNegative = false;	
}

BigInteger::BigInteger(std::string really_big_number)
{
  //Check if the string is a valid integer
  bool valid_string = valid_int_string(really_big_number);

  if(valid_string){
    if(really_big_number[0] == '-')
      isNegative = true;
    else
	  isNegative = false;
    
    string_to_vector(digit_vector, really_big_number);

	to_valid_int(digit_vector);

  } 
  else{ 
    throw Big_Ex;
  }	
	
}

std::string BigInteger::to_string()
{
  std::string big_number;
  
  if(isNegative){
	big_number += '-';
    for(int i = 1; i < digit_vector.size(); i++){
      big_number += (digit_vector[i] + '0'); 	  
    }
  }	
  else
	for(int i = 0; i < digit_vector.size(); i++){
      big_number += (digit_vector[i] + '0');	  
    }
	 
  return big_number;
}

BigInteger operator+(BigInteger & bi1, BigInteger & bi2)
{
  //Create temp vectors to hold the big integer values and sum
  MyVector<int> tempInt_1;
  MyVector<int> tempInt_2;
  MyVector<int> sum;
  
  //Get the private digit_vector by using BigInteger::to_string, and converting
  //back into a vector.
  string_to_vector(tempInt_1, bi1.to_string());
  string_to_vector(tempInt_2, bi2.to_string());
  to_valid_int(tempInt_1);
  to_valid_int(tempInt_2);

  //Determine which number is larger in size and even the sizes out
  //by placing leading zeros at the beginning of the smaller sized number.
  int sizeDiff;
  if(tempInt_1.size() > tempInt_2.size() || tempInt_1.size() == tempInt_2.size()){
    sizeDiff = tempInt_1.size() - tempInt_2.size();
	int i = sizeDiff;
	while(i > 0){
	  tempInt_2.insert(tempInt_2.begin(), 0);
	  i--;
	}
	
	//If smaller number was negative, move the negative sign to the front
	//and swap it with a leading 0
	if(tempInt_2[sizeDiff] == '-')
	  swap(tempInt_2[0], tempInt_2[sizeDiff]);
  }
  else{
	sizeDiff = tempInt_2.size() - tempInt_1.size(); 
	int i = sizeDiff;
	while(i > 0){
	  tempInt_1.insert(tempInt_1.begin(), 0);
	  i--;
	}
	
	if(tempInt_1[sizeDiff] == '-')
	  swap(tempInt_1[0], tempInt_1[sizeDiff]);
  }
  
  cout << "\nAfter modification: \n" << tempInt_1 << endl << tempInt_2;
  
  
  //Determine which BigIntegers are negative and act accordingly
  if(tempInt_1[0] == '-' && tempInt_2[0] != '-'){
    if(greaterThan(tempInt_1, tempInt_2)){
	  
	  //Get rid of the '-' sign and leading 0 from other value to balance size
	  tempInt_1.remove(0);
	  tempInt_2.remove(0);
	  
	  //Perform Calculation and put the '-' sign back
	  sum = vectorSub(tempInt_1, tempInt_2);
	  sum.insert(sum.begin(), '-');	
	}
	else{
	  //Replace '-' with leading 0
	  tempInt_1.remove(0);
      tempInt_1.insert(0, 0);	  
	  
	  sum = vectorSub(tempInt_2, tempInt_1);
	}

  }
  else if(tempInt_1[0] != '-' && tempInt_2[0] == '-'){
	if(greaterThan(tempInt_2, tempInt_1)){
	  
	  //Get rid of the '-' sign and leading 0 from other value to balance size
	  tempInt_1.remove(0);
	  tempInt_2.remove(0);
	  
	  //Perform Calculation and put the '-' sign back
	  sum = vectorSub(tempInt_2, tempInt_1);
	  sum.insert(sum.begin(), '-');	
	}
	else{
	  //Replace '-' with leading 0
	  tempInt_2.remove(0);
      tempInt_2.insert(0, 0);	  
	  
	  sum = vectorSub(tempInt_1, tempInt_2);
	}

  }
  else if(tempInt_1[0] == '-' && tempInt_2[0] == '-'){
	tempInt_1.remove(0);
	tempInt_2.remove(0);
	
	sum = vectorAdd(tempInt_1, tempInt_2);
	sum.insert(sum.begin(), '-');
  }
  else{
	sum = vectorAdd(tempInt_1, tempInt_2);
  }

  cout << "\nSum: " << sum;
  BigInteger bigSum(vector_to_string(sum));
  return bigSum;
}

BigInteger operator-(BigInteger & bi1, BigInteger & bi2)
{
  //Create temp vectors to hold the big integer values and sum
  MyVector<int> tempInt_1;
  MyVector<int> tempInt_2;
  MyVector<int> diff;
  
  //Get the private digit_vector by using BigInteger::to_string, and converting
  //back into a vector.
  string_to_vector(tempInt_1, bi1.to_string());
  string_to_vector(tempInt_2, bi2.to_string());
  to_valid_int(tempInt_1);
  to_valid_int(tempInt_2);
  
  //Determine which number is larger in size and even the sizes out
  //by placing leading zeros at the beginning of the smaller sized number.
  int sizeDiff;
  if(tempInt_1.size() > tempInt_2.size() || tempInt_1.size() == tempInt_2.size()){
    sizeDiff = tempInt_1.size() - tempInt_2.size();
	int i = sizeDiff;
	while(i > 0){
	  tempInt_2.insert(tempInt_2.begin(), 0);
	  i--;
	}
	
	if(tempInt_2[sizeDiff] == '-')
	  swap(tempInt_2[0], tempInt_2[sizeDiff]);
	
  }
  else{
	sizeDiff = tempInt_2.size() - tempInt_1.size();
	int i = sizeDiff;
	while(i > 0){
	  tempInt_1.insert(tempInt_1.begin(), 0);
	  i--;
	}
	
	if(tempInt_1[sizeDiff] == '-')
	  swap(tempInt_1[0], tempInt_1[sizeDiff]);
	
  }
  
  cout << "\nAfter modification: \n" << tempInt_1 << endl << tempInt_2;

  //Determine which BigIntegers are negative and act accordingly
  if(tempInt_1[0] == '-' && tempInt_2[0] != '-'){
    if(greaterThan(tempInt_1, tempInt_2)){
	  //Get rid of the '-' sign.
	  tempInt_1.remove(0);
	  tempInt_1.remove(0);
	
	  //Perform Calculation
	  diff = vectorAdd(tempInt_1, tempInt_2);
	  diff.insert(diff.begin(), '-');
    }
	else{
	  tempInt_1.remove(0);
      tempInt_1.insert(0, 0);
      
      diff = vectorAdd(tempInt_1, tempInt_2);
      diff.insert(diff.begin(), '-');	 		
	}
  }
  else if(tempInt_1[0] != '-' && tempInt_2[0] == '-'){
	tempInt_2.remove(0);
	tempInt_2.insert(0,0);
	diff = vectorAdd(tempInt_1, tempInt_2);
	
	//Get rid of the extra leading 0
	if(greaterThan(tempInt_2, tempInt_1))
      diff.remove(0);
  }
  else if(tempInt_1[0] == '-' && tempInt_2[0] == '-'){
    if(greaterThan(tempInt_1, tempInt_2)){
	  tempInt_1.remove(0);
	  tempInt_2.remove(0);
	  
	  diff = vectorSub(tempInt_1, tempInt_2);
	  diff.insert(diff.begin(), '-');		
	}
	else{	
	  tempInt_1.remove(0);
	  tempInt_2.remove(0);
	  
	  diff = vectorSub(tempInt_2, tempInt_1);
	}
  }
  else{
	if(greaterThan(tempInt_1, tempInt_2)){
	  tempInt_1.remove(0);
	  tempInt_2.remove(0);
	  diff = vectorSub(tempInt_1, tempInt_2);
	}
	else{
	  diff = vectorSub(tempInt_1, tempInt_2);
      diff.insert(diff.begin(), '-');
	}
  }

  cout << "\nDifference: " << diff << endl;
  
  BigInteger bigDiff(vector_to_string(diff));
  return bigDiff;
}
