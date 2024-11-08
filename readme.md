## Compilation targets
- `make all`
- `make freecell`
- `make parkinglot`
# Freecell Problem 
## State:
- A counter which tracks highest card in play and piles of cards
## Initial State:
- A configuration of piles and a counter n at a certain number
## Goal Test:
- Check if the counter is 0
## Successor Function:
- Move a card
- Place a card on the empty pile
- Discard a card
## Heuristics: 
1. Misplaced and Blocked: Cards that aren't positioned correctly (top of the pile isn't the current counter) adds to value. Cards that are blocked by cards on top of them also add to the value
2. Weighted misplacement/ pile tricks: Counter vs top card difference is weighted, prioritizes states where difference is small. Since empty piles are needed penalizes no empty pile states that slow down the search.
# Parking Lot Problem
## State: 
- A state in the parking lot problem represents the positions of all cars in the grid.
- Each car occupies a series of contiguous grid spaces, either horizontally or vertically.
- The state keeps track of which grid positions are occupied by which car.
## Initial State:
- Position of all cars
- 1st is your car

## Goal test:
- Is your car at the desired location?

## Successor function:
- New states are generated by moving cars forward or backward
- Cars only move in the direction they're facing 
## Heuristics:
1. Manhattan Distance: Calculate the sum of the differences in horizontal and virtical. Estimates distance to goal. 
2. Blocked Cars: Counts the number of cars blocking the path. Fewer cars closer to the solve. 


