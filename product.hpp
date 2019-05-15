/**
 * A demo program for itertools.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-05
 */

#pragma once
#import "range.hpp"
#include "zip.hpp"

namespace itertools{
	

	template<typename A, typename B>
	class product{

	private:

		// fields
		A aIterable;
		B bIterable;

	public:

		product<A,B>(const A _aIterable, const B _bIterable)
			: aIterable(_aIterable),
			bIterable(_bIterable) {}

		class const_iterator {

			private:
				typename A::const_iterator tCurrent;
				typename A::const_iterator tEnd;
				typename B::const_iterator sStart;
				typename B::const_iterator sCurrent;
				typename B::const_iterator sEnd;

				bool isDone() const {
					return (sCurrent == sEnd || tCurrent == tEnd);
				}

			public:
				const_iterator(typename A::const_iterator tIt, typename A::const_iterator tItEnd, typename B::const_iterator sIt, typename B::const_iterator sItEnd):
					tCurrent(tIt), tEnd(tItEnd),
					sStart(sIt), sCurrent(sIt), sEnd(sItEnd)
				 { }

				const auto operator*() const {
					return pair(*tCurrent, *sCurrent);
				}

				// ++i;
				const_iterator& operator++() {

					++sCurrent;
					if (sCurrent == sEnd){
						++tCurrent;
						if (tCurrent != tEnd)
							sCurrent = sStart;
					}	
					return *this;
				}

				// i++;
				// Usually const_iterators are passed by value and not by const& as they are small.
				const const_iterator operator++(int) {
					const_iterator tmp= *this;
					this->product<A,B>::const_iterator::operator++();
					return tmp;
				}

				bool operator==(const const_iterator& rhs) const {
					if (this->isDone() && rhs.isDone())
						return true;
					return (this->tCurrent == rhs.tCurrent && this->sCurrent == rhs.sCurrent);
				}

				bool operator!=(const const_iterator& rhs) const {
					return !(*this==rhs);
				}

				template <typename I, typename J>
				friend std::ostream& operator <<(std::ostream& os, const typename product<I,J>::const_iterator& it);

		};  // END OF CLASS const_iterator
		
		typename product<A,B>::const_iterator begin() const {
			return product<A,B>::const_iterator(aIterable.begin(), aIterable.end(), bIterable.begin(), bIterable.end());
		}
			
		typename product<A,B>::const_iterator end() const {
			return product<A,B>::const_iterator(aIterable.end(), aIterable.end(), bIterable.end(), bIterable.end());
		}

	};   // END OF CLASS product

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const typename product<I,J>::const_iterator& it) {
		return os << (*it);
	}
}
