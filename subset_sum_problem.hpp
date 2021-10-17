//
// Created by Maciek on 17.10.2021.
//

#ifndef LAB1_SUBSET_SUM_PROBLEM_HPP
#define LAB1_SUBSET_SUM_PROBLEM_HPP
void log(std::vector<bool> solution, std::vector<int> subset);
std::vector<int> read(const std::string &filename);
int subset_sum(std::vector<bool> taken_items, std::vector<int> problem);
#endif //LAB1_SUBSET_SUM_PROBLEM_HPP
