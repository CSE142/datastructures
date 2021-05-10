#include "archlab.hpp"
#include <cstdlib>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <list>
#include "pin_tags.h"

#include <iostream>
#include <algorithm>
#include <iterator>


extern int MCMPS();
extern int IPC();
extern int MBMPS();
extern int all_around();

void run_canary(int clock_rate)
{
	pristine_machine();
	set_cpu_clock_frequency(clock_rate);
	theDataCollector->disable_prefetcher();
	ArchLabTimer timer; // create it.
	timer.attr("function", "_canary");
	timer.go();
	archlab_canary(100000000);
}


int main(int argc, char *argv[])
{
    std::vector<int> mhz_s;
    std::vector<int> default_mhz;
    bool do_run_canary = false;
    load_frequencies();
    default_mhz.push_back(cpu_frequencies_array[0]);

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

    std::vector<std::string> function_s;
    std::vector<std::string> default_functions;
    default_functions.push_back("all");
    archlab_add_multi_option<std::vector<std::string> >("function",
							function_s,
							default_functions,
							"all",
							"Which function to run: 'IPC', 'MBMPS', 'MCMPS', 'all_around', or 'all'.  Pass multiple values to run multiple tests.");
    
    
    
    archlab_add_flag("run-canary", do_run_canary, false ,  "Run the canary.");
    archlab_parse_cmd_line(&argc, argv);

    if (do_run_canary) {
	    run_canary(mhz_s[0]);
    }
    
    std::cout << "Set clock to " << mhz_s[0] << "MHz.\n";

    for(auto & f: function_s) {
	    int ran = 0;

	    if (f == "MCMPS"|| f == "all") {
		    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
		    set_cpu_clock_frequency(mhz_s[0]);
		    {
			    ArchLabTimer timer;
			    timer.attr("function", "MCMPS").go(); // Start measuring
			    MCMPS();
		    }
		    ran++;
	    } else if (f == "IPC"|| f == "all") {
		    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
		    set_cpu_clock_frequency(mhz_s[0]);
		    {
			    ArchLabTimer timer;
			    timer.attr("function", "IPC").go(); // Start measuring
			    IPC();
		    }
		    ran++;
	    } else if (f == "MBMPS"|| f == "all") {

		    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
		    set_cpu_clock_frequency(mhz_s[0]);
		    {
			    ArchLabTimer timer;
			    timer.attr("function", "MBMPS").go(); // Start measuring
			    MBMPS();
		    }
		    ran++;
	    } else if (f == "all_around"|| f == "all") {

		    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
		    set_cpu_clock_frequency(mhz_s[0]);
		    std::cout << "Set clock to " << mhz_s[0] << "MHz.\n";
		    {
			    ArchLabTimer timer;
			    timer.attr("function", "all_around").go(); // Start measuring
			    all_around();
		    }
		    ran++;
	    }
	    if (ran == 0) {
		    std::cerr << "unknown functions: " << f << "\n";
		    exit(1);
	    }
    }
    
    archlab_write_stats();
    return 0;
}
// Empty
