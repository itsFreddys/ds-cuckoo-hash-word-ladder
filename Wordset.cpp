#include "Wordset.hpp"
#include <string>


unsigned polynomialHashFunction(const std::string &s, unsigned base, unsigned mod)
{
    unsigned total = 0;
    unsigned base_multi = 1;  // Initialize power of base

    for (int i = s.size() - 1; i >= 0; --i)
    {
        total = (total + (static_cast<int>(s[i] - 'a') + 1) * base_multi) % mod;
        base_multi = (base_multi * base) % mod;
    }

    return total;
}




WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold)
{
    thresh = evictionThreshold;
    cap = initialCapacity;
    num_keys = 0;

    t0 = new std::string[cap];
    t1 = new std::string[cap];
}

WordSet::~WordSet()
{
    delete[] t0;
    delete[] t1;
}

void WordSet::insert(const std::string & s)
{
    if (contains(s)) {return;}

    unsigned i,i2;

    unsigned evict_count = thresh;
    std::string temp_s = s;
    std::string evicted_s;
    bool eviction = true;


    while (eviction){
        if (evict_count <= 1) { // need to rehash and resize and reset threshold counter to try again to add that key.
            resize();
            evict_count = thresh;
        }
        i = polynomialHashFunction(temp_s, BASE_H1, cap);
        if (!t0[i].empty()){
            // there is an eviction happening
            evicted_s = t0[i];
            t0[i] = temp_s;
            evict_count--;
            i2 = polynomialHashFunction(evicted_s, BASE_H2, cap);
            if (!t1[i2].empty()){
                // there is another eviction, but in t1, so need to do the loop again.
                temp_s = t1[i2];
                t1[i2] = evicted_s;
                evict_count--;
            } else {
                t1[i2] = evicted_s;
                eviction = false;
            }

        } else {
            // no eviction
            t0[i] = temp_s;
            eviction = false;
        }
    } num_keys++;

}


bool WordSet::contains(const std::string & s) const
{
    unsigned i0 = polynomialHashFunction(s, BASE_H1, cap);
    unsigned i1 = polynomialHashFunction(s, BASE_H2, cap);

    if (t0[i0] == s || t1[i1] == s){
        return true;
    }
    return false;  // stub, not correct.
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
    return num_keys; // this is not the right answer.
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
    // for testing what its cap, thresh, and num_keys are
//    std::cout<<"cap: "<<cap<<" thresh: "<<thresh<<" num_keys: "<<num_keys<<std::endl;
    return cap; // that isn't even a prime number!
}

void WordSet::print_arrays() {
    for (unsigned i = 0; i < cap; ++i){
        std::cout<<"t0: "<<t0[i]<<" "<< "t1: "<< t1[i]<<std::endl;
    }
}

void WordSet::resize(){
    unsigned old_cap = cap;
    cap = get_prime(cap);

    std::string* new_t0 = new std::string[cap];
    std::string* new_t1 = new std::string[cap];
    std::string* del_t0 = t0;
    std::string* del_t1 = t1;
    t0 = new_t0;
    t1 = new_t1;

    rehash(del_t0, del_t1, old_cap);

    delete[] del_t0;
    delete[] del_t1;
}

void WordSet::rehash(std::string* old_t0, std::string* old_t1, unsigned old_cap){
    num_keys = 0;
    for (unsigned i = 0; i < old_cap; i++){
        if (!old_t0[i].empty()){
            insert(old_t0[i]);
        }
        if (!old_t1[i].empty()){
            insert(old_t1[i]);
        }
    }
}

unsigned get_prime(unsigned cap){
    unsigned prime = cap*2;
    while (true){
        if (prime % 2 == 0 || prime % 3 == 0){
            prime++;
        } else {return prime;}
    }
}