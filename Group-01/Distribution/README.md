# Distribution Class

## Description
This class will create and/or manage various distributions of values that are then used to create graphs with such distributions. Pre-calculating the distributions in order to draw the random faster. 

## Similar Classes
- std::vector
- std::rand
- std::accumulate

## Key Functions
Being able to do any distribution we would need for our graphs:  Binomial and normal with an expansion to power-law, uniform, Poisson, etc. Pre-calculating the distributions will make computation time faster. 

## Error Conditions
If data has not been initialized. If there are not enough data points for any of the said distributions. If the probability is not formatted correctly We could potentially add a checker to see if any applied distribution is within a certain range of accuracy.

## Expected Challenges
Knowing all different distributions that are required (or helpful) for our final website currently. Making sure to catch any errors associated with it. Making sure it runs smoothly and quickly even at large sets and data requirements. cd ..

## Other Class Projects
Assert will help this class be able to test edge conditions.
  