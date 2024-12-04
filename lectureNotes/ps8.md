# TODO:


# TIPS:
- cross product is very important, shows the CCW orientation (includes seeing if the points are collinear), area, does convex hull
- use integers and never divide
- plan the implementation first

### Constellation
find stars to form a triangle
all other stars must lie outside this triangle.

sort by x then by y, this makes it so it starts from the most extreme
and then the triangle formed, the way i did it was not good juts checking if a triangle is forming (so non-collinear check)
but you should find the triangle that gives the minimum area, meaning that it will not overlap any other points.

### Pair of Lines
given  n points, can these points be split into two separate lines encapsulating everything.

just a base case, if n is <= 4 definitely possible.

however, if it is not possible we choose 3 points.
For every line to lie on two lines, we choose to make a line from
A -> B
B -> C
C -> A

so among these are one of the lines, dont know which must brute force check

so we try every single point, does it lie on A->B? if not then push it to a vector
then that vector, every point in it MUST be on the same line then since they dont lie on the A->B

if true then yay if not
try the next lie does every point lie on B->C? etcetc

if reach the end without finding then gg

to check collinearty, we cna do a cross product and the answer be 0.
```cpp
bool isCollinear(const pt& a, const pt& b, const pt& c) {
    return ((c.y - b.y)*(b.x - a.x) == (b.y - a.y)*(c.x - b.x));
}
```