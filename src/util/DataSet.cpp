//
// Created by hhuebner on 1/1/24.
//

#include "util/DataSet.h"

using namespace std;

void inline swap(std::vector<float>& vec, int a, int b) {
    float t = vec[a];
    vec[a] = vec[b];
    vec[b] = t;
}

void DataSet::shuffle() {
    for (int k = 0; k < this->size(); k++) {
        int r = k + this->random() % (this->size() - k);
        swap(this->features, k, r);
    }
}

void DataSet::mixBatches() {

    for (int i = 0; i < this->batches(); i++) {
        // shuffle each batch's examples
        for (int k = 0; k < this->batchSize; k++) {
            int r2 = k + this->random() % (this->size() - k);
            swap(this->labels, this->currentBatch + k, r2);
            swap(this->features, this->currentBatch + k, r2);
        }
    }

    // shuffle batches
    for (int i = 0; i < this->batches(); i++) {
        long r = this->random() % i;

        for (int j = 0; j < this->batchSize; j++) {
            swap(this->labels, i + j, r + j);
            swap(this->features, i + j, r + j);
        }
    }
}

pair<vector<float>, vector<float>> DataSet::nextBatch() {
    vector<float> newLabels;
    vector<float> newFeatures;

    for (int i = 0; i < this->batchSize; i++) {
        newLabels[i] = this->labels[this->currentBatch * this->batchSize + i];
        newFeatures[i] = this->features[this->currentBatch * this->batchSize + i];
    }

    this->currentBatch++;
    return make_pair(newFeatures, newLabels);
}
