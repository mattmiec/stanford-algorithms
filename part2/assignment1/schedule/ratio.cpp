// schedule jobs in decreasing order of ratio weight/length
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

bool compare(std::pair<int, int>, std::pair<int, int>);

int main()
{
	int w, l;
	std::vector<std::pair<int, int> > jobs; // vector to hold (w, l) pairs
	std::ifstream myfile("jobs.txt");

	// read number of jobs and allocate vector accordingly
	myfile >> w;
	jobs.reserve(w);

	// loop over jobs and add to job
	while (myfile >> w) {
		myfile >> l;
		jobs.push_back(std::make_pair(w, l));
	}

	// sort using difference score
	std::sort(jobs.begin(), jobs.end(), compare);

	// calculate weighted sum
	long long c = 0, sum = 0;
	for (auto it = jobs.begin(); it != jobs.end(); it++) {
		c += it->second;
		sum += c * it->first;
	}

	std::cout << "sum of weighted completion times: " << sum << std::endl;
}


bool compare(std::pair<int, int> job1, std::pair<int, int> job2)
// returns true if  w1/l1 > w2/l2
{
	return ((float)(job1.first))/((float)(job1.second)) > ((float)(job2.first))/((float)(job2.second));
}