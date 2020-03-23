#!/usr/bin/python2
from sys import stdin
import sys
import re

integer = "[1-9][0-9]*"
name = "(\w+)"

line = stdin.readline()
assert re.match(integer + " " + integer + "\n", line)
c, n = [int(a) for a in line[:-1].split()]
assert 1 <= c <= 100
assert c <= n <= 500

names = set()
for i in range(n):
    line = stdin.readline()
    assert re.match(name + " " + integer + "\n", line)
    n, p = line[:-1].split()
    p = int(p)

    assert n not in names
    names.add(n)
    assert 1 <= p <= 1000000

assert stdin.readline() == ''

# All good
sys.exit(42)
