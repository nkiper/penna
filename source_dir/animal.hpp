// animal.hpp
// Animal class for the Penna simulation

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "genome.hpp"

namespace Penna {

class Animal {
    public:
        Animal() : genome_(), age_(0), mutations_(0) {} // default ctor
        Animal(const Genome& g) : genome_(g), age_(0), mutations_(g.gene_at(0)) {} // ctor from genome
        // ~Animal() {} // dtor not needed, handled by compiler

        static void set_mutation_threshold( count_t );
        static void set_reproductive_age( count_t );
        static void set_birth_rate( double );

        Genome genome() const { return genome_; };
        count_t age() const { return age_; }; // age of the animal
        count_t mutations() const { return mutations_; }; // count no. of deleterious mutations already suffered
        static count_t reproductive_age() { return R_;};
        static count_t mutation_threshold() { return T_;};
        static double birth_rate() { return birth_rate_; };
        void grow(); // increase age by 1
        Animal reproduce() const; // produce new animal
    private:
        Genome genome_; // animal's genome string
        static count_t T_; // mutation threshold
        static count_t R_; // reproductive age
        static double birth_rate_; // probability of producing an offspring
        count_t age_; // age of the animal (timesteps since birth)
        count_t mutations_; // total deleterious mutations suffered
};

} // namespace Penna

#endif // ANIMAL_HPP