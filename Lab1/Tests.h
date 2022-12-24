#include <iostream>
#include "ArraySequence.h"
#include "LinkedListSequence.h"
#include "Functions.h"
#include <time.h>
#include <chrono>

class Timer
        {
        private:
            using clock_t = std::chrono::high_resolution_clock;
            using second_t = std::chrono::duration<double, std::ratio<1> >;

            std::chrono::time_point<clock_t> m_beg;

        public:
            Timer() : m_beg(clock_t::now())
            {
            }

            void reset()
            {
                m_beg = clock_t::now();
            }

            double elapsed() const
            {
                return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
            }
        };


void TEST(int sizetest){
    int data[sizetest];
    std::cout << "Start test" << std::endl;
    for (int i = 0; i < sizetest; ++i) {
        data[i] = rand() % 1000;
    }

    std::cout << "Array BinaryInsertSort : " << std::endl;   // Тест сортировок на динамическом массиве
    ArraySequence<int> a(data, sizetest);
    Timer t_1;
    a.BinaryInsertSort(cmp3,cmp2);
    std::cout << "Sorting time: " << t_1.elapsed()*1000 << '\n';
    IsOk(&a,cmp1);
    Timer t_2;
    a.BinaryInsertSort(cmp3,cmp2);
    std::cout << "sorting time of the sorted data: " << t_2.elapsed()*1000 << '\n';
    IsOk(&a,cmp1);
    a.BinaryInsertSort(cmp2,cmp3);
    std::cout << "Test result of sorted data in reverse order: ";
    IsOk(&a,cmp4);
    Timer t_3;
    a.BinaryInsertSort(cmp3,cmp2);
    std::cout << "sorting time of the data sorted in reverse order: " << t_3.elapsed()*1000 << '\n';
    IsOk(&a,cmp1);
    std::cout << std::endl <<std::endl;

    std::cout << "List BinaryInsertSort : " << std::endl;   // Тест сортировок на связном списке
    LinkedListSequence<int> b(data, sizetest);
    Timer t_4;
    b.BinaryInsertSort(cmp3,cmp2);     //смена местами cmp3 <-> cmp2 дает сортировку по убыванию
    std::cout << "Sorting time: " << t_4.elapsed()*1000 << '\n';
    IsOk(&b,cmp1);
    Timer t_5;
    b.BinaryInsertSort(cmp3,cmp2);
    std::cout << "sorting time of the sorted data: " << t_5.elapsed()*1000 << '\n';
    IsOk(&b,cmp1);
    b.BinaryInsertSort(cmp2,cmp3);
    std::cout << "Test result of sorted data in reverse order: ";
    IsOk(&b,cmp4);
    Timer t_6;
    b.BinaryInsertSort(cmp3,cmp2);
    std::cout << "sorting time of the data sorted in reverse order: " << t_6.elapsed()*1000 << '\n';
    IsOk(&b,cmp1);
    std::cout << std::endl <<std::endl;


    std::cout << "Array ShellSort : " << std::endl;
    ArraySequence<int> c(data, sizetest);
    Timer t_7;
    c.ShellSort(cmp3);
    std::cout << "Sorting time: " << t_7.elapsed()*1000 << '\n';
    IsOk(&c,cmp1);
    Timer t_8;
    c.ShellSort(cmp3);
    std::cout << "sorting time of the sorted data: " << t_8.elapsed()*1000 << '\n';
    IsOk(&c,cmp1);
    c.ShellSort(cmp2);
    std::cout << "Test result of sorted data in reverse order: ";
    IsOk(&c,cmp4);
    Timer t_9;
    c.ShellSort(cmp3);
    std::cout << "sorting time of the data sorted in reverse order: " << t_9.elapsed()*1000 << '\n';
    IsOk(&c,cmp1);
    std::cout << std::endl <<std::endl;


    std::cout << "List ShellSort : " << std::endl;
    LinkedListSequence<int> d(data, sizetest);
    Timer t_10;
    d.ShellSort(cmp3);
    std::cout << "Sorting time: " << t_10.elapsed()* 1000<< '\n';
    IsOk(&d,cmp1);
    Timer t_11;
    d.ShellSort(cmp3);
    std::cout << "sorting time of the sorted data: " << t_11.elapsed() * 1000 << '\n';
    IsOk(&d,cmp1);
    d.ShellSort(cmp2);
    std::cout << "Test result of sorted data in reverse order: ";
    IsOk(&d,cmp4);
    Timer t_12;
    d.ShellSort(cmp3);
    std::cout << "sorting time of the data sorted in reverse order: " << t_12.elapsed() *1000<< '\n';
    IsOk(&d,cmp1);
    std::cout << std::endl <<std::endl;


    std::cout << "Array BubbleSort : " << std::endl;
    ArraySequence<int> e(data, sizetest);
    Timer t_13;
    e.BubbleSort(cmp2);
    std::cout << "Sorting time: " << t_13.elapsed() *1000<< '\n';
    IsOk(&e,cmp1);
    Timer t_14;
    e.BubbleSort(cmp2);
    std::cout << "sorting time of the sorted data: " << t_14.elapsed() *1000<< '\n';
    IsOk(&e,cmp1);
    e.BubbleSort(cmp3);
    std::cout << "Test result of sorted data in reverse order: ";
    IsOk(&e,cmp4);
    Timer t_15;
    e.BubbleSort(cmp2);
    std::cout << "sorting time of the data sorted in reverse order: " << t_15.elapsed()*1000 << '\n';
    IsOk(&e,cmp1);
    std::cout << std::endl <<std::endl;



    std::cout << "List BubbleSort : " << std::endl;
    LinkedListSequence<int> f(data, sizetest);
    Timer t_17;
    f.BubbleSort(cmp2);
    std::cout << "Sorting time: " << t_17.elapsed()*1000 << '\n';
    IsOk(&f,cmp1);
    Timer t_18;
    f.BubbleSort(cmp2);
    std::cout << "sorting time of the sorted data: " << t_18.elapsed()*1000 << '\n';
    IsOk(&f,cmp1);
    f.BubbleSort(cmp3);
    std::cout << "Test result of sorted data in reverse order: ";
    IsOk(&f,cmp4);
    Timer t_19;
    f.BubbleSort(cmp2);
    std::cout << "sorting time of the data sorted in reverse order: " << t_19.elapsed()*1000 << '\n';
    IsOk(&f,cmp1);
    std::cout << std::endl <<std::endl;

}