// rng.hpp
// generate random numbers for mutations and death probabilities

#ifndef RNG_HPP
#define RNG_HPP

namespace Penna {

void init_rng(unsigned seed);
double random_double();
int random_int(int min, int max);

} // namespace Penna

#endif //RNG_HPP