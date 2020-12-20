#include "Data.hh"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

using namespace std;

Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
  // Exercise 1b)
  // read in data from file: m_siz bin uncertainties
  for (int i = 0; i < size; ++i) {
    double uncertainty;
    file >> uncertainty;
    m_sigma.push_back(uncertainty);
  }

  // done! close the file
  file.close();

  assertSizes();
};

void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size());
                          // Exercise 1b)
                           assert(m_data.size() == m_sigma.size()); }

// Exercise 1d)
int Data::checkCompatibility(const Data& in, int n) {
  double absdiff, sigma;
  int count = 0;
  for (unsigned int i = 0; i < this->size(); i++) {
    absdiff = abs(this->measurement(i) - in.measurement(i));
    sigma = sqrt(pow(this->error(i), 2) + pow(in.error(i), 2)); // Correct?
    if (absdiff > n * sigma) {
      count += 1;
    }
  }
  return count;
};

// Exercise 1e)
// merges a new Data object to a new one:
// sum12 = data1.average(data2);
Data Data::average(Data data2) {
  double w1, w2;
  Data sum = *this;  // make a copy to ensure identical size of data & bins
  for (unsigned int i = 0; i < this->size(); ++i) {
    w1 = pow(m_sigma[i], -2);
    w2 = pow( data2.m_sigma[i], -2);
    sum.m_data[i] = (w1 * m_data[i] + w2 * data2.m_data[i]) / (w1 + w2);
    sum.m_sigma[i] = sqrt(1.0 / (w1 + w2));
  }
  return sum;
}

// Exercise 2
double bg(double x) {
  // background function
  const double a = 0.005, b = -0.00001, c = 0.08, d = 0.015;
  return a + b * x + c * std::exp(-1.0 * d * x);
}

// Exercise 2
double Data::chi2() {
  double c2 = 0.0;          // = chi-square
  for (unsigned int i = 0; i < this->size(); ++i) {
    c2 += pow((m_data[i]- bg(binCenter(i))), 2) / pow(m_sigma[i], 2);
  }
  return c2;
}

Data Data::operator+(Data& data2) {
  double w1, w2;
  Data sum = *this;  // make a copy to ensure identical size of data & bins
  for (unsigned int i = 0; i < this->size(); ++i) {
    w1 = pow(m_sigma[i], -2);
    w2 = pow( data2.m_sigma[i], -2);
    sum.m_data[i] = (w1 * m_data[i] + w2 * data2.m_data[i]) / (w1 + w2);
    sum.m_sigma[i] = sqrt(1.0 / (w1 + w2));
  }
  return sum;
}

