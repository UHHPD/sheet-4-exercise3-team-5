#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>

class Data {
  public:
    Data(const std::string& filename);

    unsigned int size() const { return m_data.size(); }
    double measurement(int i) const { return m_data[i]; }
    double uncertainty(int i) const { return m_sigma[i]; }
    double binCenter(int i) const { return 0; }
    double binLow(int i) const { return 0; }
    double binHigh(int i) const { return 0; }
    // Exercise 1b)
    double error(int i) const { return 0; }

  private:
    Data() {}  // disallow empty data set
    void assertSizes();
    // Exercise 1b)
    std::vector<double> m_sigma;
    std::vector<double> m_data;
    std::vector<double> m_bins;
};

#endif
