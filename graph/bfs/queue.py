
class Queue:
	def __init__(self, max_size=float('Inf')):
		self.queue = []
		self.size = 0
		self.max_size = max_size

	def enqueue(self, element):
		if self.size >= self.max_size:
			raise IndexError()
		self.queue.append(element)
		self.size += 1

	def dequeue(self):
		if self.size <= 0:
			raise IndexError()
		self.size -= 1
		return self.queue.pop(0)

	def is_empty(self):
		return not self.size