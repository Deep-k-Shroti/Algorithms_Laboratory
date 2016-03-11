#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct complexTag{
    float re, im;
}complexType, *complexPtr;

typedef struct inputNumTag {
    int *num;
} inputNumType, *inputNumPtr;

int randBetween(int min, int max);
inputNumType generateNum(int Num1Size ,int inputNumSize);
complexType complexMultiply (complexType a, complexType b);
complexType complexAdd (complexType a, complexType b);
complexType complexSubstract (complexType a, complexType b);
void complexDisplay (complexType a);
complexType complexScalerDiv (complexType a, float n);
void fft(int n, complexType A[], complexType F[]);
void ifft(int n, complexType A[], complexType F[]);
void displayOutput(int inputNumSize,complexType a_complex[]);
void multiplyCoeff(int size, complexType A[], complexType B[], complexType C[]);
void fftshift(int size, complexType A[] ,complexType A_shift[]);
inputNumType recombineDigits(int size, complexType A[]);


int main(){
    int i;
    int Num1Size, Num2Size, inputNumSize;
    inputNumType a,b,product;


    printf("Please enter the Number of Digits for first Number <Example Input: 1024>\n");
    scanf("%d", &Num1Size );
    printf("Please enter the Number of Digits for second Number <Example Input: 1024>\n");
    scanf("%d", &Num2Size );


    inputNumSize = (Num1Size >= Num2Size) ? Num1Size : Num2Size;
    inputNumSize = (int)pow(2,((int)ceil(log(inputNumSize)/log(2))+1));


    printf("The Generated Numbers are -->\n");
    a = generateNum(Num1Size ,inputNumSize);
    printf("A: ");
    for( i = 0 ; i < inputNumSize; i++ ){
        printf("%d", a.num[i]);
    }
    printf("\n");


    b = generateNum(Num2Size ,inputNumSize);
    printf("B: ");
    for( i = 0 ; i < inputNumSize; i++ ){
        printf("%d", b.num[i]);
    }
    printf("\n");


    complexType a_complex[inputNumSize], b_complex[inputNumSize], A[inputNumSize], B[inputNumSize], C[inputNumSize];
    complexType c[inputNumSize], A_shift[inputNumSize], B_shift[inputNumSize], c_shift[inputNumSize], c_shift2[inputNumSize];

    for(i = 0; i < inputNumSize ; i++){
        a_complex[i].re = a.num[i] ;
        a_complex[i].im = 0 ;

        b_complex[i].re = b.num[i] ;
        b_complex[i].im = 0 ;
    }


    // inputNumSize = 8;
    // complexType a_complex[8] = {{1,0},{2,0},{3,0},{4,0},{0,0},{0,0},{0,0},{0,0}};
    // complexType b_complex[8] = {{5,0},{6,0},{7,0},{8,0},{0,0},{0,0},{0,0},{0,0}};
    // complexType A[inputNumSize], B[inputNumSize], C[inputNumSize];
    // complexType c[inputNumSize], A_shift[inputNumSize], B_shift[inputNumSize], c_shift[inputNumSize], c_shift2[inputNumSize];


    // printf("Complex A: \n");
    // displayOutput(inputNumSize,a_complex);
    //
    // printf("Complex B: \n");
    // displayOutput(inputNumSize,b_complex);


    fft(inputNumSize, a_complex, A);
    fftshift(inputNumSize, A, A_shift);
    // printf("FFT of A: \n");
    // displayOutput(inputNumSize,A_shift);


    fft(inputNumSize, b_complex, B);
    fftshift(inputNumSize, B, B_shift);
    // printf("FFT of B: \n");
    // displayOutput(inputNumSize, B_shift);


    multiplyCoeff(inputNumSize, A_shift, B_shift, C);
    // printf("C: \n");
    // displayOutput(inputNumSize,C);

    ifft(inputNumSize, C, c);
    fftshift(inputNumSize, c, c_shift);
    // printf("IFFT of C: \n");
    for(i=0;i < inputNumSize;i++){
        c_shift[i] =  complexScalerDiv(c_shift[i],inputNumSize);
    }
    // displayOutput(inputNumSize,c_shift);

    fftshift(inputNumSize, c_shift, c_shift2);
    // printf("Shift of IFFT of C\n");
    // displayOutput(inputNumSize,c_shift2);

    product = recombineDigits(inputNumSize,c_shift2);
    printf("The Product is:");
    for( i = 0 ; i < inputNumSize; i++ ){
        printf("%d", product.num[i]);
    }
    printf("\n");
    return 0;
}


void displayOutput(int size, complexType A[]){
    int i;
    for(i=0;i < size;i++){
        complexDisplay(A[i]);
    }

}

int randBetween(int min, int max) {
    return (rand() % (max - min + 1) + min);
}

inputNumType generateNum(int numSize, int numDigits){
    int i;
    inputNumType A;
    printf("numDigits:%d\n",numDigits);
    printf("numSize:%d\n",numSize);

    A.num = (int*)malloc(numDigits*sizeof(int));
    for( i = 0; i < numDigits; i++ ){
        if(i < numDigits-numSize){
            A.num[i] = 0;
        }
        else{
            A.num[i] = randBetween(0,9);
        }
    }
    return A;
}



complexType complexMultiply (complexType a, complexType b){
    complexType c;
    c.re = a.re*b.re - a.im*b.im;
    c.im = a.im*b.re + a.re*b.im;
    return c;
}

complexType complexAdd (complexType a, complexType b){
    complexType c;
    c.re = a.re + b.re;
    c.im = a.im + b.im;
    return c;
}

complexType complexSubstract (complexType a, complexType b){
    complexType c;
    c.re = a.re - b.re;
    c.im = a.im - b.im;
    return c;
}

complexType complexScalerDiv (complexType a, float n){
    complexType c;
    c.re = a.re/n;
    c.im = a.im/n;
    return c;
}

void complexDisplay (complexType a){
    printf("%f,%fi\n", a.re,a.im);
}

void fft(int n, complexType A[], complexType F[]){
    // printf("Computing FFT...");
    int i,k,shift = n/2;

    if (n == 1){
        F[0] = A[0];
        return;
    }
    complexType omega,omegaK, E[n/2], O[n/2], EF[n/2], OF[n/2] ;

    for (i = 0 , k = 0 ; i < n ; k = k+1, i = i+2){
        E[k] = A[i];
        O[k] = A[i+1];
    }

    fft(n/2, E , EF);
    fft(n/2, O , OF);

    omega.re = cos(2*PI/n); omega.im = -sin(2*PI/n);
    omegaK = omega;

    for(i = 0; i < n/2; i++, omegaK = complexMultiply(omegaK, omega) ){
        F[i] = complexAdd(EF[i], complexMultiply(omegaK, OF[i]));
        F[i+shift] = complexSubstract(EF[i], complexMultiply(omegaK, OF[i]));
    }
}

void ifft(int n, complexType A[], complexType F[]){
    // printf("Computing IFFT...");
    int i,k,shift = n/2;

    if (n == 1){
        F[0] = A[0];
        return;
    }
    complexType omega,omegaK, E[n/2], O[n/2], EF[n/2], OF[n/2] ;

    for (i = 0 , k = 0 ; i < n ; k = k+1, i = i+2){
        E[k] = A[i];
        O[k] = A[i+1];
    }

    ifft(n/2, E , EF);
    ifft(n/2, O , OF);

    omega.re = cos(2*PI/n); omega.im = sin(2*PI/n);
    omegaK = omega;

    for(i = 0; i < n/2; i++, omegaK = complexMultiply(omegaK, omega) ){
        F[i] = complexAdd(EF[i], complexMultiply(omegaK, OF[i]));
        F[i+shift] = complexSubstract(EF[i], complexMultiply(omegaK, OF[i]));
    }
}

void fftshift(int size, complexType A[] ,complexType A_shift[]){
    int i;
    for(i = 0 ; i < size ; i++){
        A_shift[(i+1)%size] = A[i];
    }

}

void multiplyCoeff(int size, complexType A[], complexType B[], complexType C[]){
    int i;
    for (i = 0; i < size ; i++){
        C[i] = complexMultiply(A[i],B[i]);
    }
    return;
}

inputNumType recombineDigits(int size, complexType A[]){
    int i, digit, digit1, digit2;
    inputNumType sum;

    sum.num = calloc(size,sizeof(int));
    for(i= size-1 ; i > 0 ; i--){
        digit = sum.num[i]+round(A[i].re);
        digit1 = (int)digit%10;
        digit2 = (digit/10);
        sum.num[i] = digit1;
        // printf("sum.num[i]: %d\n",sum.num[i]);
        sum.num[i-1] = digit2;
        // printf("sum.num[i-1]: %d\n",sum.num[i-1]);
    }
    return sum;
}
