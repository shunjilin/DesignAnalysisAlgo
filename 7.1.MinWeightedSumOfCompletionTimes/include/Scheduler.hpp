//Copyright 2016 <Shunji Lin>

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include <utility>
#include <algorithm>

using Job = std::pair<int, int>;

namespace Scheduler {
    // job list input is vector of pairs,
    // pair.first is the weight of job, and pair.second is the duration of job


    int differenceScore(Job job) {
	return job.first - job.second;
    }
    
    struct differenceComparator {
	bool operator()(Job lhs, Job rhs) {
	    int lhs_score = differenceScore(lhs);
	    int rhs_score = differenceScore(rhs);
	    if (lhs_score == rhs_score) { // tie-break
		return lhs.second > rhs.second;
	    }
	    return lhs_score > rhs_score;   
	}	
    };

    // Order by decreasing value of wj - lj, tie break by scheduling higher weight first
    void differenceScheduler(std::vector<Job> &jobList) {
	std::sort(jobList.begin(), jobList.end(), differenceComparator());
    }

    double ratioScore(Job job) {
	return static_cast<double>(job.first) / static_cast<double>(job.second);
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
	    completionTime += job.second;
	    weightedSumOfCompletedTimes += job.first * (completionTime);
	}
	return weightedSumOfCompletedTimes;
    }

		
}

#endif
