#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define FLOOR 1
#define CEIL 10000
#define TRUE 1
#define FALSE 0

typedef int bool;

typedef struct fibNodeTag{
	int key;
	struct fibNodeTag *parent;
	struct fibNodeTag *child;
	struct fibNodeTag *left;
	struct fibNodeTag *right;
	bool mark;
	int degree;
}fibNodeType, *fibNodePtr;

typedef struct  fibHeapTag{
	fibNodePtr min;
	int number;
}fibHeapType, *fibHeapPtr;

fibHeapPtr fibHeapInitialize(){
	fibHeapPtr fibHeap = (fibHeapPtr)malloc(1*sizeof(fibHeapType));
	fibHeap -> min = NULL;
	fibHeap -> number = 0;
	return fibHeap;
}

fibNodePtr fibNodeCreate(int value){
	fibNodePtr node;
	node = (fibNodePtr)malloc(1*sizeof(fibNodeType));
	node -> key = value;
	// node -> parent = NULL;
	// node -> child  = NULL;
	node -> left = node;
	node -> right = node;
	// node -> mark = FALSE;
	// node -> degree = 0;

	return node;
}

void fibHeapInsert(fibHeapPtr *H, fibNodePtr x){
	x -> degree = 0;
	x -> parent = NULL;
	x -> child  = NULL;
	x -> mark = FALSE;

	if((*H) -> min == NULL){
		(*H) -> min = x -> left = x -> right = x;
	}else{
		(*H) -> min -> left -> right = x;
		x->left = (*H) -> min->left;
		(*H) -> min -> left = x;
		x -> right = (*H) -> min;
		if(x -> key < (*H)-> min -> key){
			(*H) -> min = x;
		}
	}
	(*H) -> number = (*H)-> number + 1;
}

fibHeapPtr fibHeapUnion(fibHeapPtr H1, fibHeapPtr H2){
	fibHeapPtr H;
	H = fibHeapInitialize();
	H -> min = H1 -> min;

	if ( H -> min != NULL && H2 -> min != NULL){
		H -> min -> right -> left = H2 -> min -> left;
		H2 -> min ->left -> right = H -> min -> right;
		H -> min -> right = H2 -> min;
		H2 -> min -> left = H -> min;
	}
	if( (H1 -> min == NULL) || (H2 -> min != NULL && H2 -> min -> key < H1 -> min -> key)){
		H -> min = H2 -> min;
	}
	H -> number = H1 -> number + H2 -> number;
	return H;
}

void fibHeapDisplay(fibNodePtr min){
	fibNodePtr node = min;

	if (node == NULL){
		printf("The Heap is Empty\n");
		// printf("...\n");
		return ;
	}
	printf("\n");

	// printf("H -> min: %d; H-> degree: %d\n", min -> key, min -> degree);
	do{
		printf("%d", node -> key);
		if(node -> child != NULL){
			printf("...");
			fibHeapDisplay(node->child);
		}
		node = node->right;
		if (node != min){
			// printf("H -> min: %d\n",H -> min -> key);
			printf("-->");
		}
	}
	// while (0);
	while (node != min && node->right != NULL);
	printf("\n");
}

void exchageNode(fibNodePtr* x, fibNodePtr* y){
	fibNodePtr temp;

	temp = *x;
	*x = *y;
	*y = temp;
	return;
}

void fibHeapLink(fibHeapPtr H, fibNodePtr y, fibNodePtr x){
	// printf("fibHeapLink\n");
	// printf("x->key: %d, y->key: %d\n", x->key, y->key);
	y->left->right = y->right;
	y->right->left = y->left;

	if ( x->child != NULL ){
		x->child->left->right = y;
		y->left = x->child->left;
		x->child->left = y;
		y->right = x->child;
	}
	else{
		x->child = y;
		y->right = y;
		y->left = y;
	}
	y -> parent = x;
	x -> degree = x -> degree + 1;
	y->mark = FALSE;
	return;
}

void consolidate(fibHeapPtr H){

	int i, rootSize, d;
	int maxDegree;
	fibNodePtr *A, *rootList;
	fibNodePtr w, next, x, y, temp;

	maxDegree = (int)(floor(log((double)(H -> number))/log((double)(1 + sqrt((double)(5)))/2)));
	// printf("maxDegree: %d\n",maxDegree);

	A = (fibNodePtr*)malloc((maxDegree+2)*sizeof(fibNodePtr)); // plus two both for indexing to max degree and so A[maxDegree+1] == NIL
	for(i = 0 ; i < maxDegree + 2 ; i++){
		A[i] = NULL;
	}


	w = H -> min;
	rootSize = 0;
	next = w;
	// printf("Calculating Root Size\n");
	do{
		rootSize++;
		// printf("%d-->",next->key);
		next = next->right;
	} while ( next != w );
	// printf("\n");
	// printf("rootSize: %d\n", rootSize);

	rootList = (fibNodePtr*)malloc((rootSize)*sizeof(fibNodePtr));
	for ( i = 0; i < rootSize; i++ ){
		rootList[i] = next;
		next = next->right;
	}

	// printf("for each node W in the root list of H\n");
	for ( i = 0; i < rootSize; i++ ){
		w = rootList[i];
		// printf("%d-->",w->key);
		x = w;
		d = x -> degree;
		while ( A[d] != NULL ){
			// printf("d:%d\n",d);
			y = A[d];
			if ( x->key > y->key ){
				// temp = x;
				// x = y;
				// y = temp;
				// printf("x -> key: %d y -> key: %d\n", x -> key , y -> key );
				exchageNode(&x,&y);
				// printf("x -> key: %d y -> key: %d\n", x -> key , y -> key );
			}

			fibHeapLink(H,y,x);
			A[d] = NULL;
			d = d + 1; // 13
		}
		A[d] = x; // 14
	}

	// printf("\n");
	// for(i = 0 ; i < rootSize ; i++){
	// 	free(rootList[i]);
	// }
	// free(rootList);


	H -> min = NULL; // 15
	for ( i = 0; i < maxDegree+2; i++ ){ // 16
		if ( A[i] != NULL ){ // 17
			if ( H->min == NULL){ 	// 18
				A[i]->left = A[i]->right = A[i]; //19
				H -> min = A[i];//20
			}else{
				// 21
				H->min->left->right = A[i];
				A[i]->left = H->min->left;
				H->min->left = A[i];
				A[i]->right = H->min;
				if ( A[i]->key < H->min->key ){
					H->min = A[i];
				}
			}
		}
	}
	// for(i = 0; i < maxDegree+2; i++){
	// 	free(A[i]);
	// }
	// free(A);

	return;
}

fibNodePtr fibHeapExtractMin(fibHeapPtr H){
	// printf("fibHeapExtractMin key:%d\n", H -> min -> key);
	int i;
	fibNodePtr z, x, next;
	fibNodePtr *childList;

	z = (H) -> min;
	// z -> key = -100;
	if(z != NULL){

		x = z -> child;
		if(x != NULL){
			// printf("z->degree: %d\n",z->degree);
			childList = (fibNodePtr*)malloc((z-> degree)*sizeof(fibNodePtr));
			next = x;
			for(i = 0; i < z->degree; i++ ){
				childList[i] = next;
				// printf("next->key: %d\n",next->key);
				next = next ->right;
			}
			for(i = 0 ; i < z->degree ; i++){
				x = childList[i];
				H -> min -> left -> right = x;
				x -> left = H -> min -> left;
				H -> min -> left = x;
				x -> right = H -> min;
				x-> parent = NULL;
			}

			// for(i = 0 ; i < z->degree ; i++){
			// 	free(childList[i]);
			// }
			// free(childList);
		}
		z->left->right = z->right;
		z->right->left = z->left;

		if( z == z-> right){
			H -> min = NULL;
		}else{
			H -> min = z-> right;
		// printf("z-> right -> key: %d\n", z -> right -> key);
		// printf("H-> min -> key: %d\n", H -> min -> key);
		// 	printf("z-> right -> right -> key: %d\n", z -> right -> right -> key);
			// printf("TO CONSOLIDATE\n");
			consolidate(H);
		}
		H -> number = H -> number - 1;
	}
	return z;
}

void cut(fibHeapPtr H, fibNodePtr x, fibNodePtr y){
	// 1
	printf("CUT x->key: %d; y->key: %d\n",x->key, y->key);
	if (x->right == x){
		y->child = NULL;
	}else{
		x->right->left = x->left;
		x->left->right = x->right;
		if ( y->child == x ){
			y->child = x->right;
		}
	}
	y->degree = y->degree - 1;
	//2
	H->min->right->left = x;
	x->right = H->min->right;
	H->min->right = x;
	x->left = H->min;
	x->parent = NULL;
	//4
	x->mark = FALSE;
}

void cascadingCut(fibHeapPtr H, fibNodePtr y ){
	fibNodePtr z;
	z = y->parent; //// 1

	if ( z != NULL ){
		if ( y->mark == FALSE ){
			y->mark = TRUE; //4
		}else{
			cut(H,y,z); //6
			cascadingCut(H,z);
		}
	}
}


void fibHeapDecKey(fibHeapPtr H, fibNodePtr x, int k ){
	printf("fibHeapDecKey x->key: %d, k: %d\n",x->key,k);
	fibNodePtr y;
	if ( k > x->key ){ //1
		printf( "New key is greater than current key");
		return;
	}
	x->key = k;
	y = x->parent;
	// printf("x->parent->key: %d, x->key: %d\n",x->parent->key, x->key);
	if (y != NULL && x->key < y->key){
		printf("If condition\n");
		cut(H,x,y); // 6
		cascadingCut(H,y);
	}
	// 8
	if (x->key < H->min->key){
		// 9
		H->min = x;
	}
}


void fibHeapDelete(fibHeapPtr H, fibNodePtr x ){
	fibHeapDecKey(H,x,INT_MIN);
	fibNodePtr fn = fibHeapExtractMin(H);
	free(fn);
}


int* genUniRandList(int lowValue, int HigValue, int size){
	printf("Generate Unique\n");
	int i, j, count = 0;
	int temp = rand()%HigValue + lowValue;

	int *list = (int*)calloc(size,sizeof(int));

	for(i = 0 ; i < size ; i++){
		//printf("[%d]: %d\n",i,temp);
		for(j = 0; j < i ; j++){
			if(list[j] == temp){
				temp = rand()%HigValue + lowValue;
				j = 0;
			}
		}
		//printf("[%d]: %d\n",i,temp);
		list[i] = temp;
	}
	return list;
}

void printList(int* list, int size){
	int i;
	printf("size of list: %d\n",size);
	for(i = 0; i < size ; i++){
		printf("%d, ",list[i]);
	}
	return;
}

void print2DList(int **list2D, int row, int col){
	int i,j;
	for(i = 0; i < row; i++){
		for(j =0; j < col; j++){
			printf("%d,",list2D[i][j]);
		}
		printf("\n");
	}
	return;
}


void merge(int array[], int left, int mid, int right)
{
    int i, j, k;
    int node1 = mid - left + 1;
    int node2 =  right - mid;
    int L[node1], R[node2];

    for(i = 0; i < node1; i++)
        L[i] = array[left + i];
    for(j = 0; j < node2; j++)
        R[j] = array[mid + 1+ j];

    i = 0;
    j = 0;
    k = left;
    while (i < node1 && j < node2){
        if (L[i] <= R[j]){
            array[k] = L[i];
            i++;
        }else{
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < node1){
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < node2){
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int left, int right){
    if (left < right){
        int mid = left+(right-left)/2;
        mergeSort(array, left, mid);
        mergeSort(array, mid+1, right);
        merge(array, left, mid, right);
        }
}

int findMax(int a , int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int binarySearch( int * list, int left , int right, int key){
	if (right >= left){
		int mid = left + (right-left)/2;

		if(list[mid] == key){
			return mid;
		}
		if(list[mid] > key){
			binarySearch(list, left, mid - 1 , key);
		}else{
			binarySearch(list, mid + 1, right, key);

		}
	}
	return -1;
}

int main(){
	printf("<< Assignment:9 Fibbonacci Heaps >> \n");

	int k,m,i,j;
	int *list, *globalSortedList;
	int **list2D;

	fibHeapPtr H1, H2, H;
	fibNodePtr node, maxNode;

	// int maxListValue;

	printf("Please enter the value of k\n");
	scanf("%d",&k);
	// k = 10;
	printf("Please enter the value of m\n");
	scanf("%d",&m);
	// m = 15;

	// list = (int*)malloc((k*m)*sizeof(int));

	list = genUniRandList(FLOOR, CEIL, k*m);
	printList(list, k*m);
	printf("\n");

	list2D = (int**)malloc(k*sizeof(int*));
	for(j = 0; j < k ; j++){
		list2D[j] = (int*)malloc(m*sizeof(int));
	}


	int count = 0;
	for(i = 0 ; i < k; i ++){
		for(j = 0; j < m ; j++){
			list2D[i][j] = list[count];
			count++;
		}
	}

	printf("Generated 2D Array\n");
	print2DList(list2D, k ,m);

	for(i = 0; i < k ; i++){
		mergeSort(list2D[i], 0 , m-1);
	}

	printf("Sorted Row-Wise\n");
	print2DList(list2D, k ,m);

	H = fibHeapInitialize();
	// H1 = fibHeapInitialize();

	int finalMax = INT_MIN;

	for(i = 0 ; i < k ; i++){
		printf("Processing list to form Heap: %d\n",i);
		H1 = fibHeapInitialize();
		for(j = 0 ; j < m ; j++){

			printf("Inserting Node: %d\n", list2D[i][j]);

			// finalMax = findMax(finalMax,list2D[i][j]));
			node = fibNodeCreate(list2D[i][j]);
			if(finalMax < list2D[i][j]){
				finalMax =  list2D[i][j];
				maxNode = node;
			}
			fibHeapInsert(&H1, node);
		}
		fibHeapDisplay(H1 -> min);

		H = fibHeapUnion(H, H1);
		printf("The United heap is:\n");
		fibHeapDisplay(H -> min);
	}

	printf("Final Global Heap is (min is: %d)\n", H -> min -> key);
	fibHeapDisplay(H -> min);

	printf("Decresing Key: %d to %d\n",maxNode->key, H->min->key-1);
	fibHeapDecKey(H, maxNode, H->min->key-1);

	fibHeapDisplay(H -> min);

	globalSortedList = (int*)malloc(sizeof(int));
	for(i = 0 ; i < k*m ; i++){
		globalSortedList[i] = H->min->key;
		fibHeapExtractMin(H);
	}

	printList(globalSortedList, k*m);
	printf("\n");

/*printf("Fibbonacci Heap Initialisation\n");
	fibHeapDisplay(H -> min);

	printf("Inserting: 1\n");
	node = fibNodeCreate(1);
	fibHeapInsert(&H, node);
	printf("Inserting: 2\n");
	node = fibNodeCreate(2);
	fibHeapInsert(&H, node);
	printf("Inserting: 3\n");
	node = fibNodeCreate(3);
	fibHeapInsert(&H, node);
	printf("Inserting: 4\n");
	node = fibNodeCreate(4);
	fibHeapInsert(&H, node);
	printf("Inserting: 5\n");
	node = fibNodeCreate(5);
	fibHeapInsert(&H, node);
	printf("The Fibonacci Heap H1 is\n");
	fibHeapDisplay(H -> min);

	fibHeapPtr H2;
	H2 = fibHeapInitialize();
	node = fibNodeCreate(11);
	fibHeapInsert(&H2, node);
	printf("The Fibonacci Heap H2 is \n");
	fibHeapDisplay(H2 -> min);

	printf("<<<Union of H1 and H2>>>\n");
	H = fibHeapUnion (H2,H);
	fibHeapDisplay(H -> min);

	printf("<<<Extract Minimum: %d>>>\n", H->min->key);
	// printf("H->min->key: %d, H->number: %d\n", H->min->key, H->number);
	fibHeapExtractMin(H);
	// printf("H->min->key: %d, H->number: %d\n", H->min->key, H->number);
	fibHeapDisplay(H -> min);

	printf("<<<Extract Minimum: %d>>>\n", H->min->key);
	// printf("H->min->key: %d, H->number: %d\n", H->min->key, H->number);
	// printf("H->min->right->key: %d, H->number: %d\n", H->min->right->key, H->number);
	fibHeapExtractMin(H);
	// printf("H->min->key: %d, H->number: %d\n", H->min->key, H->number);
	fibHeapDisplay(H -> min);

	// printf("<<<Decrease key: %d>>>\n", H->min->child->right->parent->key);
	printf("<<<Decrease key: %d>>>\n", H->min->child->key);
	fibHeapDecKey(H, H->min->child,2);
	fibHeapDisplay(H -> min);

*/
	return 0;
}
