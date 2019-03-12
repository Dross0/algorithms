class Stack():
	def __init__(self, max_size = float("Inf")):
		self.stack = []
		self.size = 0
		self.max_size = max_size

	def push(self, element):
		if self.size >= self.max_size:
			raise IndexError()
		self.stack.append(element)
		self.size += 1

	def pop(self):
		if self.size <= 0:
			raise IndexError()
		self.size -= 1
		return self.stack.pop()

	def top(self):
		if self.size <= 0:
			raise IndexError()
		return self.stack[self.size - 1]

	def is_empty(self):
		return not self.size
