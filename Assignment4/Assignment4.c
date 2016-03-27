#include <stdio.h>
#include <stdlib.h>

int lastManStanding;

int lastStanding_2(int n , int array[]){
	// printf("\n\n");
	int i, index, odd;

	if (n == 1){
		printf("Base Case\n");
		array[0] = 1;
		printf("%d,", array[0]);
		return 1;
	}
	else{

		if((n)%2 != 0){
			// odd
			index = lastStanding_2(n/2, array);

			if((index%2) == 0){
				printf("\nODD -> EVEN\n");
				for(i = 0; i < n;i++){
					if(i < index){

						array[i] = 2*array[i]+1;
						printf("%d,", array[i]);
					}else{
						if(n - index - 1 == i ){
							array[n - index - 1] = 1;
							printf("%d,", array[i]);

						}else{
							array[i]= (n-i)*2;
							printf("%d,", array[i]);
						}
					}
				}

				return (2*index+1);
			}else{
				printf("\nODD -> ODD\n");
				// printf("index:%d\n",index);
				for(i = 0; i < n;i++){
					if(i < index){
							array[i] = 2*array[i]+1;
							printf("%d,", array[i]);
					}

					else{
						if((n - index - 1) == i){
							array[i] = 1;
							printf("%d,", array[i]);
						}else{
							array[i]= (n-i)*2;
							printf("%d,", array[i]);
						}
					}
				}
				return (2*index+1);
			}

		}else{

			//even
			index = lastStanding_2(n/2, array);


			if((index%2) == 0){
				printf("\nEVEN -> EVEN\n");
				for(i = 0; i < n;i++){
					if(i < index){

						array[i] = 2*array[i]-1;
						printf("%d,", array[i]);
					}
					else{

						array[i]= (n-i)*2;
						printf("%d,", array[i]);
					}
				}
				return (2*index);
			}else{
				printf("\nEVEN -> ODD\n");
				for(i = 0; i < n;i++){
					if(i < index){

						array[i] = 2*array[i]-1;
						printf("%d,", array[i]);
					}
					else{

						array[i]= (n-i)*2;
						printf("%d,", array[i]);
					}
				}
				return(2*index);
			}
		}
	}
}


void lastStanding(int a, int d, int size){
	int i = 1;
	int flagLast = 0;
	printf("\n");
	// printf("a: %d,d: %d,size: %d\n", a,d,size);

	if(a > size){
		// printf("\nLast standing: %d", a);
		return;
	}
	// printf("Eliminated: ");

	while((a+(i-1)*d) <= size){
		if(i%2 == 0){
			printf("%d,",(a+(i-1)*d));
			if(size == (a+(i-1)*d)){
				flagLast = 1;
			}
		}
		i++;
	}

	// printf("flagLast: %d\n", flagLast);

	if(flagLast == 0){
		lastManStanding = a;
		printf("%d",a);
		lastStanding(a+2*d, 2*d, size);
	}else{
		// lastManStanding = a;
		lastStanding(a, 2*d, size-d);
	}

	return;
}



int main(){
	int i ,option, size , index;

	int *array;
	array = (int*)malloc(size*sizeof(int));


	printf("Give the number of elements ");
	scanf("%d", &size);

	printf("The generated elements are: ");

	for(i = 1 ; i <= size; i++){
		printf("%d,",i);
	}
	printf("\n");

	printf("Which Algorithm to follow ?\n");
	printf("1. Top to Bottom\n");
	printf("2. Bottom to Top\n");

	scanf("%d", &option);
	if(option == 1){
		lastStanding(1,1,size);

	}else if (option == 2){
		for(i = size-1 ; i < 0 ; i--){
			printf("%d,", array[i]);
		}

		index = lastStanding_2(size, array);
		lastManStanding = array[0];
		printf("\n");
	}else{
		printf("Sorry!! Option not found. \nExiting....");
		return -1;
	}

	printf("Therefore, last man standing is: %d\n", lastManStanding);


	int m = 1;
	int power = 0;

	while(m <= size){
		m = m*2;
		power++;
	}
	power--;

	printf("m: %d\n",power);
	printf("l: %d\n", size - m/2);

	printf("2*(size - m/2)+1): %d\n",2*(size - m/2)+1);
	printf("lastManStanding: %d\n", lastManStanding);
	if((2*(size - m/2)+1) == lastManStanding){
		printf("V(2^m + l) = 2l + 1, VERIFIED!!");
	}


	printf("\n");
	return 0;
}
