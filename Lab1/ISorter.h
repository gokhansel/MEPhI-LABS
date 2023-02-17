#include "Sequences.h"

template <typename T> class ISorter {
public:
  virtual void Sort(bool (*cmp1)(const T &, const T &), Sequence<T> *seq,
                    bool (*cmp2)(const T &, const T &) = nullptr) = 0;
};

template <typename T> class IQuickSort : public ISorter<T> {
public:
  void Sort(bool (*cmp1)(const T &, const T &), Sequence<T> *seq,
            bool (*cmp2)(const T &, const T &) = nullptr) override {
    quickSort(seq, 0, seq->GetLength() - 1, cmp1);
  }

private:
  void quickSort(Sequence<T> *seq, int left, int right,
                 bool (*cmp1)(const T &, const T &)) {
    if (left < right) {
      int pivotIndex = partition(seq, left, right, cmp1);
      quickSort(seq, left, pivotIndex - 1, cmp1);
      quickSort(seq, pivotIndex + 1, right, cmp1);
    }
  }

  int partition(Sequence<T> *seq, int left, int right,
                bool (*cmp1)(const T &, const T &)) {
    T pivot = seq->Get(right);
    int i = left - 1;
    for (int j = left; j < right; j++) {
      if (cmp1(seq->Get(j), pivot)) {
        i++;
        swap(seq->Get(i), seq->Get(j));
      }
    }
    swap(seq->Get(i + 1), seq->Get(right));
    return i + 1;
  }
  void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
  }
};

/*template<typename T>
class IBubbleSort : public ISorter<T> {
public:
    void
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const
T &, const T &) = nullptr) override { int n = seq->GetLength(); int k;
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
    Sort(bool(*cmp1)(const T &, const T &), Sequence<T> *seq, bool(*cmp2)(const
T &, const T &) = nullptr) override { for (int i = 0; i < seq->GetLength() - 1;
i++)
        {
            for (int j = (seq->GetLength() - 1); j > i; j--) // для всех
элементов после i-ого
                {
                if (cmp1(seq->Get(j), seq->Get(j-1))) // если текущий элемент
меньше предыдущего
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

template <typename T> class IMergeSort : public ISorter<T> {
public:
    void Merge(Sequence<T>* seq, int left, int mid, int right, bool(*cmp)(const T&, const T&)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        T *L = new T[n1];
        T *R = new T[n2];

        for (int i = 0; i < n1; i++)
            L[i] = seq->Get(left + i);

        for (int j = 0; j < n2; j++)
            R[j] = seq->Get(mid + 1 + j);

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (!cmp(L[i], R[j])) {
                seq->Get(k) = L[i];
                i++;
            } else {
                seq->Get(k) = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            seq->Get(k) = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            seq->Get(k) = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void MergeSort(Sequence<T>* seq, int left, int right, bool(*cmp)(const T&, const T&)) {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        MergeSort(seq, left, mid, cmp);
        MergeSort(seq, mid + 1, right, cmp);
        Merge(seq, left, mid, right, cmp);
    }

    void Sort(bool (*cmp1)(const T &, const T &), Sequence<T> *seq, bool (*cmp2)(const T &, const T &) = nullptr) override {
      //if(seq->GetLength() == 0){
      //  return;
      //}
        MergeSort(seq, 0, seq->GetLength() - 1, cmp1);
    }
};

template <typename T> class IBinaryInsertSort : public ISorter<T> {
public:
  void Sort(bool (*cmp1)(const T &, const T &), Sequence<T> *seq,
            bool (*cmp2)(const T &, const T &) = nullptr) override {
    for (int i = 1; i < seq->GetLength(); ++i) {
      if (cmp1(seq->Get(i - 1), seq->Get(i))) { //>
        T x = seq->Get(i);
        int left = 0;
        int right = i - 1;
        do {
          int mid = (left + right) / 2;
          if (cmp2(seq->Get(mid), x)) //<
            left = mid + 1;
          else
            right = mid - 1;
        } while (left <= right);
        for (int j = i - 1; j >= left; j--) {
          seq->Get(j + 1) = seq->Get(j);
        }
        seq->Get(left) = x;
      }
    }
  }
};