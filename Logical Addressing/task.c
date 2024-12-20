#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<math.h>

int checkP2(int x);
int *dTob(int n,int l);
int bTod(int a[],int l);

int main(){
	int pgs=4; //page size
	int ms=32; //memory size
	int nof=ms/pgs; //number of frames
	int offset_bit; //find out # of bits required for offset
	int m; //find out address spaces required in main memory
	int pg_num_bit; ////find out # of bits required for page number

	int la[]={8,4,3,2,15,18,25}; //logical addresses generated by the CPU

	int pmt[]={3,6,8,12,2}; //page table

	/*
	find out corresponding physical addresses of generated logical
	addresses
	using the formula: physical address = (frame # * page
	size)+offset
	*/
	printf("Page size: %d\n",pgs);
	printf("Memory size: %d\n",ms);
	printf("Number of frames required: %d\n",nof);
	int n;
	m = checkP2(ms);
	n = checkP2(pgs);
	pg_num_bit = m-n;
	printf("Page number bits: %d\n",pg_num_bit);
	printf("Offset bits: %d\n",n);
	printf("Number of address spaces: %d",m);
	printf("Page Table_____\n");
	for(int i=0;i<5;i++){
		printf("%d -> %d\n",i,pmt[i]);
	}
	for(int i=0;i<7;i++){
		int *arr;
		arr = dTob(la[i],m);
		int pa[pg_num_bit];
		for(int i=0; i< pg_num_bit;i++){
			pa[i]=arr[i];
		}
		
		int off[n];
		for(int i=0;i<n;i++){
			off[i]=arr[pg_num_bit+i];
		}
		int p,o;
		p = bTod(pa,pg_num_bit);
		o = bTod(off,n);
		int ph;
		ph = pmt[p] * pgs + o;
		
		
		if (ph >= ms && p<5 ){
			printf("%d is an invalid physical adress\n",ph);
		}
		else if(p>5){
			printf("%d is an invalid page number\n",p);
		}
		else{
			printf("Corresponding physical address of logical address %d: %d\n",la[i],ph);
		}
		free(arr);
	}

	return 0;
}

int checkP2(int x){
	int i=-1;
	while(x>0){
		x= floor(x/2);
		i++;
	}
	return i;
}

int *dTob(int n,int l){
	int *a = malloc(l);
	int i=1;
	while(i <= l){
		a[l-i]=n%2;
		n = floor(n/2);
		i++;
	}
	return a;
}

int bTod(int a[],int l){
	int num=0;
	int base =1;
	l--;
	while(l){
		num += a[l] * base;
		base *= 2;
		l--;
	}
	num += a[l] * base;
	return num;
}
