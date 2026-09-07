// Test that genome is mutated correctly, i. e. <= M_ times.

#include <genome.hpp>

using namespace Penna;

void test_mutation_genome( count_t mutation_rate ) {
    Genome g;
    g.set_mutation_rate(mutation_rate);
    g.mutate();
    count_t mutation_count = 0;
    for (count_t i = 0; i < Genome::genome_size; ++i ) {
        if (g.gene_at(i)) {
            mutation_count += 1;
        } 
    }
    if ( mutation_rate == 0 && mutation_count != 0 ) {
        throw std::logic_error("Mutation occurred even though mutation_rate = 0.");
    } else if ( mutation_count > mutation_rate ) {
        throw std::logic_error("More mutations than mutation_rate occurred.");
    }

}

int main() {
    test_mutation_genome( 0 );
    test_mutation_genome( 1 );
    test_mutation_genome( 10 );
}
