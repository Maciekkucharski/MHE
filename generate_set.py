import random
import sys

f = open(sys.argv[1], "w")
for i in range(0, int(sys.argv[2])):
    print(random.randint(int(sys.argv[3]), int(sys.argv[4])), file=f)
f.close()
