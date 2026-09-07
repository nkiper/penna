// Test that genome is initialized with only good genes by default

#include <genome.hpp>

using namespace Penna;

void test_default_genome() {
    Genome g;
    for (count_t i = 0; i < Genome::genome_size; ++i ) {
        if (g.gene_at(i)) {
            throw std::logic_error("Default Genome contains > 0 mutations.");
        } 
    }
}

int main() {
    test_default_genome();
}
