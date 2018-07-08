#ifndef GUARD_unionfind
#define GUARD_unionfind

#define KEYTYPE unsigned long

#include <iostream>

struct ufnode {
    KEYTYPE leader;
    KEYTYPE rank;
};

class unionfind {
    public:
	unionfind(KEYTYPE mysize) : size(mysize) {
	    ufarray = new ufnode[size];
	    for (KEYTYPE i = 0; i < size; ++i) {
		ufarray[i].leader = i;
		ufarray[i].rank = 0;
	    }
	};
	KEYTYPE find(KEYTYPE key) {
	    while (ufarray[key].leader != key) {
		key = ufarray[key].leader;
	    }
	    return key;
	};
	void unite(KEYTYPE key1, KEYTYPE key2) {
	    KEYTYPE leader1 = find(key1);
	    KEYTYPE leader2 = find(key2);
	    if (ufarray[leader1].rank > ufarray[leader2].rank) {
		ufarray[leader2].leader = leader1;
	    } else if  (ufarray[leader1].rank < ufarray[leader2].rank) {
		ufarray[leader1].leader = leader2;
	    } else {
		ufarray[leader2].leader = leader1;
		++ufarray[leader1].rank;
	    }
	};
	void print() {
	    for (KEYTYPE i = 0; i < size; ++i) {
		std::cout << "KEY " << i << std::endl;
		std::cout << "leader: " << ufarray[i].leader << std::endl;
		std::cout << "rank: " << ufarray[i].rank << std::endl << std::endl;
	    }
	};
    private:
	KEYTYPE size;
	ufnode* ufarray;
};
#endif
