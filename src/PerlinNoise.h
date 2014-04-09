// THIS CLASS IS A TRANSLATION TO C++11 FROM THE REFERENCE
// JAVA IMPLEMENTATION OF THE IMPROVED PERLIN FUNCTION (see http://mrl.nyu.edu/~perlin/noise/)
// THE ORIGINAL JAVA IMPLEMENTATION IS COPYRIGHT 2002 KEN PERLIN
#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H
#include <vector>

struct PerlinNoise {
  public:
    PerlinNoise(unsigned int seed);

    double noise(double x, double y, double z);
  private:
    std::vector<int> p_;

    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
};

#endif
