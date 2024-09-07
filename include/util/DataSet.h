#pragma once

#include <random>
#include <stdexcept>
#include <vector>

class DataSet {

   private:
    std::vector<float> features;
    std::vector<float> labels;
    std::mt19937 random;
    const uint32_t batchSize;
    uint32_t currentBatch = 0;

   public:
    DataSet(std::vector<float> features, std::vector<float> labels, std::mt19937 random,
            uint32_t batchSize)
        : features(features), labels(labels), random(random), batchSize(batchSize) {
        if (this->size() % batchSize != 0) {
            throw new std::invalid_argument("Dataset size must be divisible by batch size");
        }
    }

    [[nodiscard]] inline int size() const { return this->features.size(); }

    inline uint32_t batches() const { return this->size() / this->batchSize; }

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

};
