/**
 * A demo program for itertools.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-05
 */

#pragma once
#include <math.h>
#include <set>
#include <functional>

namespace itertools{
	

	template<typename T>
	class powerset{

	private:
		// fields
		T iterable;

		uint sizeOfSet() const {
			uint fullSetSize=0;
			for (auto element : iterable)
				fullSetSize++;
			return fullSetSize;
		}		

	public:
		powerset<T>(const T _iterable)
			: iterable(_iterable) {}

		class const_iterator {

			private:
				const T& fullSet;
				uint binSets;	

			public:
				const_iterator(const T& _fullSet, int index)
				: fullSet(_fullSet), binSets(index) { }


				auto operator*() const {
					std::set<typename std::remove_reference<typename std::remove_const<decltype(*(iterable.begin()))>::type>::type> myset = {};
					int i=1;
					for (auto element : fullSet){
						if (i & binSets)
							myset.insert(element);
						i=i<<1;
					}
					return myset;
				}

				// ++i;
				const_iterator& operator++() {
					++binSets;
					return *this;
				}

				// i++;
				const const_iterator operator++(int) {
					const_iterator tmp= *this;
					++binSets;
					return tmp;
				}

				bool operator==(const const_iterator& rhs) const {
					return this->binSets == rhs.binSets;
				}

				bool operator!=(const const_iterator& rhs) const {
					return !(this->binSets == rhs.binSets);
				}

				template <typename U>
				friend std::ostream& operator <<(std::ostream& os, const typename powerset<U>::const_iterator& it);

		};  // END OF CLASS const_iterator

		const_iterator begin() const {
			return powerset<T>::const_iterator(this->iterable, 0);
		}
			
		const_iterator end() const {
			return powerset<T>::const_iterator(this->iterable, int(pow(2,sizeOfSet())));
		}

	};   // END OF CLASS powerset

	template <typename U>
	std::ostream& operator <<(std::ostream& os, const typename powerset<U>::const_iterator& it) {
		return os << *it;
	}

	template <typename U>
	std::ostream& operator <<(std::ostream& os, const typename std::set<U> myset) {
		os << "{";
		for (auto element : myset){
			os << element << ",";
		}
		if (myset.size()) // The subset is not the empty set
			os.seekp(-1, os.cur); //Delete last char (,)
		os << "}";
		return os;
}

}
