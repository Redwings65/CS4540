/*
 * CS 4540 Assignment #5 - Virtual Address
 * PROGRAM    : a5.c
 * AUTHOR     : Brandon Scott Seager
 * DATE       : 4/2/2018
 * CLASS      : Operating Systems (CS 4540)
 * DESCRIPTION: This is the Virtural Address
 */
//All items in this program are referenced in a seprate reference document!!!!
/*
TO RUN THE Program
make
make test
*/

#include <stdio.h>

int main(int argc, char *argv[]){
unsigned long page;
unsigned long offset;
unsigned long address;
address= atoll(argv[1]);
page = address >> 12;
offset = address & 0xfff;
printf("The address %lu contains: \n", address);
printf("page number = %lu\n",page);
printf("offset = %lu\n", offset);
return 0;
}
