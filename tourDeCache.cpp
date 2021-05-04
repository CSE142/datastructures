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
    archlab_add_flag("run-canary", do_run_canary, false ,  "Run the canary.");
    archlab_parse_cmd_line(&argc, argv);

    if (do_run_canary) {
	    run_canary(mhz_s[0]);
    }
    
    std::cout << "Set clock to " << mhz_s[0] << "MHz.\n";

    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
    set_cpu_clock_frequency(mhz_s[0]);
    {
        ArchLabTimer timer;
        timer.attr("function", "MCMPS").go(); // Start measuring
        MCMPS();
    }

    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
    set_cpu_clock_frequency(mhz_s[0]);
    {
        ArchLabTimer timer;
        timer.attr("function", "IPC").go(); // Start measuring
        IPC();
    }

    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
    set_cpu_clock_frequency(mhz_s[0]);
    {
        ArchLabTimer timer;
        timer.attr("function", "MBMPS").go(); // Start measuring
        MBMPS();
    }

    pristine_machine(); // clear caches, disable turbo boost, reset clock speed
    set_cpu_clock_frequency(mhz_s[0]);
    std::cout << "Set clock to " << mhz_s[0] << "MHz.\n";
    {
        ArchLabTimer timer;
        timer.attr("function", "all_around").go(); // Start measuring
        all_around();
    }

    archlab_write_stats();
    return 0;
}
// Empty
