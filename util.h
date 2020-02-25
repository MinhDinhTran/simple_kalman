#ifndef __UTIL_H__
#define __UTIL_H__ 

#include <stdbool.h>
#include <math.h>

bool nearly_equal(float a, float b) {
		float absA = fabs(a);
		float absB = fabs(b);
		float diff = fabs(a - b);
        float epsilon = __FLT_EPSILON__;

		if (a == b) { // shortcut, handles infinities
			return true;
        } else if (a == 0 || b == 0 || (absA + absB < __FLT_MAX__)) {
			// a or b is zero or both are extremely close to it
			// relative error is less meaningful here
			return diff < (epsilon * __FLT_EPSILON__);
		} else { // use relative error
			return diff / fmin((absA + absB), __FLT_MAX__) < epsilon;
		}
}

#endif