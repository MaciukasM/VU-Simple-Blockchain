#ifndef LAIKAS_HPP
#define LAIKAS_HPP

#include <chrono>

//laiko matavimo klase
class LaikoMatavimas {
  using Laikas = std::chrono::high_resolution_clock;
  using durationDouble = std::chrono::duration<double>; 
  private:
    std::chrono::time_point<Laikas> start;
  public:
    LaikoMatavimas() : start{ Laikas::now() } {}
    ~LaikoMatavimas() {}
    void reset() {
      start = Laikas::now();
    }
    double elapsed() const {
      return durationDouble (Laikas::now() - start).count();
    }
};
//laiko matavimo klase

#endif