## <span id="group-3" style="color: blue">Group 3: Hopper</span>

**Members**: Sanya Nigam, Wendy Jiang, Owen Garcia, Riley Vernon, and Alex Bodell

**Shared Interests**: Games / Art

**Notable Strengths**: Graphics, Math, User Interfaces

### Classes to Build

| Class               | Description |
| ------------------- | ----------- |
| **`FixedPoint`**    | A simple class that can handle decimal values, but with a fixed precision; likely an integer type under the hood.  You should plan to overload all of the standard mathematical operators and set up conversions to other mathematical types. Conduct speed tests to determine if this will be a faster choice than `double` for the project. |
| **`FunctionSet`**   | A container that can hold a collection of functions, all with the same signature.  All of these functions can be called simultaneously with a single set of arguments passed in. |
| **`Circle`**        | A simple geometric shape that tracks its position and radius and can identify overlaps with other Circles. |
| **`Surface`**       | An area that tracks a set of shapes, identifying all overlaps; particularly useful as the basis for a simple physics model. Make sure it can handle shapes moving and detecting overlaps as soon as they occur. For a speedup, you can either use sectors (where a circle can only overlap with circles in the same or neighboring sectors) or a [quadtree](https://en.wikipedia.org/wiki/Quadtree).  |
| **`DataTracker`**   | An object to track a series of data values over time.  It should be able to return the mean, median, min, max, or number of values collect at any point in time; other stats could also be helpful. If you want to scale up it's capabilities, you can set template flags that specify what it should track, even to the point of saving all values. |

### Application Suggestion

A **physics-based [cellular automaton](https://en.wikipedia.org/wiki/Cellular_automaton) (CA)**.  While most CAs are on a grid with each cell having a state, your project would be on a collection of moving circles, bouncing around on the screen like rubber balls (that have a state).  When two circles collide, a set of rules will determine what happens to them before they bounce apart.  For example if the balls have the states "rock", "paper", "scissors", then the winner converts the loser to their type (i.e., if rock and paper collide, the rock becomes paper.)  States can also change with time.  For example, states might be "healthy" or "infected".  If two healthy states collide there is a chance (X%) of producing an offspring.  If a healthy circle collides with an infected one, the healthy becomes infected.  After Y seconds infected circles die.

Suggested **challenges**: Web app.  Perhaps allow users to set up rules in real time.  Or even turn this into a proper game, perhaps where a player controls one of the circles and is trying to aim for a particular outcome (e.g., making the infected cells all die out so the uninfected population can fully takeover).
