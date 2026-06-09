# Naive Bayes Implementation (Machine Learning) Author: ***Vagelis Kosmiadis***

This is the implementation of Naive Bayes Machine Learning Classification Algorithm as a personal project which can also be used in commercial and open source applications as it is licensed under the MIT open-source license.

### There are **two** main parts
- The first one is training
- The second one is predicting

## Goals
The goal of this simple implementation is to understand the Naive-Bayes algorithm and combine academic knowledge with coding skills in c++. ***The implementation aims to classify emails as **spam or no spam** ***

## Implementation

To start of this implementation we need to define the problem we are solving. The spam or no-spam classification problem is already satisfied at our everyday email providers that we use. It consists of judging an email as malicious or not (spam or no-spam) via many parameters of the content, the sender etc. The first part consists of defining the data the model expects. To keep it simple I just kept the content of the email as the only parameter from which words extraction will be made. Those words then will be processed through a naive bayes implementation using Baye's Theorem. 

