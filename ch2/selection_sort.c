#include "stdio.h"

enum type { MIN, MAX};

void swap(int * a, int * b){

	int temp = (*a);
	(*a) = (*b);
	(*b) = temp;
	return;
}

int pop(int list[], int newSortedList[], int * size,int extremeElementIndex){
	int extremeElement = list[extremeElementIndex];
	swap(&list[extremeElementIndex], &list[(*size)-1]);
	(*size)=(*size)-1;
	return extremeElement;


}

int findMin(int list[], int size){
	int min = list[0], min_index = 0;
	int i = 0;
	for(;i<size;i++){
		if(list[i] < min){
			min = list[i];min_index=i;
		}
	}
	/*printf("MIN: %d INDEX: %d \n", min,min_index);*/
	return min_index;

}

int findMax(int list[], int size){
	int max = list[0], max_index = 0;
	int i = 0;
	for(;i<size;i++){
		if(list[i] > max){
			max = list[i];max_index=i;
		}
	}
	/*printf("MAX: %d INDEX: %d \n", max,max_index);*/
	return max_index;

}

void print_array(int list[], int size){
	int k = 0;
	for(;k<size;k++) printf("%d\t", list[k]);
	printf("\n");



}

void selectionSort(int list[], int newSortedList[], int size, enum type x){
	/* I use some indexing and swap to emulate the pop() in python like on page 35,
	* basically once you find your extreme element, swap it to the end of the
	* array and then decrease to the size by 1
	*
	* You endup having both a auxiliary version and in-place version
	* of selection sort
	* list[](in-place) will be the reverse of your sorted list
	* newSortedList(auxiliary) will be your intended sorted list
	*/
	int index=0;
	while(size != 0){
		int extremeElementIndex;
		if (x == MAX){
			extremeElementIndex = findMax(list,size);
		}
		else{
			extremeElementIndex = findMin(list,size);
		}

		newSortedList[index]=pop(list,newSortedList,&size,extremeElementIndex);
		index++;

	}
	return;


}

int main(void){

	printf("Original List\n");
	int list[] ={9,5,6,3,8,0,1,4,2,7};
	print_array(list,10);
	int newSortedList[10];
	selectionSort(list,newSortedList,10, MIN);
	printf("Sorted by MIN\n");
	print_array(newSortedList,10);

	printf("Original List\n");
	int max_list[] ={9,5,6,3,8,0,1,4,2,7};
	print_array(max_list,10);
	selectionSort(max_list,newSortedList,10, MAX);
	printf("Sorted by MAX\n");
	print_array(newSortedList,10);


}


