//Copyright 2016 Shunji Lin

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Scheduler.hpp"
#include "steadyClockTimer.hpp"

using namespace Scheduler;

int main(int argc, char *argv[])
{
    std::ifstream infile;
    infile.open("../jobs.txt");
    if (!infile) {
	std::cout << "Opening file failed." << std::endl;
	return -1;
    }

    std::vector<Job> jobList1, jobList2;

    std::string line;
    int n_jobs;

    std::getline(infile, line); //number of jobs
    std::istringstream iss(line);
    iss >> n_jobs;
    if (iss.fail()) {
	std::cout << "Reading error or incorrect type." << std::endl;
	return -1;
    }
    for (int i = 0; i < n_jobs; ++i) {
	std::getline(infile, line);
	std::istringstream iss(line);
	int weight, length;
	iss >> weight >> length;
	if (iss.fail()) {
	    std::cout << "Reading error or incorrect type." << std::endl;
	    return -1;
	}
	Job job(weight, length);
	jobList1.emplace_back(job);
	jobList2.emplace_back(job);
    }

    SteadyClockTimer timer;
    timer.start();
    
    differenceScheduler(jobList1);
    ratioScheduler(jobList2);
    
    std::cout << "Min weighted sum of completion times for difference scheduler is :"
	      << weightedSumOfCompletionTimes(jobList1) << std::endl;
    std::cout << "Min weighted sum of completion times for ratio scheduler is :"
	      << weightedSumOfCompletionTimes(jobList2) << std::endl;
    std::cout << "time taken is: " << timer.getMs() << " ms" << std::endl;
    return 0;
}
