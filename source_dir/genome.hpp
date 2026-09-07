// genome.hpp
// Genome class for the Penna simulation

#ifndef GENOME_HPP
#define GENOME_HPP

#include <bitset>
#include <limits>

namespace Penna {

using count_t = unsigned int;

void init_rng(); // initiate random number generator

class Genome{
    public:
        static constexpr count_t genome_size = std::numeric_limits<unsigned long>::digits;
        // Genome() {} // ctor (default) not needed, handled by compiler
        // ~Genome() {} // dtor not needed, handled by compiler
        static void set_max_age ( count_t maxage = genome_size );
        static void set_mutation_rate( count_t rate = 0 );
        static count_t max_age() { return maxage_; }
        bool gene_at( count_t i ) const { return genes_.test(i); }
        void mutate(); // mutate by flipping M_ genes
        
    private:
        static count_t M_; // mutation rate
        static count_t maxage_;
        std::bitset<genome_size> genes_;
};

} // namespace Penna

#endif // GENOME_HPP