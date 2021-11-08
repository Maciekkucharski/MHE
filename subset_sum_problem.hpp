//
// Created by Maciek on 17.10.2021.
//

#ifndef LAB1_SUBSET_SUM_PROBLEM_HPP
#define LAB1_SUBSET_SUM_PROBLEM_HPP
void log(std::vector<bool> solution, std::vector<int> subset, std::ostream &out);
double goal_function(std::vector<bool> solution);
std::vector<int> read(std::istream &input_file);
std::pair<std::vector<bool>, double> subset_sum(std::vector<bool> solution, std::vector<int> problem, std::ostream &out = std::cout);
std::vector<bool> random_working_point(int problem_size);
void iterate_working_point(std::vector<bool> &working_point, int iterator = 0);
void is_solution(int solution);
#endif //LAB1_SUBSET_SUM_PROBLEM_HPP
