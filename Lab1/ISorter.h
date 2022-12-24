#include "Sequences.h"

template<typename T>
class ISorter {
public:
    virtual void Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) = 0;
};




template<typename T>
class IBubbleSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        for (int i = 0; i < seq->GetLength(); ++i) {
            for (int j = 0; j < seq->GetLength(); ++j) {
                if (cmp1(seq->Get(i), seq->Get(j))) {
                    T tmp = seq->Get(i);
                    seq->Get(i) = seq->Get(j);
                    seq->Get(j) = tmp;
                }
            }
        }
    }
};

/*template<typename T>
class IBubbleSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        int n = seq->GetLength();
        int k;
        while(n>1) {
            k=0;
            for (int i=1; i<n;++i) {
                if(cmp1(seq->Get(i), seq->Get(i-1))) {
                    T tmp = seq->Get(i-1);
                    seq->Get(i-1)=seq->Get(i);
                    seq->Get(i)=tmp;
                    k=i;
                }
            }
            n=k;
        }
    }
};

template<typename T>
class IBubbleSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        for (int i = 0; i < seq->GetLength() - 1; i++)
        {
            for (int j = (seq->GetLength() - 1); j > i; j--) // для всех элементов после i-ого
                {
                if (cmp1(seq->Get(j), seq->Get(j-1))) // если текущий элемент меньше предыдущего
                    {
                    T temp = seq->Get(j-1); // меняем их местами
                    seq->Get(j-1) = seq->Get(j);
                    seq->Get(j) = temp;
                    }
                }
        }
    }
};
*/





template<typename T>
class IShellSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        int size = seq->GetLength();
        int gap = size / 2;

        while (gap > 0) {
            for (int i = gap; i < size; ++i) {
                T curr = seq->Get(i);
                int pos = i;
                while (pos >= gap && cmp1(seq->Get(pos - gap), curr)) {
                    seq->Get(pos) = seq->Get(pos - gap);
                    pos -= gap;
                    seq->Get(pos) = curr;
                }
            }
            gap = gap / 2;
        }
    }
};


template<typename T>
class IBinaryInsertSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const T &, const T &) = nullptr) override {
        for (int i = 1; i < seq->GetLength(); ++i) {
            if(cmp1(seq->Get(i - 1),seq->Get(i))){//>
                T x = seq->Get(i);
                int left = 0;
                int right = i - 1;
                do {
                    int mid = (left + right) / 2;
                    if(cmp2(seq->Get(mid), x))//<
                        left = mid + 1;
                    else
                        right = mid - 1;
                } while (left <= right);
                for (int j = i - 1; j >= left ; j--) {
                    seq->Get(j + 1) = seq->Get(j);
                }
                seq->Get(left) = x;
            }
        }
    }
};