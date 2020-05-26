# UnificationAlgorithm
 
 Unification is the process of making tow different logical atomic expressions identical by finding a substitution.
 
 The algorithm takes two expressions and returns its substitution if it exists.
 I will give some definitions that will be needed to define the algorithm.
 
 The set of disagreements in the set of non-empty W expressions is obtained by subtracting from the W the subtexts
 that begin with the symbols in the W set when compared to the left from the previous position, 
 having the position given by the first disagreement in the comparison.
 
 W is the set of expressions
 Wk is the set of disagreements
 x is an empty substitution
 xk is the current substitution
 
 Description of the algorithm according to Chen C., Lee R. Mathematical logic and automatic proof of theorems 1983 book
 
 1. k = 0,Wk = W and xk = x
 2. If Wk is contained the same elements, stop working on the algorithm.
    xk is the common unifier for the set W. Otherwise we find the set of Dk disagreements for the set Wk
 3. If there are vk և tk elements in the Dk set that vk is variable and tk is a term that does not contain the vk variable,
    then move on to step 4. Otherwise, stop working on the algorithm. W can not be unified
 4. x(k+1) = xk{tk/vk} W(k+1) = Wk{tk/vk}
 5. k = k+1 go to 2 step
 
 
