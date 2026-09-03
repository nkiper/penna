// genome.hpp
// Genome class for the Penna simulation

#ifndef GENOME_HPP
#define GENOME_HPP

#include <bitset>
#include <limits>

namespace Penna {

using count_t = unsigned int;


class Genome{
    public:
        static constexpr count_t genome_size = std::numeric_limits<unsigned long>::digits;
        Genome() {} // ctor (default)
        ~Genome() {} // dtor
        static void set_max_age ( count_t maxage = genome_size );
        static void set_mutation_rate( count_t rate = 0 );
        void mutate(); // mutate by flipping M_ genes
    private:
        static count_t M_; // mutation rate
        static count_t maxage_;
        std::bitset<genome_size> genes_;
};

// count_t Genome::M_ = 0; // -> genome.cpp
// count_t Genome::maxage_ = Genome::genome_size; // genome.cpp

} // namespace Penna

#endif // GENOME_HPP