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
