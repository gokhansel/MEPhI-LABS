// sorts.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

// Динамический массив
template <class T> class TSequence
{
public:
	T *v;
	int capacity; // Размер массива
	int size; // Количество значимых элементов

	// Вырастить массив
	void grow( int s )
	{
		if (v == NULL)
		{
			v = (T*) malloc( sizeof(T) * s );
			 memset( v, 0, sizeof(T) * s );
		}
		else
		{
			v = (T*) realloc( v, sizeof(T) * s );

			for( int i = capacity; i < s; i++ )
				v[i] = 0;
		}

		capacity = s;
	}

	TSequence()
	{
		v = NULL;
		grow( 16 );
		size = 0;
	}

	~TSequence()
	{
		free( v );
	}

	void add( T val )
	{
		if (size == capacity)
			grow( capacity*2 );

		v[size++] = val;
	}

	void clear()
	{
		size = 0;
	}
};

template <class T> void copy( TSequence<T> *from, TSequence<T> *to )
{
	to->clear();

	for( int i = 0; i < from->size; i++ )
		to->add( from->v[i] );
}

void rndArr( TSequence<int> *a, int n )
{
	srand(time(0));
	for( int i = 0; i < n; i++ )
		a->add( rand() % 1000 );
}

void arrUp( TSequence<int> *a, int n )
{
	for( int i = 0; i < n; i++ )
		a->add( i );
}

void arrDown( TSequence<int> *a, int n )
{
	for( int i = 0; i < n; i++ )
		a->add( n-i );
}

template <class T> void swap( T &t1, T &t2 )
{
	T t = t1;
	t1 = t2;
	t2 = t;
	// swapcnt++;
}

template <class T> void bubbleSort( TSequence<T> *a, int (*cmp)( T a, T b) )
{
    int i, i2, t;

	for( i = 0; i < a->size; i++ )
		for( i2 = 0; i2 < a->size-1; i2++ )
		{
			// Если более ранний больше, то меняем местами
            if (cmp( a->v[i2], a->v[i2+1]) > 0)
				swap( a->v[i2], a->v[i2+1] );
            
			// itercnt++;
		}
}

template <class T> void insertSort( TSequence<T> *arr, int (*cmp)( T a, T b) )
{
    int i, i2;
    T t;

    for( i = 0; i < arr->size; i++ )
	{
		t = arr->v[i];

        for( i2 = i-1; (i2 >= 0) && (cmp( t, arr->v[i2]) < 0); i2-- )
        {
            // stat.iter++;
			// stat.exch++;

			arr->v[i2+1] = arr->v[i2];
        }

		arr->v[i2+1] = t;
	}
}

template <class T> void myqsort( TSequence<T> *arr, int start, int end, int (*cmp)( T a, T b) )
{
	int i, j;
	T p, t;

	//For Linked list need sort qsort and merchsort nlogn
	//for array toshe samaya
	//Graphic 
	//Test
	//Git pull request 
	
	p = arr->v[ (start+end)/2 ];
	
	i = start;
	j = end;

	
	while (i <= j)
	{
		while (cmp( arr->v[i], p ) < 0) i++;
		while (cmp( arr->v[j], p ) > 0) j--;

		
		if ( (i <= j) )
		{
			swap( arr->v[i], arr->v[j] );
			i++; j--;
		}
	}

	
	if (j > start) myqsort( arr, start, j, cmp );
	if (i < end) myqsort( arr, i, end, cmp );
}


void print( TSequence<int> *arr )
{
	for( int i = 0; i < arr->size; i++ )
		printf( "%d ", arr->v[i] );
	printf( "\n" );
}

void calcCheck( TSequence<int> *arr )
{
	int c1 = 0, c2 = 0;

	// Проверка суммы (+) и через функцию xor.
	// Используется свойство коммутативности (a+b = b+a), так что перестановка не 
	// поменяет суммы, а вот если будет измнение количества элементов, то сумма поменяется.
	for( int i = 0; i < arr->size; i++ )
	{
		c1 = (c1 + arr->v[i]) % 65531;
		c2 = c2 ^ arr->v[i];
	}

	printf( "Sum %d and %d\n", c1, c2 );
}

int cmp_int( int a, int b )
{
	return a - b;
}

int main()
{
	TSequence<int> a, b;

	rndArr( &a, 100 );

	printf("Initial: ");
	print( &a );
	calcCheck( &a );

	// Пузырек
	copy( &a, &b );

	bubbleSort( &b, cmp_int );

	printf("Bubble\n");
	printf( "Sorted: " );
	print( &b );
	calcCheck( &b );

	// Вставками
	copy( &a, &b );

	insertSort( &b, cmp_int );

	printf( "Insert\n" );
	printf( "Sorted: " );
	print( &b );
	calcCheck( &b );

	// Быстрая
	copy( &a, &b );

	myqsort( &b, 0, b.size-1, cmp_int );

	printf( "QSort\n" );
	printf( "Sorted: " );
	print( &b );
	calcCheck( &b );

	getchar();


	return 0;
}

