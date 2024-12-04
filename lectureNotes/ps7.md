# TODO:
- look how to do operations modulo a prime
- do primality testing, prime factorisation, find divisors both for single n and for all n <= N
- binomial coefficient module a prime??
- COMBINATRONICS example with DP
- Exponentation quickly using matrices

# TIPS:
- set difference, counting problem is easier if you group the expression in a different way
- need to understand what it means to prime factorise
- rest are combinatorial DP

### Set Difference
Find the max and min of EVERY subset in given set, add up the formula
max(s) + min(s). for every subset.

So to do this we wanna sort it,
and treat each element and the max n min

so given position i, then if i is the max then its the max of 
2^i subsets (everything to the left of it)

then if i is min then its the min of
2^(n - i - 1) subsets.

so 
[1, 2, 3, 4, 5, 6]

given pos 3. it will be max of 
[1, 2, 3]
[1, 3]
[2, 3]
[3] 
so i = 2, which matches position = 2^2

it will be the min of 
[3, 4, 5, 6]
[3, 4, 6]
[3, 4]
[3, 5]
[3, 6]
[3, 5, 6]
[3, 4, 5]
[3]

which is 2^(n - i - 1) = 2^(6 - 2 - 1) = 2^3. the i is given

### Math
given integer, can sqrt or multiply by some x.

Always think about the prime sof the given number

We can always reduce the number to the bsae prime factorization

given
2^3 x 3^3 x 5^2
We can always multiply by 2^1 x 3^1 x 5^2, and then square root twice
becoming
2 x 3 x 5.

Always possible so what we need to find out is the largest exponent thats closest to the next
power of 2, so in this case 3 is the closest to 4, five would be closest to 8.
Then find log(the largest power closest to 2) to find how many square roots you have to do.

```cpp
    if (!isPowerOfTwo(largest_exponent)) {
        moves = floor(log2(largest_exponent)) + 1;
        // make it to be 
    } else {
        moves = log2(largest_exponent);
    }
```

figure out if the largest exponent is apower of two,
if not we can just cmopute it to be the floor + 1 as florring makes it the lowerbound
then + 1 means to make it the closest (NEXT) power of two,
cus if you get like 2.16 as the returned exponent, means you must make it 3
not 2 moves.

multiplication can be done in one move. then after that
squareroot is just the log of it.

### Magic Gems
You can split gems into M normal gems

How many ways to get to gems X using a variety of magic and normal

Recurrence being
to get to 
dp[n] you can get there by using dp[n - 1] ways + dp[n - m] ways
as the last gem can either be a normal or a magic gem.

so
dp[n] = dp[n - 1] + dp[n - m]
however this will take a very long time to compute so we wanna do some matrix exponentation

To do this the first row will be the variables in the recurrence
so matrix[0][0] would be n - 1;
but since n - 1 is at the 0th index, to get to the 
m spot, it would be m - 1, as its zero index based.

so matrix[0][m - 1];

i thikn i overcomplicated it, juts make the first row all ones for the vairables you lookin for.

then do the diagonal 1's for the transitions.

and make sure to modify the multiplying to always mod. check the pset


OKAYYY SO we always need a base vector, however, if there is only one base case
the base vector would have <i, i -1, i-2 .. i - k  + 1>
the i in this case is the largest i such that it's a base case.
and for freddy and magic gems the only base case was
dp[0] = 1; number of ways to use space of 0 is one.
and dp[1] is a recurrence but if i - M < 0 then it equals to 0.

So the first row of the transition matrix effectively does everything for u already??

GPT:
Multiplying by the base vector 
[1,0,0,…] is redundant, because:
The multiplication only affects the first column of 
rec^𝑛, which is already computed during exponentiation.

computing M^n already gives u the entire matrix, by doing a statevecotr
<1, 0 ,0 ...> all it does is take the entire matrix n then cut it into just the first column
so it doesn't do anything we can still find the naswer by doing M[0][0].

### Two Divisors

given a number, find two divisors such that
d1 + d2 and the number gcd is 1 so they are coprime.

Notice whenever is GCD, just look at primes.

So we notice that the d1 and d2 should be coprime
gcd(d1, d2) needs to be 1 or else its not possible when added up 

so best to work with primes (i think only prime work?)

It takes too long to try out every prime combination, but we know that if given an integer

i = abcd
then it is guaranteed that bcd cannot be divided by a and a cannot be divided by bcd.

So to find value of bcd, we can take original number and divide it by 'a', if there is an exponent just keep 
dividing.

So to find all the primes, we precompute all primes up to n!
then test every prime up to the number, if we see that one of the prime divides it, then we can find bcd
by keep on dividng

MAKE SURE TO USE INT NOT LONG LONG OR ELSE WILL FAIL.


### Bag
no clue