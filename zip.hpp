/**
 * A demo program for itertools.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-05
 */

#pragma once
#import "range.hpp"

namespace itertools{

	/*template<typename A, typename B>
	class pair{
		A a;
		B b;

	public:
		pair(A otherA, B otherB):
			a(otherA), b(otherB){}

		pair():
			a(int (0)), b(int (0)){}
		
		template <typename I, typename J>
		friend std::ostream& operator <<(std::ostream& os, const pair<I,J> myPair);
	};*/

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const pair<I,J> myPair) {
		return os << myPair.first << "," << myPair.second;
	}	

	template<typename A, typename B>
	class zip{

	private:

		// fields
		A aIterable;
		B bIterable;
		

	public:

		zip<A,B>(const A _aIterable, const B _bIterable)
			: aIterable(_aIterable),
			bIterable(_bIterable) {}

		class const_iterator {

			private:
				typename A::const_iterator tCurrent;
				typename A::const_iterator tEnd;
				typename B::const_iterator sCurrent;
				typename B::const_iterator sEnd;

			public:
				const_iterator(typename A::const_iterator tIt, typename A::const_iterator tItEnd, typename B::const_iterator sIt, typename B::const_iterator sItEnd):
					tCurrent(tIt), tEnd(tItEnd),
					sCurrent(sIt), sEnd(sItEnd)
				 { }

				const auto operator*() const {
					return pair(*tCurrent, *sCurrent);
				}

				// ++i;
				const_iterator& operator++() {
					++tCurrent;
					++sCurrent;
					return *this;
				}

				// i++;
				// Usually const_iterators are passed by value and not by const& as they are small.
				const const_iterator operator++(int) {
					const_iterator tmp= *this;
					this->zip<A,B>::const_iterator::operator++();
					return tmp;
				}

				bool operator==(const const_iterator& rhs) const {
					return (this->tCurrent == rhs.tCurrent && this->sCurrent == rhs.sCurrent);
				}

				bool operator!=(const const_iterator& rhs) const {
					return !(*this==rhs);
				}

				template <typename I, typename J>
				friend std::ostream& operator <<(std::ostream& os, const typename zip<I,J>::const_iterator& it);

		};  // END OF CLASS const_iterator
		
		typename zip<A,B>::const_iterator begin() const {
			return zip<A,B>::const_iterator(aIterable.begin(), aIterable.end(), bIterable.begin(), bIterable.end());
		}
			
		typename zip<A,B>::const_iterator end() const {
			return zip<A,B>::const_iterator(aIterable.end(), aIterable.end(), bIterable.end(), bIterable.end());
		}

	};   // END OF CLASS zip

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const typename zip<I,J>::const_iterator& it) {
		return os << (*it);
	}
}
