# TODO
import cs50
import sys

def ff(query):
    for row in query:
        if row['middle'] == None:
            print(f"{row['first']} {row['last']}, born {row['birth']}")
        else:
            print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")

if len(sys.argv)!=2:
    print("error")
    exit(1)

house = sys.argv[1]
db = cs50.SQL("sqlite:///students.db")
query = db.execute("SELECT first, middle, last, birth from students where house = ? ORDER BY last,first;",house)
ff(query)