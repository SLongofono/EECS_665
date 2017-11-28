"""
Given an absolute path to a flat directory of test case files, calls the given
executable and the testing executable with the input files.  Outputs are saved
into expected and results, and then each is diffed.
"""
import os, errno
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--test_dir', '-d', required=True, type=str,
                    help="EXAMPLE: python testscript.py -d <absolute path>")
args = parser.parse_args();

TESTDIR = args.test_dir
EXP_OUT = "expected/"
RES_OUT = "results"

# Fetch list of test cases
files = []
for (dpath, dnames, fnames) in os.walk(TESTDIR):
    files.extend(fnames)
    break

# Make output dirs if they do not exist
try:
    os.makedirs(EXP_OUT)
except OSError as err:
    if err.errno != errno.EEXIST:
        raise

try:
    os.makedirs(RES_OUT)
except OSError as err:
    if err.errno != errno.EEXIST:
        raise

files = sorted(files)

# Run tests and save outputs
for f in files:
    command = "./sem_base.exe < {} > {}".format(os.path.join(TESTDIR, f),
                                                os.path.join(EXP_OUT, "{}.out".format(f)))
    command2 = "./csem < {} > {}".format(os.path.join(TESTDIR, f),
                                                os.path.join(RES_OUT, "{}.out".format(f)))
    command3 = "diff {} {}".format(os.path.join(EXP_OUT, "{}.out".format(f)),
                                  os.path.join(RES_OUT, "{}.out".format(f)))
    r1 = os.system(command)
    
    r2 = os.system(command2)
    
    if(r1+r2 > 0):
        print("Error:\n\tCall {} returned {}\n\tCall {} returned {}\n".format(command, r1, command2, r2))
        print("File in question: {}".format(f))

    else:
        print("=============================================================\nFILE {}\n=============================================================\n".format(f))
        print("\n")
        r3 = os.system(command3)

