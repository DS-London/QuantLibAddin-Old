
/*
 Copyright (C) 2004, 2005 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <Addins/C/qladdin.h>
#include <stdio.h>

int main() {
    double dividendYield = 0.00;
    double riskFreeRate = 0.06;
    double volatility = 0.20;
    double underlying = 36;
    double strike = 40;
    long timeSteps = 801;
    long exerciseDate = 36297;       // (17, May, 1999);
    long settlementDate = 35932;     // (17, May, 1998);
    long todaysDate = 35930;         // (15, May, 1998);
    VariesList vbs;                  // attributes of black scholes object
    VariesList vo;                   // attributes of option object
    int i;

    printf("hi\n");

    QL_LOGFILE("quantlib.log");
    QL_LOGMESSAGE("begin example program");

    if (QL_STOCHASTIC_PROCESS(
            "my_stochastic", 
            underlying, 
            "ACT360",
            settlementDate, 
            riskFreeRate, 
            dividendYield, 
            volatility, 
            &vbs) != SUCCESS) {
        printf("Error on call to QL_STOCHASTIC_PROCESS\n");
        goto fail;
    }

    if (QL_OPTION_VANILLA(
            "my_option",                    // option handle
            "my_stochastic",                // stochastic process handle
            "PUT",                          // option type
            "VAN",                          // payoff type (plain vanilla)
			strike,                         // strike price
            "AM",                           // exercise type (american)
            exerciseDate,                   // exercise date
            settlementDate,                 // settlement date
            "JR",                           // engine type (jarrow rudd)
            timeSteps,                      // time steps
            &vo) != SUCCESS) {
        printf("Error on call to QL_OPTION_VANILLA\n");
        goto fail;
    }

    printf("\nhigh-level interrogation - after QL_OPTION_VANILLA\n");
    for (i=0; i<vo.count; i++)
        printf("field = %s, value = %s\n", vo.varies[i].Label, variesToString(&vo.varies[i]));

    if (QL_OPTION_SETENGINE(
            "my_option", 
            "AEQPB",   // AdditiveEQPBinomialTree
            801, 
            &vo) != SUCCESS) {
        printf("Error on call to QL_OPTION_SETENGINE\n");
        goto fail;
    }

    printf("\nhigh-level interrogation - after QL_OPTION_SETENGINE\n");
    for (i=0; i<vo.count; i++)
        printf("field = %s, value = %s\n", vo.varies[i].Label, variesToString(&vo.varies[i]));

    freeVariesList(&vbs);
    freeVariesList(&vo);

    QL_LOGMESSAGE("end example program");

    printf("\nbye\n");

    return 0;

fail:

    return 1;
}

