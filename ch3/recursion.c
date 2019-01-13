#include "stdio.h"

int sum(int * x, int size){

	if(size == 1 ){
		return x[size-1];
	}
	else{
		int victim = x[size-1];
		return victim + sum(x,size-1);
	}


}

int count_items(int * x){

	if (*x == -1){
		return 0;
	}
	else{
		x++;
		return 1 + count_items(x);
	}

}

int max(int *x, int size, int maximum){
	if(size == 0) return maximum;
	else {
		if (maximum < x[size-1]){
			maximum = x[size-1];
		}
		size-=1;
		return max(x,size,maximum);
	}

}

int main(void){

	int list[] ={2,100,1,6,99,-1};
	int * plist = &list[0];
	/*
	printf("plist: %d %d \n", *plist,plist);
	plist++;
	printf("plist: %d %d \n", *plist,plist);
	plist++;
	printf("plist: %d %d \n", *plist,plist);
	plist++;
	printf("plist: %d %d \n", *plist,plist);
	*/

	int final = sum(list,5);
	printf("%d\n", final);
	printf("count %d\n", count_items(plist));
	plist = &list[0];

	printf("max %d\n", max(plist,5,0));
	return 0;
}


