
#ifndef LAB1_GENETIC_H
#define LAB1_GENETIC_H

#include <functional>

using genotype_t = std::vector<bool>;
using population_t = std::vector<genotype_t>;
using population_fitness_t = std::vector<double>;

std::vector<int> selection_roulette(population_fitness_t fitnesses);
std::pair<genotype_t, genotype_t> empty_crossover_f(genotype_t a, genotype_t b);
genotype_t empty_mutation_f(genotype_t a, double);
std::pair<genotype_t, genotype_t> one_point_crossover_f(genotype_t a, genotype_t b);
genotype_t uniform_mutation_f(genotype_t a, double p_m);
population_t genetic_algorithm(
        std::vector<int> problem,
        std::function<double(std::vector<bool>, std::vector<int>)> fitnes_f,
        const population_t init_population,
        double crossover_probability,
        double mutation_probability,
        std::function<std::pair<genotype_t, genotype_t>(genotype_t, genotype_t)> crossover_f,
        std::function<genotype_t(genotype_t, double)> mutation_f,
        std::function<std::vector<int>(population_fitness_t)> select_f,
        std::function<bool(population_t, population_fitness_t, int)> termination_cond = [](auto, auto, auto i) {
            return i < 100;
        });
double one_max(genotype_t gene);


#endif //LAB1_GENETIC_H
