//  DO NOT TURN IN SOME PREDICATE DO NOT TURN IT IN
#include <iostream>
using namespace std;

bool somePredicate(double x)
{
    return x < 0;
}

// Return true if the somePredicate function returns true for at
  // least one of the array elements, false otherwise.

/*
 DO NOT TURN IN SOME PREDICATE DO NOT TURN IT IN
 */
bool anyTrue(const double a[], int n)
{
    /*
     base case: if what a points to is true, then return true
     anyTrue(*(a+1), n-1);
     */
    if (n <= 0)
        return false;
    if (somePredicate(*a))
        return true;
    return (anyTrue(a+1, n-1));
}

  // Return the number of elements in the array for which the
  // somePredicate function returns true.
int countTrue(const double a[], int n)
{
    /*
    base case: assessed all elements
    */
    int numTrue = 0;
    if (n <= 0)
        return numTrue;
    if (somePredicate(*a))
        numTrue++;
    return(numTrue += countTrue(a+1, n-1));
}

  // Return the subscript of the first element in the array for which
  // the somePredicate function returns true.  If there is no such
  // element, return -1.
int firstTrue(const double a[], int n)
{
    if (n == 0)
        return -1;
    if (somePredicate(*a))
        return 0;
    int num = (firstTrue(a+1, n-1));
    if (num < 0) // huh??
        return num;
    else return num+1;
}

  // Return the subscript of the largest element in the array (i.e.,
  // return the smallest subscript m such that a[m] >= a[k] for all
  // k from 0 to n-1).  If the function is told to examine no
  // elements, return -1.
int positionOfMax(const double a[], int n)
{
    /*
     base case: visited all elements
     if it's bigger than the current max, check it against using position of max on rest of array
     */
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;
    int max = positionOfMax(a, n-1);
    if (a[max] < a[n-1])
        return n-1;
    else
        return max;
}

  // If all n1 elements of a1 appear in the n2 element array a2, in
  // the same order (though not necessarily consecutively), then
  // return true; otherwise (i.e., if the array a2 is not a
  // not-necessarily-contiguous subsequence of a1), return false.
  // (Of course, if a1 is empty (i.e., n1 is 0), return true.)
  // For example, if a2 is the 7 element array
  //    10 50 40 20 50 40 30
  // then the function should return true if a1 is
  //    50 20 30
  // or
  //    50 40 40
  // and it should return false if a1 is
  //    50 30 20
  // or
  //    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    /*
     base case: if all items in a1 are found in a2
     if first item is found move onto the next, then the next, the next
     
     */
    if (n1 == 0)
        return true;
    if (n1 < 0 || n2 <= 0)
        return false;
    if (a1[0] == a2[0])
    {
        return (isIn(a1+1, n1-1, a2+1, n2-1));
    }
    
    return isIn(a1, n1, a2+1, n2-1);
}

int main()
{
    /* double arr[5] = { -1, 3, 4, 9, -5 };
    if (anyTrue(arr, 5))
        cout << "anyTrue returns true" << endl;
    else
        cout << "anyTrue returns false" << endl;
    cout << "countTrue says " << countTrue(arr, 5) << " are true." << endl;
    cout << "firstTrue says position " << firstTrue(arr, 5) << "." << endl;
    cout << "positionOfMax says position " << positionOfMax(arr, 5) << "." << endl;*/
    
    double arr2[7] = { 10, 50, 40, 20, 50, 40, 30 };
    double arr1[3] = { 50, 20, 30 };
    double arr3[3] = { 50, 30, 20 };
    double arr4[3] = { 10, 20, 20 };
    if (isIn(arr1, 3, arr2, 7)) cout << "True! " << endl;
    else cout << "False!" << endl;
    if (isIn(arr3, 3, arr2, 7)) cout << "True! " << endl;
    else cout << "False!" << endl;
    if (isIn(arr4, 3, arr2, 7)) cout << "True! " << endl;
    else cout << "False!" << endl;
    
    return 0;
}
