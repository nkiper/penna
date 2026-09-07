// test that animal default ctor works.

#include <animal.hpp>

using namespace Penna;

void test_animal_copy_constructor() {
    Genome::set_mutation_rate(10);
    Genome g;
    g.mutate();
    Animal a(g);
    Animal b(a);
    for (count_t i = 0; i < Genome::genome_size-1; ++i ) {
        if (a.mutations() != b.mutations()) {
            throw std::logic_error("Copy assignment causes mutations.");
        } 
        a.grow();
        b.grow();
    }
}

int main () {
    test_animal_copy_constructor();
}