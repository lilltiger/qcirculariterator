//
// C++ Interface: qcirculariterator
//
// Description: 
//
//
// Author: Peter Bengtsson <dev@lilltiger.se>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef QCIRCULAR_ITERATOR_H
#define QCIRCULAR_ITERATOR_H

template<
	typename Container
>
class CircularIterator
{
	public:
		CircularIterator(Container &c) : container_(c) {}
		CircularIterator(const CircularIterator& i) : iterator_(i.iterator_), container_(i.container_)
		{
			
		}

		CircularIterator(const Container &c, const typename Container::iterator& i) : iterator_(i), container_(i.container_)
		{
			
		}
	
		CircularIterator& operator=(const typename Container::iterator& i)
		{
			// If the assigned iterator is at the end() pos set the circular iterator to be at the begning.
			if (i == container_.end() ) {
				(*this).toFront();
			} else {
				iterator_ = i;
			}
			return *this;
		}

		CircularIterator& operator=(const CircularIterator& i)
		{
			iterator_ = i;
			return *this;
		}

		CircularIterator operator++(int)
		{
			CircularIterator R(*this);
			++(*this);
			return R;
		}

		CircularIterator& operator++()
		{
			++iterator_;
			if(iterator_ == container_.end()) {
				iterator_ = container_.begin();
			}

			return *this;
		}

		CircularIterator& operator--(int)
		{
			CircularIterator R(*this);
			--(*this);
			return R;
		}

		CircularIterator& operator--()
		{
			if(iterator_ == container_.begin()) {
				iterator_ = container_.end();
			} 

			--iterator_;

			return *this;
		}

		typename Container::value_type& operator*()
		{
			return *iterator_;
		}

		typename Container::value_type& operator->()
		{
			return *iterator_;
		}

		CircularIterator& toFront()
		{
			iterator_ = container_.begin();
			return *this;
		}

		CircularIterator& toBack()
		{
			iterator_ = container_.end()-1;
			return *this;
		}

		CircularIterator& peek(int steps)
		{
			//TODO; implement.. need to check end..
		}

		CircularIterator operator+(int value)
		{
			CircularIterator ite(*this);

			if(value < 0) {
				for(int i = 0; i > value; --i) {
					--(ite);
				}
			} else {
				for(int i = 0; i < value; ++i) {
					++(ite);
				}
			}

			return ite;
		}

		CircularIterator operator-(int value)
		{
			CircularIterator ite(*this);

			if(value > 0) {
				for(int i = 0; i > value; ++i) {
					++(ite);
				}
			} else {
				for(int i = 0; i < value; ++i) {
					--(ite);
				}
			}

			return ite;
		}

		const typename Container::iterator& getIterator() const
		{
			return iterator_;
		}
	private:
		typename Container::iterator iterator_;
		Container& container_;
};

#endif
