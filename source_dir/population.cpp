// population.cpp
// implementation of population class

#include "population.hpp"
#include "rng.hpp"
#include <iostream>
#include <algorithm>

namespace Penna {

count_t Population::Nmax_ = 10;

void Population::add_animal (const Animal& a){
    if (animals_.size() < Nmax_) {
        animals_.push_back(a);
    } else {
        std::cout << "Max. population size " << Nmax_ << " reached. Could not add animal.\n";
    }
}

aggr_t Population::average_age() const {
    count_t N = animals_.size();
    if ( N == 0 ) return 0;
    aggr_t total_age = 0;
    for (const auto& animal : animals_) {
        total_age += animal.age();
    }
    return total_age/N;
}

aggr_t Population::average_mutations_suffered() const {
    count_t N = animals_.size();
    if ( N == 0 ) return 0;
    aggr_t total_mutations = 0;
    for (const auto& animal : animals_) {
        total_mutations += animal.mutations();
    }
    return total_mutations/N;
}

aggr_t Population::average_mutations_total() const {
    count_t N = animals_.size();
    if ( N == 0 ) return 0;
    aggr_t total_mutations = 0;
    for (const auto& animal : animals_) {
        total_mutations += animal.genome().total_mutations();
    }
    return total_mutations/N;
}

void Population::timestep() {
    // age all animals by one
    for (auto& animal : animals_) {
        animal.grow();
    }
    // reproduce all animals with age > reproductive age
    std::vector<Animal> offspring;
    for (const auto& animal : animals_) {
        if (animal.age() > Animal::reproductive_age()) {
            Animal child = animal.reproduce();
            offspring.push_back(child);
        }
    }
    // add offspring to population
    for (const auto& child : offspring) {
        add_animal(child);
    }

    // animals with age > maxage die, animals with mutations > threshold die with prob. 1-N/N_max
    std::erase_if(animals_, [this](const Animal& a) {
        return (a.age() > Genome::max_age()) || (a.mutations() > Animal::mutation_threshold() && death_probability_check());
    });
}

bool Population::death_probability_check() {
    aggr_t prob = 1-(double)animals_.size()/Nmax_;
    return random_double() < prob;
}

} // namespace Penna