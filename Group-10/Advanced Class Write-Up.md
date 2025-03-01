## ComboManager

Current Capabilities: Calculate all combinations of a container then iterate forward or backward through them


### Current Functions

Reset() - Resets back to the first combination 

GetCurrentCombo() - Gets the first possible combination when an instance is constructed then can use NextCombo and PrevCombo to step through all possible combinations.

NextCombo() - Steps to the next possible combination. Returns true if it did and false if there is no next combination.

PrevCombo() - Steps back to the last possible combination. Returns true if it did and false if there is no previous combination.

GetCurrentIndices() - Returns the indices of the current combination.

GetTotalCombinations() - Returns the number of the total amount of combinations in the container.


### Ideas

Permutations

Iterators

Selecting required elements

Skip ahead n number of combinations


### Planned Additions



* Iterators - Bidirectional and Const Iterators for ease of use (begin() and end() as well)
* Repetitions - Modify BinomialCoefficient to handle repeating elements, and constructor includes an option for permutation settings (including max number of repeated elements)
* Required Elements - Specify an element required to appear inside of the combinations
* Full Permutations Settings - (order matters), i.e. ABC and BAC are different combinations. Included in the constructor to specify desired results and handled in Binomial Coefficient

New Constructor:

ComboManager(vector&lt;items>, int comboSize, permutationsAllowed=false, repeatingAllowed=false, repeatingLimit = comboSize)


## BruteForceOptimizer

Current Capabilities: Can solve for the knapsack problem, both with weights and no weights. All items have a value


### Structs

Item(name, weight, value)


### Current Functions

SetItems(items) - assigns items to the Optimizer

SetCapacity(cap) - assigns cap to the max capacity (i.e. maximum allowed weight)

FindOptimalSolution() - User-end function to return a pair of the value + the vector of chosen items for the optimal solution

Backtrack(index, currentWeight, currentValue) - Recursive function that tests all combinations of a vector of items for the optimal solutions


### Ideas

Add ComboManager into implementation

Handle multiple problems - multiple variations of Knapsack



* Currently, items with same weight different value and different weight and different problems
* Future: items can repeat, items cannot repeat, only a specified number of repeating items, multiple-constrained knapsack (both weight and volume restriction), cannot exceed a certain value

Optimization for problem solving


### Planned Additions


* Include Constructor for non-Item vectors (vec(items), vec(weights), vec(values))
* ComboManager implemented to return different combinations to evaluate
* Optimization for determining the best combination - Pruning, bounding, etc.
* Expand Knapsack problem-solving to handle more versions - possible setting to determine which version to solve. Current plans - items can/cannot repeat, items can repeat a limited number of times. Items have a max value limit