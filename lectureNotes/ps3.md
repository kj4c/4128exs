# TODO
- look at tree DP, exponentail DP, DP with data structures
- look at all the examples

# TIPS
- colouring trees shows how to design a good state
- wi-fi: dp with a data structure, 
- time complexity: num of states * time for each state

### Basketball exercise
three possible states
important that we can only look backwards.
so given i take the brother here, i cannot take the brother on the same row behind
which means i can take the brother on the other row one behind
BUT i can also take the brother on the other row two behind.
thats it find the maximum at the very end.

### Kefa and Dishes
BITSET TIMEEEE
you know to use bitset when n is very samll like 18.
Bitset is used to bruteforce and find every single possibility

Given kefa has n dishes, eating m, but theres a set of rules to increase the satisfaction.

some tips, to try every single bitset we do

```cpp
for (int mask = 1; mask < (1 << n); mask++) {
}
```

This is because 1 << n  means the maximum number which is 2^n

Then to check how many 1's there are we do 
```cpp
__builtin__popcount(mask)
```

Then using & and |'s we can check the existance of something in the set and also change the value to be 1 instead of 0.
So for this we just loop every mark, check the last dish eaten with the next dish eaten given that you have
not eaten that  dish, then find the score by doing a 2d array of rules.
This will test every combo of eating one before the other n then just do a maximum to find out.

### Coloring Trees
Notice that there are a lot of states
need to know what the last colour was, what the beauty was
what the current colour is,

so we iterate every index, trying different combo of colours
trying a prev color and a then seeing the current colour at this tree.

if it's already coloured then see if the beauty will increase, when matching the same colour
then set the new colour to be the minimum of the already existing score and the score of the previous color ( the new ting to add )

if not already coloured you try it with every colour, updating the beauty for each and the paint cost.

lastly output would be the minimum cost given beauty is k, try every single colour.
if they remain infinity then not possible 

### WiFI Cover
WiFi, this is a segment cover exercise with range trees
querying should be minimum.

so each room, numbered 1 to n
make segements, where you minus k and plus k, with bounds.
c being the cost of placing the boy there

then initialise all points to be infinity.

we try directly connecting the segmenets so dp[i] = dp[i-1]  + (i + 1)
thats the base cost rn.

However then we find any segments that cover this that end at [i].
as we wanna find the minimum segment that will be covering i,

```cpp
ll prevcost = seg.first == 0 ? 0 : query(seg.first - 1, i);
```

this basically covers from s - 1 up to i. find the minimum of this with the current dp[i]

update the range tree after for that value i.

### Keyboard Purchase
oh boy
so find best keyboard that will give u the min slowness.

given m is 20 we know to use bitset.

First count the frequencies of all the letters.
So given the string we wanna type, we do the frequency that these letters are adjacent to each other.

Then we use dp to find the minimum slowness given that our keyboard has the letter already placed
where the position in the bitset is which letter has been placed.

then have an array so this array will tell us how many bits are already in the given mask,
so when you wanna add a new letter to this mask it will automatically be placed at the end
by calculating the size of the previous mask. this will tell you the distance between this letter n all other letters
in the keyboard.

then we precompute the frequency given a letter for all possible mask.
So just saying ok we have mask1 and the new letter is 'z', we already precomputed the amount for 'z' to all other letters in the keyboard

then now we do the actual dp, given the mask check if the letter is already in the mask, if it is then skip,
if not we add it, then  find out the current position for the new letter,
then do the formula. multiply the new position by the amount of frequencies 
the minus part is saying for all letters already in the mask minus all letters not in the mask.
cus the d[msk][x] just counts for all frequencies in the password given the letter x resides in the msk.
so by doing d[subsets - 1 - nmsk] this will count for all the frequencies not including the letters in nmsk.
Just avoids double counting.

```cpp
dp[nmsk] = min(dp[nmsk], dp[msk] + pos * (d[msk][x] - d[subsets - 1 - nmsk][x]));
```

lastly just output the final answer being dp[subsets - 1].

### Exponential DP


### Tree DP

