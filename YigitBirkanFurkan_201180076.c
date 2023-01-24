//YÝÐÝT BÝRKAN FURKAN 201180076 Group Number:1
/*
* Sparse Matrix Representation in C Using an array of structures
*/
//I wrote the code considering all the exceptions in sparce matrix multiplication. (You can use negative numbers in matrices if you want.)
/*
I used TitleCase for main Struct name;
I used lowerCase for variables,arrays that are type of Struct  and functions;
I used one-letter case for loop variables
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_TERM 101
#define _K 4
#define _L 4
#define _M 4
//struct definition

typedef struct
{
 int row, column, value;
} SparseMatrix;
//signature of functions
void multiply(SparseMatrix*);
void print(SparseMatrix*);
void sorting(SparseMatrix*);
void swap(int*,int*,int*);
void fixsparse(SparseMatrix*);
int main()
{
//i and j are loop variables
   int i,j;
 int matrix1[_K][_L] = { {0,10,0,5 }, {0,2,4,0}, {0 , 0 , 0 , 0 }, {3, 0, 0 ,7 } };
 int count1 = 1;
 //Struct array
 SparseMatrix sparseMatrix1[MAX_TERM];
 
sparseMatrix1[0].row = _K;
sparseMatrix1[0].column = _L;

 //Making of new matrix
 for (i = 0; i < _K; i++)
 {
 for ( j = 0; j < _L; j++)
 {
 if (matrix1[i][j]!=0)
 {
 sparseMatrix1[count1].row = i;
 sparseMatrix1[count1].column = j;
 sparseMatrix1[count1].value = matrix1[i][j];
 count1++;
 }
 }
 }
sparseMatrix1[0].value = count1-1;

 multiply(sparseMatrix1);

}


	
	        
	
		
	
	

//multiplication function
void multiply(SparseMatrix sparseMatrix[MAX_TERM])
{  
 //i,j,k are loop variables and temp is my temporary variable.
 int temp,i,j,k=1;
	int count2=1;
	SparseMatrix resultMatrix[MAX_TERM];
	SparseMatrix sparseMatrix2[MAX_TERM];
	sparseMatrix2[0].row = _L;
    sparseMatrix2[0].column= _M;
	SparseMatrix transposeMatrix[MAX_TERM];
 int matrix2[_L][_M] = {  {1 , 0 , 0 , 2 }, {0 , 0 , 3 , 0 }, {0 , 8 , 0 , 0 }, {5 , 0 , 10 , 0 } };
 //making of new matrix
 for ( i = 0; i < _L; i++)
 {
 for (j = 0; j < _M; j++)
 {
 if (matrix2[i][j]!=0)
 {
 sparseMatrix2[count2].row = i;
 sparseMatrix2[count2].column = j;
 sparseMatrix2[count2].value = matrix2[i][j];
 count2++;
 }
 }
 }
sparseMatrix2[0].value = count2-1;
 
//MY REFERENCE
//transpose part (I learnt this algorithm from Ceng205 Data Structures slide of lecture 4.My reference is here.)

	//Struct array
	SparseMatrix sparseMatrixEmpty[MAX_TERM];
	
	        sparseMatrixEmpty[0].row=sparseMatrix2[0].row;
			sparseMatrixEmpty[0].column=sparseMatrix2[0].column;
			sparseMatrixEmpty[0].value=sparseMatrix2[0].value;
	swap(&sparseMatrixEmpty[0].row,&sparseMatrixEmpty[0].column,&temp);
	for( i=1;i<=sparseMatrix2[0].column;i++){
	for( j=1;j<=sparseMatrix2[0].value;j++){
		if(sparseMatrix2[j].column==i-1){
			
			sparseMatrixEmpty[k].row=sparseMatrix2[j].row;
			sparseMatrixEmpty[k].column=sparseMatrix2[j].column;
			sparseMatrixEmpty[k].value=sparseMatrix2[j].value;
			swap(&sparseMatrixEmpty[k].row,&sparseMatrixEmpty[k].column,&temp);
			k++;
			
		}
	}
	}

	
	//end of transpose part
	
	//MULTIPLY PART	
	//MY REFERENCE
	//https://www.youtube.com/watch?v=x70zNUIHR0k&t=1s  a little help for algorithm of multiply sparse matrices...
	
if(sparseMatrix[0].column!=sparseMatrixEmpty[0].column){
	printf("these two matrices cannot be multiplied");
}
 else{
 //a,b,l,m,n are my loop variables and index is index of my result matrix.
 	int index=1,l,m,n,a,b;
 	resultMatrix[0].row=sparseMatrix[0].row;
 	resultMatrix[0].column=sparseMatrixEmpty[0].row;
 	//part of transferring nonzero elements of two multiplied sparse matrices to the result matrix array
 	for(i=1;i<=sparseMatrix[0].value;i++){
 		for(j=1;j<=sparseMatrixEmpty[0].value;j++){
 			if(sparseMatrix[i].column==sparseMatrixEmpty[j].column){
 				resultMatrix[index].value=sparseMatrix[i].value*sparseMatrixEmpty[j].value;
 				resultMatrix[index].row=sparseMatrix[i].row;
 				resultMatrix[index].column=sparseMatrixEmpty[j].row;
 				index++;
			 }
			 
		 }
	 }
	 resultMatrix[0].value=index-1;
	 //end of transferring part
	 
	 /*Determining and summing the numbers in the same row and column in the result matrix 
	 and assigning them to the first of the numbers in the same row and column*/
	 for(l=1;l<=resultMatrix[0].value;l++){
 		for(m=l+1;m<=resultMatrix[0].value;m++){
 			if(resultMatrix[l].row ==resultMatrix[m].row&&resultMatrix[l].column ==resultMatrix[m].column){
 				if(resultMatrix[l].value+resultMatrix[m].value!=0){
 					resultMatrix[l].value=resultMatrix[l].value+resultMatrix[m].value;
				 }
 				else{
 					/*In this section, if the sum of the elements in the same row and column is zero,
					  I assigned the value 0 to the upper element from the same ones.*/
 					resultMatrix[l].value=0;
				 }
 			 }
			 
			  }
		   
		 }
		//end of part of summing in the result matrix part
 			
		
		//In this part, I continue to run my matrix, which I edited with the fixsparse function, until there is no error.
		for(a=1;a<resultMatrix[0].value;a++){
			for(b=a+1;b<resultMatrix[0].value;b++){
				if(resultMatrix[a].row ==resultMatrix[b].row&&resultMatrix[a].column ==resultMatrix[b].column){
					fixsparse(resultMatrix);
				}
			}
		}
		//end of fixsparse part
		
	sorting(resultMatrix);
	print(resultMatrix);
	
	 }
	 
}
//end of multiply function
		 
	
		
	 
	 

			 
//MY FUNCTIONS
void fixsparse(SparseMatrix sparseMatrix[MAX_TERM]){
	int a,b,n,c;//a,b,n,c are my loop variables
	/*Finally, if the number of elements in the result matrix, 
		which should be in the same column and row, is kept in the result matrix and the other one is removed from the matrix.*/
		for(a=1;a<=sparseMatrix[0].value;a++){
 		for(b=a+1;b<=sparseMatrix[0].value;b++){
 			if(sparseMatrix[a].row ==sparseMatrix[b].row&&sparseMatrix[a].column ==sparseMatrix[b].column){
 				
 				n=b;	
 			while(n<sparseMatrix[0].value){
 				sparseMatrix[n].column=sparseMatrix[n+1].column;
 				sparseMatrix[n].row=sparseMatrix[n+1].row;
 				sparseMatrix[n].value=sparseMatrix[n+1].value;
 				
				 n++;
 			}
			 //end of first while
			 //I decreased one sparseMatrix[0].value because last two rows that are in resultMatrix would be same in end of while
 			sparseMatrix[0].value--;
 			/*The purpose of this second while production is if the sum of the total amount with the same row and column values is 0, 
			 leaving not only the second number but also the first number to close from the matrix.*/
 			if(	sparseMatrix[a].value==0){
 				c=a;
 			while(c<sparseMatrix[0].value){
 					sparseMatrix[c].column=	sparseMatrix[c+1].column;
 					sparseMatrix[c].row=sparseMatrix[c+1].row;
 					sparseMatrix[c].value=sparseMatrix[c+1].value;
 				
				 c++;
				 
 			}
			 //end of second while
			 //I decreased one sparseMatrix[0].value because last two rows that are in resultMatrix would be same in end of while
			 		sparseMatrix[0].value--;
			 }
			 //ending of second if
			 
			 }
			 //ending of first if
			 
			 	
			  }
			  //ending of second for
		   
		 }
		  //ending of first for
		
		
		  
	 }
	 //ending of fixsparse function

    void swap(int *a,int*b,int*c){
	//swapping part
	*c=*b;
	*b=*a;
	*a=*c;
}
//ending of swap function

	 	// I used this function to access the order of the arrays in the result matrix row major.I also used swap function in this function	
	void sorting (SparseMatrix sparseMatrix[MAX_TERM]){
		//i,j,k are my loop variables and temp is my temporary variable
	 	int i,j,temp,k;
	 	for(i=1;i<=sparseMatrix[0].value;i++){
	 		for(k=i+1;k<=sparseMatrix[0].value;k++){
	 			if(sparseMatrix[i].row==sparseMatrix[k].row&&sparseMatrix[i].column>sparseMatrix[k].column){
	 			swap(&sparseMatrix[k].column,&sparseMatrix[i].column,&temp);
	 			swap(&sparseMatrix[k].value,&sparseMatrix[i].value,&temp);
			 }
			 //ending of if
			 }
			 //ending of first for
		 
		 }
		 //ending of first for
	 }
	 //ending of sorting function
	 
	 
	 //print the array of structures.
//Output result
void print(SparseMatrix sparseMatrix[MAX_TERM])
{
//i is loop variable
	int i;
 printf("Sparse Matrix Multiplication:\nRow\tColumn\tValue\n");
 for (i = 0; i <=sparseMatrix[0].value; i++)
 {
if(i==0){
	printf("%d\t %d\t %d \n",sparseMatrix[0].row, sparseMatrix[0].column, sparseMatrix[0].value);
}
else{
	printf("%d\t %d\t %d \n",sparseMatrix[i].row+1, sparseMatrix[i].column+1, sparseMatrix[i].value);
}
 

 }
 
}
//ending of print function
//END OF MY FUNCTONS 	
	 
 	
	



 


