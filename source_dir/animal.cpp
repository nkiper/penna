// animal.cpp
// Implementation of the animal class

#include "animal.hpp"
#include <iostream>

namespace Penna {

count_t Animal::T_ = 1;
count_t Animal::R_ = 1;
double Animal::birth_rate_ = 1;

void Animal::set_mutation_threshold ( count_t threshold ) {
    if ( threshold > Genome::max_age()) {
        std::cerr << "Warning: requested mutation threshold (" << threshold
                  << ") exceeds max age (" << Genome::max_age()
                  << "); clamping to " << Genome::max_age() << ".\n";
        threshold = Genome::max_age();
    }
    if ( threshold < 1) {
        std::cerr << "Warning: requested mutation threshold (" << threshold
                  << ") must be positive integer; clamping to " << 1 << ".\n";
        threshold = 1;
    }
    T_ = threshold;
}

void Animal::set_reproductive_age ( count_t r ) {
    if ( r > Genome::max_age()) {
        std::cerr << "Warning: requested reproductive age (" << r
                  << ") exceeds max age (" << Genome::max_age()
                  << "); clamping to " << Genome::max_age() << ".\n";
        r = Genome::max_age();
    }
    if ( r < 1) {
        std::cerr << "Warning: requested reproductive age (" << r
                  << ") must be positive integer; clamping to " << 1 << ".\n";
        r = 1;
    }
    R_ = r;
}

void Animal::set_birth_rate ( double r ) {
    if ( r > 1. ) {
        std::cerr << "Warning: requested reproductive rate (" << r
                  << ") exceeds max rate (" << 1
                  << "); clamping to " << 1 << ".\n";
        r = 1.;
    }
    if ( r < 0. ) {
        std::cerr << "Warning: requested reproductive rate (" << r
                  << ") must be larger >= 0; clamping to " << 0 << ".\n";
        r = 0.;
    }
    birth_rate_ = r;
}

void Animal::grow() {
    ++age_;
    if (age_ <= Genome::max_age() && genome_.gene_at(age_)) {
        mutations_ += 1;
    }
}

Animal Animal::reproduce() const {
    Animal child(genome_);
    child.genome_.mutate();
    return child;
}

} // namespace Penna