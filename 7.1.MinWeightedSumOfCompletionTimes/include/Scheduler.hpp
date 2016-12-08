//Copyright 2016 <Shunji Lin>

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include <utility>
#include <algorithm>


namespace Scheduler {

    struct Job {
	Job(int weight, int length) : weight(weight), length(length) {}
	int weight;
	int length;
    };


    int differenceScore(Job job) {
	return job.weight - job.length;
    }
    
    struct differenceComparator {
	bool operator()(Job lhs, Job rhs) {
	    int lhs_score = differenceScore(lhs);
	    int rhs_score = differenceScore(rhs);
	    if (lhs_score == rhs_score) { // tie-break
		return lhs.length > rhs.length;
	    }
	    return lhs_score > rhs_score;   
	}	
    };

    // Order by decreasing value of wj - lj, tie break by scheduling higher weight first
    void differenceScheduler(std::vector<Job> &jobList) {
	std::sort(jobList.begin(), jobList.end(), differenceComparator());
    }

    double ratioScore(Job job) {
	return static_cast<double>(job.weight) / static_cast<double>(job.length);
    }
    
    struct ratioComparator {
	bool operator()(Job lhs, Job rhs) {
	    return ratioScore(lhs) > ratioScore(rhs);
	}
    };

    // Order by decreasing value of wj / lj, tie breaking does not matter
    void ratioScheduler(std::vector<Job> &jobList) {
	std::sort(jobList.begin(), jobList.end(), ratioComparator());
    }

    long int weightedSumOfCompletionTimes(const std::vector<Job> &jobList) {
	long int completionTime = 0;
	long int weightedSumOfCompletedTimes = 0;
	for (auto &job : jobList) {
	    completionTime += job.length;
	    weightedSumOfCompletedTimes += job.weight * (completionTime);
	}
	return weightedSumOfCompletedTimes;
    }

		
}

#endif
