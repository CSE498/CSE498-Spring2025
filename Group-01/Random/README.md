# Random Class

## Description
A random number generator class that provides uniform random values across different numerical types and ranges. The class is initialized with a seed value for reproducible randomness. Its main use is for convenient methods for generating random numbers in specified ranges and probability-based boolean decisions.

## Similar Classes
- std::rand and std::srand for basic random number generation
- std::uniform_real_distribution and std::uniform_int_distribution for generating uniform random numbers
- std::mt19937 and other random number engines from the <random> library

## Key Functions
- Random(unsigned int seed) - Initializes the random number generator with a specified seed
- double GetDouble(double min, double max) - Returns a uniform random double in the range [min, max]
- int GetInt(int min, int max) - Returns a uniform random integer in the range [min, max]
- bool P(double probability) - Returns true with the specified probability (0.0 to 1.0)
- void SetSeed(unsigned int seed) - Allows resetting the random seed
- template<typename T> T Get(T min, T max) - Generic version for different numeric types

## Error Conditions
- Providing max < min in any of the Get functions
- Providing probability < 0.0 or probability > 1.0 in P()
- Using invalid numeric types with the template Get function

Recoverable Errors (Exception)
- Overflow conditions when generating numbers near type limits
- Memory allocation failures (if any internal buffers are needed)

User Errors (Custom Return)
- Invalid inputs

## Expected Challenges
- Maintaining uniform distribution across the entire range
- Maintaining good random properties while allowing for reproducibility
- Maintaining edge cases around numeric limits and type conversions
- Learning about different random number generation algorithms 

## Other Class Projects
- StateGrid
- ArgManager