# TODO


# TIPS
Classrooms:
- sweeping with a set

Ancient Berland Roads:
- doing a different order, maintaining extra data with the combination of union find

### Classrooms
so have to find how many activites you can fit given you have k classrooms and each activity
has an ending time

Greedy solution is to just sort it by the earliest ending time as you wanna
prioritise the activities that end earlier so that more rooms will be used up.

learn to use lower bound here, and a multiset.
First initially make all k rooms have an ending time of 0, this is important
so the classroom selection is not random, then make sure that there is spot for that classroom
if iterator returns begin that means that its at the start of the multiset, so nothing is possible

### Minimal string
given a string, you can extract the first character of s to put in t
and then take last character of t and append to u. get the stuff lexicographically minimal.

The thing to notice is that you can use a stack for t as you only pop the latest and a queue for s.
So you do a first precomputation of the minimum char from the back of 's'.
Then associate each index by the minimum string so
'sabcade'
would be
min is a, a, a, a, a, a, d, e.
so you wanna take everything from the queue away until you reach the min char for your index.
Then you pop from the stack of 't' as this will make it lexigoraphically minimal.
Need to make sure that when popping, the t.top() is <= min n keep on pop pop op.

### Preparing for the contest
bugs, n students to work, each student wants some passes, bugs each have a complexity, student has ability.
student can fix if the abilits is >= complexity. Fix as much as possible while also having a max S passes to give away.

To do this we wanna sort by descending order of complexities, sort students by skill.
Then we wanna binary search, for the minimum number of days it would take to solve all bugs, if false go up

To find out if they can complete it, we use a priority queue where we push each student onto it and its sorted based on the least amount of passes
BUT we only push if that student can sovle that problem keep doing until solve all bugs.

Then just keep count of passes, how mnay bugs compelted etc.
Trick was to make the student solve bulk of bugs at once sinc ewe only need to achieve the Days amount, we can make
each student solvve Days amount of bugs which cuts down a lot.

### The Problem Set
Just a range tree, adding more nodes to it, needa know the max, sum, increasing decreasing
to find increasing/decreasing

```cpp
    if (left && right) {
        if (qL < mid && qR > mid) {
            return tree[i * 2].right <= tree[i * 2 + 1].left;
        }
        return true;
    }

    tree[i].increasing = tree[i*2].increasing && tree[i*2+1].increasing &&
                        (tree[i*2].right <= tree[i*2+1].left);
    tree[i].decreasing = tree[i*2].decreasing && tree[i*2+1].decreasing &&
        (tree[i*2].right >= tree[i*2+1].left);
```
you store the left n right nodes of the thing n then return true or false.

### Ancient Berland Roads
The problem was to find the size of the most populated region after every query.
You can delete and also update stuff.

Union-Find is the play here as there, 100000 nodes and 500000 queries & edges
each query needs logn time or else itll be too slow 500000000000.

Since union-find cannot delete stufff we wanna process stuff from the back where a deletion counts as an addition.
We also wanna modify union-find to keep population as well.

So keep track of each town's population changes, so if OG 10 then 12 then 50
array is [10, 12, 50].

Then for deletions make it a connection, start with an initially empty graph (keeping edge that were not deleted).
Having the population be the most recent update, then loop back through the queries, if it has a P then you update to the second
latest population for the index, if it's a D then you connect and findthe max.

also thing to note is calculate the Sum before adding in, justdraw out n u will see.


