#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>

typedef struct buildingTag{
	float start;
	float start_height;
	float end;
	float end_height;
}buildingType, *buildingPtr;

typedef struct lineTag{
	float x1;
	float y1;
	float x2;
	float y2;
}lineType;

typedef struct stripTag{
	float location;
	float height;
}stripLineType, *stripLinePtr;


float max(float number1, float number2){
	if(number1>number2){
		return number1;
	}
	else{
		return number2;
	}
}

float lineSlope(lineType l1){
	float slope;
	slope = (l1.y2 - l1.y1)/(l1.x2 - l1.x1);
	return slope;
}

float lineConstant(lineType l1){
	float constant;
	constant = -1*(l1.x1*((l1.y2-l1.y1)/(l1.x2-l1.x1)))+l1.y1;
	return constant;
}

int lineIntersection(lineType l1, lineType l2, stripLineType &p , float x_left, float x_right){

	float num1;
	float num2;
	float deno;
	if(fabs(lineSlope(l1)-lineSlope(l2)) < 0.0001 && fabs(lineConstant(l1)-lineConstant(l2))< 0.0001){
		return -1;
	}
	num1 = (l1.x1*l1.y2 - l1.y1*l1.x2)*(l2.x1 - l2.x2) - (l1.x1 - l1.x2)*(l2.x1*l2.y2 - l2.y1*l2.x2);
	num2 = (l1.x1*l1.y2 - l1.y1*l1.x2)*(l2.y1 - l2.y2) - (l1.y1 - l1.y2)*(l2.x1*l2.y2 - l2.y1*l2.x2);
	deno = (l1.x1 - l1.x2)*(l2.y1-l2.y2) - (l1.y1 - l1.y2)*(l2.x1 - l2.x2);
	p.location  = num1/deno;
	p.height  = num2/deno;

	if(p.location < x_left || p.location > x_right|| isnan(p.location)){
		return -1;
	}
	// printf("Intersection: (%0.2f,%0.2f)\n",p.location , p.height );
	return 1;
}

lineType constructLine(stripLineType p1, stripLineType p2){
	lineType l;
	l.x1 = p1.location;
	l.y1 = p1.height;
	l.x2 = p2.location;
	l.y2 = p2.height;
	return l;
}

float heightAtLocation(lineType l1,float x){
	float height = (lineSlope(l1)*x+lineConstant(l1));
	// printf("Cal Height: %f\n", height);
	if( isnan(height))
		return (0.0);

	return height;
}

void append(float l , float h, stripLineType result[], int count){
	// printf("Appended: (%0.2f,%0.2f)\n",l,h);
	result[count].location = l;
	result[count].height = h;

	return;
}

void mergeSkyLine(stripLineType* result1,stripLineType* result2, stripLineType result[], int result1Length, int result2Length, int &resultLength){

	int flag;
	lineType l1,l2;
	l1.x1 = 0.0;
	l1.y1 = 0.0;
	l1.x2 = 0.0;
	l1.y2 = 0.0;
	l2 = l1;
	stripLineType p;
	float previousX;
	int i,j,k;
	// printf("\n" );
	// for(i = 0; i < result1Length; i++)
	// 	printf(" (%0.2f, %0.2f)", result1[i].location, result1[i].height);
	// printf(" \n");
	// for(i = 0; i < result2Length; i++)
	// 	printf(" (%0.2f, %0.2f)", result2[i].location, result2[i].height);
	// printf(" \n");

	i =  j = k = 0;



	while(j < result2Length && i < result1Length){
		// printf("1. (%d, %d) result1[i].location: %0.2f result2[j].location: %0.2f\n",i,j,result1[i].location,result2[j].location);
		if(result1[i].location < result2[j].location){
			if(k != 0){
				previousX = result[k-1].location;
			}
			else{
				previousX = -FLT_MAX;
			}

			int flag = lineIntersection(l1, l2, p, previousX, result1[i].location);

			if(flag == 1){
				append(p.location, p.height, result, k);
				k++;
			}
			append(result1[i].location, max(result1[i].height,heightAtLocation(l2,result1[i].location)), result, k);

			if(i<(result1Length-1)){
				l1 = constructLine(result1[i],result1[i+1]);
				// printf("1. line constructed: (%0.2f,%0.2f); (%0.2f,%0.2f)\n",result1[i].location,result1[i].height ,result1[i+1].location,result1[i+1].height );
			}
			i++;k++;
		}
		else{

			if(k!=0){
				previousX = result[k-1].location;
			}
			else{
				previousX = -FLT_MAX;
			}

			int flag = lineIntersection(l1,l2,p,previousX,result2[j].location);

			if(flag==1){
				append(p.location, p.height, result, k++);
			}
			append( result2[j].location, max(result2[j].height,heightAtLocation(l1,result2[j].location)), result, k);

			if(j<(result2Length-1))
			l2 = constructLine(result2[j],result2[j+1]);
			// printf("2. line constructed: (%0.2f,%0.2f); (%0.2f,%0.2f)\n",result2[j].location,result2[j].height ,result2[j+1].location,result2[j+1].height );

			j++;k++;
		}
	}
	while(i<result1Length){
		// printf("2 . (%d,%d) result1[i].location: %0.2f result2[j].location : %0.2f\n",i,j,result1[i].location,result2[j].location);
		append(result1[i].location, result1[i].height, result, k);
		i++;
		k++;
	}
	while(j<result2Length){
		// printf("3 . (%d,%d) result1[i].location: %0.2f result2[j].location : %0.2f\n",i,j,result1[i].location,result2[j].location);
		append(result2[j].location, result2[j].height, result, k);
		j++;
		k++;
	}
	resultLength = k;

	int pointer1 = 0;
	int pointer2 = 0;

	// printf("Inside print1\n");
	// for(i = 0; i < resultLength; i++){
	// 	printf(" (%f, %f)", result[i].location, result[i].height);
	// }
	// printf("\n");
	//redundant/repeating points are removed from skyline
	while(pointer2 < resultLength){
		append(result[pointer2].location, result[pointer2].height, result, pointer1);

		if(pointer2 < resultLength-1){
			while((result[pointer2].location == result[pointer2+1].location) && (result[pointer2].height == result[pointer2+1].height)){
				pointer2++;
			}
		}
		pointer2++;
		pointer1++;
	}
	// printf("Inside print2\n");
	// for(i = 0; i < resultLength; i++){
	// 	printf(" (%f, %f)", result[i].location, result[i].height);
	// }
	// printf("\n");

	resultLength = pointer1;
	pointer1 = pointer2 = 0;
	float maxHeight;

	//Redunduncy is removed in location
	while(pointer2 < resultLength){
		append(result[pointer2].location, result[pointer2].height, result, pointer1);

		maxHeight = result[pointer1].height;
		if(maxHeight!=0.0 && (pointer2 < (resultLength-1) ) ){
			while(result[pointer2].location==result[pointer2+1].location&&result[pointer2+1].height!=0.0){
				// printf("Chosen:%f->%f,%f: ", result[pointer2].location, maxHeight,result[pointer2+1].height );
				maxHeight = max(result[pointer2+1].height, maxHeight);
				// printf("%f\n", maxHeight);
				pointer2++;
			}
		}

		result[pointer1].height = maxHeight;
		pointer1++;
		pointer2++;
	}
	resultLength = pointer1;
	float slope1 = 0.0;
	float slope2 = 0.0;

	// printf("Inside print4\n");
	// for(i = 0; i < resultLength; i++){
	// 	printf(" (%f, %f)", result[i].location, result[i].height);
	// }
	// printf("\n");


	pointer1 = 0;pointer2 = 0;
	//Collinear points are removed from skyline
	while(pointer2 < resultLength){
		append(result[pointer2].location, result[pointer2].height, result, pointer1);

		pointer2++;
		if(pointer2 < resultLength-1){
			while(1){
				slope1 = lineSlope(constructLine(result[pointer2],result[pointer2-1]));
				slope2 = lineSlope(constructLine(result[pointer2],result[pointer2+1]));
				// printf("Slopes: %f, %f \n", slope1, slope2);
				if(fabs(slope1 - slope2) > 0.01)
					break;
				pointer2++;
			}
		}
		pointer1++;
	}

	resultLength = pointer1;
	// printf("Inside print3\n");
	// for(i = 0; i < resultLength; i++){
		// printf(" (%f, %f)", result[i].location, result[i].height);
	// }
	// printf("\n");


}

void findSkyLine(buildingType building[], int left, int right, stripLineType result[], int &resultLength){

	// printf("left: %d, right:%d \n", left , right);
	int flag;
	if(left==right)
	{
		// printf("BASE CASE, (%f, %f) , (%f, %f)\n",building[left].start, building[left].start_height,building[left].end, building[left].end_height);
		// int k = 0;
		append(building[left].start, 0, result, 0);
		append(building[left].start, building[left].start_height, result, 1);
		append(building[left].end, building[left].end_height, result, 2);
		append(building[left].end, 0, result, 3);
		resultLength = 4;

		return;
	}
	int mid = (left+right)/2;
	stripLineType result1[10*(mid-left+1)], result2[10*(right-mid)];
	int result1Length, result2Length;
	findSkyLine(building,left,mid,result1,result1Length);
	findSkyLine(building,mid+1,right,result2,result2Length);
	mergeSkyLine(result1, result2, result, result1Length, result2Length, resultLength);
	return;
}

void printStripList(stripLinePtr arr, int len){
	int i;
	for(i = 0; i < len; i++){
		printf("(%.2f,%.2f) ", arr[i].location, arr[i].height);
	}
	return;
}

void mergeBuildings(buildingType arr[],int left, int mid, int right)
{
    int i, j, k;
    int node1 = mid - left + 1;
    int node2 =  right - mid;
    buildingType L[node1], R[node2];

    for(i = 0; i < node1; i++)
        L[i] = arr[left + i];

    for(j = 0; j < node2; j++)
        R[j] = arr[mid + 1+ j];

    i = 0;
    j = 0;
    k = left;
    while (i < node1 && j < node2){
        if (L[i].start <= R[j].start)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < node1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < node2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void sortBuildings(buildingType arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left+(right-left)/2; //Same as (left+right)/2, but avoids overflow for large left and h
        sortBuildings(arr, left, mid);
        sortBuildings(arr, mid+1, right);
        mergeBuildings(arr, left, mid, right);
    }
}

int randInterval(int min, int max)
{
    int r;
    const int range = 1 + max - min;
    const int buckets = RAND_MAX / range;
    const int limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

int main(){

	int option, size, i;
	// stripLineType result[100];
	int len;
	printf("Select option: \n1. Choose default set of buildings\n2. Choose new buildings\n3. Choose random buildings\n");
	scanf("%d",&option);

	if(option == 1){
		// buildingType buildingList[] = {{1,11,5,14}, {1,5,5,18}};
		// buildingType buildingList[] = {{1,4,6,2}, {2,2,8,4}};
		// buildingType buildingList[] = {{2,2,8,4},{0,4,6,2}, {10,4,9,5}};

		buildingType buildingList[] = {{1,4,4,2}, {3,4,7,2}, {5,2,8,4}};

		size = sizeof(buildingList)/sizeof(buildingType);
		printf("The buildings are: (l,l_h,r,r_h) \n");

		for(i = 0 ; i < size ; i++){
			printf("(%0.2f,%0.2f,%0.2f,%0.2f);", buildingList[i].start,buildingList[i].start_height, buildingList[i].end, buildingList[i].end_height);
		}

		printf("\n\n");

		sortBuildings(buildingList,0,size-1);
		printf("The Sorted buildings are: \n");

		for(i = 0 ; i < size ; i++){
			printf("(%0.2f,%0.2f,%0.2f,%0.2f);", buildingList[i].start,buildingList[i].start_height, buildingList[i].end, buildingList[i].end_height);
		}

	    printf("\n\n");

		printf("The skyline is:\n");
		stripLineType *result = (stripLinePtr)calloc(10*size, sizeof(stripLineType));
		findSkyLine(buildingList,0,size-1,result, len);
		printf("\n");
		printStripList(result, len);
		printf("\n");

	}else if(option == 2){
		printf("Enter the number of buildings\n");
		scanf("%d",&size);

		if(size <= 0){
			printf("Error: Please enter atleat 1 building\n");
			return -1;
		}

		buildingType *buildingList = (buildingPtr)calloc(size, sizeof(buildingType));
		printf("Please enter the building coordinates ;Example <x> <x_h> <y> <y_h>\n");

		for(i= 0; i < size; i++){
			scanf("%f %f %f %f",&buildingList[i].start ,&buildingList[i].start_height,&buildingList[i].end ,&buildingList[i].end_height);
		}

		printf("The buildings are: ");

		for(i = 0 ; i < size ; i++){
			printf("(%0.2f,%0.2f,%0.2f,%0.2f);", buildingList[i].start,buildingList[i].start_height, buildingList[i].end, buildingList[i].end_height);
		}

		printf("\n\n");

		sortBuildings(buildingList,0,size-1);
		printf("The Sorted buildings are: \n");

		for(i = 0 ; i < size ; i++){
			printf("(%0.2f,%0.2f,%0.2f,%0.2f);", buildingList[i].start,buildingList[i].start_height, buildingList[i].end, buildingList[i].end_height);
		}

	    printf("\n\n");

		printf("The Skyline is: \n");
		stripLineType *result = (stripLinePtr)calloc(10*size, sizeof(stripLineType));
		findSkyLine(buildingList , 0 , size-1 ,result,len);
		printStripList(result, len);
		printf("\n");

	}else if(option == 3){
		printf("Enter the number of buildings\n");
		scanf("%d",&size);

		if(size <= 0){
			printf("Error: Please enter atleat 1 building\n");
			return -1;
		}

		buildingType *buildingList = (buildingPtr)calloc(size, sizeof(buildingType));

		for(i = 0; i < size; i++){
			buildingList[i].start =  randInterval(0, 10);
			buildingList[i].start_height = randInterval(0,10);
			buildingList[i].end = buildingList[i].start + randInterval(1, 4);
			buildingList[i].end_height = randInterval(0,10);
		}

		printf("The buildings are: \n");
		for(i = 0 ; i < size ; i++){
			printf("(%0.2f,%0.2f,%0.2f,%0.2f);", buildingList[i].start,buildingList[i].start_height, buildingList[i].end, buildingList[i].end_height);

		}
		printf("\n\n");

		sortBuildings(buildingList,0,size-1);
		printf("The Sorted buildings are: \n");

		for(i = 0 ; i < size ; i++){
			printf("(%0.2f,%0.2f,%0.2f,%0.2f);", buildingList[i].start,buildingList[i].start_height, buildingList[i].end, buildingList[i].end_height);
		}

		printf("\n");
		printf("\nThe Skyline is: \n");
		stripLineType *result = (stripLinePtr)calloc(10*size, sizeof(stripLineType));
		findSkyLine(buildingList , 0 , size-1 ,result,len);
		printStripList(result, len);
		printf("\n");

	}else{
		printf("No option Found!!\n");
		return -1;
	}


	return 0 ;
}
