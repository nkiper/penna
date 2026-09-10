Implementation of the Penna biological aging model [T. J. P. Penna, J. Stat. Phys. 78, 1629 (1995), https://link.springer.com/article/10.1007/BF02180147].

# Model Summary

The Penna model is a bit string model to simulate population aging. It implements a population of $N(t)$ individuals at time $t$, each with a genome of length $B$. The genome is a bit string determined at birth. If the $i$-th bit is one, the individual will suffer a mutation at time $i$. An individual who has passed the mutation threshold $T$ will stay alive with probability $1-N(t)/N_{max}$, where $N_{max}$ is the maximal population size. Individuals that are older than the reproduction age R generate one baby with probability $r_\text{birth}$, whose genome will be the same as the parents', except for $M$ randomly changed bits.

## Parameters
- $B$: genome size
- $T$: mutation threshold
- $N_{max}$: maximal number of individuals
- $M$: mutation rate ($M\leq B$)
- $R$: reproduction age
- $r_\text{birth}$: birth rate ($0\leq r_\text{birth}\leq 1$)