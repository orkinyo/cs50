from cs50 import *
from math import *

def averL(s):
    words = len(s.split(" "))
    #print(f" words = {words}")
    letters = sum(c.isalpha() for c in s)
    return letters * (100.0 / words)

def averS(s):
    count = 0

    for i in range(1,len(s)):
        if s[i-1] != '.' and s[i-1] != '?' and s[i-1] != '!' and (s[i] == '.' or s[i] == '?' or s[i] == '!' ):
            count += 1
    words = len(s.split(" "))
    return count * (100.0/words)




txt = get_string("Text: ")

L = averL(txt)
S = averS(txt)

#print(f"L = {L}, S = {S}")

grade = int(round(0.0588 * L - 0.296 * S - 15.8))

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")

