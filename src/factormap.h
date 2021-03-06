/***********************************************************************
Copyright 2018 Gregory Bryant

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************/


#ifndef FACTORMAP_H
#define FACTORMAP_H
#include <boost/multiprecision/gmp.hpp>
using boost::multiprecision::mpz_int;
#include "nedisplayobject.h"


class FactorMap : public NEDisplayObject
{
public:
    FactorMap();
    void render(NEView *view);
    mpz_int fixYOffsetAndSign(mpz_int x, mpz_int y);

    mpz_int left;
    mpz_int right;
    mpz_int top;
    mpz_int bottom;

    mpz_int i;
    mpz_int j;

    mpz_int temp;
};

#endif // FACTORMAP_H
