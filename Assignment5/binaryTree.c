#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100

typedef struct nodeTag{
	int value;
	struct nodeTag *left;
	struct nodeTag *right;
}treeNode;

typedef treeNode *binaryTree;

int findMaxSum2(treeNode *root, treeNode** path){

    int sumK, sumL, sumR;

    if(root == NULL){
        treeNode temp = {INT_MIN, NULL, NULL};
        *path = NULL;
        return 0;
    }

    treeNode *leftSub = (treeNode *)malloc(sizeof(treeNode));
    treeNode *rightSub = (treeNode *)malloc(sizeof(treeNode));
    sumL = findMaxSum2( root->left, &leftSub );
    sumR = findMaxSum2( root->right, &rightSub );

    if( sumL > sumR )
        if((root->value + sumL) >= 0){
            (*path)->value = (root->value);
            (*path)->left = leftSub;
            (*path)->right = NULL;
            return (sumL + root->value);
        }
        else{
            (*path)->value = (root->value);
            (*path)->left = NULL;
            (*path)->right = NULL;

            return (root->value);
        }
    else
        if( (root->value + sumR) >= 0){
            (*path)->value = (root->value);
            (*path)->left = rightSub;
            (*path)->right = NULL;
            return (sumR + root->value);
        }
        else{
            (*path)->value = (root->value);
            (*path)->left = rightSub;
            (*path)->right = NULL;


            return (root->value);
        }


}

void findMaxNodes(treeNode *root, treeNode** path, int *maxVal){

    int sumK, sumL, sumR;

    if(root == NULL){
        treeNode temp = {INT_MIN, NULL, NULL};
        *path = NULL;
        return ;
    }


    treeNode *leftSub = (treeNode *)malloc(sizeof(treeNode));
    treeNode *rightSub = (treeNode *)malloc(sizeof(treeNode));
    findMaxNodes( root->left, &leftSub, maxVal );
    findMaxNodes( root->right, &rightSub, maxVal );

    sumL = findMaxSum2(root->left, &leftSub);
    sumR = findMaxSum2(root->right, &rightSub);

    if((sumL + sumR + root->value) > *maxVal){
        (*path)->value = root->value;
        (*path)->left = leftSub;
        (*path)->right = rightSub;
        *maxVal = sumL + sumR + root->value;
    }
    else if(root->value >= 0){
        if( (sumL > sumR) && ((sumL + root->value) > *maxVal)){
            (*path)->value = (root->value);
            (*path)->left = leftSub;
            (*path)->right = NULL;
            *maxVal = sumL + root->value;
        }
        else if( (sumL + root->value) > *maxVal) {
            (*path)->value = (root->value);
            (*path)->left = rightSub;
            (*path)->right = NULL;
            *maxVal = sumR + root->value;
        }
    }
    else{
        if( (sumL > sumR) && ((sumL + root->value) > *maxVal)){
            (*path) = leftSub;
            *maxVal = sumL;
        }
        else if(((sumL + root->value) > *maxVal)){
            (*path)= rightSub;
            *maxVal = sumR;
        }
    }

}

treeNode *generateTree(int n){

	treeNode *leaf;
	int m;

	if(n == 0){
		return NULL;
	}

	leaf = (treeNode*)malloc(1*sizeof(treeNode));
	leaf -> value = rand()%200 + (-100);

	m = (int)((1.0*(rand()%3)/10 + 0.4)*n);

	leaf -> left  = generateTree(m);
	leaf -> right = generateTree(n-m-1);

	return leaf;
}

int max(int a , int b){
	if(a > b)
		return a;
	else
		return b;
}


int findMaxSum(binaryTree tree, int sum){

	if(tree == NULL)
		return sum;
	sum = sum + tree -> value;
	int leftSum , rightSum;
	leftSum = findMaxSum(tree -> left , sum);
	rightSum = findMaxSum(tree -> right, sum);

	sum = max(leftSum , rightSum);

	return sum;
}

void findPath(binaryTree tree, int maxSum , int presentSum){

	if(tree == NULL)
		return;

	printf("%d ", tree -> value);
	presentSum = presentSum + tree -> value;
	if((tree -> right == NULL) && (tree -> left == NULL)){
		// printf("\n");
		return;
	}
	int temp;
	temp = findMaxSum(tree -> right , presentSum);
	if(temp == maxSum){
		findPath(tree -> right, maxSum, presentSum);
	}else{
		findPath(tree -> left , maxSum , presentSum);
	}
}

void preOrder(binaryTree tree){
	if(tree == NULL){
		// printf("NULL");
		return;
	}else{
		printf("%d ", tree -> value);
		preOrder(tree -> left);
		preOrder(tree -> right);
	}
	return;
}

void postOrder(binaryTree tree){
	if(tree == NULL){
		// printf("\n");
		return;
	}
	else{
		postOrder(tree -> left);
		postOrder(tree -> right);
		printf("%d ", tree -> value);
		return;
	}
}

void inOrder(binaryTree tree){
	if(tree == NULL){
		// printf("\n");
		return;
	}else{
		if(tree->left != NULL)
	        inOrder(tree -> left);

		printf("%d ", tree -> value);

		if(tree->right != NULL)
	        inOrder(tree->right);

		return;
	}
}

int findMaxUtil(treeNode* root, int res[]){
    if (root == NULL)
        return 0;

    int l = findMaxUtil(root->left,res);
    int r = findMaxUtil(root->right,res);

    int max_single = max(max(l, r) + root->value, root->value);
    int max_top = max(max_single, l + r + root->value);
    res[0] = max(res[0], max_top);

    return max_single;
}

void findMaxSum3(treeNode *root, int res[]){
    findMaxUtil(root, res);
    return;
}

int main(){
	binaryTree myTree;
	int size = SIZE;
	int k = 0;
	int maxSum;
	// int res[1];

	myTree = generateTree(size);
	// printf("\nIn-Order Tree Transversal\n");
	printf("\n");
	inOrder(myTree);
	printf("\n\n");
	// printf("\nPre-Order Tree Transversal\n");
    preOrder(myTree);
	printf("\n\n");
	// printf("\nPost-Order Tree Transversal\n");
    postOrder(myTree);
	printf("\n\n");

	maxSum  = findMaxSum(myTree, 0);
	// printf("\nMaximum Sum from root to leaf is: %d\n", maxSum);
	findPath(myTree , maxSum , 0 );
	// printf("\n\n");
	// printf("\n\n");
	// findMaxSum2(myTree, res);
	// printf("\nMaximum Sum from node to node: %d\n", res[0]);

	int sum = INT_MIN;
	treeNode *path = (treeNode*)malloc(sizeof(treeNode));
    path->right = NULL;

	// sum = findMaxSum2(myTree, &path);
	// sum = INT_MIN;
	findMaxNodes(myTree, &path, &sum);
	// printf("Sum:%d \n\n", sum);
	printf("\n\n");
	// treeNode* root;
	// root = (treeNode*)malloc(sizeof(treeNode));
	// root-> value = -100;
	// root -> left = (treeNode*)malloc(sizeof(treeNode));
	// root -> left -> value = 2;
	//
	// root -> right = (treeNode*)malloc(sizeof(treeNode));
	// root -> right -> value = 10;
	//
	// root -> left -> left = (treeNode*)malloc(sizeof(treeNode));
	// root -> left -> left -> value = 20;
	// root -> left -> right = (treeNode*)malloc(sizeof(treeNode));
	// root -> left -> right -> value = 50;
	//
	//
	// root -> right -> right = (treeNode*)malloc(sizeof(treeNode));
	// root -> right -> right -> value = -25;
	//
	// root -> right -> right -> left = (treeNode*)malloc(sizeof(treeNode));
	// root -> right -> right -> left -> value = 3;
	//
	// root -> right -> right -> right = (treeNode*)malloc(sizeof(treeNode));
	// root -> right -> right -> right -> value = 4;
	//
	// sum = findMaxSum2(root, &path);
	// sum = INT_MIN;
	// findMaxNodes(root, &path, &sum);
	// printf("Sum:%d \n\n", sum);

    inOrder(path);
	printf("\n\n");
	return 0 ;
}
