#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <algorithm>
#include "archlab.hpp"
#include <cstdlib>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <list>
#include <set>
#include <unordered_set>
#include <iomanip> // for setprecision
#include "pin_tags.h"

#include <iostream>
#include <algorithm>
#include <iterator>

// These macros, MY_START_TIMER and MY_STOP_TIMER, are used specifically to do two things:
// 1. create new timers for each phase, to see how long each portion takes 
// 2. create moneta tags for each phase
// To get only moneta traces, continue to use DUMP_START_ALL and DUMP_STOP
#define MY_START_TIMER(tag) {				\
			ArchLabTimer timer;		\
			timer.attr("phase", tag).go();	\
			DUMP_START_ALL(tag, false) 
				    
#define MY_STOP_TIMER(tag) 	       	    DUMP_STOP(tag);	\
	}
		    
using namespace std;

template <class T>
float sum_datastructure(T &values){
	DUMP_START_ALL("sum", true);
	float float_sum = 0.0;
	for (auto i: values){
		float_sum += i;
	}
	DUMP_STOP("sum");
	return float_sum;
}

unordered_set<float> init_random_unordered_set(int size){
	unordered_set<float> values;
	srand(666);
	while((int)values.size() < size){
		values.insert(float(rand())/float(RAND_MAX));
	}
	return values;
}

vector<float> init_random_vector(int size){
	vector<float> values;
	//Use the unordered_set to ensure values are unique
	//To compare error between set,unordered_set and other datastructures
	unordered_set<float> unique_values = init_random_unordered_set(size); 
	values.resize(size);
	int i =0;
	for(auto val: unique_values){
		values[i++] = val;
	}
	return values;
}

list<float> init_random_list(int size){
	list<float> values;
	//Use the unordered_set to ensure values are unique
	//To compare error between set,unordered_set and other datastructures
	unordered_set<float> unique_values = init_random_unordered_set(size); 
	for(auto val: unique_values){
		values.push_back(val);
	}
	return values;
}

set<float> init_random_set(int size){
	set<float> values;
	srand(666);
	while((int)values.size() < size){
		values.insert(float(rand())/float(RAND_MAX));
	}
	return values;
}

float sorted_sum_vector(vector<float> &values){
	DUMP_START_ALL("vector_sort", true);
	sort(values.begin(), values.end());
	DUMP_STOP("vector_sort");
	//DUMP_START_ALL("vector_sum2", true);
	return sum_datastructure(values);
	//DUMP_STOP("vector_sum2");
}

float sorted_sum_list(list<float> &values){
	values.sort();
	return sum_datastructure(values);
}

float sum_set(set<float> &values){
	return sum_datastructure(values);
}

float sum_unordered_set(unordered_set<float> &values){
	return sum_datastructure(values);
}

void chop_list(list<float> &values) {

	int s = values.size();
	for(int i = 0; i < s/2; i++) {
		values.pop_front();
	}
	
}


void grow_list(list<float> &values) {
	int s = values.size();
	for (int i=0; i<s; i++)
		values.push_back(float(rand())/float(RAND_MAX));
	
}

int main(int argc, char *argv[])
{

	//  This is all boiler plate and command line arguments.
	std::vector<int> sizes;
	int scale_factor;
	std::vector<int> default_set;
	default_set.push_back(1024);

	std::vector<std::string> ds;
	std::vector<std::string> default_ds;
	default_ds.push_back("vector");

	std::vector<int> mhz_s;
	std::vector<int> default_mhz;

	bool disable_prefetcher;
	load_frequencies();
	default_mhz.push_back(cpu_frequencies_array[0]);

	archlab_add_option<int>("scale", scale_factor, 1, "The scale factor.  Bigger (smaller) numbers mean longer (shorter) run times by running more samples.  The default is 10, which should allow optimized code to run to completion without timing out.  If you want to run without opts, turn it down.");

	archlab_add_flag("no-prefetch", disable_prefetcher, false, "Disable the HW prefetcher.");
	archlab_add_option<std::vector<int> >("size",
					      sizes,
					      default_set,
					      "1024",
					      "Number of elements"
					      "Pass it multiple times to run summation on multiple sets of elements.");

	archlab_add_option<std::vector<std::string> >("datastructure",
						      ds,
						      default_ds,
						      "vector",
						      "datastructure to use"
						      "Pass it multiple times to run summation on different underlying datastructures");

	std::stringstream clocks;
	for (int i = 0; cpu_frequencies_array[i] != 0; i++)
		{
			clocks << cpu_frequencies_array[i] << " ";
		}
	std::stringstream fastest;
	fastest << cpu_frequencies_array[0];
	archlab_add_option<std::vector<int> >("MHz",
					      mhz_s,
					      default_mhz,
					      fastest.str(),
					      "Which clock rate to run.  Possibilities on this machine are: " + clocks.str() +
                                              ".  Pass it multiple times to run the experiment and multiple frequencies.");
	archlab_parse_cmd_line(&argc, argv);

	float result = 0.0;
	

	// The interesting part starts here
	START_TRACE();
	pristine_machine();
	set_cpu_clock_frequency(mhz_s[0]);
	if (disable_prefetcher)  {
		theDataCollector->disable_prefetcher();
	}
	
	if (ds[0] == "vector") {
		std::vector<float> values_vector;
		ArchLabTimer timer; // create it.
		timer.attr("phase", "all");
		timer.go();
		DUMP_START_ALL("vector_init", true);
		values_vector = init_random_vector(sizes[0]);
		DUMP_STOP("vector_init");
		//DUMP_START_ALL("vector_sum", true);
		result = sorted_sum_vector(values_vector);
		//DUMP_STOP("vector_sum");
	} else if (ds[0] == "list") {
		std::list<float> values_list;
		MY_START_TIMER("init");
		values_list = init_random_list(sizes[0]);
		MY_STOP_TIMER("init");
		    
		MY_START_TIMER("sort_sum");
		result = sorted_sum_list(values_list);
		MY_STOP_TIMER("sort_sum");
		    
		MY_START_TIMER("chop");
		chop_list(values_list);
		MY_STOP_TIMER("chop");

		MY_START_TIMER("init2");
		grow_list(values_list);
		MY_STOP_TIMER("init2");

		MY_START_TIMER("sort_sum2");
		result = sorted_sum_list(values_list);
		MY_STOP_TIMER("sort_sum2");

	} else if(ds[0] == "set"){
	std::set<float> values_set;
		ArchLabTimer timer; // create it.
		timer.attr("phase", "all");
		timer.go();
		DUMP_START_ALL("set_init", true);
		values_set = init_random_set(sizes[0]);
		DUMP_STOP("set_init");
		DUMP_START_ALL("set_sum", true);
		result = sum_set(values_set);
		DUMP_STOP("set_sum");
	} else if(ds[0] == "unordered_set"){
		std::unordered_set<float> values_unordered_set;
		ArchLabTimer timer; // create it.
		timer.attr("phase", "all");
		timer.go();
		DUMP_START_ALL("unordered_set_init", true);
		values_unordered_set = init_random_unordered_set(sizes[0]);
		DUMP_STOP("unordered_set_init");
		DUMP_START_ALL("unordered_set_sum", true);
		result = sum_unordered_set(values_unordered_set);
		DUMP_STOP("unordered_set_sum");
	} else{
		std::cout << "Unsupported datastructure! Exiting." << std::endl;
		return 0;
	}

	
	archlab_write_stats();
	std::cout << "The Sum = " << std::fixed << std::setprecision(8) << result << std::endl;
	return 0;
}
