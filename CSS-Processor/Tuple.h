#ifndef TUPLE_H
#define TUPLE_H

template <class T, class T2>
class Tuple
{
public:
	T first;
	T2 second;
	Tuple(T first, T2 second);
};

template <class T, class T2>
Tuple<T, T2>::Tuple(T first, T2 second) :
	first{first}, second{second}
{

}

#endif