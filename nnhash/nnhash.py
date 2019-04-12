#!/usr/bin/env python3

import random
from pprint import pprint


def main():
	bins = open("bin.txt").readlines()
	chars = set()
	[chars.add(l) for bin in bins for l in bin]
	chars = { c : i for i, c in enumerate(sorted(chars))}
	hashmap = {i : [] for i, _ in enumerate(sorted(chars))}
	vector = [1.5] * len(chars)
	vector = [0.0] * len(chars)
	vectors = []
	for bin in bins:
		v = vector.copy()
		len_bin = len(bin)
		for l in reversed(bin):
			v[chars[l]] += len_bin
			len_bin -= 1
		vectors.append(v)
	for x, i in zip(bins ,vectors):
		print(x, i)






if __name__ == '__main__':
	main()
