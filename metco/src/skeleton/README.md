
/*! \mainpage Metaheuristic-based Extensible Tool for Cooperative Optimisation (METCO) -- Version registered at Safe Creative

Welcome! You've found the source code of METCO, a registered tool which can be use to developing and testing metaheuristics in C/C++ language.

## Quick start

1. Download or clone this repo
2. Unzip if needed and move to `local_path/software-metco/oplink/algorithms/team/src/skeleton/main`
3. Make sure you have installed all the dependencies (below) 
4. Run `gen.sh`.
5. Run the `configure` script.
6. Run `make` to build the tool.

Now you are ready to start using METCO.

## Dependencies

| Dependency       	| How to install  (Debian/Ubuntu Distros)                                 	| Link                                                                                            	|
|------------------	|--------------------------------------------------	|-------------------------------------------------------------------------------------------------	|
| gcc/g++ compiler 	| sudo apt-get install build-essential             	| [GCC/G++](https://gcc.gnu.org/)                                                                            	|
| Autotools        	| sudo apt-get install autotools-dev automake          	| [Autotools](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html) 	|
| Bison            	| sudo apt-get install bison                       	| [Bison](https://launchpad.net/ubuntu/+source/bison)                                                      	|
| Flex             	| sudo apt-get install flex                        	| [Flex](http://manpages.ubuntu.com/manpages/xenial/es/man1/flex.1.html)                                  	|
| MPICH*            	| sudo apt-get install libcr-dev mpich2 mpich2-doc 	| [MPICH](https://www.mpich.org/)                                                                          	|
| GNU GSL          	| sudo apt-get install libgsl0-dev                 	| [GNU GSL](https://www.gnu.org/software/gsl/)                                                               	|

\* Make sure you are allowed to run mpicc compiler from your command line.