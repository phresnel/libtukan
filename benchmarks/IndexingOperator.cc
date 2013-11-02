// (C) 2013 Sebastian Mach (1983), this file is published under the terms of the
// GNU General Public License, Version 3 (a.k.a. GPLv3).
// See COPYING in the root-folder of the excygen project folder.
#include <iostream>

template<class T>
class Vector3
{
public:
   Vector3(const T &xx, const T &yy, const T &zz) :
      x(xx), y(yy), z(zz)
   {
   };

   T& operator[](size_t idx)
   {
      return this->*offsets_[idx];
   };

   const T& operator[](size_t idx) const
   {
      return this->*offsets_[idx];
   };

public:
   T x,y,z;
private:
   static T Vector3::* const offsets_[3];
};

template<class T>
T Vector3<T>::* const Vector3<T>::offsets_[3] =
{
   &Vector3<T>::x,
   &Vector3<T>::y,
   &Vector3<T>::z
};

template <typename T>
std::ostream& operator<< (std::ostream &os, Vector3<T> rhs) {
    return os << "vector3{" << rhs.x << "," << rhs.y << "," << rhs.z << "}";
}

struct PlainVector3 {
    float p[3];

    PlainVector3(float x, float y, float z) {
        p[0] = x;
        p[1] = y;
        p[2] = z;
    }
};
std::ostream& operator<< (std::ostream &os, PlainVector3 rhs) {
    return os << "plainvector3{" << rhs.p[0] << "," << rhs.p[1] << "," << rhs.p[2] << "}";
}

#include <ctime>

int main()
{
   Vector3<float> vec(1,2,3);
   PlainVector3 pvec(1,2,3);
   vec[0] = 5;
   pvec.p[0] = 5;
   std::cout << vec << std::endl;
   std::cout << pvec << std::endl;

   std::cout << "benchmark\n";
   unsigned num = 4294967295U;
   {
       std::clock_t start = std::clock();
       asm volatile ("# TRICK ");
       for (unsigned i=0; i!=num; ++i) {
           for (int x=0; x<3; ++x) {
               vec[x] += i;
           }
       }
       asm volatile ("# TRICK");
       std::clock_t end = std::clock();

       std::cout << (end-start)/float(CLOCKS_PER_SEC) << ":" << vec << std::endl;
   }

   {
       std::clock_t start = std::clock();
       asm volatile ("# NO INDEX ");
       for (unsigned i=0; i!=num; ++i) {
           vec.x += i;
           vec.y += i;
           vec.z += i;
       }
       asm volatile ("# NN INDEX");
       std::clock_t end = std::clock();

       std::cout << (end-start)/float(CLOCKS_PER_SEC) << ":" << vec << std::endl;
   }

   {
       std::clock_t start = std::clock();
       asm volatile ("# PLAIN ");
       for (unsigned i=0; i!=num; ++i) {
           for (int x=0; x<3; ++x) {
               pvec.p[x] += i;
           }
       }
       asm volatile ("# PLAIN");
       std::clock_t end = std::clock();

       std::cout << (end-start)/float(CLOCKS_PER_SEC) << ":" << pvec << std::endl;
   }
}
