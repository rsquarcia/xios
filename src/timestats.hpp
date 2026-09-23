#ifndef __XIOS_TIMESTATS_HPP__
#define __XIOS_TIMESTATS_HPP__

namespace xios
{
  using namespace std;
  double calcMinDouble(std::vector<double>&);
  double calcMaxDouble(std::vector<double>&);

  double calcMeanDouble(std::vector<double>&);
  double calcStdDouble(std::vector<double>&);
  std::vector<double> percentageRatioVecDouble(std::vector<double>&, std::vector<double>&);
}

#endif
