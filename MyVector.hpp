/* Define all your MyVector-related functions here.
 * You do not need to include the h file.
 * It included this file at the bottom.
 */

/*~~Exception~~~*/
const int DEFAULT_MAX_SIZE = 1;
const int DEFAULT_DATA_SIZE = 0;


template <typename T>
void swap(T & a, T & b)
{
  T temp = b;
  b = a;
  a = temp;  
}

/*~~~MyVector Functions~~~*/

template <typename T>
MyVector<T>::MyVector()
{
  reserved_size = DEFAULT_MAX_SIZE;
  data_size = DEFAULT_DATA_SIZE;
  m_data = new T[reserved_size];
}

// We're giving you this one for free
// and as a guide for the syntax.
template <typename T>
MyVector<T>::~MyVector()
{
    delete[] m_data;
}

template <typename T>
MyVector<T> & MyVector<T>::operator=(const MyVector<T> &source)
{
  //Clear the current vector before assigning
  delete[] m_data;
  
  //Copy the maximum size of the source vector
  reserved_size = source.reserved_size;
  
  //Create a new array to be copied into
  m_data = new T[reserved_size];
  
  //Copy the data size of the source vector
  data_size = source.data_size;
  
  //Assign each element
  for(int i = 0; i < data_size; i++){
	m_data[i] = source.m_data[i];  
  }
  
  return *this;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &source)
{
  //Copy the maximum size of the source vector
  reserved_size = source.reserved_size;
  
  //Create an array to be copied into
  m_data = new T[reserved_size];
  
  //Copy the data size of the source vector
  data_size = source.data_size;
  
  //Assign each element
  for(int i = 0; i < data_size; i++){
	m_data[i] = source.m_data[i];  
  }

}

template <typename T>
T & MyVector<T>::operator[](int i)
{
  return m_data[i];	
}

// Another example: remember, return type first, 
// then scope just before the function name.
template <typename T>
T & MyVector<T>::at(int index)
{
  OutOfBoundsException MyException;
  //Throw MyException when out of bounds, catch in calling function 
  if(index < 0 || index >= data_size)
    throw MyException;

  return m_data[index];
}

template <typename T>
T & MyVector<T>::front()
{
  return m_data[0];	
}

template <typename T>
T & MyVector<T>::back()
{
  return m_data[data_size-1];
}

template <typename T>
int MyVector<T>::capacity()
{
  return reserved_size;	
}

template <typename T>
void MyVector<T>::reserve(int new_cap)
{
  if(new_cap > reserved_size){
	reserved_size = new_cap;
	
    //Create a temp array with the new maximum size
	T * tempArray = new T[reserved_size];
	
	//Copy the old array into a temp one.
	for(int i = 0; i < data_size; i++){
	  tempArray[i] = m_data[i];
	}
	
	//Delete the old array.
	delete[] m_data;
	
	//Set the new array equal to the temp
	m_data = tempArray;
  }
  
}

//Should be called anytime the array gets below 1/4 full
template <typename T>
void MyVector<T>::shrink_to_fit()
{
  reserved_size = data_size * 2;
  
  //Shrink the array to twice the size of the data size.
  T * tempArray = new T[reserved_size];
  
  //Copy the old array into a temp one.
  for(int i = 0; i < data_size; i++){
  	tempArray[i] = m_data[i];
  }
	
  //Delete the old array.
  delete[] m_data;
	
  //Set the new array equal to the temp
  m_data = tempArray;
 
}

template <typename T>
void MyVector<T>::assign(int count, const T &value)
{
  //Set the max size to the size of the data
  data_size = count;
  reserved_size = data_size;
  
  //Reinitialize the array
  delete[] m_data;
  m_data = new T[reserved_size];
    
}

template <typename T>
void MyVector<T>::clear()
{  
  data_size = DEFAULT_DATA_SIZE;
  reserved_size = DEFAULT_MAX_SIZE;
  
  delete[] m_data;
  m_data = new T[reserved_size];
}

template <typename T>
void MyVector<T>::push_back(const T &x)
{
  //All functions that insert will increase the size of the array
  //There should be no instance where data is inserted passed the 
  //bounds of the array.
  if(!(data_size < reserved_size))
    reserve(reserved_size * 2);	
	
  m_data[data_size++] = x;
  
  if(data_size < (reserved_size / 4))
	shrink_to_fit();
  
}

template <typename T>
void MyVector<T>::pop_back()
{
  //Decrement the data size
  data_size--;
  if(data_size < 0)
	data_size = 0;
  
  if(data_size < (reserved_size / 4))
	shrink_to_fit();

}

template <typename T>
void MyVector<T>::insert(int i, const T &x)
{
  OutOfBoundsException MyException;
  //Check if the array needs resized
  if(!(data_size < reserved_size))
    reserve(reserved_size * 2);
	
  //Check if we are trying to index a location outside of bounds
  if(data_size == 0 && i != 0)
	throw MyException;
  else if(i < 0 || (i > data_size && data_size != 0))
    throw MyException;

  //Push back all elements from index i back 1 space each
  for(int k = data_size; k > i; k--){
    m_data[k] = m_data[k-1];  
  }

  //Set the value at index i to x, this also sets the 
  m_data[i] = x;
  data_size++;

}

template <typename T>
void MyVector<T>::remove(int i)
{
  OutOfBoundsException MyException;
  //Check if we are trying to index a location outside the bounds
  if(i < 0 || i >= data_size)
    throw MyException;

  //Move the elements down 1 position each
  for(int k = i; k < data_size - 1; k++){
	  m_data[k] = m_data[k+1]; 	  
  }
  
  data_size--;
  
  if(data_size < (reserved_size / 4))
	shrink_to_fit();

}

template <typename T>
int MyVector<T>::size()
{
  return data_size;	
}
