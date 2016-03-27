#include <stdio.h>
#include <stdlib.h>

typedef struct buildingTag{
	int start;
	int height;
	int end;
}buildingType, *buildingPtr;

typedef struct stripTag{
	int location;
	int height;
}stripLineType, *stripLinePtr;

void printStripList(stripLinePtr arr, int len){
	int i, check = 0;
	for(i = 0; i < len; i++){
		if(check != arr[i].height)
		printf("(%d,%d) ", arr[i].location, arr[i].height);
		check = arr[i].height;
	}
	return;
}

int append(int l , int h, stripLineType result[], int count){
	if(count > 0 && result[count-1].location == l){
		result[count-1].height = max(result[count-1].height , h);
		return -1;
	}
	result[count].location = l;
	result[count].height = h;

	return 0;
}

void printBuilding(buildingType building){
	printf("(%d,%d,%d);", building.start,building.height, building.end);
	return;
}

int max(int number1, int number2){
	if(number1>number2){
		return number1;
	}
	else{
		return number2;
	}
}

int mergeSkyLine(stripLineType result1[], stripLineType result2[], stripLineType result[]){

	int i=0,j=0,k = 0;
	int flag;
	int height1 = 0 , height2 = 0, location = 0;
	int maxHeight=0;

	while( (result1[i].location > 0) && (result2[j].location > 0 )){
		if(result1[i].location <= result2[j].location){
			height1 = result1[i].height;
			location = result1[i].location;
			maxHeight = max(height1, height2);
			flag = append(location, maxHeight, result, k++);
			if(flag == -1){
				k--;
			}
			i++;
		}
		else{

			height2 = result2[j].height;
			location = result2[j].location;
			maxHeight = max(height1, height2);
			flag = append(location, maxHeight, result, k++);
			if(flag == -1){
				k--;
			}
			j++;
		}

	}

	while(result1[i].location >  0 ){
		flag = append(result1[i].location, result1[i].height, result, k++);
		if(flag == -1){
			k--;
		}
		i++;
	}

	while(result2[j].location > 0 ){
		flag = append(result2[j].location, result2[j].height, result, k++);
		if(flag == -1){
			k--;
		}
		j++;
	}
	append(0, 0, result, k++);
	return (k-1);
}

int findSkyLine(buildingType arr[] , int l, int r, stripLineType result[]){

	printf(" ");
	int flag;
	int len = 0;
	if (l == r){
		int k = 0;
		flag = append(arr[l].start, arr[l].height, result, k++);
		flag = append(arr[l].end, 0, result, k++);
		flag = append(0,0,result,k++);
		return 2;
	}

	if (l < r){
		int m = l+(r-l)/2;
		stripLineType result1[m-l+3];
		stripLineType result2[r-m+2];//Same as (l+r)/2, but avoids overflow for large l and h
		findSkyLine(arr, l, m, result1);
		findSkyLine(arr, m+1, r, result2);
		len = mergeSkyLine(result1, result2,result);
	}
	return len;
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

	printf("Select option: \n1. Choose default set of buildings\n2. Choose new buildings\n3. Choose random buildings\n");
	scanf("%d",&option);

	if(option == 1){

		// buildingType buildingList[] = {{1, 11, 5}, {2, 6, 7}, {3, 13, 9},
		// {12, 7, 16}, {14, 3, 25}, {19, 18, 22},
		// {23, 13, 29}, {24, 4, 28}};

		buildingType buildingList[] = {	{12, 7, 16}, {14, 3, 25}, {19, 18, 22},{1, 11, 5}, {2, 6, 7}, {3, 13, 9},
		{23, 13, 29}, {24, 4, 28}};

		size = 8;
		printf("The buildings are: \n");

		for(i = 0 ; i < size ; i++){
			printf("(%d,%d,%d);", buildingList[i].start,buildingList[i].height, buildingList[i].end);
		}

		printf("\n\n");

		sortBuildings(buildingList,0,size-1);
		printf("The Sorted buildings are: \n");

		for(i = 0 ; i < size ; i++){
			printf("(%d,%d,%d);", buildingList[i].start,buildingList[i].height, buildingList[i].end);
		}

		printf("\n\n");

		printf("The skyline is:\n");
		stripLineType *result = (stripLinePtr)calloc(2*size, sizeof(stripLineType));
		int len = findSkyLine(buildingList , 0 , size ,result);
		printf("\n");
		printStripList(result, len);
		printf("\n");


	}else if(option == 2){
		printf("Enter the number of buildings\n");
		scanf("%d",&size);

		if(size <= 0){
			printf("Error: Please enter atleat 1 building\n");
			return;
		}

		buildingType *buildingList = (buildingPtr)calloc(size, sizeof(buildingType));

		printf("Please enter the building coordinates ;Example <x> <x_h> <y> <y_h>\n");
		for(i= 0; i < size; i++){
			scanf("%d %d %d",&buildingList[i].start ,&buildingList[i].height ,&buildingList[i].end);
		}

		printf("The buildings are: \n");
		for(i = 0 ; i < size ; i++){
			printf("(%d,%d,%d);", buildingList[i].start,buildingList[i].height, buildingList[i].end);
		}
		printf("\n\n");

		sortBuildings(buildingList,0,size-1);
		printf("The Sorted buildings are: \n");

		for(i = 0 ; i < size ; i++){
			printf("(%d,%d,%d);", buildingList[i].start,buildingList[i].height, buildingList[i].end);
		}


		printf("\n");
		printf("\nThe Skyline is: \n");
		stripLineType *result = (stripLinePtr)calloc(2*size, sizeof(stripLineType));
		int len = findSkyLine(buildingList , 0 , size ,result);
		printStripList(result, len);
		printf("\n");

	}else if(option == 3){
		printf("Enter the number of buildings\n");
		scanf("%d",&size);

		if(size <= 0){
			printf("Error: Please enter atleat 1 building\n");
			return;
		}

		buildingType *buildingList = (buildingPtr)calloc(size, sizeof(buildingType));

		for(i = 0; i < size; i++){
			buildingList[i].start =  randInterval(0, 10);
			buildingList[i].height = randInterval(0, 10);
			buildingList[i].end = buildingList[i].start + randInterval(1, 4);
		}

		printf("The buildings are: \n");
		for(i = 0 ; i < size ; i++){
			printf("(%d,%d,%d);", buildingList[i].start,buildingList[i].height, buildingList[i].end);
		}
		printf("\n\n");

		sortBuildings(buildingList,0,size-1);
		printf("The Sorted buildings are: \n");

		for(i = 0 ; i < size ; i++){
			printf("(%d,%d,%d);", buildingList[i].start,buildingList[i].height, buildingList[i].end);
		}

		printf("\n");
		printf("\nThe Skyline is: \n");
		stripLineType *result = (stripLinePtr)calloc(2*size, sizeof(stripLineType));
		int len = findSkyLine(buildingList , 0 , size ,result);
		printStripList(result, len);
		printf("\n");

	}else{
		printf("No option Found!!\n");
		return;
	}
	return ;
}
