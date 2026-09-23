#ifndef __XIOS_TIMER_HPP__
#define __XIOS_TIMER_HPP__

#include <string>
#include <map>
#include <vector>
#include "mpi.hpp"

namespace xios
{
  class CTimer
  {
    public:
      double cumulatedTime;
      double lastTime;
      bool suspended;
      bool isTracing_ ;
      std::string name;
      size_t num_ ;

      CTimer(const std::string& name, bool trace=true);
      void suspend(void);
      void resume(void);
      void reset(void);
      void add(double time) { cumulatedTime+=time ;}
      void minus(double time) { cumulatedTime-=time ;}
      double getCumulatedTime(void);
      double getNumCall(void) ;
      double getAverageTime(void) ;
      static std::map<std::string,CTimer> allTimer;
      static double getTime(void);
      static CTimer& get(std::string name, bool trace=true);
      static std::string getAllCumulatedTime(void) ;
      static void release(void) { allTimer.clear() ;}
      bool isSuspended() { return suspended; }

      static std::vector<double>collateTimings(std::string timing_param, MPI_Comm comm);
      static void writeSummaryTimings(std::vector<double>& collated_results, std::string results_label);
      static void writeHeaderTimings();
  };
}



#endif
