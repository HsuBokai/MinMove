#include <iostream>

#include "cindex.h"

using namespace std;

CIndex::CIndex(const int n, const int m):_index(0), _max(0){
	if(n < m) {
		cerr << "Error!! n < m\n";
		return;
	}
	if(n > sizeof(int)*8-1) {
		cerr << "Error!! n too large\n";
		return;
	}
	for(int i=0; i<m; ++i) _max = _max * 2 + 1;
	for(int i=m; i<n; ++i) _max *= 2;
}

CIndex::operator int() const { return _index; }

CIndex::operator bool() const { return _index!=0; }

CIndex& CIndex::operator ++ () { 
	if(_max==0) return *this; 
	if(_index==0){
		_index = _max;
		while(_index%2==0) _index/=2;
	}
	else if(_index==_max){
		_index = 0;
	}
	else {
		int a=1, b=0, i=_index;
		while(i%2==0){
			a *= 2;
			i /= 2;
		}
		i /= 2;
		while(i%2==1){
			b = b*2+1;
			i /= 2;
		}
		_index += (a+b);
	}
	return *this; 
}

//CIndex operator ++ (int) { return *this; }

int CIndex::max() const { return _max; }

