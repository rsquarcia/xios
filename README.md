# XIOS - XML Input Output Server

XIOS is a library dedicated to I/O management for simulation code.

XIOS aims to provide applicable Input Output data flow services for simulations, the first implementation is I/O servers.

XIOS provides:
* Management of input data and output diagnostics;
* Temporal post-processing online operations (averaging, max/min, instant, etc…);
* Spatial post-processing online operations.

XIOS interfaces with simulation codes using [MPI](https://www.mpi-forum.org/docs/) and 
interfaces with attached storage using MPI-IO, HDF5 & NetCDF.

XIOS is implemented in C++, with the primary simulation client interface being provided in Fortran.

Configuration is delivered through XML files provided at runtime, and a Fortran interface
that enables programmatic configuration, complementary to the XML.

## XIOS Goals

XIOS targets two main goals: flexibility & performance.

* Flexibility
    * Simplification of the I/O management into the code.
        * Minimize calling subroutine related to I/O definition:
            * file creation, axis and dimensions management, adding output fields.
        * Minimize arguments of I/O call.
    * Ideally : output a field require only a identifier and the data.
        * `CALL xios_send_field(“field_id”, field)`
    * Outsourcing the input and output definitions in an XML file.
        * Hierarchical management of definitions with inheritance.
        * Simple and compact definitions.
        * Avoid unnecessary repetition.
        * Changing I/O definitions without recompiling.
        * Everything is dynamic, XML file is parsed at runtime.
* Performance
    * Writing data must not slow down the computation.
        * Simultaneous writing and computing by asynchronous call.
    * Using one or more “server” processes dedicated exclusively to the I/O management.
        * Asynchronous transfer of data from clients to servers.
        * Asynchronous data writing by each server.
    * Use of parallel file system ability via Netcdf4-HDF5 file format.
        * Simultaneous writing in a same single file by all servers.
        * No more post-processing rebuilding of the files.

## Compiling XIOS

See [make_xios](make_xios), including

`./make_xios --help`

`arch/arch-{PLATFORM}.[env|path|fcm]` provide configurations for specific target platforms.
Configurations can be customised and extended to target building for different platform configurations and dependency management tools.

Simply add a new trio of `[env|path|fcm]` files with a `{PLATFORM}` file name path to your local source and build with:

`./make_xios --arch {PLATFORM}` using the PLATFORM string used to name the `arch` files.

## Client & Server

XIOS operates on a client and server model.

Clients are bespoke programmes, often Fortran, that implement context specific code, including XIOS code.

Servers are instances of the compiled `xios_server.exe` executable.

### Attached Mode

In attached mode, only client programmes are called in MPI initialisation.
All XIOS interactions are undertaken by the client programmes.

This mode is useful for testing and development, but may not scale well for large MPI communicators with many ranks.

### Server Mode

In server mode then client and `xios_server.exe` programmes are called in MPI initialisation, running MPI in MPMD mode (Multiple Programs, Multiple Data).

e.g. `mpiexec -n 512 simulation_executable : -n 8 xios_server.exe`

The client programmes configure the XIOS context(s), then offload I/O operations to instances of `xios_server.exe`.

Server mode enables many I/O operations to run asynchronously allowing clients such as simulation programmes to optimise
their run configuration and minimise interactions with the storage hardware.

There are many optimisation opportunities for running large simulations in server mode configuration.

## Contributing

See the [CONTRIBUTING.md](CONTRIBUTING.md) guide for details of how to engage with the development of XIOS.

## Release Management

See the [ReleaseManagement.md](ReleaseManagement.md) guide for details of how releases are managed.
