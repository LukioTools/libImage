
# import required module
import os
# assign directory
directory = 'formats/'

# iterate over files in
# that directory
ofile = open("include_formats.hpp", "w");
ofile.write("#pragma once\n")
for filename in os.listdir(directory):
    f = os.path.join(directory, filename)
    # checking if it is a file
    if os.path.isfile(f):
        ofile.write(f'#include "{f}"\n')


ofile.close()        

