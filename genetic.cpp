#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <tuple>
#include <vector>
#include <numeric>

using genotype_t = std::vector<bool>;
using population_t = std::vector<genotype_t>;
using population_fitness_t = std::vector<double>;


std::random_device random_dev;
std::default_random_engine random_engine(random_dev());
std::uniform_real_distribution<double> double_random_dist(0.0, 1.0);
std::uniform_int_distribution<> rand_01(0, 1);


std::vector<int> selection_roulette(population_fitness_t fitnesses)
{
    std::vector<int> ret;
    double sum_fit = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0);
    std::uniform_real_distribution<double> random_distr(0.0, sum_fit);
    for (int j = 0; j < fitnesses.size(); j++) {
        double rand_selected = random_distr(random_engine);
        double s = fitnesses[0];
        int selected_i = fitnesses.size() - 1;
        for (int i = 0; i < fitnesses.size() - 1; i++) {
            if (s > rand_selected) {
                selected_i = i;
                break;
            }
            s = s + fitnesses[i + 1];
        }

        ret.push_back(selected_i);
    }
    return ret;
}

std::pair<genotype_t, genotype_t> empty_crossover_f(genotype_t a, genotype_t b)
{
    return {a, b};
}
genotype_t empty_mutation_f(genotype_t a, double)
{
    return a;
}

std::pair<genotype_t, genotype_t> one_point_crossover_f(genotype_t a, genotype_t b)
{
    std::uniform_int_distribution<int> cross_p_dist(0, a.size() - 1);
    int cross_p = cross_p_dist(random_engine);
    genotype_t a2 = a, b2 = b;
    for (int i = cross_p; i < a.size(); i++) {
        swap(a2[i], b2[i]);
    }
    return {a2, b2};
}

genotype_t uniform_mutation_f(genotype_t a, double p_m)
{
    auto result = a;
    for (int i = 0; i < a.size(); ++i) {
        if (double_random_dist(random_engine) < p_m) a[i] = !a[i];
    }
//    auto result = a;
//    for (auto && i : a) {
//        if (double_random_dist(random_engine) < p_m) i = !i;
//    }
    return a;
}


/**
 * genetic algorithm implementation
 * */
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
        })
{
    int iteration = 0;
    population_t population = init_population;
    population_fitness_t population_fit;
    for (auto& gene : population)
        population_fit.push_back(fitnes_f(gene, problem));

    auto get_elite = [&]() {
        int best_i = 0;
        for (int i = 0; i < population.size(); i++) {
            if (population_fit[i] > population_fit[best_i]) best_i = i;
        }
        return population[best_i];
    };
    auto replace_elite = [&](genotype_t e) {
        int worse_i = 0;
        for (int i = 0; i < population.size(); i++) {
            if (population_fit[i]< population_fit[worse_i]) worse_i = i;
        }
        population[worse_i] = e;
        population_fit[worse_i] = fitnes_f(e, problem);
    };


    while (termination_cond(population, population_fit, iteration)) {
        genotype_t elite = get_elite();
        std::vector<int> parent_pop_i = select_f(population_fit);

        population_t offspring_pop(parent_pop_i.size());
        for (int i = 1; i < parent_pop_i.size(); i += 2) {
            int parent_idx_0 = parent_pop_i[i - 1];
            int parent_idx_1 = parent_pop_i[i];
            if (double_random_dist(random_engine) < crossover_probability) {
                auto [a, b] = crossover_f(population[parent_idx_0], population[parent_idx_1]);
                offspring_pop[i - 1] = a;
                offspring_pop[i] = b;
            } else {
                offspring_pop[i - 1] = population[parent_idx_0];
                offspring_pop[i] = population[parent_idx_1];
            }
        }

        for (int i = 0; i < parent_pop_i.size(); i++) {
            offspring_pop[i] = mutation_f(offspring_pop[i], mutation_probability);
        }

        population = offspring_pop;

        for (int i = 0; i < population.size(); i++)
            population_fit[i] = fitnes_f(population[i], problem);

        replace_elite(elite);
        iteration++;
    }

    return population;
}


/////// problem implementation

double one_max(genotype_t gene)
{
    return std::accumulate(gene.begin(), gene.end(), 0.0);
}