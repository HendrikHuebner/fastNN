//
// Created by hhuebner on 12/30/23.
//

#ifndef FASTNN_DATASET_H
#define FASTNN_DATASET_H


#include <vector>
#include <random>
#include <algorithm>
#include <stdexcept>

class DataSet {

public:
    DataSet(std::vector<float> features, std::vector<float> labels, std::mt19937 random, int batchSize):
        features(features), labels(labels), random(random), batchSize(batchSize) {
        if (this->size() % batchSize != 0) {
            throw new std::invalid_argument("Dataset size must be divisible by batch size");
        }
    }

    [[nodiscard]] inline int size() const {
        return this->features.size();
    }

    inline int batches() const {
        return this->size() / this->batchSize;
    }

    /**
     * Shuffles all examples
     */
    void shuffle();

    /**
     * Shuffles all batches of examples AND all batches
     */
    void mixBatches();

    /**
     * Returns the next set of features and labels as a pair (features, labels)
     */
    std::pair<std::vector<float>, std::vector<float>> nextBatch();

private:
    std::vector<float> features;
    std::vector<float> labels;
    const int batchSize;
    int currentBatch = 0;
    std::mt19937 random;
};

#endif //FASTNN_DATASET_H
