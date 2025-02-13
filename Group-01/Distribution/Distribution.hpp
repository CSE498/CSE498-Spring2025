#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>

namespace cse498 {

  class Distribution {
  private:
    std::vector<double> probs;
    std::vector<double> cumulative_probs;

  public:
    double getProb(std::int32_t);
    double getCumulativeProb(std::int32_t);
    void BuildBinomial(std::int32_t, double);
    void BuildUniform(std::int32_t);
    void BuildNormal(std::int32_t);
    void BuildPoisson(std::int32_t);
    void BuildPowerLaw(std::int32_t);
  };


void Distribution::BuildBinomial(std::int32_t trials, double prob){
    cumulative_probs.resize(trials);
    probs.resize(trials);
    if(prob > 1 || prob < 0){
        throw std::out_of_range("Probability not expessed as a decimal.");
    }
    if(trials < 1){
        throw std::runtime_error("Must have at least 1 datapoint");
    }
    for(int i = 0; i < trials; ++i){
        probs[i] = std::tgamma(trials+1)/(std::tgamma(i+1)*std::tgamma(trials-i+1))*std::pow(prob,i)*std::pow((1-prob),trials-i);
        
        if (i>0){
            cumulative_probs[i] = cumulative_probs[i-1] + probs[i];
        }
        else if (i=0){
            cumulative_probs[i] = probs[i];
        }
    }
}

void Distribution::BuildUniform(std::int32_t trials){
    if(trials < 1){
        throw std::runtime_error("Must have at least 1 datapoint");
    }
    double odds = 1.0/trials;
    probs.assign(trials, odds);
    cumulative_probs.resize(trials);
    cumulative_probs[0] = odds;
    for(int i = 1; i < trials; ++i){
        cumulative_probs[i] = cumulative_probs[i-1] + odds;
    }
}

void Distribution::BuildNormal(std::int32_t trials){
    
}

void Distribution::BuildPoisson(std::int32_t trials){
    
}

void Distribution::BuildPowerLaw(std::int32_t trials){
    
}

double Distribution::getProb(std::int32_t trials){
    if(probs.empty()){
        throw std::runtime_error("You have not built a distrubtion");
    }
    if(trials < 1){
        std::out_of_range("Must have at least 1 trial");
    }
    if(trials >= probs.size()){
        return 0.0;
    }
    return probs[trials-1];
}

double Distribution::getCumulativeProb(std::int32_t trials){
   if(cumulative_probs.empty()){
        throw std::runtime_error("You have not built a distrubtion");
    }
    if(trials < 1){
        std::out_of_range("Must have at least 1 trial");
    }
    if(trials >= cumulative_probs.size()){
        return 0.0;
    }
    return cumulative_probs[trials-1];
}

} // namespace cse498