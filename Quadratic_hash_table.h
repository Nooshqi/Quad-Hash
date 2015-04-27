/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  bkinuthi @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int erase_count;
		int power;
		int array_size;
		int mask;
		Type *array;
		bin_state_t *occupied;

		int hash( Type const & ) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), erase_count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

// Your implementation here
template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table(){
	//The destructor clears everything from the array and also deletes the occupied array

	clear();
	//delete[] array;
	//array = nullptr;
	delete[] occupied;
	occupied = nullptr;

}

template <typename Type>
//Calls the hash function to return the hash # of the object
int Quadratic_hash_table<Type>::hash(Type const &obj) const{
	int hash = static_cast<int>(obj) % array_size;
	if (hash < 0){
		hash += array_size;

	}

 return hash;

}

template <typename Type>
int Quadratic_hash_table<Type>::size() const{
	//returns the number of objects that have been stored in the container
	//thus returns the updated element count 
	return count;
}



template <typename Type>
int Quadratic_hash_table<Type>::capacity() const{
	//returns the size of the container in this case the array capacity
	return array_size;
}




template <typename Type>
double Quadratic_hash_table<Type>::load_factor() const{
	//returns the load_factor ratio(λ) --> occupied bins / total # of bins 
	double total = static_cast<double>(count + erase_count);
	return total/array_size;
}




template <typename Type>
bool Quadratic_hash_table<Type>::empty() const{
	//checks if table is empty returns true(when empty) or false
	return(size() == 0);
}



template <typename Type>
bool Quadratic_hash_table<Type>::member( Type const &obj ) const{
	//returns true if the parsed object is in the table, false otherwise

int initial = hash(obj);
int bin = 0;
for ( int k = 0; k < array_size; ++k ) {
	    bin = (initial + (k + k*k)/2) % array_size;
		if(occupied[bin] == OCCUPIED){
			if(array[bin] == obj){
				return true;
			}
		}
		else if(occupied[bin] == UNOCCUPIED){
			return false;
		}    
		


}
return false;
}



template <typename Type>
Type Quadratic_hash_table<Type>::bin( int n ) const{
	//returns the entry in the parsed bin/location number
	//function is undefined if the location/bin is empty
	return array[n];

}


template <typename Type>
void Quadratic_hash_table<Type>::print() const{
	//prints out the class: Used for testing and not marked
	std::cout<<*this<<std::endl;
	for (int i = 0; i<array_size ; i++){
		std::cout<<array[i];
	}

}

template <typename Type>
//inserts an object to the hash table/array
void Quadratic_hash_table<Type>::insert( Type const &obj ){

int initial = hash(obj);
int bin = 0;
if (array_size == count){     
	throw overflow();

}

if(occupied[initial] == UNOCCUPIED){
	array[initial] = obj;
	occupied[initial] = OCCUPIED;
	count++;
	return;
} 

for ( int k = 0; k < array_size; ++k ) {
	    bin = (initial + (k + k*k)/2) % array_size;
	    // std::cout<<"bin="<<bin<<std::endl;
		if(occupied[bin] == UNOCCUPIED){
			array[bin] = obj;
			occupied[bin] = OCCUPIED;
			count++;
			return;
		}

}

}



template <typename Type>
//erases the parsed object from the hashtable/array and returns true, else false 
//done by getting the bin index/hash # and jumping to the pos and erasing else 
//exit if uniccupied
bool Quadratic_hash_table<Type>::erase( Type const &obj ){

int initial = hash(obj);
int bin = 0;
if(occupied[initial] == OCCUPIED){
	if(array[bin] == obj){
		occupied[bin] = ERASED;
		count -=1;
		erase_count++;
		return true;
	}
}
for ( int k = 0; k < array_size; ++k ) {
		    bin = (initial + (k + k*k)/2) % array_size;
		if(occupied[bin] == OCCUPIED){
			if(array[bin] == obj){
				occupied[bin] = ERASED;
				count -=1;
				erase_count++;
				return true;
			}
		}
		else if(occupied[bin] == UNOCCUPIED){
			return false;
		}    
		
}
return false;

}



template <typename Type>
//Deletes array and sets all the counters to zero, also sets everything 
//in the occupied array to 'unoccupied'
void Quadratic_hash_table<Type>::clear(){

	delete[] array;
	array = nullptr;
	count = 0;
	erase_count = 0;
	//array_size = 0;
	for (int i=0; i<array_size ; i++){
		occupied[i] = UNOCCUPIED;
	}

}


template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
