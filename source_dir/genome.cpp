// genome.cpp
// Implementation of the genome class

#include "genome.hpp"
#include "rng.hpp"
#include <iostream>
#include <set>

namespace Penna {

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
    std::set<count_t> flipped;
    while (flipped.size() < M_) {
        count_t pos = random_int(0, maxage_ - 1);
        if (pos >= genome_size) {
            std::cerr << "ERROR in mutate: random_int returned " << pos 
                      << " (genome_size = " << genome_size 
                      << ", maxage_ = " << maxage_ << ")\n";
        }
        flipped.insert(pos);  // set automatically ignores duplicates
    }
    for (count_t pos : flipped) {
        genes_.flip(pos);
    }
}

count_t Genome::total_mutations() const {
    count_t mutation_count = 0;
    for (count_t i = 0; i < Genome::genome_size; ++i ) {
        if ( this->gene_at(i) ) {
            mutation_count += 1;
        } 
    }
    return mutation_count;
}

bool Genome::gene_at( count_t i ) const { 
    if (i >= genome_size) {
        std::cerr << "ERROR in gene_at: index " << i 
                << " >= genome_size " << genome_size << "\n";
        return false;
    }
    return genes_.test(i);
}

} // namespace Penna