//Copyright 2016 <Shunji Lin>

#include <gmock/gmock.h>
#include "Scheduler.hpp"
#include <random>
#include <vector>
#include <utility>

using namespace testing;
using namespace Scheduler;
using Job = std::pair<int, int>;
const int N_JOBS = 10;

class JobListInitialize : public Test {
public:
    std::default_random_engine generator;
    std::uniform_int_distribution<int>
    distribution{std::uniform_int_distribution<int>(0,100)};
    std::vector<Job> jobList;

    virtual void SetUp() {
	for (int i = 0; i < N_JOBS; ++i) {
	    jobList.emplace_back(std::make_pair(distribution(generator),
					     distribution(generator)));
	}
    }
    
};

/***********************//**
 * Difference Scheduler
 ***************************/

TEST_F(JobListInitialize, DifferenceSchedulerReturnsCorrectSize) {
    differenceScheduler(jobList);
    ASSERT_EQ(N_JOBS, jobList.size());
}


TEST_F(JobListInitialize, DifferenceSchedulerMaintainsDifferenceInvariant) {
    differenceScheduler(jobList);
    bool invariantMaintained = true;
    for (int i = 0; i < N_JOBS - 1; ++i) {
	if (jobList[i].first - jobList[i].second < jobList[i+1].first - jobList[i+1].second) {
	    invariantMaintained = false;
	    break;
	}
    }
    ASSERT_EQ(true, invariantMaintained);
}

TEST_F(JobListInitialize, DifferenceSchedulerMaintainsTieBreakInvariant) {
    differenceScheduler(jobList);
    bool invariantMaintained = true;
    for (int i = 0; i < N_JOBS - 1; ++i) {
	if (jobList[i].first - jobList[i].second == jobList[i+1].first - jobList[i+1].second) {
	    if (jobList[i].first < jobList[i+1].first) {
		invariantMaintained = false;
		break;
	    }
	}
    }

    ASSERT_EQ(true, invariantMaintained);
}

/******************//**
 * Ratio Scheduler
 **********************/

TEST_F(JobListInitialize, RatioSchedulerReturnsCorrectSize) {
    ratioScheduler(jobList);
    ASSERT_EQ(N_JOBS, jobList.size());
}

TEST_F(JobListInitialize,RatioSchedulerMaintainsRatioInvariant) {
    ratioScheduler(jobList);
    bool invariantMaintained = true;
    for (int i = 0; i < N_JOBS - 1; ++i) {
	if (static_cast<double>(jobList[i].first) / static_cast<double>(jobList[i].second) <
	    static_cast<double>(jobList[i+1].first) / static_cast<double>(jobList[i+1].second)) {
	    invariantMaintained = false;
	    break;
	}
    }
    ASSERT_EQ(true, invariantMaintained);
}

/***********************************************************//**
 * Compare Two Schedulers' Weighted Sum of Completion Times
 ***************************************************************/

TEST_F(JobListInitialize, DifferenceSchedulerNotBetterThanRatioScheduler) {
    std::vector<Job> differenceJobList = jobList;
    std::vector<Job> ratioJobList = jobList;
    differenceScheduler(differenceJobList);
    ratioScheduler(ratioJobList);
    ASSERT_GE(weightedSumOfCompletionTimes(differenceJobList), 
		weightedSumOfCompletionTimes(ratioJobList));
}


int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
