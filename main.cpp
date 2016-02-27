#include <vector>

#include <stdio.h> // sscanf
#include <fcntl.h> // open
#include <unistd.h> // close read

#include "cIndex.h"

using namespace std;

int make_table(const vector<int>& row, const CIndex& ci_i, const int* const table){
	int k = (int)(ci_i), index = 0, value = 1, max = 0;
	while(k>0){
		if(k%2==1){
			int option = row[index] + table[(int)(ci_i) - value];
			if(option > max) max = option;
		}
		++index;
		value *= 2;
		k /= 2;
	}
	return max;
}

int minMove(const vector< vector<int> >& matrix) {
	int m = matrix.size();
	int n = matrix[0].size();
	CIndex ci_m(n,m);
	int* table = new int[ci_m.max()+1];
	table[0] = 0;
	for(int i=0; i<m; ++i){
		CIndex ci_i(n,i+1);
		while(++ci_i){
			table[(int)(ci_i)] = make_table(matrix[i], ci_i, table);
		}
	}
	int total_sum = 0;
	int* column_max = new int[n];
	for(int i=0; i<n; ++i){
		int max = 0;
		for(int j=0; j<m; ++j){
			int value = matrix[j][i];
			if(value > max) max = value;
			total_sum += value;
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
	delete [] column_max;
	delete [] table;
	fprintf(stdout, "total_sum = %d\n", total_sum);
	fprintf(stdout, "total_max = %d\n", total_max);
	return total_sum - total_max;
}

#define BUFSIZE 10

int main(int argc, char* argv[]){
	if(argc < 2){
		fprintf(stderr, "%s < boxes.data >\n", argv[0]);
		return -1;
	}
	int fd = open(argv[1], O_RDONLY, 0666);
	if(fd < 0){
		fprintf(stderr, "%s file not found\n", argv[1]);
		return -1;
	}
	vector< vector<int> > matrix;
	bool isReady = false;
	char num_buf[10];
	int index = 0;
	char buf[BUFSIZE];
	int len;
	int column = 0;
	while((len = read(fd, buf, BUFSIZE)) > 0){
		for(int i=0; i<len; ++i) {
			char c = buf[i];
			if(!isReady && c==',') matrix.push_back( vector<int>() );
			else if(!isReady && c=='\n'){
				matrix.push_back( vector<int>() );
				isReady = true;
			}
			else if('0' <= c && c <= '9' ) num_buf[index++] = c;
			else if(isReady && (c==',' || c=='\n')){
				int num = 0;
				sscanf(num_buf, "%d", &num);
				while(index--) num_buf[index] = 0;
				index = 0;
				matrix[column++].push_back(num);
				if(c=='\n') column = 0;
			}
		}
	}
	if( close(fd) < 0 ){
		fprintf(stderr, "close file %s fail\n", argv[1]);
		return -1;
	}
	fprintf(stdout, "minMove = %d\n", minMove(matrix));
	return 0;
}
