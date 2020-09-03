# TODO
import cs50
import csv
import sys

if len(sys.argv)!=2:
    print("error!")
    exit(1)
db = cs50.SQL("sqlite:///students.db")


with open(sys.argv[1],"r") as f:

    reader = csv.DictReader(f)

    for row in reader:
        name = row['name'].split()
        if len(name) == 2:
            names =[name[0],None,name[1]]
        else:
            names = [name[0],name[1],name[2]]

        birth = int(row['birth'])
        house = row['house']
        db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?) ",names[0],names[1],names[2],house,birth)