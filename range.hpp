/**
 * A demo program for itertools.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-05
 */

#pragma once

namespace itertools{

	template<typename T>
	class range{

	private:
		// fields
		T start, finish;		

	public:
		range<T>(const T _start, const T _finish)
			: start(_start), finish(_finish) {}

		range<T> (const range& rhs)
			: start(rhs.start), finish(rhs.finish) {}

		class const_iterator {

			private:
				T current;

			public:
				const_iterator(T element)
					: current(element) {
				}

				const_iterator(const const_iterator &other)
					: current(other.current) {
				}

				const T operator*() const {
					return current;
				}

				// ++i;
				const_iterator& operator++() {
					++(current);
					return *this;
				}

				// i++;
				// Usually iterators are passed by value and not by const& as they are small.
				const const_iterator operator++(int) {
					iterator tmp= *this;
					(current)++;
					return tmp;
				}

				bool operator==(const const_iterator& rhs) const {
					return current == rhs.current;
				}

				bool operator!=(const const_iterator& rhs) const {
					return current != rhs.current;
				}

				template <typename U>
				friend std::ostream& operator <<(std::ostream& os, const const_iterator& it);

		};  // END OF CLASS ITERATOR

		const_iterator begin() const {
			return range<T>::const_iterator(start);
		}
			
		const_iterator end() const {
			return range<T>::const_iterator(finish);
		}

	};   // END OF CLASS RANGE

	template <typename U>
	ostream& operator <<(ostream& os, const typename range<U>::const_iterator& it) {
		return os << (*it);
	}
}
