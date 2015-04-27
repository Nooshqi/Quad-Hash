

#include <iostream>
#include "Quadratic_hash_table.h"

using namespace std;

int main() {
	Quadratic_hash_table<int> ht(10);

	for ( int i = 93251234; i < 93251534; i += 9382 ) {
		ht.insert( i );
	}

	return 0;
}
