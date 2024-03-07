//
// Created by hhuebner on 3/2/24.
//

#ifndef FASTNN_DATASET_H
#define FASTNN_DATASET_H

#include <iterator>

template<class T>
class DataIterator : public std::iterator<std::input_iterator_tag, T> {

private:
    const int batchSize;

public:
    DataIterator(const int batchSize) : batchSize(batchSize) {}


};

#endif //FASTNN_DATASET_H
