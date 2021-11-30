import re
import os
import sys

stats = list()
with open(sys.argv[1], 'r') as infile:
    for line in infile:
        cell = [re.search("\w+", line).group(0), float(re.search("\d+", line).group(0)), float(re.search("\d+\.\d+", line).group(0)),
                float(re.search("\d+$", line).group(0))]
        if cell:
            stats.append(cell)
av_time = list()
av_score = list()
for algorithm in stats:
    for i, value in enumerate(algorithm):
        if i == 2:
            av_time.append(value)
        if i == 3:
            av_score.append(value)
with open(sys.argv[2], 'w') as outfile:
    print(f"{stats[0][0]}, {stats[0][1]}, {sum(av_time)/len(av_time)},{sum(av_score)/len(av_score)}", file=outfile)
