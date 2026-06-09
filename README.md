# Naive Bayes Implementation (Machine Learning) on Email Filtering (SPAM/NO-SPAM)

This is the implementation of Naive Bayes Machine Learning Classification Algorithm as a personal project for Email Classification (SPAM/NO-SPAM) which can also be used in commercial and open source applications as it is licensed under the MIT open-source license.

## How it works

**The implementation consists of two parts**

- The first one is the training of the model
- The second one is the prediction the model makes

## Goals
The goal of this simple implementation is to understand the Naive-Bayes algorithm and combine academic knowledge with coding skills in C++. **The implementation aims to classify emails as spam or no spam**

## Implementation

- The first part consists of defining the data the model expects. 
    The SPAM or NO_SPAM classification tag is handle via an enum as follows:
    ```
        enum CLASSIFICATION {
            SPAM,
            NO_SPAM
        };
    ```
    There are two main different structs for this purpose:
        1. TrainingData --> The data the model ingests and gets trained
            
        2. PredictionData --> The user input to the model to make a prediction

To keep it simple I just kept the content of the email as the only parameter from which words extraction will be made. Those words then will be processed through a naive bayes implementation using Baye's Theorem. 

