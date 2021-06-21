import re
import string

itemsFile = "ItemsPurchased.txt"
groceryItems = {} # Empty dictionary to contain all grocery items and count.

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def ReadItems(file):
    inFile = open(file)         # Open grocery list.
    lines = inFile.readlines()  # Read in list.
    inFile.close()              # Close the file.
    for ln in lines:                                        # Process items...
        item = ln[:-1]                                      # Get the current item, removing the end line character
        try:                                                
            groceryItems[item] = groceryItems[item] + 1     # Increment item if it exits in the dictionary.
        except KeyError as s:
            groceryItems[item] = 1                          # Add item if its not in the dictionary.

def DisplayItems():
    ReadItems(itemsFile)
    print("\nItems")
    print("-----")
    for item in sorted(groceryItems):
        print("{}: {}".format(item, groceryItems[item]))
    return 0

def GetItemCount(item):     # Returns the quantity of an item.
    ReadItems(itemsFile)    # Read in the data.
    try:
        return groceryItems[item] 
    except KeyError as s:
        print("Could not find item. Error: {}".format(s))
        return 0

def WriteFrequencyFile():
    ReadItems(itemsFile)

    dataFile = open("frequency.dat",'w')
    for item in sorted(groceryItems):
        dataFile.write("{} {}\n".format(item, groceryItems[item]))
    dataFile.close()

def DisplayHistogram():     # Displays a histogram... Would have been the easier way to do this... :[
    ReadItems(itemsFile)
    maxKeyLen = 0       # Longest Key String Length.
    for item in groceryItems:       # Get the longest key's string length...
        if len(item) > maxKeyLen:
            maxKeyLen = len(item)
    
    print("\nHistogram")
    print("---------")
    for item in sorted(groceryItems):                                                       # Process the items in grocery items.
        print("{}: {}".format( item.rjust(maxKeyLen,' '), ("*" * groceryItems[item]) ))     # Print each item with an '*' for the quantity.


#DisplayItems("ItemsPurchased.txt")
#print(groceryItems)
#DisplayHistogram()
#WriteFrequencyFile()