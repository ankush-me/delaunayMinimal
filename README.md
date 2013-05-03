delaunay
========
CS274 Final Project -- Ankush Gupta

Compiling/Running the Code
==========================

This code was tested on a machine running Ubuntu 12.04. The only external libraries it
needs are the boost libraries. The source contains tuxfamily Eigen used internally to
represent points. The code can be compiled by making a build directory and then running
cmake, followed by make, as following:

			 cd build
			 cmake ${PATH TO PROJECT DIRECTORY}
			 make delaunay


The code is executed as following (assuming we are in the build directory):

		./bin/delaunay -i input filename [-o output filename] [-V or -A][-T]


For an explanation of the various flags, run
		
		./bin/delaunay -h.
