import xios
import numpy as np
from mpi4py import MPI
import sys



client_number = 2
server_number = 1
ts_max = 5
ni_glo = 4
nj_glo = 3
n_glo  = 2

comm_world = MPI.COMM_WORLD
rank = comm_world.Get_rank()
size = comm_world.Get_size()


if size != client_number + server_number:
    if rank == 0:
        print("ERROR: need ", client_number + server_number,
            "MPI processes or change the client/server numbers")
    MPI.Finalize()
    sys.exit()


if (rank > client_number-1 and rank <=client_number+server_number-1):

    print("Rank", rank, ": starting XIOS server")
    xios.init_server()

elif (rank < client_number):

    print("Rank", rank, ": starting XIOS client")
    comm = xios.initialize("client")
    ctx = xios.Context("test", comm)
    rank = comm.rank
    size_loc = client_number    

    cal = ctx.calendar
    cal.define(type = "Gregorian", timestep = xios.Duration(day = 1))

    if ni_glo%size_loc != 0 :
        print("ERROR: You must have a number of client : ", size_loc, " that devide exactly ni_glo : ", ni_glo)

    ni = ni_glo//size_loc
    nj = nj_glo
    n = n_glo

    n_fields = ctx.variable("output_field_model_number").get(0)
    TESTS = [ctx.field(f"output_field_model_{i}").comment for i in range(n_fields)]

    ctx.domain("domain").set_attr(
        ni_glo=ni_glo,
        nj_glo=nj_glo,
        ni=ni,        
        nj=nj,       
        ibegin=ni*rank,
        jbegin=0
    )

    ctx.axis("axis").n_glo = n_glo

    ctx.close_definition()

    # 3D array of one
    input_field_model_data = np.arange(n_glo)[:, None, None]* np.ones((1, nj, ni)) + 1
    output_data = np.zeros((n, nj, ni))

    if rank == 0 : print("\nSending and applying filter through XIOS : \n")
    for i in range(n_fields):
        if rank == 0 : print(f"\t{ctx.field(f"output_field_model_{i}").id} -> {TESTS[i]}")

    if rank == 0 : print("\n")
    for ts in range(1, ts_max):

        cal.update(ts)
        if rank == 0 : print("update calendar : ", ts, " and sending fields .. ")

        ctx.field("input_field_model").send(input_field_model_data*ts)

        for i in range(n_fields):
            output_data = ctx.field(f"output_field_model_{i}").recv(output_data)
            

    ctx.finalize()
    xios.finalize()
        