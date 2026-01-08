def main():
    size = getsize()
    while not size:
        size = getsize()
    printblocks(size)


def getsize():
    try:
        size = int(input("Size of blocks: "))
    except:
        return False
    else:
        if size < 1:
            return False
        if size > 8:
            return False
        return size


def printblocks(size):
    stage = 1
    while True:
        print(" " * (size - stage), end="")
        print("#" * stage)
        stage += 1
        if stage > size:
            break


main()
