#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct nodeTag{
    int priorityValue;
    int generationTime;
    int processID;
    struct nodeTag* next;
}nodeType , *nodePtr;

typedef struct redBlackTreeNode {
    void* key;
    nodePtr list;
    int listCount;
    void* info;
    int red; /* if red=0 then the node is black */
    struct redBlackTreeNode* left;
    struct redBlackTreeNode* right;
    struct redBlackTreeNode* parent;
} redBlackTreeNode;

typedef struct redBlackTree {
    redBlackTreeNode* root;
    redBlackTreeNode* nil;
} redBlackTree;


void IntDest(void* a);
int IntComp(const void* a,const void* b);
void IntPrint(const void* a);
nodePtr newNode(int priority, int genTime , int id);
void printList(nodePtr head);
void deleteHeadNode(nodePtr *headRef);
void deleteList(nodePtr* head_ref);
void sortedInsert(nodeType** head, nodePtr newNode);
redBlackTreeNode* treeMinimum(redBlackTree* tree);
redBlackTree* redBlackTreeCreate();
redBlackTreeNode * redBlackTreeInsert(redBlackTree*, void* key, void* info);
void leftRotate(redBlackTree* tree, redBlackTreeNode* x);
void rightRotate(redBlackTree* tree, redBlackTreeNode* y);
void redBlackTreeInsertHelp(redBlackTree* tree, redBlackTreeNode* z);
void redBlackTreePrint(redBlackTree*);
void redBlackTreeDelete(redBlackTree* , redBlackTreeNode* );
redBlackTreeNode * redBlackTreeInsert(redBlackTree* tree, void* key, void* info);
redBlackTreeNode* TreePredecessor(redBlackTree*,redBlackTreeNode*);
redBlackTreeNode* TreeSuccessor(redBlackTree*,redBlackTreeNode*);
redBlackTreeNode* redBlackTreeSearch(redBlackTree*, void*);



void IntDest(void* a) {
    free((int*)a);
}

int IntComp(const void* a,const void* b) {
    if( *(int*)a > *(int*)b) return(1);
    if( *(int*)a < *(int*)b) return(-1);
    return(0);
}

void IntPrint(const void* a) {
    printf("%i",*(int*)a);
}

nodePtr newNode(int priority, int genTime , int id){
    nodePtr tempNode = (nodePtr)malloc(sizeof(nodeType));
    tempNode -> generationTime = genTime;
    tempNode -> priorityValue  = priority;
    tempNode -> processID = id;
    tempNode -> next =  NULL;
    return tempNode;
}

void printList(nodePtr head){

    if(head == NULL){
        printf("...");
    }
    nodePtr tempNode = head;
    while(tempNode != NULL){
        printf("%d[%d], ", tempNode -> priorityValue , tempNode -> generationTime);
        tempNode = tempNode->next;
    }
}


void deleteHeadNode(nodePtr *headRef){
    nodePtr temp = *headRef;

    if (temp == NULL){
        printf("NULL List !!\n");
        return;
    }

    *headRef = temp -> next;
    return;
}

void deleteList(nodePtr* head_ref){
    /* deref head_ref to get the real head */
    nodePtr current = *head_ref;
    nodePtr temp;

    while (current != NULL){
        temp = current->next;
        free(current);
        current = temp;
    }
    /* deref head_ref to affect the real head back
    in the caller. */
    *head_ref = NULL;
}

redBlackTreeNode* treeMinimum(redBlackTree* tree){
    redBlackTreeNode* x = tree->root->left;
    redBlackTreeNode* nil = tree->nil;

    while((x-> left) != nil){
        (x) = (x) -> left ;
    }
    printf("Minimum Execution Node Value %d\n", *(int*)(x -> key));
    return (x);
}


redBlackTree* redBlackTreeCreate() {
    redBlackTree* newTree;
    redBlackTreeNode* temp;
    newTree=(redBlackTree*) malloc(sizeof(redBlackTree));
    temp=newTree->nil= (redBlackTreeNode*) malloc(sizeof(redBlackTreeNode));
    temp->parent=temp->left=temp->right=temp;
    temp->red=0;
    temp->key=0;
    temp->listCount = 0;
    temp=newTree->root= (redBlackTreeNode*) malloc(sizeof(redBlackTreeNode));
    temp->parent=temp->left=temp->right=newTree->nil;
    temp->key=0;
    temp->red=0;
    temp->listCount = 0;
    return(newTree);
}

void sortedInsert(nodeType** head, nodePtr newNode){
    nodePtr currentNode ;

    if (*head == NULL || (*head)-> priorityValue >= newNode-> priorityValue){
        newNode -> next = *head;
        *head = newNode;
    }
    else{
        currentNode  = *head;
        while (currentNode -> next!=NULL && currentNode -> next-> priorityValue < newNode -> priorityValue){
            currentNode  = currentNode -> next;
        }
        newNode -> next = currentNode -> next;
        currentNode -> next = newNode;
    }
    return;
}

void leftRotate(redBlackTree* tree, redBlackTreeNode* x) {
    redBlackTreeNode* y;
    redBlackTreeNode* nil=tree->nil;

    y=x->right;
    x->right=y->left;

    if (y->left != nil) y->left->parent=x;
    y->parent=x->parent;
    if( x == x->parent->left) {
        x->parent->left=y;
    } else {
        x->parent->right=y;
    }
    y->left=x;
    x->parent=y;
}

void rightRotate(redBlackTree* tree, redBlackTreeNode* y) {
    redBlackTreeNode* x;
    redBlackTreeNode* nil=tree->nil;
    x=y->left;
    y->left=x->right;

    if (nil != x->right)  x->right->parent=y;
    x->parent=y->parent;
    if( y == y->parent->left) {
        y->parent->left=x;
    } else {
        y->parent->right=x;
    }
    x->right=y;
    y->parent=x;

}

void redBlackTreeInsertHelp(redBlackTree* tree, redBlackTreeNode* z) {
    redBlackTreeNode* x;
    redBlackTreeNode* y;
    redBlackTreeNode* nil=tree->nil;

    z->left=z->right=nil;
    y=tree->root;
    x=tree->root->left;
    while( x != nil) {
        y=x;
        if (1 == IntComp(x->key,z->key)) {
            x=x->left;
        } else {
            x=x->right;
        }
    }
    z->parent=y;
    if ( (y == tree->root) || (1 == IntComp(y->key,z->key))) {
        y->left=z;
    } else {
        y->right=z;
    }
}

redBlackTreeNode * redBlackTreeInsert(redBlackTree* tree, void* key, void* info) {
    redBlackTreeNode * y;
    redBlackTreeNode * x;
    redBlackTreeNode * newNode;

    x=(redBlackTreeNode*) malloc(sizeof(redBlackTreeNode));
    x->key=key;
    x->info=info;

    redBlackTreeInsertHelp(tree,x);
    newNode=x;
    x->red=1;
    while(x->parent->red) {
        if (x->parent == x->parent->parent->left) {
            y=x->parent->parent->right;
            if (y->red) {
                x->parent->red=0;
                y->red=0;
                x->parent->parent->red=1;
                x=x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x=x->parent;
                    leftRotate(tree,x);
                }
                x->parent->red=0;
                x->parent->parent->red=1;
                rightRotate(tree,x->parent->parent);
            }
        } else {
            y=x->parent->parent->left;
            if (y->red) {
                x->parent->red=0;
                y->red=0;
                x->parent->parent->red=1;
                x=x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x=x->parent;
                    rightRotate(tree,x);
                }
                x->parent->red=0;
                x->parent->parent->red=1;
                leftRotate(tree,x->parent->parent);
            }
        }
    }
    tree->root->left->red=0;
    return(newNode);
}

redBlackTreeNode* TreeSuccessor(redBlackTree* tree,redBlackTreeNode* x) {
    redBlackTreeNode* y;
    redBlackTreeNode* nil=tree->nil;
    redBlackTreeNode* root=tree->root;

    if (nil != (y = x->right)) {
        while(y->left != nil) {
            y=y->left;
        }
        return(y);
    } else {
        y=x->parent;
        while(x == y->right) {
            x=y;
            y=y->parent;
        }
        if (y == root) return(nil);
        return(y);
    }
}

redBlackTreeNode* TreePredecessor(redBlackTree* tree, redBlackTreeNode* x) {
    redBlackTreeNode* y;
    redBlackTreeNode* nil=tree->nil;
    redBlackTreeNode* root=tree->root;

    if (nil != (y = x->left)) {
        while(y->right != nil) {
            y=y->right;
        }
        return(y);
    } else {
        y=x->parent;
        while(x == y->left) {
            if (y == root) return(nil);
            x=y;
            y=y->parent;
        }
        return(y);
    }
}

void printInorder(redBlackTree* tree, redBlackTreeNode* x) {
    redBlackTreeNode* nil=tree->nil;
    redBlackTreeNode* root=tree->root;
    if (x != tree->nil) {
        printInorder(tree,x->left);
        printf("  key=");
        IntPrint(x->key);
        printf("  l->key=");
        if( x->left == nil) printf("NULL"); else IntPrint(x->left->key);
        printf("  r->key=");
        if( x->right == nil) printf("NULL"); else IntPrint(x->right->key);
        printf("  p->key=");
        if( x->parent == root) printf("NULL"); else IntPrint(x->parent->key);
        printf("  red=%i",x->red);
        printf("  list=");
        printList(x -> list);
        printf("  listCount=%d", x -> listCount);
        printf("\n");
        printInorder(tree,x->right);
    }
}

void redBlackTreePrint(redBlackTree* tree) {
    printInorder(tree,tree->root->left);
}


redBlackTreeNode* redBlackTreeSearch(redBlackTree* tree, void* q) {
    redBlackTreeNode* x=tree->root->left;
    redBlackTreeNode* nil=tree->nil;
    int compVal;
    if (x == nil) return(0);
    compVal = IntComp(x->key,(int*) q);
    while(0 != compVal) {
        if (1 == compVal) {
            x=x->left;
        } else {
            x=x->right;
        }
        if ( x == nil) return(0);
        compVal = IntComp(x->key,(int*) q);
    }
    return(x);
}

void redBlackTreeDeleteFixUp(redBlackTree* tree, redBlackTreeNode* x) {
    redBlackTreeNode* root=tree->root->left;
    redBlackTreeNode* w;

    while( (!x->red) && (root != x)) {
        if (x == x->parent->left) {
            w=x->parent->right;
            if (w->red) {
                w->red=0;
                x->parent->red=1;
                leftRotate(tree,x->parent);
                w=x->parent->right;
            }
            if ( (!w->right->red) && (!w->left->red) ) {
                w->red=1;
                x=x->parent;
            } else {
                if (!w->right->red) {
                    w->left->red=0;
                    w->red=1;
                    rightRotate(tree,w);
                    w=x->parent->right;
                }
                w->red=x->parent->red;
                x->parent->red=0;
                w->right->red=0;
                leftRotate(tree,x->parent);
                x=root;
            }
        } else {
            w=x->parent->left;
            if (w->red) {
                w->red=0;
                x->parent->red=1;
                rightRotate(tree,x->parent);
                w=x->parent->left;
            }
            if ( (!w->right->red) && (!w->left->red) ) {
                w->red=1;
                x=x->parent;
            } else {
                if (!w->left->red) {
                    w->right->red=0;
                    w->red=1;
                    leftRotate(tree,w);
                    w=x->parent->left;
                }
                w->red=x->parent->red;
                x->parent->red=0;
                w->left->red=0;
                rightRotate(tree,x->parent);
                x=root;
            }
        }
    }
    x->red=0;
}

void redBlackTreeDelete(redBlackTree* tree, redBlackTreeNode* z){
    redBlackTreeNode* y;
    redBlackTreeNode* x;
    redBlackTreeNode* nil=tree->nil;
    redBlackTreeNode* root=tree->root;

    y= ((z->left == nil) || (z->right == nil)) ? z : TreeSuccessor(tree,z);
    x= (y->left == nil) ? y->right : y->left;
    if (root == (x->parent = y->parent)) {
        root->left=x;
    } else {
        if (y == y->parent->left) {
            y->parent->left=x;
        } else {
            y->parent->right=x;
        }
    }
    if (y != z) {


        if (!(y->red)) redBlackTreeDeleteFixUp(tree,x);
        IntDest(z->key);
        y->left=z->left;
        y->right=z->right;
        y->parent=z->parent;
        y->red=z->red;
        z->left->parent=z->right->parent=y;
        if (z == z->parent->left) {
            z->parent->left=y;
        } else {
            z->parent->right=y;
        }
        free(z);
    } else {
        IntDest(y->key);
        if (!(y->red)) redBlackTreeDeleteFixUp(tree,x);
        free(y);
    }
}

int main() {

    int N;
    int M;
    int executionTime, priority;
    int i, systemClock, numProcess = 0;
    int currentMin = 0, exeTime;
    int liveProcessPresent = 1;
    int timedata;
    FILE *filePtr;
    int* newInt;
    redBlackTreeNode* searchPtr;
    nodePtr listNode;
    redBlackTreeNode* minExecTimeNode;

    int tempPriority, tempExecutionTime, tempGenerationTime, tempProcessID;
    int golbalProcessID = 0;
    int schedulingTime, preemptingTime, completionTime;

    printf("Enter the Number of Live Prcess to be there: ");
    scanf("%d", &N);

    printf("Enter the Number of Processes to Simulate: ");
    scanf("%d", &M);

    systemClock = 0;
    filePtr = fopen("log.txt", "w");
    fprintf(filePtr, "Process ID, Creation Time, Priority, Scheduling time, Preempting Time, Completion Time\n");

    redBlackTree *tree = redBlackTreeCreate();

    for( i = 0; i <= M ;){
        if( (i < M) && (numProcess < N) ){
            printf("<<<Process Creater Running numProcess: %d>>>\n",numProcess);
            executionTime = rand()%1000 + 1;
            priority = rand()%4 + 1;
            golbalProcessID = golbalProcessID + 1;
            printf("ExecutionTime: %d Priority: %d process ID: %d\n", executionTime, priority, golbalProcessID);
            // fprintf(filePtr, "%d,%d,%d,%d,%d,%d\n", golbalProcessID, systemClock ,priority, -1 , -1 , -1);
            listNode =  newNode( priority ,systemClock, golbalProcessID);

            if ( ( searchPtr = redBlackTreeSearch(tree,&(executionTime)) ) ) {/*assignment*/
                printf("Execution Time found in tree of value %d!!\n", *(int*)(searchPtr -> key));
                sortedInsert(&(searchPtr -> list), listNode);
                (searchPtr -> listCount)++;
            } else {
                printf("Execution Time: %d Not in tree, Creating Node!!\n", executionTime);
                newInt=(int*) malloc(sizeof(int));
                *newInt = executionTime;
                searchPtr = redBlackTreeInsert(tree, newInt, 0);
                sortedInsert(&(searchPtr -> list), listNode);
                (searchPtr -> listCount) = 1;
            }
            numProcess++;
            i++;
        }


        printf("<<<<Scheduler Running numProcess: %d>>>>\n", numProcess);
        minExecTimeNode = treeMinimum(tree);
        schedulingTime = systemClock;
        if ( minExecTimeNode ) {
            if(minExecTimeNode -> listCount > 1){

                printf("List Count more than 1\n");
                (minExecTimeNode -> listCount )--;

                tempPriority = minExecTimeNode -> list -> priorityValue;
                tempGenerationTime = minExecTimeNode -> list -> generationTime;
                tempExecutionTime =  *(int*)(minExecTimeNode -> key);
                tempProcessID = minExecTimeNode -> list -> processID;
                deleteHeadNode(&(searchPtr -> list));

                printf("Min Execution Time: %d, Priority Value: %d Generation Time: %d Process ID: %d\n",tempExecutionTime, tempPriority, tempGenerationTime, tempProcessID);


                systemClock = systemClock + tempPriority*50;
                tempExecutionTime = tempExecutionTime - tempPriority*50;
                preemptingTime = systemClock;
                if(tempExecutionTime > 0)
                fprintf(filePtr, "%d,%d,%d,%d,%d,%d\n", tempProcessID,tempGenerationTime,tempPriority, schedulingTime, preemptingTime , -1);

            }else if(minExecTimeNode -> listCount == 1){
                printf("List Count equal to 1\n");

                tempPriority = minExecTimeNode -> list -> priorityValue;
                tempGenerationTime = minExecTimeNode -> list -> generationTime;
                tempExecutionTime =  *(int*)(minExecTimeNode -> key);
                tempProcessID = minExecTimeNode -> list -> processID;

                deleteList(&(minExecTimeNode->list));
                redBlackTreeDelete(tree,minExecTimeNode);

                printf("Min Execution Time: %d, Priority Value: %d Generation Time: %d Process ID: %d\n",tempExecutionTime, tempPriority, tempGenerationTime, tempProcessID);
                systemClock = systemClock + tempPriority*50;
                tempExecutionTime = tempExecutionTime - tempPriority*50;
                preemptingTime = systemClock;

                if(tempExecutionTime > 0)
                fprintf(filePtr, "%d,%d,%d,%d,%d,%d\n", tempProcessID,tempGenerationTime,tempPriority, schedulingTime, preemptingTime , -1);


            }else{
                printf("Problem in List\n");
            }

            if(tempExecutionTime > 0){
                printf("<<<Inserting Again with modification>>>\n");
                listNode =  newNode( tempPriority , tempGenerationTime, tempProcessID);
                if ( ( searchPtr = redBlackTreeSearch(tree,&(tempExecutionTime)) ) ) {/*assignment*/
                    printf("Execution Time found in tree of value %d!!\n", *(int*)(searchPtr -> key));
                    sortedInsert(&(searchPtr -> list), listNode);
                    schedulingTime = systemClock;
                    (searchPtr -> listCount)++;
                } else {

                    printf("Execution Time: %d Not in tree, Creating Node!!\n", tempExecutionTime);
                    newInt=(int*) malloc(sizeof(int));
                    *newInt = tempExecutionTime;
                    searchPtr = redBlackTreeInsert(tree, newInt, 0);
                    sortedInsert(&(searchPtr -> list), listNode);
                    schedulingTime = systemClock;
                    (searchPtr -> listCount) = 1;
                }
                // redBlackTreePrint(tree);
            }else{
                if(systemClock < systemClock + tempExecutionTime){
                    completionTime = systemClock;
                }else{
                    completionTime = systemClock + tempExecutionTime ;
                }

                fprintf(filePtr, "%d,%d,%d,%d,%d,%d\n", tempProcessID,tempGenerationTime, tempPriority, schedulingTime, preemptingTime,completionTime);
                numProcess--;
                if( numProcess == 0)
                break;
            }

        }else{
            printf("Execution Time not found\n");
        }

        if( numProcess == 0)
        break;

    }
    redBlackTreePrint(tree);

    fclose( filePtr );
    return 0;

}
