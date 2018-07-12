#include <iostream>

#define ull unsigned long long

template <class T> class array3d {

    public:
	array3d(ull l, ull m, ull n) {
	    ll = l;
	    mm = m;
	    nn = n;
	    ptr = new T[l * m * n];
	}
	~array3d() {
	    delete ptr;
	}
	T& operator()(ull l, ull m, ull n) {
	    return ptr[l * mm * nn + m * nn + n];
	}
	void print() {
	    for (ull l = 0; l < ll; ++l) {
		for (ull m = 0; m < mm; ++m) {
		    for (ull n = 0; n < nn; ++n) {
			std::cout << operator()(l, m , n) << " ";
		    }
		    std::cout << std::endl;
		}
		std::cout << std::endl;
	    }
	}
    private:
	T* ptr;
	ull ll, mm, nn;
};
