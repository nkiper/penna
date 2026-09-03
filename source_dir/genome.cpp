// genome.cpp
// Implementation of the genome class

#include "genome.hpp"
#include <iostream>
#include <random>

namespace {
    constexpr int random_seed = 42;
    std::mt19937 e{random_seed};
} 

namespace Penna {

void init_rng() { // in main.cpp, call Penna::init_rng();
    std::cout << "Using random seed " << random_seed << ".\n";
}

count_t Genome::M_ = 0;
count_t Genome::maxage_ = Genome::genome_size-1;

void Genome::set_mutation_rate ( count_t rate ){
    if ( rate > maxage_ ) {
        std::cerr << "Warning: requested mutation rate (" << rate
                  << ") exceeds max age (" << maxage_
                  << "); clamping to " << maxage_ << ".\n";
        rate = maxage_;
    }
    M_ = rate;
}

void Genome::set_max_age( count_t maxage ){
    if ( maxage > genome_size-1 ) {
        std::cerr << "Warning: requested maxage (" << maxage
                  << ") exceeds genome_size (" << genome_size-1
                  << "); clamping to " << genome_size-1 << ".\n";
        maxage = genome_size-1;
    }
    if ( maxage < 1 ) {
        std::cerr << "Warning: requested maxage (" << maxage
                  << ") must be positive integer; clamping to " << 1 << ".\n";
        maxage = 1;
    }
    maxage_ = maxage;
}

void Genome::mutate() {
    // randomly flip M_ of the first maxage_ bits in genome
    std::uniform_int_distribution<count_t> dist(0,maxage_-1);
    count_t mutation_counter = 0;
    while (mutation_counter < M_) {
        genes_.flip(dist(e));
        ++mutation_counter;
    } 
}

} // namespace Penna