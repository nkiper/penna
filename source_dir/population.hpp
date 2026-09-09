// population.hpp
// Population class for the Penna simulation

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "animal.hpp"
#include <vector>

namespace Penna {

using aggr_t = double; // type for aggregate values

class Population {
    public:
        static void set_N_max( count_t );

        void add_animal (const Animal& a);
        count_t N() const {return animals_.size();}
        aggr_t average_age() const;
        aggr_t average_mutations_suffered() const; // mutations already suffered up to present time
        aggr_t average_mutations_total() const; // total mutations in genomes

        void timestep(); // age all animals by one, reproduce, die
        bool death_probability_check(); // determine death prob. based on current population size

        std::vector<count_t> get_age_distribution() const;
        std::vector<count_t> get_suffered_mutations_distribution() const;
        std::vector<count_t> get_total_mutations_distribution() const;
    private:
        std::vector<Animal> animals_;
        static count_t Nmax_;
};

} // namespace Penna

#endif //POPULATION_HPP