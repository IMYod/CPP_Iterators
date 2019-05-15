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
	class pairWithChoice{
		A a;
		B b;
		bool isA;

	public:
		pairWithChoice(A otherA, B otherB, bool _isA):
			a(otherA), b(otherB)
		{
			isA = _isA;
		}
		
		template <typename I, typename J>
		friend std::ostream& operator <<(std::ostream& os, const pairWithChoice<I,J> myPair);
	};

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const pairWithChoice<I,J> myPair) {
		if (myPair.isA)
			return os << myPair.a;
		return os << myPair.b;
	}*/	

	template<typename A, typename B>
	class chain{

	private:

		// fields
		A aIterable;
		B bIterable;
		

	public:

		chain<A,B>(const A _aIterable, const B _bIterable)
			: aIterable(_aIterable),
			bIterable(_bIterable) {}

		class const_iterator {

			private:
				typename A::const_iterator tCurrent;
				typename A::const_iterator tEnd;
				typename B::const_iterator sCurrent;

				bool inFirst() const {return tCurrent != tEnd;}

			public:
				const_iterator(const typename A::const_iterator &tIt, const typename A::const_iterator &tItEnd, const typename B::const_iterator &sIt):
					tCurrent(tIt), tEnd(tItEnd),
					sCurrent(sIt)
				 { }

				const_iterator(const const_iterator &other): //copy contructor
					tCurrent(other.tCurrent), tEnd(other.tEnd),
					sCurrent(other.sCurrent)
				 { }

				const auto operator*() const {
					//return pairWithChoice(*tCurrent, *sCurrent, inFirst());
					if (inFirst())
						return *tCurrent;
					return *sCurrent;
				}


				// ++i;
				const_iterator& operator++() {
					if (inFirst())
						++tCurrent;
					else
						++sCurrent;
					return *this;
				}

				// i++;
				// Usually iterators are passed by value and not by const& as they are small.
				const const_iterator operator++(int) {
					const_iterator tmp= *this;
					this->chain<A,B>::const_iterator::operator++();
					return tmp;
				}

				bool operator==(const const_iterator& rhs) const {
					return (this->tCurrent == rhs.tCurrent && this->sCurrent == rhs.sCurrent);
				}

				bool operator!=(const const_iterator& rhs) const {
					return !(*this==rhs);
				}

				template <typename I, typename J>
				friend std::ostream& operator <<(std::ostream& os, const typename chain<I,J>::iterator& it);

		};  // END OF CLASS ITERATOR
		
		typename chain<A,B>::const_iterator begin() const {
			return chain<A,B>::const_iterator(aIterable.begin(), aIterable.end(), bIterable.begin());
		}
			
		typename chain<A,B>::const_iterator end() const {
			return chain<A,B>::const_iterator(aIterable.end(), aIterable.end(), bIterable.end());
		}

	};   // END OF CLASS chain

	template <typename I, typename J>
	ostream& operator <<(ostream& os, const typename chain<I,J>::const_iterator& it) {
		return os << (*it);
	}
}
