from sys import *
import re
import csv

file = open(argv[1],"r")
dna = open(argv[2],"r").read()
reader = csv.reader(file)
i = 0
people = []
for row in reader:
    if i == 0:
        row.pop(0)
        seq = row
    else:
        people.append(row)
    i += 1
found = []

for i in range(len(people)):
    for j in range(1,len(people[i])):
        people[i][j] = int(people[i][j])

for i in range(len(seq)):
    pattern = re.compile(f"(?:{seq[i]})+")
    found.append(max([len(x) for x in re.findall(pattern, dna)])//len(seq[i]))


for i in people:
    if i[1:] == found:
        print(i[0])