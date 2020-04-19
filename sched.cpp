#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include "Job.h"

using namespace std;

bool comparison(Job a, Job b)
{
	return (a.profit() > b.profit());
}


std::vector<std::string>
greedy_solve(const std::vector<Job>& jobs) {
	vector<Job> job = jobs; //getting rid of const argument of jobs
	int k;
	sort(job.begin(), job.end(), comparison); //Sort the jobs by profit descending order

	//Finding the maximum Jobs to do.
	int MaxJobs = 0;
	for (int i = 0; i < job.size(); i++)
	{
		if (job[i].deadline() > MaxJobs)
			MaxJobs = job[i].deadline();
	}

	vector<string> JobNames(MaxJobs);
	//Most profitable Job Scheduling , and pushing the Name into the right spot in JobNames vector.
	for (int i = 0; i < job.size(); i++) {
		k = job[i].deadline();
		while (k > 0) {
			if (JobNames[k - 1] == "") {
				JobNames[k - 1] = job[i].name();
				break;
			}

			else
				k--; //If the job spot is taken go to the left side of the vector
		}
	}


	return JobNames;
}

//Matrix<int> dp_solve(std::vector<Job>& jobs);

int main() {
	std::ifstream ifs;
	std::string instr;
	ifs.open("jobs.txt");
	std::vector<Job> jobs;

	while (std::getline(ifs, instr)) {
		instr.erase(std::remove(instr.begin(),
			instr.end(), ' '), instr.end());
		if (instr.find('#') != std::string::npos || instr.size() == 0)
			continue;

		jobs.push_back(read_job(instr));
	}
	
	//Matrix<int> solution;
	//solution = dp_solve(jobs);
	//for (int i = 0; i < solution.rows(); i++) {
	//	for (int j = 0; j < solution.cols(); j++) {
	//		std::cout << solution[i][j] << ",";
	//	}
	//	std::cout << std::endl;
	//}

	std::vector<std::string> greedy_sol;
	greedy_sol = greedy_solve(jobs);
	auto itr = greedy_sol.begin();
	for (; itr != greedy_sol.end()-1; itr++)
		std::cout << *itr << ",";
	//skip the comma for the last item
	itr = greedy_sol.end() - 1;
	std::cout << *itr << std::endl;


}