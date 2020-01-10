 #include <iostream>
#include <tgmath.h>

using namespace std;

const int size = 200;

int * Array_Sum_2 (int E_1[64], int E_2[64]);
int * Array_Sum_3 (int A[64], int D[64], int E[64]);
int * Array_Shift(int array_size, int shift_size, int array[64]);
int Array_Size(int B[64]);
int * Karatsuba(int X[2], int Y[2]);

/**************************************** Main Function *******************************************/
int main(int argc, char** argv) {
	
    int n = 64;
	int Number_1[n], Number_2[n];
	int x[2], y[2];
	
    cout << "please enter number one\n";
	for (int i = n-1; i >= 0; i--)
	{
		cin >> Number_1[i];
	}
	
	cout << "please enter number two\n";	
	for (int i = n-1; i >= 0; i--)
	{
		cin >> Number_2[i];
	}
	cout << "\nOk\n";
	cout << "Processing...\n\n";
	
	int *a, *d, *e_1, *e_2, *t, *result;
	int A[size], D[size], E_1[size], E_2[size], E[size], Temp[size], R_j[4][size], R_k[4][size], R_l[4][size], R_m[4][size], R_total[size];
	int temp = 0;
	int n_a;
	int n_e;
	int n_4 = 4, n_8 = 8, n_16 = 16, n_32 = 32;
	int Num_j_1[n_4], Num_k_1[n_8], Num_l_1[n_16], Num_m_1[n_32];
	int Num_j_2[n_4], Num_k_2[n_8], Num_l_2[n_16], Num_m_2[n_32];
	for(int m = 0; m < n_4; m++)
	{
		for(int i = 0; i < n_32; i++)
		{
			Num_m_1[i] = Number_1[(!(m % 2)) * n_32 + i];
			Num_m_2[i] = Number_2[(!(m % 3)) * n_32 + i];
		}
	
		for(int l = 0; l < n_4; l++)
		{
			for(int i = 0; i < n_16; i++)
			{
				Num_l_1[i] = Num_m_1[(!(l % 2)) * n_16 + i];
				Num_l_2[i] = Num_m_2[(!(l % 3)) * n_16 + i];
			}
			
			for (int k = 0; k < n_4; k++)
			{
				for(int i = 0; i < n_8; i++)
				{
					Num_k_1[i] = Num_l_1[(!(k % 2)) * n_8 + i];
					Num_k_2[i] = Num_l_2[(!(k % 3)) * n_8 + i];
				}
				
				for(int j = 0; j <= 3; j = j+1) 
				{	
					//**************************************Specification******************************
					for(int i = 0; i < n_4; i++)
					{
						Num_j_1[i] = Num_k_1[(!(j % 2)) * n_4 + i];
						Num_j_2[i] = Num_k_2[(!(j % 3)) * n_4 + i];
					}
					
					//**************************************Reset**************************************
					for(int i = 0; i < size; i++)
					{
						A[i] = 0; 
						D[i] = 0; 
						E_1[i] = 0; 
						E_2[i] = 0; 
						E[i] = 0;
						Temp[i] = 0;	
					}
					//**************************************A Calculation*******************************
					x[1] = Num_j_1[n_4-1];
					x[0] = Num_j_1[n_4-2];
					
					y[1] = Num_j_2[n_4-1];
					y[0] = Num_j_2[n_4-2];
				    a = Karatsuba(x, y);
				    for ( int i = size - 1; i >= 0; i-- )
				    {
				      A[i] = *(a + i);
				    }
				    //**************************************D Calculation*******************************
				    x[1] = Num_j_1[n_4-3];
					x[0] = Num_j_1[n_4-4];
					
					y[1] = Num_j_2[n_4-3];
					y[0] = Num_j_2[n_4-4];
				    d = Karatsuba(x, y);
				    for ( int i = size - 1; i >= 0; i-- )
				    {
				      D[i] = *(d + i);
				    }
				    
				    //**************************************E Calculation*******************************
				    x[1] = Num_j_1[n_4-3];
					x[0] = Num_j_1[n_4-4];
					
					y[1] = Num_j_2[n_4-1];
					y[0] = Num_j_2[n_4-2];
				    e_1 = Karatsuba(x, y);
				    for ( int i = size - 1; i >= 0; i-- )
				    {
				      E_1[i] = *(e_1 + i);
				    }
				    
				    x[1] = Num_j_1[n_4-1];
					x[0] = Num_j_1[n_4-2];
					
					y[1] = Num_j_2[n_4-3];
					y[0] = Num_j_2[n_4-4];
					e_2 = Karatsuba(x, y);
					for ( int i = size - 1; i >= 0; i-- )
				    {
				      E_2[i] = *(e_2 + i);
				    }
					t = Array_Sum_2 (E_1, E_2);
					for ( int i = size - 1; i >= 0; i-- )
					{
				    	E[i] = *(t + i);
					}
				    
					//**************************************Sizing A and E**************************************
					n_a = Array_Size (A);
					n_e = Array_Size (E);	
					//**************************************Shifing A and E*************************************
					t = Array_Shift(n_a, 4, A);
					for ( int i = size - 1; i >= 0; i-- )
				    {
				      A[i] = *(t + i);
				    }
				    
				    t = Array_Shift(n_e, 2, E);
				    for ( int i = size - 1; i >= 0; i-- )
				    {
				      E[i] = *(t + i);
				    }
				    //**************************************Result Calculation************************************
					result = Array_Sum_3 (A, D, E);
					for ( int i = size - 1; i >= 0; i-- )
				    {
				      R_j[j][i] = *(result + i);
				    }
			
				}	
				
				t = Array_Sum_2 (R_j[2], R_j[3]);
				for ( int i = size - 1; i >= 0; i-- )
				{
				   	E[i] = *(t + i);
				   	A[i] = R_j[0][i];
				   	D[i] = R_j[1][i];
				}
				//**************************************Sizing A and E**************************************
				n_a = Array_Size (A);
				n_e = Array_Size (E);	
				//**************************************Shifing A and E*************************************
				t = Array_Shift(n_a, 8, A);
				for ( int i = size - 1; i >= 0; i-- )
				{
				    A[i] = *(t + i);
				}
				    
				t = Array_Shift(n_e, 4, E);
				for ( int i = size - 1; i >= 0; i-- )
				{
				    E[i] = *(t + i);
				}
		
				t = Array_Sum_3 (A, D, E);
				for ( int i = size - 1; i >= 0; i-- )
				{
				    R_k[k][i] = *(t + i);
				}
		
			}
			t = Array_Sum_2 (R_k[2], R_k[3]);
			for ( int i = size - 1; i >= 0; i-- )
			{
				E[i] = *(t + i);
				A[i] = R_k[0][i];
				D[i] = R_k[1][i];	   	
			}
			//**************************************Sizing A and E**************************************
			n_a = Array_Size (A);
			n_e = Array_Size (E);	
			//**************************************Shifing A and E*************************************
			t = Array_Shift(n_a, 16, A);
			for ( int i = size - 1; i >= 0; i-- )
			{
				A[i] = *(t + i);
			}
				    
			t = Array_Shift(n_e, 8, E);	
			for ( int i = size - 1; i >= 0; i-- )
			{
				E[i] = *(t + i);
			}
			t = Array_Sum_3 (A, D, E);
			for ( int i = size - 1; i >= 0; i-- )
			{
				R_l[l][i] = *(t + i);
			}	
		}
		t = Array_Sum_2 (R_l[2], R_l[3]);
		for ( int i = size - 1; i >= 0; i-- )
		{
			E[i] = *(t + i);
			A[i] = R_l[0][i];
			D[i] = R_l[1][i];	   	
		}
		//**************************************Sizing A and E**************************************
		n_a = Array_Size (A);
		n_e = Array_Size (E);	
		//**************************************Shifing A and E*************************************
		t = Array_Shift(n_a, 32, A);
		for ( int i = size - 1; i >= 0; i-- )
		{
			A[i] = *(t + i);
		}
				    
		t = Array_Shift(n_e, 16, E);		
		for ( int i = size - 1; i >= 0; i-- )
		{
			E[i] = *(t + i);
		}
		
		t = Array_Sum_3 (A, D, E);
		for ( int i = size - 1; i >= 0; i-- )
		{
			R_m[m][i] = *(t + i);
		}	
	}
	t = Array_Sum_2 (R_m[2], R_m[3]);
	for ( int i = size - 1; i >= 0; i-- )
	{
		E[i] = *(t + i);
		A[i] = R_m[0][i];
		D[i] = R_m[1][i];	   	
	}
	//**************************************Sizing A and E**************************************
	n_a = Array_Size (A);
	n_e = Array_Size (E);	
	//**************************************Shifing A and E*************************************
	t = Array_Shift(n_a, 64, A);
	for ( int i = size - 1; i >= 0; i-- )
	{
		A[i] = *(t + i);
	}
				    
	t = Array_Shift(n_e, 32, E);			
	for ( int i = size - 1; i >= 0; i-- )
	{
		E[i] = *(t + i);
	}
	
	t = Array_Sum_3 (A, D, E);
	for ( int i = size - 1; i >= 0; i-- )
	{
		R_total[i] = *(t + i);
	}	
	
	cout << endl << "Result = ";
	for ( int i = size - 1; i >= 0; i-- )
	{
		cout << R_total[i];
	}
}

/******************************** Function declaration *****************************************/
int * Array_Sum_2 (int E_1[200], int E_2[200])
{
	int N = 200;
	int temp = 0;
	int E[200];
	for ( int i = 0; i < N; i++ )
	{			
	   	if (10 <= (E_1[i] + E_2[i]))
		{
			E[i] = temp + ((E_1[i] + E_2[i] ) % 10);
			temp = (E_1[i] + E_2[i] ) / 10;
		}
		else
		{
	 		E[i] = temp + E_1[i] + E_2[i];
	 		temp = 0;
		}
	}
	return E;
}


int * Array_Sum_3 (int A[200], int D[200], int E[200])
{
	int temp = 0;
	int N = 200;
	int R[200];
	for ( int i = 0; i < N; i++ )
	{	
	    if (10 <= (temp + A[i] + D[i] + E[i]))
		{
			R[i] = (temp + E[i] + A[i] + D[i]) % 10;
			temp = (temp + E[i] + A[i] + D[i]) / 10;
		}
		else
		{
			R[i] = temp + E[i] + A[i] + D[i];
			temp = 0;
		}
	}
	return R;
}


int * Array_Shift(int array_size, int shift_size, int array[200])
{
	for  (int i = (array_size + shift_size); i >= 0; i-- )
	{
		if (i >= (shift_size - 1))
			array[i] = array[i-shift_size];
		else
			array[i] = 0;
	}
	return array;
}

int Array_Size (int B[200])
{
	int N = 200;
	int Size;
	for (int i = N-1; i >= 0; i--)
	{
		if (B[i] != 0)
		{
			Size = i;
			break;
		}	
	}
	return Size;
		
}


int * Karatsuba(int X[2], int Y[2])
{
	int a = 0, n_a = 0, d = 0, n_d = 0, e_1 = 0, e_2 = 0, n_e_1 = 0, n_e_2 = 0, result = 0, temp = 0;
	static int Arr_a[size], Arr_d[size], Arr_e_1[size], Arr_e_2[size], Arr_e[size], Arr_result[size];
	for(int i = 0; i < size; i++)
	{
		Arr_a[i] = 0; 
		Arr_d[i] = 0; 
		Arr_e_1[i] = 0; 
		Arr_e_2[i] = 0;
		Arr_e[i] = 0; 
		Arr_result[i] = 0;
	}
	
	// A calculation
	a = X[1] * Y[1];
	n_a = log10(a);
	for ( int i = 0; i <= n_a; i++ )
	{
		Arr_a[i] = a % 10;
		a = a / 10;
	}
	
	// D calculation
	d = X[0] * Y[0];
	n_d = log10(d);
	for ( int i = 0; i <= n_d; i++ )
	{
		Arr_d[i] = d % 10;
		d = d / 10;
	}
	
	//E calculation
	e_1 = X[1] * Y[0];
	n_e_1 = log10(e_1);
	for ( int i = 0; i <= n_e_1; i++ )
	{
		Arr_e_1[i] = e_1 % 10;
		e_1 = e_1 / 10;
	}
	
	e_2 = X[0] * Y[1];
	n_e_2 = log10(e_2);
	for ( int i = 0; i <= n_e_2; i++ )
	{
		Arr_e_2[i] = e_2 % 10;
		e_2 = e_2 / 10;
	}
	
 	for ( int i = 0; i < size; i++ )
	{
		
    	if (10 <= (Arr_e_1[i] + Arr_e_2[i]))
		{
			Arr_e[i] = temp + ((Arr_e_1[i] + Arr_e_2[i] ) % 10);
			temp = (Arr_e_1[i] + Arr_e_2[i] ) / 10;
		}
		else
		{
	 		Arr_e[i] = temp + Arr_e_1[i] + Arr_e_2[i];
	 		temp = 0;
		}
	}
	temp = 0;

	//Shifing A and E
	for  (int i = 16; i >= 0; i-- )
	{
		Arr_a[i] = Arr_a[i-2];	
	}
	for  (int i = 16; i >= 0; i-- )
	{
		Arr_e[i] = Arr_e[i-1];	
	}

	//Result Calculation
	temp = 0;
	for ( int i = 0; i <= 16; i++ )
	{
    	if (10 <= (temp + Arr_a[i] + Arr_d[i] + Arr_e[i]))
		{
			Arr_result[i] = temp +((Arr_e[i] + Arr_a[i] + Arr_d[i]) % 10);
			temp = (Arr_e[i] + Arr_a[i] + Arr_d[i]) / 10;
		}
		else
		{
	 		Arr_result[i] = temp + Arr_e[i] + Arr_a[i] + Arr_d[i];
	 		temp = 0;
		}
	}
	return Arr_result;
}




