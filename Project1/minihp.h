#ifndef MINIHP_H
#define MINIHP_H

#include <iostream>
#include <vector>
#include "node.h"
template <typename T>
class minihp {
public:

    std::vector<T> queue;

    minihp();
    ~minihp();
    void insert(T &t1);

    bool contains(T &t1);
    void erase(T &t1);
    void clear();
    int size();
    T	pop();
    T   peek();

    std::vector<node> queue1;
    void insert(node & t1, int i);
    bool contains(node &t1,int ii);
    void erase(node &t1,int ii);
    //void clear();
    int size(int i);
    node	pop(int ii);
    node   peek(int ii);

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
    int p = queue.size() - 1;
    //	cout << p << endl;

    while (p != 0 && queue[(p + 1) / 2 - 1] > queue[p])
    {
        T temp = queue[(p + 1) / 2 - 1];
        queue[(p + 1) / 2 - 1] = queue[p];

        queue[p] = temp;
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

inline void minihp<node>::insert(node &t1,int i)
{
    queue1.push_back(t1);
    int p = queue1.size() - 1;
    //	cout << p << endl;

    while (p != 0 && queue1[(p + 1) / 2 - 1].f[i] > queue1[p].f[i])
    {
        node temp = queue1[(p + 1) / 2 - 1];
        queue1[(p + 1) / 2 - 1] = queue1[p];

        queue1[p] = temp;
        //queue.swap(p, (p + 1) / 2 - 1);
        p = (p + 1) / 2 - 1;

        for (int i = 0; i <queue1.size(); i++)
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
    for (std::vector<T>::iterator i = queue.begin(); i != queue.end(); ++i)
    {
        if (*i == t1) return true;
    }
    return false;
}

template<typename T>
inline bool minihp<T>::contains(node & t1, int ii)
{

 //   for (std::vector<node>::iterator i = queue1.begin(); i != queue1.end(); ++i)
    {
 //       if (*i->f[ii]== t1.f[ii]) return true;
    }

     for (int i=0;i<queue1.size();i++){
         if(queue1[i]==t1) return true;

     }
    return false;
}

template<typename T>
inline void minihp<T>::erase(T &t1)
{
    for (int i = 0; i < queue.size(); i++)
    {
        if (queue[i] == t1) {
            queue[i] = queue[queue.size() - 1];
            queue.erase(queue.begin() + (queue.size() - 1));
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
inline void minihp<T>::erase(node & t1, int ii)
{
    for (int i = 0; i < queue1.size(); i++)
    {
        if (queue1[i].f[ii] == t1.f[ii]) {
            queue1[i] = queue1[queue1.size() - 1];
            queue1.erase(queue1.begin() + (queue1.size() - 1));
        }

        /*		while(i!=0&&queue[i] < queue[(i + 1) / 2 - 1]) {
        //queue.swap(i, (i + 1) / 2 - 1);

        T temp;
        temp = queue[i];
        queue[i] = queue[(i + 1) / 2 - 1];
        queue[(i + 1) / 2 - 1] = temp;

        i = (i + 1) / 2 - 1;
        }*/

        while ((2 * (i + 1) - 1 < queue1.size() && queue1[i].f[ii] > queue1[2 * (i + 1) - 1].f[ii]) ||
            (2 * (i + 1) < queue1.size() && queue1[i].f[ii] > queue1[2 * (i + 1)].f[ii])) {
            if (2 * (i + 1) < queue1.size()) {
                //	queue.swap(i,queue[2 * (i + 1)-1]<queue[2 * (i + 1)]? 2 * (i + 1) - 1: 2 * (i + 1) );

                node temp;
                temp = queue1[i];
                int j = queue1[2 * (i + 1) - 1].f[ii] < queue1[2 * (i + 1)].f[ii] ? 2 * (i + 1) - 1 : 2 * (i + 1);
                queue1[i] = queue1[j];
                queue1[j] = temp;
                i = j;

            }
            else {
                //queue.swap(i, 2 * (i + 1) - 1);
                node temp;
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
template<typename T>
inline int minihp<T>::size(int i)
{
    return queue1.size();
}


//TODO: check if the queue is NULL
template<typename T>
inline node minihp<T>::pop(int i)
{

    if (queue1.size() == 0) {
        std::cout << "cannot pop" << std::endl;
        node res;
        return  res;
    }
    node res = queue1[0];
    queue1[0] = queue1[queue1.size() - 1];

    //std::cout<<"erase b"<<queue1.size();
    minihp<T>::erase(queue1[queue1.size() - 1],i);
// std::cout<<"erase a"<<queue1.size();
    return res;
}


template<typename T>
inline T minihp<T>::pop()
{

    if (queue.size() == 0) {
        std::cout << "cannot pop" << std::endl;
        T res;
        return  res;
    }
    T res = queue[0];
    queue[0] = queue[queue.size() - 1];
    minihp<T>::erase(queue[queue.size() - 1]);
    return res;



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
}

//TODO: write a function which only peek the top of queue without dequeue it
template<typename T>
inline T minihp<T>::peek()
{

    if (queue.size() == 0) {
        std::cout << "cannot peek" << std::endl;
        T res;
        return  res;
    }
    T res = queue[0];

    return res;
}


template<typename T>
inline node minihp<T>::peek(int i)
{
    if (queue1.size() == 0) {
        std::cout << "cannot peek" << std::endl;
        node res;
        return  res;
    }
    node res = queue1[0];

    return res;
}


#endif
