import re
import string

items = {}

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def readItems(file):
    inFile = open(file)
    lines = inFile.readlines()
    inFile.close()
    for ln in lines:
        item = ln[:-1]
        try:
            items[item] = items[item] + 1
        except KeyError as s:
            items[item] = 1


readItems("ItemsPurchased.txt")
print(items)
