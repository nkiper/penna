// test that animal default ctor works.

#include <animal.hpp>

using namespace Penna;

void test_animal_ctor() {
    Animal a;
    for (count_t i = 0; i < Genome::genome_size-1; ++i ) {
        if (a.mutations() > 0) {
            throw std::logic_error("Default Animal's genome contains > 0 mutations.");
        }
        a.grow();
    }
}

int main () {
    test_animal_ctor();
}