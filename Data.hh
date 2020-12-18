#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>
#include <cmath>

class Data {
  public:
    Data(const std::string& filename);

    unsigned int size() const { return m_data.size(); }
    double measurement(int i) const { return m_data[i]; }
    double binCenter(int i) const {
      return 0.5 * (m_bins[i] + m_bins[i + 1]);
    }
    double binLow(int i) const { return m_bins[i]; }
    double binHigh(int i) const { return m_bins[i + 1]; }
    // Exercise 1b)
    double error(int i) const { return m_sigma[i];; }
    // Exercise 1d)
    int checkCompatibility(const Data&, int);
    // Exercise 1e)
    // merges a new Data object to an exiting one:
    // sum12 = data1.average(data2);
    Data average(Data);
    // Exercise 2
    double chi2();

  private:
    Data() {}  // disallow empty data set
    void assertSizes();
    // Exercise 1b)
    std::vector<double> m_sigma;
    std::vector<double> m_data;
    std::vector<double> m_bins;
};
// Exercise 2
double bg(double);
// background function

#endif
