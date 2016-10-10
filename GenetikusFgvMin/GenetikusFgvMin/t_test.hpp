//
//  t_test.hpp
//  GenetikusFgvMin
//
//  Created by Anna Gujgiczer on 2016/10/08.
//  Copyright © 2016 Anna Gujgiczer. All rights reserved.
//

#ifndef t_test_hpp
#define t_test_hpp

#include <stdio.h>

// Needed headers:
#include <boost/math/distributions/students_t.hpp>
#include <iostream>
#include <iomanip>
// Simplify usage:
using namespace boost::math;
using namespace std;

void two_samples_t_test_equal_sd(
                                 double Sm1,       // Sm1 = Sample 1 Mean.
                                 double Sd1,       // Sd1 = Sample 1 Standard Deviation.
                                 unsigned Sn1,     // Sn1 = Sample 1 Size.
                                 double Sm2,       // Sm2 = Sample 2 Mean.
                                 double Sd2,       // Sd2 = Sample 2 Standard Deviation.
                                 unsigned Sn2,     // Sn2 = Sample 2 Size.
                                 double alpha);     // alpha = Significance Level.

#endif /* t_test_hpp */
