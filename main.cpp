#include <iostream>
using namespace std;

template <typename T>
class MaxQueue {
public:
    MaxQueue(int n);
    MaxQueue(const MaxQueue& copy);
    
    ~MaxQueue(void);
    
    MaxQueue& operator=(const MaxQueue&);
    
    void Parse(void);
    
    bool frontIsEmpty(void);
    bool backIsEmpty(void);
    
    void push_front(T x);
    void push_back(T x);
    T pop_front(void);
    T pop_back(void);
    
    void Enqueue(T x);
    T Dequeue(void);
    T Maximum(void);
    bool queueIsEmpty(void);
    bool queueIsFull(void);
    void ReallocSpace(void);    
private:
    T *data, *max, *max_o;
    int cap, top1, top2;
};

template <typename T>
MaxQueue<T>::MaxQueue(int size):
    top1 (0),
    top2 (size-1),
    cap (size),
    data (new T[size]),
    max (new T[size]),
    max_o (new T[size]) {}

template <typename T>
MaxQueue<T>::MaxQueue(const MaxQueue<T>& copy) :
    top1 (copy.top1),
    top2 (copy.top2),
    cap (copy.cap),
    data (new T[cap]),
    max (new T[cap]),
    max_o (new T[cap])
{
    for (int i = 0; i < cap; i++) {
        data[i] = copy.data[i];
        max = copy.max[i];
        max_o[i] = copy.max_o[i];
    }
}

template <typename T>
MaxQueue<T>::~MaxQueue(void) {
    delete[]max;
    delete[]max_o;
    delete[]data;
}

template <typename T>
MaxQueue<T>&  MaxQueue<T>::operator=(const MaxQueue<T>& right) {
    top1 = right.top1;
    top2 = right.top2;
    if (cap != right.cap) {
        delete []data;
        delete []max;
        delete []max_o;
        data = new T[right.cap];
        max = new T[right.cap];
        max_o = new T[right.cap];
    }
    cap = right.cap;
    for (int i = 0; i < cap; i++) {
        data[i] = right.data[i];
        max = right.max[i];
        max_o[i] = right.max_o[i];
    }
    return *this;
}

template <typename T>
void MaxQueue<T>::Parse(void) {
    string command;
    
    for (;;) {
        cin >> command;
        
        if (command == "ENQ") {
            T num;
            cin >> num;
            Enqueue(num);
        }
        else {
            cout << "\t\t\t";
            
            if (command == "DEQ") {
                if (queueIsEmpty())
                    cout << "Queue is empty!";
                else
                    cout << Dequeue();
            }
            
            else if (command == "MAX") {
                if (queueIsEmpty())
                    cout << "Queue is empty!";
                else
                    cout << Maximum();
            }
            
            else if (command == "EMPTY") {
                if (queueIsEmpty())
                    cout << "true";
                else
                    cout << "false";
            }
            
            else if (command == "HALT") {
                return ;
            }
            cout << "\n";
        }
    }
}

template <typename T>
bool MaxQueue<T>::queueIsEmpty(void) {
    return frontIsEmpty() && backIsEmpty();
}

template <typename T>
bool MaxQueue<T>::queueIsFull(void) {
    return (top1 > top2);
}

template <typename T>
void MaxQueue<T>::ReallocSpace(void) {
    int new_cap = cap + 1;
    T *new_data = new T[new_cap];
    T *new_max  =  new T[new_cap];
    T *new_max_o = new T[new_cap];
    for (int i=0; i < top1; i++) {
        new_data[i] = data[i];
        new_max[i] = max[i];
        new_max_o[i] = max_o[i];
    }
    for (int i=top2 + 1; i < cap; i++) {
        new_data[i+1] = data[i];
        new_max[i+1] = max[i];
        new_max_o[i+1] = max_o[i];
    }
    delete []max;
    delete []max_o;
    delete []data;
    data = new_data;
    max = new_max;
    max_o = new_max_o;
    cap = new_cap;
    top2++;
}

template <typename T>
void MaxQueue<T>::Enqueue(T x) {
    
    if (queueIsFull())
        ReallocSpace();
    
    if (top1 == 0)
        max[0] = x;
    else
    {
        if (max[top1-1] > x)
            max[top1] = max[top1-1];
        else
            max[top1] = x;
    }
    
    push_front(x);
    return;
}

template <typename T>
T MaxQueue<T>::Dequeue(void) {
    T x;
        
    if ( backIsEmpty() )
        while ( !frontIsEmpty() ) {
            x = pop_front();
            push_back(x);
            
            if (top2 + 1 == cap - 1)
                max_o[top2 + 1] = x;
            else if (max_o[top2 + 2] > x)
                max_o[top2 + 1] = max_o[top2 + 2];
            else
                max_o[top2 + 1] = x;
            
        }
    
    x = pop_back();
    return x;
}

template <typename T>
T MaxQueue<T>::Maximum(void) {
    
    if (top1 == 0)
        return max_o[top2+1];
    
    else if ( !backIsEmpty() )
        return max[top1-1];
    
    else if (max[top1-1] > max_o[top2+1])
        return max[top1-1];
    
    else
        return max_o[top2 + 1];
}

template <typename T>
void MaxQueue<T>::push_front(T x) {
    data[top1] = x;
    top1++;
}

template <typename T>
void MaxQueue<T>::push_back(T x) {
    data[top2] = x;
    top2--;
}

template <typename T>
T MaxQueue<T>::pop_front (void) {
    top1--;
    return data[top1];
}

template <typename T>
T MaxQueue<T>::pop_back (void) {
    top2++;
    return data[top2];
}

template <typename T>
bool MaxQueue<T>::frontIsEmpty(void) {
    return (top1 == 0); 
}

template <typename T> 
bool MaxQueue<T>::backIsEmpty(void) {
    return (top2 == cap - 1); 
}

int main() {
    MaxQueue<int> a(1);
    a.Parse();
    return 0;
}
