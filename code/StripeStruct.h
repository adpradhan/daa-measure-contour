#ifndef STRIPESTRUCT_H
#define STRIPESTRUCT_H

#include "Stripe.h"
/*! \struct StripeStruct
    This stores all the required variables to be returned from the STRIPES function.
	@see STRIPES()
*/
class StripeStruct
{
	public:
	vector<Interval> L;
	vector<Interval> R;
	set<int> P;
	vector<Stripe> S;
};

#endif