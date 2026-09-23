#include "server.hpp"
#include <cmath>

namespace xios
{
  double calcMinDouble(std::vector<double>& data_values) {
    // Return the minimum value of vector data_values
    double min_val = *std::min_element(data_values.begin(), data_values.end());
    return min_val;
  }

  double calcMaxDouble(std::vector<double>& data_values) {
    // Return the maximum value of vector data_values
    double max_val = *std::max_element(data_values.begin(), data_values.end());
    return max_val;
  }
  
  double calcMeanDouble(std::vector<double>& data_values) {
    // Calculate the mean of of data_values
    double cumulative_sum = 0.;
    for (int i = 0; i < data_values.size(); i++) {
      cumulative_sum += data_values[i];
    }
    double mean = cumulative_sum / (double) data_values.size();
    return mean;
  }

  double calcStdDouble(std::vector<double>& data_values) {
    // Calculate the standard deviation of data values
    double mean = calcMeanDouble(data_values);
    double cumulative_sum = 0.;
    for (int i = 0; i < data_values.size(); i++) {
      cumulative_sum += pow((data_values[i] - mean), 2.0);
    }
    cumulative_sum = cumulative_sum / (double) data_values.size();
    double std_dev = pow(cumulative_sum, 0.5);
    return std_dev;
  }

  std::vector<double> percentageRatioVecDouble(std::vector<double>& a, std::vector<double>& b) {

    // Find the percentage ratio of a with respect to vector of doubles b elementwise
    std::vector<double> result(a.size());
    for (int i=0; i<a.size(); i++) {
      result[i] = (a[i]/b[i]) * 100.;
    }
    return result;
  }
}
