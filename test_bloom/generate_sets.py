#!/usr/bin/env python2

import gzip
import random

sizeOfA = 10 * 1000
sizeOfB = 20

# read all words
lines = [line.strip() for line in gzip.open('words.txt.gz')]

# get A lines
A = random.sample(lines, sizeOfA)

# get B from the first sieOfB element
B = A[:sizeOfB]
A = A[sizeOfB:]


AFile = open('A.h', 'w')
AFile.write('const int lenA = ' + str(sizeOfA - sizeOfB) + ';\n')
AFile.write('const char* A[' + str(sizeOfA - sizeOfB) + '] = {')
AFile.writelines(",".join('"' + x + '"\n' for x in A))
AFile.write('};\n')

BFile = open('B.h', 'w')
BFile.write('const int lenB = ' + str(sizeOfB) + ';\n')
BFile.write('const char* B[' + str(sizeOfB) + '] = {')
BFile.writelines(",".join('"' + x + '"\n' for x in B))
BFile.write('};\n')


print("A.h and B.h generated")
