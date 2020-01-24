# mc-neutron
This project implements a Monte Carlo simulation of neutron transport, serial and parallel, using C and MPI.

After verifying the MPI kernel extension is loaded, running the Makefile yields two executables:
- nt-serial
- nt-parallel

"nt-serial" and "nt-parallel" both perform the neutron transport simulations.  "gen_data.py" calls the compiled executable of nt_serial and writes information to a CSV.  "plot_data.py" can then use Pandas/Matplotlib to read-in + format the data and display a three-dimensional representation of the results.
