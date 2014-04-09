#include "PerlinNoise.h"
#include <cmath>
#include <random>
#include <algorithm>

PerlinNoise::PerlinNoise(unsigned int seed) {
  p_.resize(256);

  //Fill p with values from 0 to 255
  std::iota(p_.begin(), p_.end(), 0);

  //std::default_random_engine engine(seed);
  std::minstd_rand0 engine((seed));

  std::shuffle(p_.begin(), p_.end(), engine);

  p_.insert(p_.end(), p_.begin(), p_.end());
}

double PerlinNoise::noise(double x, double y, double z) {
  //Find the unit cube that contains the point
  int X = (int) floor(x) & 255;
  int Y = (int) floor(y) & 255;
  int Z = (int) floor(z) & 255;

  //Find relative x,y,z of point in cube
  x -= floor(x);
  y -= floor(y);
  z -= floor(z);

  //Compute fade curves
  double u = fade(x);
  double v = fade(y);
  double w = fade(z);

  //Hash coords of the 8 cube corners
  int A = p_[X] + Y;
  int AA= p_[A] + Z;
  int AB= p_[A+1] + Z;
  int B = p_[X+1] + Y;
  int BA= p_[B] + Z;
  int BB= p_[B+1] + Z;

  // Add blended results from 8 corners of cube.
  double res = lerp(w, lerp(v, lerp(u, grad(p_[AA], x, y, z), grad(p_[BA], x-1, y, z)), lerp(u, grad(p_[AB], x, y-1, z), grad(p_[BB], x-1, y-1, z))),	lerp(v, lerp(u, grad(p_[AA+1], x, y, z-1), grad(p_[BA+1], x-1, y, z-1)), lerp(u, grad(p_[AB+1], x, y-1, z-1),	grad(p_[BB+1], x-1, y-1, z-1))));

  return (res + 1.0)/2.0;

}

double PerlinNoise::fade(double t) { 
  return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) { 
  return a + t * (b - a); 
}

double PerlinNoise::grad(int hash, double x, double y, double z) {
  int h = hash & 15;
  // Convert lower 4 bits of hash inot 12 gradient directions
  double u = h < 8 ? x : y,
         v = h < 4 ? y : h == 12 || h == 14 ? x : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
