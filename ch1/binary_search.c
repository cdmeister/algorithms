#include "stdio.h"
#include "stdint.h"

int binary_search(int list[],uint32_t list_size, int victim);

int binary_search(int list[],uint32_t list_size, int victim){

  /*low and high keep track of which part of the list you have to search in */
  int low = 0;
  int high = (int)list_size - 1;

  while (low <= high){
    /*integer division, fraction is truncated*/
    int middle_index = (low + high)/2;

    /* grab the middle number now */
    int  middle_number = list[middle_index];
    if (middle_number == victim){
      return middle_index;
    }
    else if (victim < middle_number){
      high = middle_index -1;

    }
    else{
      low = middle_index + 1;
    }

  }
  return -1;

}

int main(void){

  int my_list[5] = {1,3,4,7,9};
  int position = binary_search(my_list, 5,3);
  printf("%d\n",position);
  position = binary_search(my_list,5,-1);
  printf("%d\n",position);

  return 0;
}
