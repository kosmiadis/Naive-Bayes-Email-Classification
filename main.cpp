#include "NaiveBayesModel.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main () {
    NaiveBayesModel model;
    model.load_and_fit("dataset.csv");

    PredictionData email1 = { "URGENT INVESTMENT ALERT! You have been selected to claim a free bonus in our crypto trading platform. Turn $100 into millions overnight with our guaranteed automated system. Click this link immediately to receive your reward cash prize before your access expires!" };
    PredictionData email2 = { "Hi everyone, could you please review the latest updates on the project repository before tomorrow morning? We need to schedule a quick sync meeting with the development team to discuss the upcoming deployment and resolve any open bugs." };

    Prediction prediction1 = model.predict(email1);
    Prediction prediction2 = model.predict(email2);

    std::cout << prediction1;
    std::cout << prediction2;

    return 0;
}