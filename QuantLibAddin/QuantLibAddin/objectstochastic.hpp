
/*
 Copyright (C) 2004 Eric Ehlers

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

#ifndef objectstochastic_h
#define objectstochastic_h

#include <ObjectHandler/objecthandler.hpp>
#include <ql/quantlib.hpp>
using namespace QuantLib;

class ObjectStochastic : public Object {
public:
	ObjectStochastic(
		const Spread &dividendYield,
		const Rate &riskFreeRate,
		const Volatility &volatility,
		const Real &underlying,
		const Date &todaysDate,
		const Date &settlementDate);
	~ObjectStochastic();
	virtual boost::shared_ptr<void> getReference() const;
private:
	boost::shared_ptr<BlackScholesProcess> stochasticProcess_;
};

#endif
