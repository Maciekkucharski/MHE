//
// Created by Maciek on 17.10.2021.
//

#ifndef LAB1_SUBSET_SUM_PROBLEM_HPP
#define LAB1_SUBSET_SUM_PROBLEM_HPP
void log(std::vector<bool> solution, std::vector<int> subset, std::ostream &out);
double goal_function(std::vector<bool> solution, std::vector<int> problem);
std::vector<int> read(std::istream &input_file);
std::vector<bool> random_working_point(int problem_size);
void iterate_working_point(std::vector<bool> &working_point, int iterator = 0);
std::vector<std::vector<bool>> create_approximate_working_points(std::vector<bool> working_point, std::vector<int> problem);
//std::vector<bool> best_next_point(std::vector<std::vector<bool>> approximate_working_points);
#endif //LAB1_SUBSET_SUM_PROBLEM_HPP
