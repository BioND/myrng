/**
 * @file util.h
 * @date 23.05.2012
 * @author gerd
 */

#ifndef MYRNG_UTIL_H_
#define MYRNG_UTIL_H_

#include <iterator>
#include <cassert>

namespace myrng
{
namespace util
{
/**
 * Get random element from container
 * @param container Random access container (e.g., std::vector)
 * @param rnd Random variates generator
 * @return random element in @p container
 */
template<class U, class V, class RandomGen>
inline U& random_from(V& container, RandomGen& rnd)
{
	int i = rnd.IntFromTo(0, container.size() - 1);
	return container[i];
}

/**
 * Get random element from range
 * @param begin iterator pointing to beginning of range
 * @param end iterator pointing to (past the) end of range
 * @param rnd random variates generator
 * @return random iterator within range or @p end if empty range
 */
template<class _Iter, class RandomGen>
inline _Iter random_from(_Iter begin, _Iter end, RandomGen& rnd)
{
	if (begin == end)
		return end;
	int i = rnd.IntFromTo(0, std::distance(begin, end) - 1);
	std::advance(begin, i);
	assert(begin != end);
	return begin;
}

/**
 * Get random element from range
 * @param range iterator range
 * @param rnd random variates generator
 * @return random iterator within @p range or @p range.second if empty range
 */
template<class _Iter, class RandomGen>
inline _Iter random_from(std::pair<_Iter, _Iter> range, RandomGen& rnd)
{
	return random_from(range.first, range.second, rnd);
}
}
}

#endif /* UTIL_H_ */
