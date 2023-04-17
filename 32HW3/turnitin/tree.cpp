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
