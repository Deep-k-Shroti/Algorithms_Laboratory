#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct coordinateTag{
	int x;
	int y;
}coordinateType, *coordinatePtr;

coordinateType minPoint1,minPoint2;

int * extract( coordinateType P[], int n, int option);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
float minimal(coordinateType P[], int n);
float nearest(coordinateType P[], int n);
float euclDistance(coordinateType p1, coordinateType p2);
void displayPoints(int size, coordinateType A[]);
void pointDisplay (coordinateType a);


void pointDisplay (coordinateType a){
	printf("(%d,%d);", a.x, a.y);
	return;
}

void displayPoints(int size, coordinateType A[]){
    int i;
    for(i=0;i < size;i++){
        pointDisplay(A[i]);
    }
	printf("\n");
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

float euclDistance(coordinateType point1, coordinateType point2){
    return sqrt( (point1.x - point2.x)*(point1.x - point2.x) +
                 (point1.y - point2.y)*(point1.y - point2.y)
               );
}


float minStrip(coordinateType array[], int n, float d){
    float minimum = d;
    int i,j;
    int *yStrip;

    yStrip = extract(array , n, 2);
    mergeSort(yStrip, 0, n-1);

    for (i = 0; i < n; i++){
        for (j = i+1; j < n && (array[j].y - array[i].y) < minimum; j++){
            if (euclDistance(array[i],array[j]) < minimum){
                minimum = euclDistance(array[i], array[j]);
				minPoint1.x = array[i].x; minPoint1.y = array[i].y;
				minPoint2.x = array[j].x; minPoint2.y = array[j].y;
            }
        }
    }
    return minimum;
}

float minimal(coordinateType P[], int n)
{

    if (n <= 3){
          int i,j;
            float min = FLT_MAX;
            for (i = 0; i < n; ++i)
                for (j = i+1; j < n; ++j)
                    if (euclDistance(P[i], P[j]) < min){
						min = euclDistance(P[i], P[j]);

					}


            return min;
    }

    int mid = n/2;
    coordinateType midPoint = P[mid];
    coordinateType strip[n];

    float dl = minimal(P, mid);
    float dr = minimal(P + mid, n-mid);
    float d =(dl < dr)? dl : dr;
    int i,j = 0;

    for (i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;
    return (d < minStrip(strip, j, d))? d : minStrip(strip, j, d);
}

float nearest(coordinateType P[], int n){
    int *xP;
    xP = extract(P , n, 1);
    mergeSort(xP, 0, n-1);
    return minimal(P, n);
}

int * extract( coordinateType P[], int n, int option){
    int *xP = (int*)malloc(n*sizeof(int));
    int i;
    if(option ==1){
        for(i = 0; i< n ;i++){
            xP[i] = P[i].x;
        }
    }else if(option == 2){
        for(i = 0; i< n ;i++){
            xP[i] = P[i].y;
        }
    }
    return xP;
}


int main(){

	coordinateType *P;
	int i,option, size;
	printf("Select option: \n1. Choose default set of points\n2. Choose new points\n");
	scanf("%d",&option);

	if(option == 1){
		coordinateType *P = (coordinatePtr)calloc(6, sizeof(coordinateType));

		P[0].x = 2;P[0].y= 3;
		P[1].x = 12;P[1].y= 30;
		P[2].x = 40;P[2].y= 50;
		P[3].x = 5;P[3].y= 1;
		P[4].x = 12;P[4].y= 10;
		P[5].x = 3;P[5].y= 4;

		size = 6;
		printf("The default points are: ");
		displayPoints(size , P);

		printf("\n");
		printf("The smallest distance is %f \n", nearest(P, size));
		pointDisplay(minPoint1);
		pointDisplay(minPoint2);
	}else if(option == 2){
		printf("Enter the number of Points\n");
		scanf("%d",&size);

		if(size == 1){
			printf("Error: Please enter atleat 2 points\n");
			return;
		}
		coordinateType *P = (coordinatePtr)calloc(size, sizeof(coordinateType));

		printf("Please enter the coordinates ;Example <x> <y>\n");
		for(i= 0; i < size; i++){
			scanf("%d %d",&P[i].x,&P[i].y);
		}
		printf("The entered points are: ");
		displayPoints(size , P);
		printf("\n");
		printf("The smallest distance is %f \n", nearest(P, size));
		pointDisplay(minPoint1);
		pointDisplay(minPoint2);

	}else{
		printf("No option Found!!\n");
		return;
	}

	return ;
}
