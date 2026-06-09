# Naive Bayes Implementation (Machine Learning) on Email Filtering (SPAM/NO-SPAM)

This is the implementation of Naive Bayes Machine Learning Classification Algorithm as a personal project for Email Classification (SPAM/NO-SPAM) which can also be used in commercial and open source applications as it is licensed under the MIT open-source license.

## How it works

**The implementation consists of two parts**

- The first one is the training of the model
- The second one is the prediction the model makes

## Goals
The goal of this simple implementation is to understand the Naive-Bayes algorithm and combine academic knowledge with coding skills in C++. **The implementation aims to classify emails as spam or no spam**

## Implementation

- The first phase consists of defining the data the model expects and the data it outputs.
    The SPAM or NO_SPAM classification tag is handle via an enum as follows:
    ```
    enum CLASSIFICATION {
        SPAM,
        NO_SPAM
    };
    ```
    There are two main different structs for this purpose, the TrainingData and the PredictionData:
    ```

    struct TrainingData {
        //the content of the email
        std::string content;
        //SPAM, NO_SPAM
        CLASSIFICATION belong_class;
    };

    struct PredictionData {
        //the content of the email
        std::string content;
    };

    ```

    The data that the model takes as input in order to make a classification prediction is the Prediction struct:
    ```
    struct Prediction {
        //classification probability
        double probability;
        //SPAM, NO_SPAM
        CLASSIFICATION classification;
        //a result message
        string message;
    };
    ```

- The second phase consists of creating the methods for handling Naive-Bayes Model:
    1. fit(const std::vector<TrainingData> &dataset) (Here is where training happens)
    2. predict(const PredictionData &toPredictData) (The model predicts the classification)
    3. load_and_fit(const std::string &csv_filename) (Alternative way to load data from a csv, method automatically calls fit so it works the same as fit)

- The third phase consists of implementing the mathematical logic for classification using Baye's Theorem. I will not dive into it as there are many resources from which you can learn about it. (Basic Probabilities Knowledge is required)

## About Training The Model

There are two ways in which you can train the model.
- The first one is to create a std::vector<Training> dataset (this one is only for educational purposes)
- The second way is to load the dataset.csv file I have uploaded and contains over 5000+ emails with classifications (you should prefer this way for more accurate classification)

## How to use the Model

Using the model is pretty simple and straightforward. 

- First initialize an instance of the NaiveBayesModel class:
```
#include "NaiveBayesModel.h"

int main ( ){
    //initialize instance
    NaiveBayesModel model;
    
    return 0;
}

```
- Second load and fit the dataset.csv data into the model via the load_and_fit() method:
```
#include "NaiveBayesModel.h"

int main ( ){
    //initialize instance
    NaiveBayesModel model;
    
    //train the model
    model.load_and_fit("dataset.csv");

    return 0;
}
```

- Create prediction input data using PredictionData struct:
```
#include "NaiveBayesModel.h"

int main ( ){
    //initialize instance
    NaiveBayesModel model;
    
    //train the model
    model.load_and_fit("dataset.csv");

    //email1 to test
    PredictionData email1 = { "URGENT INVESTMENT ALERT! You have been selected to claim a free bonus in our crypto trading platform. Turn $100 into millions overnight with our guaranteed automated system. Click this link immediately to receive your reward cash prize before your access expires!" };

    //email2 to test
    PredictionData email2 = { "Hi everyone, could you please review the latest updates on the project repository before tomorrow morning? We need to schedule a quick sync meeting with the development team to discuss the upcoming deployment and resolve any open bugs." };
    

    return 0;
}
```

- Classify each email with the model.predict() method:

```
#include "NaiveBayesModel.h"

int main ( ){
    //initialize instance
    NaiveBayesModel model;
    
    //train the model
    model.load_and_fit("dataset.csv");

    PredictionData email1 = { "URGENT INVESTMENT ALERT! You have been selected to claim a free bonus in our crypto trading platform. Turn $100 into millions overnight with our guaranteed automated system. Click this link immediately to receive your reward cash prize before your access expires!" };

    PredictionData email2 = { "Hi everyone, could you please review the latest updates on the project repository before tomorrow morning? We need to schedule a quick sync meeting with the development team to discuss the upcoming deployment and resolve any open bugs." };
    
    Prediction prediction1 = model.predict(email1);
    Prediction prediction2 = model.predict(email2);

    std::cout << prediction1;
    std::cout << prediction2;

    return 0;
}
```

- The output of the program is something like this:
```
This email is most likely a spam with a propabillity of: 1
This email is most likely not a spam with a propabillity of: 0.982448
```