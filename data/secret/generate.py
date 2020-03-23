#!/usr/bin/env python3

import random
import math

random.seed(1311)

def generate_case(filename, c, n):
    max_pop = 1000000
    f = open(filename, 'w')
    print(' '.join([str(c),str(n)]), file=f)
    spread = max_pop/(2*c)
    centers = [random.randint(2*(i)*spread, 2*i*spread + spread) for i in range(0,c)]
    cities = [(str(i), str(random.randint(max(1, centers[i%c] - spread), 
        centers[i%c] + spread))) for i in range(n)]

    random.shuffle(cities)
    for city in cities:
        print(' '.join(city), file=f)
    
generate_case("1-small.in", 5, 20)
generate_case("2-small.in", 5, 20)
generate_case("1-max.in", 100, 500)
generate_case("2-max.in", 100, 500)
