#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct coordinateTag{
	int x;
	int y;
}coordinateType, *coordinatePtr;

void fillBoard(int **board, coordinateType ref,int maxIndex, coordinateType filled){
// printf("funtion called for Ref: %d,%d, MaxIndex: %d,Filled %d %d\n",ref.x, ref.y, maxIndex, filled.x, filled.y);

coordinateType newRef, newFill1, newFill4, newFill2, newFill3, centre;
int mid = (maxIndex+1)/2;


centre.x = ref.x + mid; centre.y = ref.y + mid;

if(maxIndex == 1){

	if(board[centre.x-1][centre.y-1]!=0 && board[centre.x][centre.y-1]==0 && board[centre.x][centre.y] ==0 && board[centre.x-1][centre.y]==0){
		// printf("Condition 1 \n");
		board[centre.x][centre.y-1] = 2;
		board[centre.x][centre.y] = 2;
		board[centre.x-1][centre.y] = 2;
		printf("Type 2 at location: (%d,%d) ,\n",centre.x,centre.y);
	}
	else if(board[centre.x-1][centre.y-1]==0 && board[centre.x][centre.y-1]!=0 && board[centre.x][centre.y] ==0 && board[centre.x-1][centre.y]==0){
		// printf("Condition 2 \n");
		board[centre.x-1][centre.y-1] = 3;
		board[centre.x][centre.y] = 3;
		board[centre.x-1][centre.y] = 3;
		printf("Type 3 at location: (%d,%d) ,\n",centre.x-1,centre.y);
	}
	else if(board[centre.x-1][centre.y-1]==0 && board[centre.x][centre.y-1]==0 && board[centre.x][centre.y] !=0 && board[centre.x-1][centre.y]==0){
		// printf("Condition 3 \n");
		board[centre.x-1][centre.y-1] = 4;
		board[centre.x][centre.y-1] = 4;
		board[centre.x-1][centre.y] = 4;
		printf("Type 4 at location: (%d,%d) ,\n",centre.x-1,centre.y-1);
	}
	else if(board[centre.x-1][centre.y-1]==0 && board[centre.x][centre.y-1]==0 && board[centre.x][centre.y] ==0 && board[centre.x-1][centre.y]!=0){
		// printf("Condition 4 \n");
		board[centre.x-1][centre.y-1] = 5;
		board[centre.x][centre.y-1] = 5;
		board[centre.x][centre.y] = 5;
		printf("Type 5 at location: (%d,%d) ,\n",centre.x,centre.y-1);
	}

	return;
}


// centre.x = ref.x + mid; centre.y = ref.y + mid;

	//box1
	if(filled.x < centre.x && filled.y < centre.y){
		board[centre.x][centre.y-1] = 2; //box 2
		board[centre.x][centre.y] = 2; //box3
		board[centre.x-1][centre.y] = 2; //box4
		printf("Type 2 at location: (%d,%d) ,\n",centre.x,centre.y);

		newFill1.x = filled.x; newFill1.y = filled.y;
		newFill2.x = centre.x; newFill2.y = centre.y-1;
		newFill3.x = centre.x; newFill3.y = centre.y;
		newFill4.x = centre.x-1; newFill4.y = centre.y;

	}
	//box2
	else if(filled.x >= centre.x && filled.y < centre.y){
		board[centre.x][centre.y] = 3; //box3
		board[centre.x-1][centre.y-1] = 3; //box1
		board[centre.x-1][centre.y] = 3;//box4
		printf("Type 3 at location: (%d,%d) ,\n",centre.x-1,centre.y);

		newFill1.x = centre.x-1; newFill1.y = centre.y-1;
		newFill2.x = filled.x; newFill2.y = filled.y;
		newFill3.x = centre.x; newFill3.y = centre.y;
		newFill4.x = centre.x-1; newFill4.y = centre.y;
	}
	//box3
	else if(filled.x >= centre.x && filled.y >= centre.y){
		board[centre.x-1][centre.y-1] = 4;
		board[centre.x][centre.y-1] = 4;
		board[centre.x-1][centre.y] = 4;
		printf("Type 4 at location: (%d,%d) ,\n",centre.x-1,centre.y-1);

		newFill1.x = centre.x-1; newFill1.y = centre.y-1;
		newFill2.x = centre.x; newFill2.y = filled.y-1;
		newFill3.x = filled.x; newFill3.y = filled.y;
		newFill4.x = centre.x-1; newFill4.y = centre.y;
	}
	//box4
	else if(filled.x < centre.x && filled.y >= centre.y){
		board[centre.x-1][centre.y-1] = 5;
		board[centre.x][centre.y-1] = 5;
		board[centre.x][centre.y] = 5;
		printf("Type 5 at location: (%d,%d) ,\n",centre.x,centre.y-1);

		newFill1.x = centre.x-1; newFill1.y = centre.y-1;
		newFill2.x = centre.x; newFill2.y = filled.y-1;
		newFill3.x = centre.x; newFill3.y = centre.y;
		newFill4.x = filled.x; newFill4.y = filled.y;
	}
	//

	newRef.x = ref.x;
	newRef.y = ref.y;
	fillBoard(board, newRef, mid-1, newFill1);

	newRef.x = ref.x+mid;
	newRef.y = ref.y;
	fillBoard(board, newRef, mid-1, newFill2);

	newRef.x = ref.x+mid;
	newRef.y = ref.y+mid;
	fillBoard(board, newRef, mid-1, newFill3);

	newRef.x = ref.x;
	newRef.y = ref.y+mid;
	fillBoard(board, newRef, mid-1, newFill4);

}




int main(){
	int i,j;
	int n,sideLength;
	int **board;
	coordinateType filled,reference;

	printf("Please Enter n side length of the board pow(2,n): ");
	scanf("%d", &n);
	sideLength = pow(2,n);
	printf("Please Enter the location (x,y) of missing cell ~$x y\n");
	scanf("%d%d", &(filled.x),&(filled.y));
	printf("Entered location is (%d,%d)\n",filled.x,filled.y);
	while(filled.x > sideLength || filled.y > sideLength){
		printf("Invalid Co-ordinates\nPlease Enter Again\n");
		scanf("%d%d", &(filled.x),&(filled.y));
		printf("Entered location is (%d,%d)\n",filled.x,filled.y);
	}



	board = (int**)calloc(sideLength , sizeof(int*));
	for(i= 0; i<sideLength ; i++){
		board[i] = (int*)calloc(sideLength, sizeof(int));
	}

	board[filled.x][filled.y] = 1;
	printf("Board allocated:  \n");
	for(i= 0 ; i< sideLength; i++){
		for(j=0;j<sideLength ; j++){
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Type 2: _| Type 3: |''' Type 4: |''' Type 5: |_" );
	reference.x = 0; reference.y =0;
	fillBoard(board, reference ,sideLength-1, filled);
	for(i= 0 ; i< sideLength; i++){
		for(j=0;j<sideLength ; j++){
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}



	return 0;
}
