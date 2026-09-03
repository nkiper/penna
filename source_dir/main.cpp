// main.cpp
// Run the Penna simulation.

#include <iostream>
#include "animal.hpp"

int main() {
    Penna::init_rng();
    
    Penna::Genome::set_max_age(10);
    Penna::Genome::set_mutation_rate(5);
    Penna::Animal a;
    a.grow();
    a.grow();
    Penna::Animal b = a.reproduce();
    while ( a.age() < 10){
        a.grow();
        b.grow();
    }

    std::cout << "Parent age: " << a.age() << "\n";
    std::cout << "Child age: " << b.age() << "\n";
    std::cout << "Parent mutation count: " << a.mutations() << "\n";
    std::cout << "Child mutation count: " << b.mutations() << "\n";

    return 0;
}