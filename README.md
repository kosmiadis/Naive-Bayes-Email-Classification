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

