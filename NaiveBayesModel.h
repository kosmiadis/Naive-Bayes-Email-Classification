#pragma once
#include "Error.h"
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
struct TrainingData {
    std::string content;
    CLASSIFICATION belong_class;
};

/*
    ex. { "Hello world", CLASSIFICATION::NO_SPAM }, { "Free offer!", CLASSIFICATION::SPAM } 
*/

//for this implementation of the algorithm we only need the emails content thus
//we define the PredictionData struct as input to predication
struct PredicationData {
    std::string content;
};

class NaiveBayesModel {
    private:
        //the dataset on top of which the model will make predictions, augmented via training phase
        std::vector<TrainingData> training_dataset;
        
    public:
        NaiveBayesModel() = default;

        //tokenize removes punctuation transforms to lowercase and splits words
        //the output is a vector of strings (words) so that the modal can process them with no problem
        std::vector<std::string> tokenize (std::string content) {
            //remove all the punctuation from the content using regex
            std::string str;
            bool passedRegex = true;


            try {
                std::regex punctuation_regex("[^a-zA-Z0-9\\s]");
                str = std::regex_replace(content, punctuation_regex, "");
            } catch (const std::regex_error& error) {
                passedRegex = false;
                Error err("Something went wrong while removing punctuation");
                std::cout << err << std::endl;
            }
            
            //convert str to lowercase
            std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            std::vector<std::string> words;

            if (passedRegex) {
                //first create a string stream with the input string as argument
                std::stringstream stream(str);

                //create "words" vector for storing words
                

                //add to each word to "words" vector
                std::string w;
                size_t i = 0;

                while (stream >> w) {
                    words.push_back(w);
                }
            }

            return words;
        }
};