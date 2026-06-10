#pragma once
#include "Error.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <map>
#include <fstream>

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

//for this implementation of the algorithm we only need the emails content thus
//we define the PredictionData struct as input to predication
struct PredictionData {
    std::string content;
};

struct Prediction {
    double probability;
    CLASSIFICATION classification;
    string message;
};


class NaiveBayesModel {
    private:
        //the dataset on top of which the model will make predictions, augmented via training phase
        std::vector<TrainingData> training_dataset;
        long spam_emails_count;
        long no_spam_emails_count;
        long dataset_size;
        
        std::map<std::string, int> spam_vocabulary;
        long spam_vocabulary_size;
        long spam_vocabulary_words_count;
        
        std::map<std::string, int> no_spam_vocabulary;
        long no_spam_vocabulary_size;
        long no_spam_vocabulary_words_count;

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
                throw Error("Something went wrong while cleaning content from punctuation and other symbols");
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
            //memoizing this->spam_vocabulary_words_count value once calculated as dataset wont change
            if (this->spam_vocabulary_words_count == -1) {
                for (auto word: spam_vocabulary) {
                    count += word.second;
                }   
                this->spam_vocabulary_words_count = count;
            }
            else {
                count = this->spam_vocabulary_words_count;
            }
            return count;
            
        }

        long getNoSpamTotalWordsCount () {  
            long count = 0;
            //memoizing this->no_spam_vocabulary_words_count value once calculated as dataset wont change
            if (this->no_spam_vocabulary_words_count == -1) {
                for (auto word: no_spam_vocabulary) {
                    count += word.second;
                }   
                this->no_spam_vocabulary_words_count = count;
            }
            else {
                count = this->no_spam_vocabulary_words_count;
            }
            return count;
        }

        //propabillity that a word belongs to spam email
        double getTokenSpamScore(const string &token) {
            int token_freq = spam_vocabulary[token];

            //apply laplace smoothing formula: (nominator + 1) / spam_words + all_unique_words
            return (double) (token_freq + 1) / (getSpamTotalWordsCount() + (spam_vocabulary.size() + no_spam_vocabulary.size()));
        }   

        //propabillity that a word belongs to no-spam email
        double getTokenNoSpamScore (const string &token) {
            int token_freq = no_spam_vocabulary[token];

            //apply laplace smoothing formula: (nominator + 1) / no_spam_words + all_unique_words
            return (double) (token_freq + 1) / (getNoSpamTotalWordsCount() + (spam_vocabulary.size() + no_spam_vocabulary.size()));
        }

    public:
        NaiveBayesModel() {
            this->spam_emails_count = 0;
            this->no_spam_emails_count = 0;
            this->dataset_size = 0;
            this->spam_vocabulary_size = 0;
            this->no_spam_vocabulary_size = 0;
            this->spam_vocabulary_words_count = -1;
            this->no_spam_vocabulary_words_count = -1;
        }

        //method to load csv file with data in order to train the model
        void load_and_fit(const std::string &csv_filename) {
            std::vector<TrainingData> training_dataset;

            ifstream datasetFileStream(csv_filename);

            std::string line;
            CLASSIFICATION classification;

            if (datasetFileStream.is_open()) {
                while(getline(datasetFileStream, line)) {
                    string content;
                    string c;

                    size_t pos = line.find_last_of(',');
                    content = line.substr(0, pos);
                        
                    c = line.substr(pos+1);

                    if (c == "NO_SPAM") {
                        classification = CLASSIFICATION::NO_SPAM;
                    }
                    else {
                        classification = CLASSIFICATION::SPAM;
                    }

                    TrainingData t_d = { content, classification};
                    training_dataset.push_back(t_d);
                }
            }
            else {
                throw Error("Training data were not loaded. Either the file could not open or it does not exist.");
            }

            datasetFileStream.close();
            this->fit(training_dataset);
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

                    //increase word frequency for spam_vocabulary
                    for (string str: tokens) {
                        spam_vocabulary[str] = spam_vocabulary[str] + 1;
                    }
                }
                //store word frequencies for no_spam_vocabulary
                else {
                    this->no_spam_emails_count +=1;

                    //increase word frequency for no_spam_vocabulary
                    for (string str: tokens) {
                        no_spam_vocabulary[str] = no_spam_vocabulary[str] + 1;
                    }
                }
            }
        }

        //make prediction
        Prediction predict (const PredictionData &toPredictData) {
            //check if there is any dataset fed into the model first
            if (this->dataset_size == 0) {
                throw Error("Empty dataset, please train the model first");
            }

            //check if content of the predictData object is empty
            if (toPredictData.content == "") {
                throw Error("Content of email cannot be empty");
            }

            //calculate P(spam) & P(no-spam)
            double spam_pos = (double) this->spam_emails_count / this->dataset_size;
            double no_spam_pos = (double) this->no_spam_emails_count / this->dataset_size;

            //initializing scores with base case as follows P(spam) | P(no_spam) but logarithmic
            double spamScore = std::log(spam_pos);
            double noSpamScore = std::log(no_spam_pos);

            //split words and for each word check spam and no-spam scoring
            std::vector<std::string> tokens = tokenize(toPredictData.content);
            for (string token : tokens) {
                spamScore += std::log(getTokenSpamScore(token));
            }

            for (string token : tokens) {
                noSpamScore += std::log(getTokenNoSpamScore(token));
            }

            //make prediction
            Prediction prediction;
            if (spamScore > noSpamScore) {
                //reverse function of log is exponential (e^x) and then normalize by diving the sum of the scores
                double spam_probability = std::exp(spamScore) / (std::exp(spamScore) + std::exp(noSpamScore));
                
                prediction = { spam_probability, CLASSIFICATION::SPAM, "This email is most likely a spam" };
            }
            else {
                //reverse function of log is exponential (e^x) and then normalize by diving the sum of the scores
                double no_spam_probability = std::exp(noSpamScore) / (std::exp(spamScore) + std::exp(noSpamScore));
                prediction = { no_spam_probability, CLASSIFICATION::NO_SPAM, "This email is most likely not a spam" };
            }
            return prediction;
        }
};

ostream &operator<<(ostream &stream, Prediction &prediction) {
    stream << prediction.message << " with a propabillity of: " << prediction.probability << endl;
    return stream;
}