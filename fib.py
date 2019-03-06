from functools import lru_cache
from matplotlib import pyplot as plt
import time


def timed(f, *args, n_iter=100):
	acc = float('inf')
	for _ in range(n_iter):
		start = time.perf_counter()
		f(*args)
		end = time.perf_counter()
		acc = min(acc, end - start)
	return acc

def compare(fc, args):
	for f in fc:
		plt.plot(args, [timed(f, arg) for arg in args], label=f.__name__)
		plt.legend()
		plt.grid(True)

def recursive_fib(n):
	assert n >= 0
	return 1 if n <= 1 else recursive_fib(n-1) + recursive_fib(n-2)

def memo(f):
	cache = {}
	def inner(n):
		if n not in cache:
			cache[n] = f(n)
		return cache[n]
	return inner

def fib(n):
	assert n >= 0
	a = 1
	b = 1
	for _ in range(n-1):
		a, b = b, a+b
	return b


old_fib = recursive_fib
recursive_fib = memo(old_fib)
print(recursive_fib(80))
recursive_fib = lru_cache(maxsize = None)(old_fib)
print(recursive_fib(80))
print(fib(80))
print(timed(fib, range(20)))
compare([fib, old_fib], range(30))


