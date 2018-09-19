#include <vector>
using std::vector;


template <class T>
void swap (T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

template <class T, class Comparator>
int partition (vector<T> &myArray, Comparator comp, int start, int end, int p) {
  T pivotValue = myArray[p];
  swap(myArray[p],myArray[end]); //this moves pivot out of the way
  int left = start;
  int right = end-1;
  while (left < right) {
    while (comp(myArray[left],pivotValue) && comp(left,right)) {
      left++;
    }
    while (comp(pivotValue,myArray[right]) && comp(left,right)) {
      right--;
    }
    if (left < right) {
      swap(myArray[left],myArray[right]);
    }
  }
  //this is where we put the pivot back
  if (comp(myArray[end],myArray[right])) {
    swap(myArray[right],myArray[end]);
    return right;
  } else {
    return end;
  }
}

template <class T, class Comparator>
void qsort (vector<T> &myArray, Comparator comp, int start, int end) {
  //base case
  if (start >= end) {
    return;
  }

  //find median of the start middle and end to get our pivot
  int pivot = 0;
  int middle = (start+end)/2;
  if ( (comp(myArray[middle],myArray[start])
  && comp(myArray[start],myArray[end]))
  || (comp(myArray[end],myArray[start])
  && comp(myArray[start],myArray[middle])) ) {
    pivot = start;
  }
  else if ( (comp(myArray[start],myArray[middle])
            && comp(myArray[middle],myArray[end]))
  || (comp(myArray[end],myArray[middle])
  && comp(myArray[middle],myArray[start])) ) {
    pivot = middle;
  }
  else if ( (comp(myArray[start],myArray[end])
  && comp(myArray[end],myArray[middle]))
  || (comp(myArray[middle],myArray[end])
  && comp(myArray[end],myArray[start])) ) {
    pivot = end;
  }

  //partition
  int loc = partition(myArray, comp, start, end, pivot);

  //recurse on both sides
  qsort(myArray, comp, start, loc-1);
  qsort(myArray, comp, loc+1, end);
}

template <class T, class Comparator>
void QuickSort (vector<T> &myArray, Comparator comp) {
  int l = 0;
  int r = myArray.size()-1;
  qsort(myArray, comp, l, r);
}
