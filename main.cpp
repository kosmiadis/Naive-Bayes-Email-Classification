#include "NaiveBayesModel.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main () {
    NaiveBayesModel model;

    try {
        model.load_and_fit("dataset.csv");
    } catch (const Error &err) {
        cout << err;
        return 0;
    }

    PredictionData email1 = { "URGENT INVESTMENT ALERT! You have been selected to claim a free bonus in our crypto trading platform" };
    PredictionData email2 = { "free and hello there" };

    try {

        Prediction prediction1 = model.predict(email1);
        std::cout << prediction1;
    } catch (const Error &err) {
        cout << err;
        return 0;
    }

    try {
        Prediction prediction2 = model.predict(email2);    
        std::cout << prediction2;
    } catch (const Error &err) {
        cout << err;
        return 0;
    }

    return 0;
}