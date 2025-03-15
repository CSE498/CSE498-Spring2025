#pragma once

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace cse {

  class Distribution {
  private:
    std::vector<double> probs;           // Holds the probabilities of the distribution
    std::vector<double> cumulativeProbs; // Holds the cumulative probabilities of the distribution
    const double noChance = 0.0;         // A value for when the probability is none or "0"
    const double maxProb = 1.0;          // The maximum probability
    const int minTrials = 1;             // The minimum number of trials you can build
    const int minTrialsCheck = 0;        // The minimum number of trials to check if successful

  public:
    void BuildBinomial(const int, const double);
    void BuildUniform(const int);
    void BuildNormal(const int);
    void BuildPoisson(const int);
    void BuildPowerLaw(const int);
    double GetProb(const int);
    double GetCumulativeProb(const int);
    double ProbCalculator(const std::vector<double>, const int trials);
  };

  // Fills the probs and cumulativeProbs vectors with binomial probabilities
  void Distribution::BuildBinomial(const int trials, const double prob) {
    if (trials < minTrials) {
      throw std::runtime_error("Must have at least 1 datapoint"); // Use the cse::assert in future
    }
    if (prob > maxProb || prob < noChance) {
      throw std::out_of_range("Probability not expessed as a decimal."); // Use the cse::assert in future
    }

    cumulativeProbs.resize(trials);
    probs.resize(trials);

    for (int i = 0; i < trials; i++) {
      // The formula for binomial probability and populate the probabilities into probs
      probs[i] = std::tgamma(trials + 1.0) / (std::tgamma(i + 1.0) * std::tgamma(trials - i + 1.0)) *
                 std::pow(prob, i) * std::pow((1.0 - prob), trials - i);

      // Populate the cumulative probabilites
      if (i > 0) {
        cumulativeProbs[i] = cumulativeProbs[i - 1] + probs[i];
      } else if (i == 0) {
        cumulativeProbs[i] = probs[i];
      }
    }
  }

  // Fills the probs and cumulativeProbs vectors with uniform probabilities
  void Distribution::BuildUniform(const int trials) {
    if (trials < minTrials) {
      throw std::runtime_error("Must have at least 1 datapoint"); // Use the cse::assert in future
    }

    // The formula for uniform probabilities
    double odds = 1.0 / trials;

    // Populate the probabilites
    probs.assign(trials, odds);

    // Populate the cumulative probabilites
    cumulativeProbs.resize(trials);
    cumulativeProbs[0] = noChance;
    for (int i = 1; i < trials; i++) {
      cumulativeProbs[i] = cumulativeProbs[i - 1] + odds;
    }
  }

  // Future dsitribution likely to be added
  void Distribution::BuildNormal([[maybe_unused]] const int trials) {}

  void Distribution::BuildPoisson([[maybe_unused]] const int trials) {}

  void Distribution::BuildPowerLaw([[maybe_unused]] const int trials) {}

  // Getters
  double Distribution::GetProb(const int trials) {
    return ProbCalculator(probs, trials);
  }
  double Distribution::GetCumulativeProb(const int trials) {
    return ProbCalculator(cumulativeProbs, trials);
  }

  // Helper function for the getters
  double Distribution::ProbCalculator(const std::vector<double> probVector, const int trials) {
    assert(trials >= minTrialsCheck); // Use the cse::assert in future
    assert(!probVector.empty());      // Use the cse::assert in future
    if (trials >= static_cast<int>(probVector.size())) {
      return noChance;
    }
    return probVector[trials];
  }

} // namespace cse