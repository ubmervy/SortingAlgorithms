//QuickSortStrategy.cpp
#include "QuickSortStrategy.h"
#include "SortStrategy.h"
#include "SortResult.h"
#include "Sequence.h"
#include <chrono>

//constructor
QuickSortStrategy::QuickSortStrategy()
{

}

//destructor
QuickSortStrategy::~QuickSortStrategy()
{

}

// Measures sorting time and returns SortResult
SortResult QuickSortStrategy::SortSequence(Sequence &sequence)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();

    QuickSortSequence(sequence);

    std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double, std::ratio< 1, 1>> dur = t2 - t1;
    sr.duration = dur.count();

    return sr;
}

//Sorts sequence of elements
void QuickSortStrategy::QuickSortSequence(Sequence &sequence)
{
    int left = 0;
    int right = sequence.fd.size() - 1;
    std::stack <int> st;
    st.push(right);
    st.push(left);
    int maxStack = st.size() / 2;

    while (!st.empty())
    {
        left = st.top();
        st.pop();
        right = st.top();
        st.pop();
        if (right <= left)
        {
            //cmp++;
            continue;
        }
        int i = MakePartition(sequence, left, right);

        //push2(s, l, i - 1);
        //push2(s, i + 1, r);

        //push2(s, i + 1, r);
        //push2(s, l, i - 1);

        if (i - left > right - i)
        {
            sr.cmp++;
            PushToStack(st, left, --i);
            PushToStack(st, ++i, right);
        }
        else
        {
            PushToStack(st, ++i, right);
            PushToStack(st, left, --i);
        }
        if (st.size() / 2 > (unsigned)maxStack)
        {
            maxStack = st.size() / 2;
            sr.cmp++;
        }
    }
}

//Gets pivot element for quicksort
int QuickSortStrategy::MakePartition(Sequence &sequence, int left, int right)
{
    int i = left - 1, j = right;
    std::string v = sequence.fd[right];
    //std::shared_ptr<void> v = sequence.fd.at(right);
    for (;;)
    {
        while (sequence.fd[++i] < v)
        {
            sr.cmp++;
        };
        sr.cmp++;
        while (v < sequence.fd.at(--j))
        {
            sr.cmp++;
            if (j == left)
            {
                break;
            }
        }
        sr.cmp++;
        if (i >= j)
        {
            sr.cmp++;
            break;
        }
        sr.cmp++;

        std::swap(sequence.fd[i], sequence.fd[j]);
        sr.moves++;
    }
    std::swap(sequence.fd[i], sequence.fd[right]);
    sr.moves++;
    return i;
}

//Pushes to stack minimal part of divided sequence to minimize stack size
void QuickSortStrategy::PushToStack(std::stack<int> &s, int &A, int &B) const
{
    s.push(B);
    s.push(A);
}
