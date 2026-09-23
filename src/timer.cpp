#include "timer.hpp"
#include "mpi.hpp"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "tracer.hpp"
#include "log.hpp"
#include "timestats.hpp"

namespace xios
{
  std::map<std::string,CTimer> CTimer::allTimer;
  
  CTimer::CTimer(const std::string& name_, bool trace) : name(name_), num_(0)
  { 
    isTracing_=trace ;
    reset();
  }

  double CTimer::getTime(void)
  {
    return MPI_Wtime();
  }
  
  void CTimer::suspend(void)
  {
    if (!suspended) 
    {
      if (isTracing_) traceEnd(name);
      cumulatedTime += getTime() - lastTime;
    }
    suspended = true;
  }
  
  void CTimer::resume(void)
  {
    if (suspended) 
    {
      num_++ ;
      lastTime = getTime();
      if (isTracing_) traceBegin(name);
    }
    suspended = false;
  }
  
  void CTimer::reset(void)
  {
    num_=  0 ;
    cumulatedTime = 0.;
    suspended = true;
  }
  
  double CTimer::getCumulatedTime(void)
  {
    return cumulatedTime;
  }
  
  double CTimer::getNumCall(void)
  {
    return num_;
  }

  double CTimer::getAverageTime(void)
  {
    if (num_==0) return 0. ;
    else return cumulatedTime/num_;
  }

  CTimer& CTimer::get(const std::string name, bool trace)
  {
    std::map<std::string,CTimer>::iterator it = allTimer.find(name);
    if (it == allTimer.end())
      it = allTimer.insert(std::make_pair(name, CTimer(name,trace))).first;
    return it->second;
  }

  string CTimer::getAllCumulatedTime(void)
  {
    std::ostringstream strOut ;
    for(std::map<std::string,CTimer>::iterator it=allTimer.begin();it!=allTimer.end();++it)
      strOut<<"Timer : "<<it->first<<"    -->   cumulated time : "<<it->second.getCumulatedTime()<<std::endl ;
    return strOut.str() ;
  }

  std::vector<double> CTimer::collateTimings(std::string timing_param, MPI_Comm comm)
  {
    int myrank, comm_size;
    MPI_Comm_rank(comm, &myrank);
    MPI_Comm_size(comm, &comm_size);
    
    std::vector<double> collated_results;
    MPI_Barrier(comm);
    if (myrank == 0)
    {
      double recv_val = 0.;
      collated_results.push_back(CTimer::get(timing_param).getCumulatedTime());
      for (int i = 1; i < comm_size; i++) {
	MPI_Recv(&recv_val, 1, MPI_DOUBLE, i, 0, comm, MPI_STATUS_IGNORE);
	collated_results.push_back(recv_val);
      }
    }
    else
    {
      double snd_val = CTimer::get(timing_param).getCumulatedTime();
      MPI_Send(&snd_val, 1, MPI_DOUBLE, 0, 0, comm);
    }
    MPI_Barrier(comm);
    return collated_results;
  }

  void CTimer::writeSummaryTimings(std::vector<double>& collated_results,
				      std::string results_label)
  {
    report(0) << setw(40) << results_label << setw(3)<< " : "
      
	      << setw(16) << calcMeanDouble(collated_results) << setw(3) << " | " 
	      << setw(16) << calcStdDouble(collated_results)  << setw(3) << " | " 
	      << setw(16) << calcMinDouble(collated_results)  << setw(3) << " | " 
	      << setw(16) << calcMaxDouble(collated_results)  << endl;
  }

  void CTimer::writeHeaderTimings()
  {
    report(0) << setw(40) << " " << setw(3)<< " : "
	      << setw(16) << " average " << setw(3) << " | " 
	      << setw(16) << " std dev " << setw(3) << " | " 
	      << setw(16) << " min "     << setw(3) << " | " 
	      << setw(16) << " max "     << setw(3) << endl;
  }
}
