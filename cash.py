from cs50 import *

change = get_float("Change owed: ")
s = [0.25,0.1,0.05,0.01]
count = 0

while change >= 0 :

    if change >= s[0] :
        change -= s[0]

    elif change >= s[1]:
        change -= s[1]

    elif change >= s[2]:
        change -= s[2]
    else:
        change -= s[3]
    count += 1

print(f"{count}")
