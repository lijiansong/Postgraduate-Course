/*
	Name: Strassen
	Copyright: 
	Author: Json Lee
	Date: 26/09/16 16:10
	Description: 
	Divide and Conquer,
	P1=A11*(B12-B22)
	P2=(A11+A12)*B22
	P3=(A21+A22)*B11
	P4=A22*(B21-B11)
	P5=(A11+A22)*(B11+B22)
	P6=(A12-A22)*(B21+B22)
	P7=(A11-A21)*(B11+B12)
	
	C11=P4+P5+P6-P2
	C12=P1+P2
	C21=P3+P4
	C22=P1+P5-P3-P7
*/

#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
//add two matrices 
void add(int** MatrixA, int** MatrixB, int** MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			MatrixResult[i][j] = MatrixA[i][j] + MatrixB[i][j];
		}
	}
}

//two matrices subtraction operation  
void sub(int** MatrixA, int** MatrixB, int** MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			MatrixResult[i][j] = MatrixA[i][j] - MatrixB[i][j];
		}
	}
}

//two matrices multiply operation
void mul(int** MatrixA, int** MatrixB, int** MatrixResult, int MatrixSize)
{
	for (int i = 0; i<MatrixSize; i++)
	{
		for (int j = 0; j<MatrixSize; j++)
		{
			MatrixResult[i][j] = 0;
			for (int k = 0; k<MatrixSize; k++)
			{
				MatrixResult[i][j] = MatrixResult[i][j] + MatrixA[i][k] * MatrixB[k][j];
			}
		}
	}
}

void strassen(int N, int **MatrixA, int **MatrixB, int **MatrixC)
{
	int HalfSize = N / 2;
	int newSize = N / 2;

	if (N <= 64)    //n<=64 take normal method
	{
		mul(MatrixA, MatrixB, MatrixC, N);
	}
	else
	{
		int** A11;int** A12;int** A21;int** A22;
		int** B11;int** B12;int** B21;int** B22;
		int** C11;int** C12;int** C21;int** C22;
		int** M1;int** M2;int** M3;int** M4;int** M5;int** M6;int** M7;
		int** AResult;int** BResult;

		//making a 1 diminsional pointer based array.
		A11 = new int *[newSize];A12 = new int *[newSize];A21 = new int *[newSize];A22 = new int *[newSize];
		B11 = new int *[newSize];B12 = new int *[newSize];B21 = new int *[newSize];B22 = new int *[newSize];
		C11 = new int *[newSize];C12 = new int *[newSize];C21 = new int *[newSize];C22 = new int *[newSize];
		M1 = new int *[newSize];M2 = new int *[newSize];M3 = new int *[newSize];M4 = new int *[newSize];M5 = new int *[newSize];M6 = new int *[newSize];M7 = new int *[newSize];
		AResult = new int *[newSize];BResult = new int *[newSize];

		int newLength = newSize;

		//making that 1 diminsional pointer based array , a 2D pointer based array
		for (int i = 0; i < newSize; i++)
		{
			A11[i] = new int[newLength];
			A12[i] = new int[newLength];
			A21[i] = new int[newLength];
			A22[i] = new int[newLength];

			B11[i] = new int[newLength];
			B12[i] = new int[newLength];
			B21[i] = new int[newLength];
			B22[i] = new int[newLength];

			C11[i] = new int[newLength];
			C12[i] = new int[newLength];
			C21[i] = new int[newLength];
			C22[i] = new int[newLength];

			M1[i] = new int[newLength];
			M2[i] = new int[newLength];
			M3[i] = new int[newLength];
			M4[i] = new int[newLength];
			M5[i] = new int[newLength];
			M6[i] = new int[newLength];
			M7[i] = new int[newLength];

			AResult[i] = new int[newLength];
			BResult[i] = new int[newLength];
		}
		//splitting input Matrixes, into 4 submatrices each.
		for (int i = 0; i < N / 2; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				A11[i][j] = MatrixA[i][j];
				A12[i][j] = MatrixA[i][j + N / 2];
				A21[i][j] = MatrixA[i + N / 2][j];
				A22[i][j] = MatrixA[i + N / 2][j + N / 2];

				B11[i][j] = MatrixB[i][j];
				B12[i][j] = MatrixB[i][j + N / 2];
				B21[i][j] = MatrixB[i + N / 2][j];
				B22[i][j] = MatrixB[i + N / 2][j + N / 2];

			}
		}

		//P5[][]
		add(A11, A22, AResult, HalfSize);
		add(B11, B22, BResult, HalfSize);
		strassen(HalfSize, AResult, BResult, M1);

		//P3[][]
		add(A21, A22, AResult, HalfSize);
		strassen(HalfSize, AResult, B11, M2);

		//P1[][]
		sub(B12, B22, BResult, HalfSize);
		strassen(HalfSize, A11, BResult, M3);

		//P4[][]
		sub(B21, B11, BResult, HalfSize);
		strassen(HalfSize, A22, BResult, M4);

		//P2[][]
		add(A11, A12, AResult, HalfSize);
		strassen(HalfSize, AResult, B22, M5);


		//P7[][]
		sub(A21, A11, AResult, HalfSize);
		add(B11, B12, BResult, HalfSize);
		strassen(HalfSize, AResult, BResult, M6);

		//P6[][]
		sub(A12, A22, AResult, HalfSize);
		add(B21, B22, BResult, HalfSize);
		strassen(HalfSize, AResult, BResult, M7);

		//C11
		add(M1, M4, AResult, HalfSize);
		sub(M7, M5, BResult, HalfSize);
		add(AResult, BResult, C11, HalfSize);

		//C12
		add(M3, M5, C12, HalfSize);

		//C21
		add(M2, M4, C21, HalfSize);

		//C22
		add(M1, M3, AResult, HalfSize);
		sub(M6, M2, BResult, HalfSize);
		add(AResult, BResult, C22, HalfSize);

		//combine c11 c12 c21 c22 to get the result Matrix.
		for (int i = 0; i < N / 2; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				MatrixC[i][j] = C11[i][j];
				MatrixC[i][j + N / 2] = C12[i][j];
				MatrixC[i + N / 2][j] = C21[i][j];
				MatrixC[i + N / 2][j + N / 2] = C22[i][j];
			}
		}

		// release
		for (int i = 0; i < newLength; i++)
		{
			delete[] A11[i]; delete[] A12[i]; delete[] A21[i];
			delete[] A22[i];

			delete[] B11[i]; delete[] B12[i]; delete[] B21[i];
			delete[] B22[i];
			delete[] C11[i]; delete[] C12[i]; delete[] C21[i];
			delete[] C22[i];
			delete[] M1[i]; delete[] M2[i]; delete[] M3[i]; delete[] M4[i];
			delete[] M5[i]; delete[] M6[i]; delete[] M7[i];
			delete[] AResult[i]; delete[] BResult[i];
		}
		delete[] A11; delete[] A12; delete[] A21; delete[] A22;
		delete[] B11; delete[] B12; delete[] B21; delete[] B22;
		delete[] C11; delete[] C12; delete[] C21; delete[] C22;
		delete[] M1; delete[] M2; delete[] M3; delete[] M4; delete[] M5;
		delete[] M6; delete[] M7;
		delete[] AResult;
		delete[] BResult;
	}
}
//generate test matrices
void fill_matrix(int** MatrixA, int** MatrixB, int length)
{
	for (int row = 0; row<length; row++)
	{
		for (int column = 0; column<length; column++)
		{

			MatrixB[row][column] = (MatrixA[row][column] = rand() % 5);
			//matrix2[row][column] = rand() % 2;
		}
	}
}

int main()
{
	freopen("p10-in.txt","r",stdin);
	freopen("p10-out.txt","w",stdout);
	//using system rand to generate test matrices
	int MatrixSize = 0;
	int** MatrixA;
	int** MatrixB;
	int** MatrixC;
	
	while(cin >> MatrixSize)
	{
		int N = MatrixSize;
		cout<<"matrix size: "<<N<<endl;
		MatrixA = new int *[MatrixSize];
		MatrixB = new int *[MatrixSize];
		MatrixC = new int *[MatrixSize];
		
		for (int i = 0; i < MatrixSize; i++)
		{
			MatrixA[i] = new int[MatrixSize];
			MatrixB[i] = new int[MatrixSize];
			MatrixC[i] = new int[MatrixSize];
		}
		
		//generate test matrices
		fill_matrix(MatrixA, MatrixB, MatrixSize);
		
		//using system clock to measure time consumption
		clock_t t1, t2;
		double duration;//time duration
		t1 = clock();
		mul(MatrixA, MatrixB, MatrixC, MatrixSize);
		t2 = clock();
		duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
		cout << "grade school method time consumption: " << duration << " s" << endl;
		
		t1 = clock();
		strassen(N, MatrixA, MatrixB, MatrixC);
		t2 = clock();
		duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
		cout << "strassen method time consumption: " << duration << " s" << endl;
	}
	return 0;
} 
