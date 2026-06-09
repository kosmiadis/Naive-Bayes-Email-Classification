#pragma once
#include "Error.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <map>

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
struct PredictionData {
    std::string content;
};

struct Prediction {
    double propabillity;
    CLASSIFICATION classification;
    string message;
};

class NaiveBayesModel {
    private:
        //the dataset on top of which the model will make predictions, augmented via training phase
        std::vector<TrainingData> training_dataset;
        int spam_emails_count;
        int no_spam_emails_count;
        int dataset_size;
        
        std::map<std::string, int> spam_vocabulary;
        long spam_vocabulary_size;
        
        std::map<std::string, int> no_spam_vocabulary;
        long no_spam_vocabulary_size;
    public:

        NaiveBayesModel() {
            this->spam_emails_count = 0;
            this->no_spam_emails_count = 0;
            this->dataset_size = 0;
            this->spam_vocabulary_size = 0;
            this->no_spam_vocabulary_size = 0;
        }

        //tokenize removes punctuation transforms to lowercase and splits words
        //the output is a vector of strings (words) so that the modal can process them with no problem
        std::vector<std::string> tokenize (const std::string &content) {

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

        long getSpamTotalWordsCount () {  
            long count = 0;
            for (auto word: spam_vocabulary) {
                count += word.second;
            }

            return count;
        }

        long getNoSpamTotalWordsCount () {  
            long count = 0;
            for (auto word: no_spam_vocabulary) {
                count += word.second;
            }

            return count;
        }

        //propabillity that a word belongs to spam email
        double getTokenSpamScore(const string &token) {

            int token_freq = spam_vocabulary[token];
            return (double) token_freq+1.0 / (getSpamTotalWordsCount() + (getSpamTotalWordsCount()+getNoSpamTotalWordsCount()));
        }   

        //propabillity that a word belongs to no-spam email
        double getTokenNoSpamScore (const string &token) {
            int token_freq = no_spam_vocabulary[token];
            return (double) token_freq+1.0 / (getNoSpamTotalWordsCount() + (getSpamTotalWordsCount()+getNoSpamTotalWordsCount()));
        }


        //train the model (fit data in the model)
        void fit (const std::vector<TrainingData> &dataset) {
            this->dataset_size = dataset.size();

            //count how many emails are spam and how many are not
            for (TrainingData i : dataset) {
                //extract words from content
                std::vector<string> tokens = tokenize(i.content);
                
                //store word frequencies for spam_vocabulary
                if (i.belong_class == CLASSIFICATION::SPAM) {
                    this->spam_emails_count +=1;

                    for (string str: tokens) {
                        //if word has not been counted yet do so
                        if (!spam_vocabulary[str]) {
                            spam_vocabulary.insert({ str, 0 });
                            this->spam_vocabulary_size += 1;
                        }
                        
                        spam_vocabulary[str] = spam_vocabulary[str] + 1;
                    }
                }
                
                //store word frequencies for no_spam_vocabulary
                else {

                    this->no_spam_emails_count +=1;
                    for (string str: tokens) {
                        //if word has not been counted yet do so
                        if (!no_spam_vocabulary[str]) {
                            no_spam_vocabulary.insert({ str, 0 });
                            this->no_spam_vocabulary_size += 1;
                        }
                        no_spam_vocabulary[str] = no_spam_vocabulary[str] + 1;
                    }
                }
            }
        }

        //make prediction
        Prediction predict (const PredictionData &toPredictData) {
            //calculate P(spam) & P(no-spam)
            double spam_pos = (double) this->spam_emails_count / this->dataset_size;
            double no_spam_pos = (double) this->no_spam_emails_count / this->dataset_size;

            //starting from 1 because multiplication follows and initial value cannot be 0
            double spamScore = 1;
            double noSpamScore = 1;

            std::vector<std::string> tokens = tokenize(toPredictData.content);

            for (string token : tokens) {
                spamScore *= getTokenSpamScore(token);
            }

            for (string token : tokens) {
                noSpamScore *= getTokenNoSpamScore(token);
            }

            double totalSpamScore = spamScore / (spamScore + noSpamScore);
            double totalNoSpamScore = noSpamScore / (spamScore + noSpamScore);

            // std::cout << "Total Spam Score: " << totalSpamScore << std::endl << "Total No Spam Score: " << totalNoSpamScore << std::endl;
            
            Prediction prediction = { 
                totalSpamScore > totalNoSpamScore ? totalSpamScore : totalNoSpamScore, 
                totalSpamScore > totalNoSpamScore ? CLASSIFICATION::SPAM : CLASSIFICATION::NO_SPAM, 
                totalSpamScore > totalNoSpamScore ? "This email is most likely a spam" : "This email is most likely not a spam"
            };

            return prediction;
        }
};

ostream &operator<<(ostream &stream, Prediction &prediction) {
    stream << prediction.message << " with a propabillity of: " << prediction.propabillity << endl;
    return stream;
}