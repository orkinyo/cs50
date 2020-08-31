from cs50 import *
from math import *
change = get_float("Change owed: ")
change = floor(change*100)
count = 0
while change > 0:
    if change >= 25:
        change -= 25
    elif change >= 10:
        change -= 10
    elif change >= 5:
        change -=  5
    else:
        change -= 1
    count += 1
print(f"{count}")
