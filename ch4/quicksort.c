#include "stdio.h"

void print_array(int list[], int size){
	int k = 0;
	for(;k<size;k++) printf("%d\t", list[k]);
	printf("\n");

}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*  partition picks the first element as the pivot and then
*   anything greater than the pivot is on the right and anything
*   less than the pivot is on the left
*
*   function return the index that seperate the two partitions
*
*/
int partition(int array[], int lowIndex, int highIndex){

 int pivot=array[lowIndex],pivotIndex=lowIndex +1,i;

  for(i=lowIndex+1;i<highIndex;i++)
  {
    printf("i: %d arrray[i]: %d \n", i, array[i]);
    if(array[i]<pivot)
    {
        if(i != pivotIndex)
      {
            int temp=array[pivotIndex];
            array[pivotIndex]=array[i];
            array[i]=temp;
      }
      pivotIndex++;
    }
  }

  array[lowIndex]=array[pivotIndex - 1];
  array[pivotIndex - 1]=pivot;
	print_array(array,10);
  printf("Pivot: %d\n", pivotIndex-1);
  return pivotIndex-1;
}


/*
*
* Different approach than what is in the book
*
* This method will still pick the first element as the pivot. You sort inplace
*
*/

void quicksort(int array[], int lowIndex, int highIndex){

  printf("lowIndex: %d\thighIndex: %d\n",lowIndex,highIndex);
  if(lowIndex<highIndex){
    int pivot = partition(array,lowIndex,highIndex);
    quicksort(array,lowIndex,pivot);
    quicksort(array,pivot+1,highIndex);
  }

}

int main(void){

  int array[] ={5,3,9,1,8,6,2,0,4,7};
  //int array[] ={9,7,4,1,8,2,5,3,6,0};
  quicksort(array,0,10);
	print_array(array,10);



	return 0;
}
