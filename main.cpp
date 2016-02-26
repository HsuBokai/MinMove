#include<iostream>

#include "cIndex.h"

using namespace std;

int main(){
	int m = 5;
	int n = 30;
	int* matrix = new int[m*n];
	for(int i=0; i<m; ++i){
		for(int j=0; j<n; ++j){
			matrix[i*n + j] = (i+1)*(j+1);
			cout << matrix[i*n + j] << '\t';
		}
		cout << '\n';
	}
	CIndex ci_m(n,m);
	int* table = new int[ci_m.max()+1];

	table[0] = 0;
	for(int i=0; i<m; ++i){
		CIndex ci_i(n,i+1);
		while(++ci_i){
			int k = (int)(ci_i), index = 0, value = 1, max = 0, base = i*n;
			while(k>0){
				while(k%2==0) {
					++index;
					value *= 2;
					k /= 2;
				}
				int option = matrix[base + index] + table[(int)(ci_i) - value];
				if(option > max) max = option;
				++index;
				value *= 2;
				k /= 2;
			}
			table[(int)(ci_i)] = max;
		}
	}
	int* column_max = new int[n];
	for(int i=0; i<n; ++i){
		int max = 0;
		for(int j=0; j<m; ++j){
			int value = matrix[j*n+i];
			if(value > max) max = value;
		}
		column_max[i] = max;
	}
	int total_max = 0;
	while(++ci_m){
		int k = (int)(ci_m), sum = 0;
		for(int i=0; i<n; ++i){
			if(k%2==0) sum += column_max[i];
			k /= 2;
		}
		int option = table[(int)(ci_m)] + sum;
		if(option > total_max) total_max = option;
	}
	cout << "total_max = " << total_max << '\n';
	delete [] column_max;
	delete [] table;
	delete [] matrix;
	return 0;
}
