import sys

def readFile(filePath):
    with open(filePath, 'r') as file:
        return file.readlines()
    
def countLog(fileLines: str):
    users = {}
    items = {}
    for l in fileLines:
        str = l[:-1].split(" ")[2:]
        if len(str) < 2:
            continue

        if str[0] == "log" and  str[1] == "in":
            if str[4] in users:
                users[str[4]] = users[str[4]] + 1
            else:
                users[str[4]] = 1
        elif str[1] == "item":
            itemId = str[2]
            itemCnt = int(str[5])
            if itemId not in items:
                    items[itemId] = 0
            if str[0] == "add":
                items[itemId] = items[itemId] + itemCnt
            elif str[0] == "sub":
                items[itemId] = items[itemId] - itemCnt
    
    for user, cnt in users.items():
        print(user, "logged in", cnt, "times")
    for itemId, itemCnt in items.items():
        if itemCnt > 0:
            print("item", itemId, "added", itemCnt, "times")
        elif itemCnt < 0:
            print("item", itemId, "subbed", itemCnt, "times")

def main():
    countLog(readFile("/home/xl/code/DummyPlayer/build/dummyPlayer.log"))

if __name__ == "__main__":
    main()