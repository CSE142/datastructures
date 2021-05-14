# Students should not edit this file, since changes here will _only_
# affect how your code runs locally.  It will not change how your code
# executes in the cloud.
from ArchLab.CSE141Lab import CSE141Lab, test_configs
import functools
import logging as log
import unittest
from gradescope_utils.autograder_utils.decorators import weight, partial_credit, visibility
import parameterized
import os
import re

 
class ThisLab(CSE141Lab):
    def __init__(self, **kwargs):
        super(ThisLab, self).__init__(
            lab_name = "Complex Data Structures and the Tour de Cache",
            short_name = "datastructs",
            output_files = ['*.csv', '*.gprof', '*.s'],
            input_files = [#'code.cpp','tourDeCache.cpp',
                           'fp_sum.cpp', 'MBMPS.cpp', 'all_around.cpp', 'IPC.cpp', 'MCMPS.cpp', 'config.env', 'outputs/*'],
            repo = kwargs.get("repo") or "https://github.com/NVSL/CSE141pp-Lab-Complex-DataStructures.git",
            reference_tag = kwargs.get("reference_tag") or "main",
            valid_options = dict(EXPERIMENT_CMD_LINE_ARGS="Command line for experiment.csv"),#MBMPS_OPTIMIZE="optimization flags for MBMPS.cpp",
                                 #MCMPS_OPTIMIZE="optimization flags for Watts.cpp",
                                 #IPC_OPTIMIZE="optimization flags for IPC.cpp",
                                 #ALL_AROUND_OPTIMIZE="optimization flags for all_around.cpp"),
            timeout = 240,
        )

    def filter_command(self, command):
        a = self.make_target_filter(command)
        return a
    

    class MetaRegressions(CSE141Lab.MetaRegressions):
        def setUp(self):
            CSE141Lab.MetaRegressions.setUp(self)
            self.lab_spec = ThisLab.load(".")

        @parameterized.parameterized.expand(test_configs("solution", "."))
        def test_solution(self, solution, flags):
            if flags.devel and "solution" == solution:
                self.skipTest("Skipping since this solution doesn't work in devel mode")
            
            result, tag = self.run_solution(solution, flags)

            js = result.results

            self.assertFileExists("inst_mix.csv", tag)
            self.assertFileExists("benchmark.csv", tag)
            self.assertFileExists("code.s", tag)

            b = self.read_text_file("inst_mix.csv", tag)
            runtime = self.lab_spec.csv_extract_by_line(b, 'runtime')
            
            if solution == ".":
                self.assertLess(runtime, 30)
                if flags.grades_valid():
                    self.assertEqual(float(js['gradescope_test_output']['score']), 1, f"Failed on {tag}: score check")
                    
            elif solution == "solution":
                self.assertLess(runtime, 30)
                if flags.grades_valid():
                    self.assertEqual(float(js['gradescope_test_output']['score']), 8, f"Failed on {tag}: score check")

            if flags.gprof:
                self.assertFileExists("inst_mix.gprof", tag)
                self.assertFileExists("benchmark.gprof", tag)

