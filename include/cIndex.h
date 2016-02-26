
#ifndef _C_INDEX_
#define _C_INDEX_

class CIndex {
public:
	CIndex(const int n, const int m);
	operator int() const ;
	operator bool() const ;
	CIndex& operator ++ ();
	//CIndex operator ++ (int) { return *this; }
	int max() const ;
private:
	int _index;
	int _max;
};

#endif
