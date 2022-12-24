#include <iostream>
#include "ArraySequence.h"
#include "LinkedListSequence.h"
#include "Functions.h"
#include "Tests.h"

int main() {

    int s1 = 0;
    while (s1 != 3) {
        std::cout << std::endl << "Select an action:" << std::endl << "1 - create data" << std::endl  << "2 - run tests" << std::endl << "3 - exit" << std::endl;
        std::cin >> s1;
        switch (s1) {
            case 1: {
                int s4 = 0;
                while (s4 < 1 || s4 > 2) {
                    std::cout << std::endl << "Select the sequence type:" << std::endl << "1 - array data" << std::endl << "2 - list data" << std::endl;
                    std::cin >> s4;
                }
                Sequence<int> *seq;
                int s3 = 0;
                while (s3 < 1 || s3 > 2) {
                    std::cout << std::endl << "Select the way to create sequence:" << std::endl << "1 - from keyboard" << std::endl << "2 - random" << std::endl;
                    std::cin >> s3;
                    switch (s3) {
                        case 1: {
                            std::cout << "Number of elements:" << std::endl;
                            int N;
                            std::cin >> N;
                            int data[N];
                            std::cout << "Enter your elements:" << std::endl;
                            int el;
                            for (int i = 0; i < N; ++i) {
                                std::cin >> el;
                                data[i] = el ;
                            }
                            if (s4 == 1) {
                                seq = new ArraySequence<int>(data, N);
                            } else {
                                seq = new LinkedListSequence<int>(data, N);
                            }
                            break;
                        }
                        case 2: {
                            std::cout << "Number of elements:" << std::endl;
                            int N;
                            std::cin >> N;
                            int data[N];
                            for (int i = 0; i < N; ++i) {
                                data[i] = rand() % 1000;
                            }
                            if (s4 == 1) {
                                seq = new ArraySequence<int>(data, N);
                            } else {
                                seq = new LinkedListSequence<int>(data, N);
                            }
                        }
                        break;
                        default: {
                            std::cout << "Enter a number from the list!" << std::endl;
                            break;
                        }
                    }
                }

                std::cout << "Your data:" << std::endl;
                seq->Print();
                int s5 = 0;
                while (s5 < 1 || s5 > 5) {
                    std::cout << std::endl << "Select the sort algorithm:" << std::endl << "1 - BinaryInsertSort" << std::endl << "2 - ShellSort" << std::endl << "3 - BubbleSort" << std::endl;
                    std::cin >> s5;
                    switch (s5) {
                        case 1: {
                            seq->BinaryInsertSort(cmp3,cmp2);
                            seq->Print();
                            break;
                        }
                        case 2: {
                            seq->ShellSort(cmp3);
                            seq->Print();
                            break;
                        }
                        case 3: {
                            seq->BubbleSort(cmp2);
                            seq->Print();
                            break;
                        }
                        default: {
                            std::cout << "Enter a number from the list!" << std::endl;
                            break;
                        }
                    }
                }
                break;
            }
            case 2: {
                std::cout << "Number of elements:" << std::endl;
                int sizetest;
                std::cin >> sizetest;
                TEST(sizetest);
                break;
            }
            case 3 : {
                break;
            }
            default: {
                std::cout << "Enter a number from the list!" << std::endl;
                break;
            }
        }
    }
    return 0;
}
