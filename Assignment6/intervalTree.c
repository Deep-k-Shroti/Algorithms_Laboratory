#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct nodeTag{
	int key;
	struct nodeTag* next;
}nodeType , *nodePtr;

typedef struct intervalTag{
	int lowerValue;
	int upperValue;
	int height;
	struct intervalTag *lChild;
	struct intervalTag *rChild;
	nodePtr list;
}intervalType , *intervalPtr;

int *generateRandom(int lowerLimit, int upperLimit, int size){
	int i;
	int *randomArray = (int*)malloc(size*sizeof(int));

	for(i = 0 ; i < size; i++){
		randomArray[i] = rand()%(upperLimit - lowerLimit + 1)+lowerLimit;
		// printf("%d,", randomArray[i]);
	}
	return randomArray;
}

int max(int a ,int b){
	if(a  > b){
		return a;
	}else{
		return b;
	}
}

void printList(nodePtr head){

	if(head == NULL){
		printf("...");
	}
	nodePtr temp = head;
	while(temp != NULL){
		printf("%d, ", temp -> key);
		temp = temp->next;
	}
}

nodePtr newNode(int value){
	nodePtr newNode = (nodePtr)malloc(sizeof(nodeType));
	newNode -> key  = value;
	newNode -> next =  NULL;
	return newNode;
}

void sortedInsert(nodeType** head, nodePtr newNode){
	nodePtr currentNode ;

	if (*head == NULL || (*head)-> key >= newNode-> key){
		newNode -> next = *head;
		*head = newNode;
	}
	else{
		currentNode  = *head;
		while (currentNode -> next!=NULL && currentNode -> next-> key < newNode -> key){
			currentNode  = currentNode -> next;
		}
		newNode -> next = currentNode -> next;
		currentNode -> next = newNode;
	}
	return;
}

void  PRETTY_PRINT (intervalPtr root){
	int i;
	if(root == NULL){
		return;
	}
	PRETTY_PRINT(root -> lChild);
	for(i = 0 ; i < root -> height; i++){
		printf("\t");
	}
	printf("[%d,%d] ", root -> lowerValue , root -> upperValue);
	printList(root -> list);
	printf("\n");
	PRETTY_PRINT(root -> rChild);
	return;
}


// void INSERT(intervalType *root , int key){
// 	if(root == NULL){
// 		return;
// 	}
//
// 	if(key >= root -> lowerValue && key <= root -> upperValue){
// 		sortedInsert(&(root -> list), newNode(key));
// 	}
// 	if(key < root -> lowerValue){
// 		INSERT(root -> lChild , key);
// 	}
//
// 	if(key > root -> upperValue){
// 		INSERT(root -> rChild, key);
// 	}
// 	return;
// }


void INSERT(intervalType *root , int key){
	if(root == NULL){
		return;
	}

	if(key >= root -> lowerValue && key <= root -> upperValue){
		sortedInsert(&(root -> list), newNode(key));

	}
	if(key < root -> lowerValue){
		INSERT(root -> lChild , key);
	}

	if(key > root -> upperValue){
		INSERT(root -> rChild, key);
	}


	if( (root)-> rChild == NULL && (root) -> lChild == NULL){
		(root) -> height = 0;
	}else if( (root)-> rChild == NULL){
		(root) -> height = (root) -> lChild -> height + 1;
	}else if( (root) -> lChild == NULL){
		(root) -> height = (root) -> rChild -> height + 1;
	}else{
		(root) -> height = max((root) -> lChild -> height , (root) -> rChild -> height) + 1;
	}

	return;
}

void append(nodePtr list, nodeType **superList){

	// (*superList) -> next = list;

	// while( (*superList) -> next != NULL){
	// 	(*superList) = (*superList) -> next;
	// }

	nodePtr temp = list;
	while(temp !=NULL){
		nodePtr node = (nodePtr)malloc(sizeof(nodeType));
		node -> key = temp -> key;
		// node -> next = temp -> next;

		(*superList) -> next = node;
		(*superList) = (*superList)-> next;
		// if(node -> next != NULL){
		// 	(*superList) = node -> next;
		// 	(*)
		// }
			temp = temp -> next;
	}

	return;
}

void  getList (intervalPtr root, nodeType **superList){
	int i;
	if(root == NULL){

		return;
	}

	getList(root -> lChild , superList);
	append(root -> list, superList);
	root -> list = NULL;
	// for(i = 0 ; i < root -> height; i++){
	// 	printf("\t");
	// }
	// printf("[%d,%d] ", root -> lowerValue , root -> upperValue);

	// printList(root -> list);
	// printf("\n");
	getList(root -> rChild , superList);
	return;
}

void insertlist (intervalType *root , nodePtr list){
	// printf("INSERTING LIST");
	if(root == NULL){
		return;
	}

	nodePtr temp = list;
	while(temp != NULL){
		// printf("%d,", temp -> key );
		INSERT(root , temp -> key);
		temp = temp -> next;
	}
	return;
}


intervalType *MERGE(intervalType *root, int insertLower, int insertUpper){
    if(root == NULL){
		return NULL;
	}

	if((insertLower > insertUpper)){
		root -> list = NULL;
		return NULL;
	}

    intervalType *temp = (intervalType *)malloc( sizeof(intervalType) );
    *temp = *root;

    if( insertUpper < root->lowerValue){
        temp->lChild = MERGE( root->lChild, insertLower, insertUpper );
		// temp -> lChild -> list = root -> lChild -> list;
		// getList(temp);
		// temp -> list = NULL;
        return temp;
    }

    if( insertLower > root->upperValue){
        temp->rChild = MERGE( root->rChild, insertLower, insertUpper );
		// temp -> lChild -> list = root -> lChild -> list;
		// getList(temp);
		// temp -> list = NULL;
        return temp;
    }

    // printf("Replacing [%d, %d] by [%d, %d]\n", root->lowerValue, root->upperValue, insertLower, insertUpper);
    temp->lowerValue = insertLower;
    temp->upperValue = insertUpper;

    // intervalType *p;

    if( (insertLower == root->lowerValue) && (insertUpper > root->lowerValue) && (insertUpper < root->upperValue)){

        temp->lChild = root->lChild;
        temp->rChild = NULL;
		// getList(temp);
		// temp -> list = NULL;
        return temp;
    }

    else if( (insertLower > root->lowerValue) && (insertLower < root->upperValue) && (insertUpper == root->upperValue )){

        temp->lChild = NULL;
        temp->rChild = root->rChild;
		// getList(temp);
		// temp -> list = NULL;
        return temp;

    }
    else if( (insertLower == root->lowerValue) && (insertUpper == root->upperValue)){
		temp->lChild = root->lChild;
        temp->rChild = root->rChild;
		// getList(temp);
		// temp -> list = NULL;
        return temp;
    }


    if( root->lChild == NULL){
		temp->lChild = NULL;
	}else{
		temp->lChild   = MERGE( root->lChild, (root->lChild)->lowerValue, insertLower-1);
		// getList(temp);
	}

    if(root->rChild == NULL){
		temp->rChild = NULL;
	}else{
		temp->rChild  = MERGE( root->rChild, insertUpper+1, (root->rChild)->upperValue);
		// getList(temp);
	}


	// temp -> list = NULL;
    return (temp);

}

intervalType *myMerge(int lowerLimit, int upperLimit, int newNumberInterval, intervalType *root){
	int i;

	intervalType *modifiedRoot;
	nodePtr superList = (nodePtr)malloc(1*sizeof(nodeType));
	nodePtr backUpList = superList;
	getList(root, &superList);
	// modifiedRoot = MERGE(root , insertLower , insertUpper);

	int sizeofInterval = (upperLimit - lowerLimit + 1)/ newNumberInterval;

	for(i = 1 ; i < newNumberInterval; i++){
		// printf("[%d,%d],", lowerLimit + (i-1)*sizeofInterval , lowerLimit + (i)*sizeofInterval - 1);
		root = MERGE(root , lowerLimit + (i-1)*sizeofInterval  , lowerLimit + (i)*sizeofInterval - 1);
	}
	if(lowerLimit + (i-1)*sizeofInterval < upperLimit){
		// printf("[%d,%d]\n", lowerLimit + (i-1)*sizeofInterval, upperLimit);
		root = MERGE(root , lowerLimit + (i-1)*sizeofInterval , upperLimit);
	}
	// printf("LIST\n");
	// printList(backUpList -> next);
	// printf("\n");

	insertlist(root , backUpList -> next);
	return root;
}


void CREATE_INTERVAL_TREE(int lowerLimit, int upperLimit , int numberInterval , intervalType** root){
	// printf("lowerLimit: %d ,upperLimit: %d ,numberInterval: %d\n",lowerLimit,upperLimit, numberInterval );
	int intervalSize = (upperLimit - lowerLimit + 1)/numberInterval;
	// printf("intervalSize: %d\n", intervalSize);

	if(numberInterval == 0 || lowerLimit > upperLimit){
		return;
	}
	if(numberInterval == 1){

		(*root) = (intervalPtr)malloc(1*sizeof(intervalType));
		(*root) -> lowerValue = lowerLimit;
		(*root) -> upperValue = upperLimit;
		(*root) -> lChild = NULL;
		(*root) -> rChild = NULL;
		(*root) -> height = 0;
		(*root) -> list = (nodePtr)malloc(1*sizeof(nodeType));
		(*root) -> list = NULL;

		// printf("(*root) -> lowerValue: %d\n", (*root) -> lowerValue);
		// printf("(*root) -> upperValue: %d\n", (*root) -> upperValue );
		// printf("\n\n");

		return;
	}

	// root = (intervalPtr)malloc(1*sizeof(intervalType));
	(*root) -> list = (nodePtr)malloc(1*sizeof(nodeType));
	// (*root) -> list -> next = NULL;
	(*root) -> list = NULL;
	// root -> height = 0;

	(*root) -> rChild = (intervalPtr)malloc(1*sizeof(intervalType));
	(*root) -> lChild = (intervalPtr)malloc(1*sizeof(intervalType));


	if(numberInterval == 2){
		(*root) -> lowerValue = lowerLimit;
		(*root) -> upperValue = lowerLimit + intervalSize -1;
		// printf("(*root) -> lowerValue: %d\n", (*root) -> lowerValue);
		// printf("(*root) -> upperValue: %d\n", (*root) -> upperValue );
		(*root) -> lChild = NULL;
		// CREATE_INTERVAL_TREE(lowerLimit, (root -> lowerValue) - 1, numberInterval/2 , root -> lChild);
		CREATE_INTERVAL_TREE(((*root) -> upperValue) + 1 , upperLimit , numberInterval - numberInterval/2 , &((*root) -> rChild));

	}else{
		(*root) -> lowerValue = (lowerLimit + ((numberInterval/2)*intervalSize));
		(*root) -> upperValue = (lowerLimit + (numberInterval/2 + 1)*intervalSize -1);
		// printf("(*root) -> lowerValue: %d\n", (*root) -> lowerValue);
		// printf("(*root) -> upperValue: %d\n", (*root) -> upperValue );

		CREATE_INTERVAL_TREE(lowerLimit, ((*root) -> lowerValue) - 1, numberInterval/2 , &((*root) -> lChild));
		CREATE_INTERVAL_TREE(((*root) -> upperValue) + 1 , upperLimit , numberInterval - numberInterval/2 - 1 , &((*root) -> rChild));
	}

	if( (*root)-> rChild == NULL && (*root) -> lChild == NULL){
		(*root) -> height = 0;
	}else if( (*root)-> rChild == NULL){
		(*root) -> height = (*root) -> lChild -> height + 1;
	}else if( (*root) -> lChild == NULL){
		(*root) -> height = (*root) -> rChild -> height + 1;
	}else{
		(*root) -> height = max((*root) -> lChild -> height , (*root) -> rChild -> height) + 1;
	}
	// printf("root -> height: %d\n",root -> height);
	return;
}


int  main(){
	int i;
	int lowerLimit, upperLimit;
	int numberInterval, newNumberInterval;
	int  insertSize;
	int *randomArray;
	intervalPtr modifiedRoot;
	nodePtr list;
	intervalPtr root;
	root = (intervalPtr)malloc(1*sizeof(intervalType));

	printf("Please enter the lower bound, upper bound, number of interval for the Interval Tree, Example (l,u,n)\n");
	scanf("%d %d %d", &lowerLimit, &upperLimit, &numberInterval);
	// lowerLimit = 1;
	// upperLimit = 55;
	// numberInterval = 11;

	printf("Enter the number of positive integers to insert in Interval Tree\n");
	scanf("%d", &insertSize);
	// insertSize = 10;

	printf("Enter an integer m < n to create a new Innterval Tree\n");
	scanf("%d", &newNumberInterval);
	// newNumberInterval = 2;

	CREATE_INTERVAL_TREE(lowerLimit , upperLimit , numberInterval , &root);
	printf("\n\n");
	PRETTY_PRINT(root);

	// INSERT(root ,27);
	// INSERT(root ,27);
	// INSERT(root ,28);
	// INSERT(root ,12);
	// INSERT(root ,13);
	// INSERT(root ,1);
	// INSERT(root ,4);
	// INSERT(root ,17);
	// INSERT(root ,18);
	// INSERT(root ,6);
	// INSERT(root ,7);
	// INSERT(root ,8);
	// INSERT(root ,22);
	// INSERT(root ,42);
	// INSERT(root ,37);
	// INSERT(root ,38);
	// INSERT(root ,42);
	// INSERT(root ,32);
	// INSERT(root ,33);
	// INSERT(root ,47);
	// INSERT(root ,51);
	// INSERT(root ,52);

	randomArray = generateRandom(lowerLimit, upperLimit, insertSize);
	for(i = 0; i < insertSize ; i++){
		// printf("%d,", randomArray[i]);
		INSERT(root , randomArray[i]);
	}
	printf("\n\n");
	PRETTY_PRINT(root);
	printf("\n\n");

	modifiedRoot = myMerge(lowerLimit, upperLimit, newNumberInterval, root);
		// int insertLower, insertUpper;
	// insertLower = 1;
	// insertUpper = 18;
	// printf("\nMERGE [%d ,%d]\n\n", insertLower , insertUpper );
	// root = myMerge(root , insertLower, insertUpper);
	// printf("\n\n");
	// PRETTY_PRINT(root);
	//
	// insertLower = 19;
	// insertUpper = 36;
	// printf("\nMERGE [%d ,%d]\n\n", insertLower , insertUpper );
	// root = myMerge(root , insertLower, insertUpper);
	// printf("\n\n");
	// PRETTY_PRINT(root);
	//
	// insertLower = 37;
	// insertUpper = 55;
	// printf("\nMERGE [%d ,%d]\n\n", insertLower , insertUpper );
	// root = myMerge(root , insertLower, insertUpper);

	// printf("FINAL\n\n");
	PRETTY_PRINT(modifiedRoot);


	printf("\n");
	return 0;
}
