/*

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include "rsa.h"
#include "euclid.h"
#ifdef _WIN32
#include "random.h"
#else
#include "unirandom.h"
#endif

/*----------------------------------------------------------------------------
This function uses Fermat's Theorem 100 times to test the primeness of a
(large) positive integer.
----------------------------------------------------------------------------*/

static bool IsPrime(const mpuint &p)
{
  mpuint pminus1(p);
  pminus1 -= 1;
  unsigned count = 101;
  while (--count != 0)
  {
    mpuint r(p.length);
    mpuint x(p.length);
    {
      for (unsigned i = 0; i < x.length; i++)
        x.value[i] = rand() << 8 | rand();
    }
    x %= p;
    if (x != 0)
    {
      mpuint::Power(x, pminus1, p, r);
      if (r != 1)
        return false;
    }
  }
  return true;
}

/*----------------------------------------------------------------------------
This function generates a (large) prime.
----------------------------------------------------------------------------*/

static void GeneratePrime(mpuint &p)
{
  Random(p);
  p.value[p.length-1] |= 0x8000;
  p.value[0] |= 1;
  while (!IsPrime(p))
    p += 2;
}


void GenerateKeys(mpuint &d, mpuint &e, mpuint &n)
{
  mpuint p(d.length/2);
  GeneratePrime(p);
  mpuint q(d.length/2);
  GeneratePrime(q);
  mpuint pp(p);
  pp -= 1;
  mpuint qq(q);
  qq -= 1;
  mpuint pq(d.length);
  pq = pp;
  pq *= qq;
  n = p;
  n *= q;
  Random(d);
  d %= pq;
  mpuint temp(d.length);
  mpuint g(d.length);
  while (true)
  {
    EuclideanAlgorithm(d, pq, e, temp, g);
    if (g == 1)
      break;
    d += 1;
  }
}
