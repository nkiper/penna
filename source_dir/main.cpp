// main.cpp
// Run the Penna simulation.

#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "population.hpp"
#include "config.hpp"

std::string generate_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

void save_distributions(const Penna::SimulationConfig& config, int replicate_id, const Penna::Population& pop, std::string output_dir) {
    std::string base_filename = "penna_" + config.param_string() + "_rep" + std::to_string(replicate_id);
    
    // Save age distribution
    {
        std::string filename = output_dir + base_filename + "_age_dist.csv";
        std::ofstream outfile(filename);
        outfile << config.csv_header();
        outfile << "Age,Count\n";
        auto dist = pop.get_age_distribution();
        for (size_t age = 0; age < dist.size(); ++age) {
            outfile << age << "," << dist[age] << "\n";
        }
        outfile.close();
    }
    
    // Save suffered mutations distribution
    {
        std::string filename = output_dir + base_filename + "_suffered_mut_dist.csv";
        std::ofstream outfile(filename);
        outfile << config.csv_header();
        outfile << "Suffered_Mutations,Count\n";
        auto dist = pop.get_suffered_mutations_distribution();
        for (size_t mut = 0; mut < dist.size(); ++mut) {
            outfile << mut << "," << dist[mut] << "\n";
        }
        outfile.close();
    }
    
    // Save total mutations distribution
    {
        std::string filename = output_dir + base_filename + "_total_mut_dist.csv";
        std::ofstream outfile(filename);
        outfile << config.csv_header();
        outfile << "Total_Mutations,Count\n";
        auto dist = pop.get_total_mutations_distribution();
        for (size_t mut = 0; mut < dist.size(); ++mut) {
            outfile << mut << "," << dist[mut] << "\n";
        }
        outfile.close();
    }
}

void run_simulation(const Penna::SimulationConfig& config, int replicate_id, std::string output_dir) {
    auto start_time = std::chrono::high_resolution_clock::now();

    Penna::init_rng(config.seed + replicate_id);
    
    Penna::Genome::set_max_age(63);
    Penna::Animal::set_mutation_threshold(config.mutation_threshold);
    Penna::Animal::set_reproductive_age(config.reproductive_age);
    Penna::Population::set_N_max(config.N_max);
    Penna::Animal::set_birth_rate(config.birth_rate);

    // Open output file with parameter metadata in filename
    std::string filename = output_dir + "penna_" + config.param_string() + "_rep" + std::to_string(replicate_id) + ".csv";
    std::ofstream outfile(filename);
    
    // Write parameter metadata as header
    outfile << config.csv_header();
    outfile << "Iteration,Generation,Population_number,Average_age,Average_no_of_mutations,Average_total_mutations\n";

    // Initialize population
    Penna::Population pop;
    Penna::Genome::set_mutation_rate((config.max_age+1)/2);
    for (Penna::count_t n = 0; n < config.N0; ++n) {
        Penna::Genome new_genome;
        new_genome.mutate();
        Penna::Animal new_animal(new_genome);
        pop.add_animal(new_animal);
    }

    Penna::Genome::set_mutation_rate(config.mutation_rate);

    // Run simulation
    for (Penna::count_t time = 0; time < config.Tmax; ++time) {
        outfile << replicate_id << "," << time << "," << pop.N() << "," 
                << pop.average_age() << "," << pop.average_mutations_suffered() 
                << "," << pop.average_mutations_total() << "\n";
        pop.timestep();
    }

    outfile.close();

    save_distributions(config, replicate_id, pop, output_dir);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    
    std::cout << "Completed: " << filename << " (" << duration.count() << "s)" << std::endl;
}

int main() {
    std::string base_output_dir = "data";
    std::string timestamp = generate_timestamp();
    std::string output_dir = base_output_dir + "/" + timestamp + "_run/";
    
    std::filesystem::create_directories(output_dir);

    // Define parameter sweep
    std::vector<Penna::SimulationConfig> configs = {
        // max_age, T, R, N_max, birth_rate, M, N0, T_max, seed, num_runs
        // Base case
        // {63, 2, 16, 10000, 0.1, 4, 1000, 10000, 42, 100},
        
        // Vary mutation threshold
        {63, 1, 16, 10000, 0.1, 4, 1000, 10000, 42, 40},
        {63, 3, 16, 10000, 0.1, 4, 1000, 10000, 42, 40},
        
        // Vary reproductive age
        {63, 2, 12, 10000, 0.1, 4, 1000, 10000, 42, 40},
        {63, 2, 20, 10000, 0.1, 4, 1000, 10000, 42, 40},
        
        // Vary birth rate
        {63, 2, 16, 10000, 0.05, 4, 1000, 10000, 42, 40},
        {63, 2, 16, 10000, 0.2, 4, 1000, 10000, 42, 40}
    };

    for (const auto& config : configs) {
        for (int rep = 0; rep < config.num_runs; ++rep) {
            run_simulation(config, rep, output_dir);
        }
    }

    return 0;
}