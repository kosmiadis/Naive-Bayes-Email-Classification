#pragma once
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>

//define the spam or no-spam classification as enum
enum CLASSIFICATION {
    SPAM,
    NO_SPAM
};

//to train the model we need to define in which class it belongs from the start
typedef struct training_data {
    std::string content;
    CLASSIFICATION belong_class;
} TrainingData;

/*
    ex. { "Hello world", CLASSIFICATION::NO_SPAM }, { "Free offer!", CLASSIFICATION::SPAM } 
*/

//for this implementation of the algorithm we only need the emails content thus
//we define the PredictionData struct as input to predication
typedef struct prediction_data {
    std::string content;
} PredictionData;

class NaiveBayesModel {
    private:
        //the dataset on top of which the model will make predictions, augmented via training phase
        std::vector<TrainingData> training_dataset;
        
    public:
        NaiveBayesModel() {};

        //tokenize removes punctuation transforms to lowercase and splits words
        //the output is a vector of strings (words) so that the modal can process them with no problem
        std::vector<std::string> tokenize (std::string content) {
            //remove all the punctuation from the content using regex
            std::regex punctuation_regex("!|@|#|$|%|^|&|*|(|)|,|.|?");
            std::string str = std::regex_replace(content, punctuation_regex, "");

            //first create a string stream with the input string as argument
            std::stringstream stream(str);

            //create "words" vector for storing words
            std::vector<std::string> words;

            //add to each word to "words" vector
            std::string w;
            size_t i = 0;

            while (stream >> w) {
                //convert words to lowercase
                for (i=0; i<w.length(); i++) {
                    w[i] = std::tolower(w[i]);
                }
                words.push_back(w);
            }

            return words;
        }
};