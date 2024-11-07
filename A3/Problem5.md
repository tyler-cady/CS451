# Problem 5 
Think of a solution to the Geography problem as a mapping from a word to
its position in the solved list of words.  For example, if the Geography problem
was {cat,toy,treat}, then the solution would be that cat has the value 1, toy has
the value 3, and treat has the value 2.

A. Given the above representation, suppose you were to solve Geography using 
local search. 

What would be the definition of state?  
    - State can be a list of word positions ex `[cat=1, treat=2, toy=3]`
What would be a suitable definition of neighbor?  
    - A neighboring state could be a list with the same words but a change in order ex. `[cat=1, toy=2, treat=3]`

What is a good objective function?
    - Should evaluate how close word order is to the solution. 
    - Use the number of adjacent word pairs where the last letter matches the first of the next word
    - Target: maximize that value

B. Given the above representation, suppose you were to solve Geography as a
CSP.  
What would the variables be?  
- position of words in the list 
What would the domain be?  
- set of all possible integer positions in the list 
What are the constraints?
- Each word's position is unique. 
- Any two consecutive words follow geography rules last letter matches first.