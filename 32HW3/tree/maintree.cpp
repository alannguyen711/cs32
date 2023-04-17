#include <iostream>
using namespace std;


  // Return the number of ways that all n1 elements of a1 appear in
  // the n2 element array a2 in the same order (though not necessarily
  // consecutively).  The empty sequence (i.e. one where n1 is 0)
  // appears in a sequence of length n2 in 1 way, even if n2 is 0.
  // For example, if a2 is the 7 element array
  //    10 50 40 20 50 40 30
  // then for this value of a1     the function must return
  //    10 20 40                             1
  //    10 40 30                             2
  //    20 10 40                             0
  //    50 40 30                             3
int countIsIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n1 < 1)
        return 1;
    if (n2 < 1 || n2 < n1)
        return 0;
    if (*a1 == *a2)
    {
        int i = countIsIn(a1, n1, a2+1, n2-1); // as if a1[0] was not found
        int j = countIsIn(a1+1, n1-1, a2+1, n2-1);
        return i+j;
    }
    
    else
        return countIsIn(a1, n1, a2+1, n2-1);
    /*
     two branches, continue counting with one branch and without it
     */
}

  // Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

  // Rearrange the elements of the array so that all the elements
  // whose value is > divider come before all the other elements,
  // and all the elements whose value is < divider come after all
  // the other elements.  Upon return, firstNotGreater is set to the
  // index of the first element in the rearranged array that is
  // <= divider, or n if there is no such element, and firstLess is
  // set to the index of the first element that is < divider, or n
  // if there is no such element.
  // In other words, upon return from the function, the array is a
  // permutation of its original value such that
  //   * for 0 <= i < firstNotGreater, a[i] > divider
  //   * for firstNotGreater <= i < firstLess, a[i] == divider
  //   * for firstLess <= i < n, a[i] < divider
  // All the elements > divider end up in no particular order.
  // All the elements < divider end up in no particular order.
void divide(double a[], int n, double divider,
                    int& firstNotGreater, int& firstLess)
{
    if (n < 0)
    n = 0;

      // It will always be the case that just before evaluating the loop
      // condition:
      //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
      //  Every element earlier than position firstNotGreater is > divider
      //  Every element from position firstNotGreater to firstUnknown-1 is
      //    == divider
      //  Every element from firstUnknown to firstLess-1 is not known yet
      //  Every element at position firstLess or later is < divider

    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
    if (a[firstUnknown] < divider)
    {
        firstLess--;
        exchange(a[firstUnknown], a[firstLess]);
    }
    else
    {
        if (a[firstUnknown] > divider)
        {
        exchange(a[firstNotGreater], a[firstUnknown]);
        firstNotGreater++;
        }
        firstUnknown++;
    }
    }
}

  // Rearrange the elements of the array so that
  // a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
  // If n <= 1, do nothing.
void order(double a[], int n)
{
    int firstNotGreater;
    int firstLess;
    if (n <= 1)
        return;
    divide(a, n, a[0], firstNotGreater, firstLess);
    order(a, firstNotGreater+1);
    order(a+firstLess, n-firstLess);
    
}
// Hint: Using the divide function, the order function can be written in fewer than eight short lines of code

int main()
{
    double a[] = {10,50, 40, 20, 50, 40, 30};
    double b[] = {10, 20, 40};
    double c[] = {10, 40, 30};
    double d[] = {20, 10, 40};
    double e[] = {50, 40, 30};
    double f[] = {};
    double g[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double h[] = {1, 2, 1, 3, 4, 5, 7, 6, 2, 5, 6, 7, 8, 2, 7, 6, 4 ,7, 9, 6, 7, 7};
    double i[] = {7, 7, 6};
    double j[] = {5, 2, 8, 4, 0, 1, 5, 3, 8, 2};
    assert(countIsIn(b, 3, a, 7) == 1);
    assert(countIsIn(c, 3, a, 7) == 2);
    assert(countIsIn(d, 3, a, 7) == 0);
    assert(countIsIn(e, 3, a, 7) == 3);
    assert(countIsIn(f, 0, a, 7) == 1);
    assert(countIsIn(a, 7, a, 7) == 1);
    assert(countIsIn(d, 0, a, 7) == 1);
    assert(countIsIn(d, -1, a, 7) == 1);
    assert(countIsIn(d, 3, a, -1) == 0);
    assert(countIsIn(i, 3, h, 22) == 9);
    double yu[] = {10, 50, 40, 20, 50, 40, 30};
    order (yu, 7);
    for (int i = 0 ; i < 7; i++)
    {
        cout << yu[i] << endl;
        
    }
    
    cout << "All tests passed." << endl;
    
    double arr[12] = { 4, 9, 3, 22, 4, 3, 5, 2, 5, 12, 42, 18 };
    int firstNotGreater = 0;
    int firstLess = 0;
    divide(arr, 12, 10, firstNotGreater, firstLess);
    for (int i = 0; i < 12; i++)
        cout << arr[i] << " ";
    cout << endl << "firstNotGreater: " << firstNotGreater << " firstLess: " << firstLess << endl;
    divide(arr, 12, 3, firstNotGreater, firstLess);
    for (int i = 0; i < 12; i++)
        cout << arr[i] << " ";
    cout << endl << "firstNotGreater: " << firstNotGreater << " firstLess: " << firstLess << endl;
}
