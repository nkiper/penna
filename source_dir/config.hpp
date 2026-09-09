// config.hpp
#ifndef PENNA_CONFIG_HPP
#define PENNA_CONFIG_HPP

#include <string>
#include <sstream>

namespace Penna {

struct SimulationConfig {
    // Model parameters
    count_t max_age;
    count_t mutation_threshold;
    count_t reproductive_age;
    count_t N_max;
    double birth_rate;
    count_t mutation_rate;
    
    // Simulation parameters
    count_t N0;           // initial population
    count_t Tmax;         // simulation duration
    int seed;
    int num_runs;   // number of runs per config
    
    // Generate a filename-safe parameter string
    std::string param_string() const {
        std::stringstream ss;
        ss <<"maxage_" << max_age
           << "_T_" << mutation_threshold 
           << "_R_" << reproductive_age 
           << "_br_" << birth_rate
           << "_M_" << mutation_rate
           << "_N0_" << N0
           << "_Nmax_" << N_max;
        return ss.str();
    }
    
    // Generate a header line for CSV with metadata
    std::string csv_header() const {
        std::stringstream ss;
        ss << "# Config: max_age=" << max_age
           << " mutation_threshold=" << mutation_threshold
           << " reproductive_age=" << reproductive_age
           << " birth_rate=" << birth_rate
           << " mutation_rate=" << mutation_rate
           << " N0=" << N0 << " Nmax=" << N_max << " Tmax=" << Tmax << "\n";
        return ss.str();
    }
};

} // namespace Penna

#endif // PENNA_CONFIG_HPP