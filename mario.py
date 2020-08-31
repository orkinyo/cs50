
def prompt(s):
    while True:
        s = input("Height: ")
        try:
            s = int(s)
        except:
            continue
        if s >= 1 and s <= 8:
            return s

s = -1
s = prompt(s)
for i in range(s):
    for k in range(s-i):
        print("",end=" ")
    for j in range(i+1):
        print("#",end='')
    print("  ",end = "")
    for j in range(i+1):
        print("#",end='')
    print()


