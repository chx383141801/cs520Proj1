#ifndef MINIHP_H
#define MINIHP_H


#include <vector>
template <typename T> 
class minihp{
public:

	std::vector<T> queue;

	minihp();
	~minihp();
    void insert(T &t1);

    bool contains(T &t1);
    void erase(T &t1);
	void clear( );
    int size();
    T	pop();
    T   peek();
	
};

template<typename T>
inline minihp<T>::minihp()
{
	
}

template<typename T>
inline minihp<T>::~minihp()
{
}

template<typename T>
inline void minihp<T>::insert(T &t1)
{
	queue.push_back(t1);
	int p = queue.size()-1;
//	cout << p << endl;

    while (p!=0&&queue[(p+1) / 2 - 1] > queue[p])
    {
        T temp = queue[(p + 1) / 2 - 1];
        queue[(p + 1) / 2 - 1] = queue[p ];

        queue[p ] = temp;
		//queue.swap(p, (p + 1) / 2 - 1);
        p = (p + 1) / 2 - 1;

        for (int i = 0; i <queue.size(); i++)
        {
            //cout << queue[i] ;
        }
        //cout << endl;
    }
    //cout << "succ" << endl;
}

//TODO: check ti or t1; rewrite this function!
//TODO: if you cannot make it by using template, try to use node type only for this
//      assignment
template<typename T>
inline bool minihp<T>::contains(T &t1)
{
    for (size_t i = queue.begin	; i != queue.end; ++i)
    {
        if (queue[i] == ti) return true;
	}
	return false;
}

template<typename T>
inline void minihp<T>::erase(T &t1)
{
	for (int i =0; i <  queue.size(); i++)
    {
		if (queue[i] == t1) {
			queue[i] = queue[queue.size() - 1];
			queue.erase(queue.begin()+(queue.size() - 1));
		}

/*		while(i!=0&&queue[i] < queue[(i + 1) / 2 - 1]) {
			//queue.swap(i, (i + 1) / 2 - 1);

			T temp;
			temp = queue[i];
			queue[i] = queue[(i + 1) / 2 - 1];
			queue[(i + 1) / 2 - 1] = temp;
			 
			i = (i + 1) / 2 - 1;
		}*/

		while ((2 * (i + 1) - 1 < queue.size() && queue[i] > queue[2 * (i + 1) - 1]) || 
			(2 * (i + 1) < queue.size() && queue[i] > queue[2 * (i + 1)])) {
			if (2 * (i + 1) < queue.size()) {
			//	queue.swap(i,queue[2 * (i + 1)-1]<queue[2 * (i + 1)]? 2 * (i + 1) - 1: 2 * (i + 1) );

				T temp;
				temp = queue[i];
				int j = queue[2 * (i + 1) - 1] < queue[2 * (i + 1)] ? 2 * (i + 1) - 1 : 2 * (i + 1);
				queue[i] = queue[j];
				queue[j] = temp;
				i = j;

			}
			else {
				//queue.swap(i, 2 * (i + 1) - 1);
				T temp;
				temp = queue[i];
				queue[i] = queue[2 * (i + 1) - 1];
				queue[2 * (i + 1) - 1] = temp;
				i = 2 * (i + 1) - 1;
			}
		}
	}
}

template<typename T>
inline void minihp<T>::clear()
{
    queue.clear();
}

template<typename T>
inline int minihp<T>::size()
{
    /*for (int i = 0; i < queue.size(); i++)
	{
        std::cout << queue[i];
    }*/
	return queue.size();
}

//TODO: check if the queue is NULL
template<typename T>
inline T minihp<T>::pop()
{
/*	//if (queue.size() == 0) return _Nil;
	T res = queue[0];
	queue[0] = queue[queue.size() - 1];
	queue.erase(queue.begin() + queue.size() - 1);
int 	i = 0;
	while ((2 * (i + 1) - 1 < queue.size() && queue[i] > queue[2 * (i + 1) - 1]) ||
		(2 * (i + 1) < queue.size() && queue[i] > queue[2 * (i + 1)])) {
		cout << "i:" << i << "," << endl;
		if (2 * (i + 1) < queue.size()) {
			//	queue.swap(i,queue[2 * (i + 1)-1]<queue[2 * (i + 1)]? 2 * (i + 1) - 1: 2 * (i + 1) );

			T temp;
			temp = queue[i];
			int j = queue[2 * (i + 1) - 1] < queue[2 * (i + 1)] ? 2 * (i + 1) - 1 : 2 * (i + 1);
			queue[i] = queue[j];
			queue[j] = temp;
			i = j;

		}
		else {
			//queue.swap(i, 2 * (i + 1) - 1);
			T temp;
			temp = queue[i];
			queue[i] = queue[2 * (i + 1) - 1];
			queue[2 * (i + 1) - 1] = temp;
			i = 2 * (i + 1) - 1;
		}
	}
	*/
	T res = queue[0];
	queue[0] = queue[queue.size() - 1];
	minihp<T>::erase(queue[queue.size() - 1]);
	return res;
}

//TODO: write a function which only peek the top of queue without dequeue it
template<typename T>
inline T minihp<T>::peek()
{

}

#endif 
