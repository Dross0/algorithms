from queue import Queue

def bfs(graph, start):
	status = {}
	for node in graph:
		status[node] = {'visited': False, 'in_queue': False}
	q = Queue()
	q.enqueue(start)
	status[start]['in_queue'] = True
	while not q.is_empty():
		node = q.dequeue()
		status[node]['in_queue'] = False
		status[node]['visited'] = True
		print(node)
		for child in graph[node]:
			if not status[child]['visited'] and not status[child]['in_queue']:
				q.enqueue(child)
				status[child]['in_queue'] = True

def main():
	graph = {}
	n = int(input("Количество вершин: "))
	for _ in range(n):
		node = input("Вершина: ")
		graph[node] = input("Связанные вершины с " + node + ": ").split()
	start = input("Вершина для начала обхода: ")
	if start not in graph:
		print("Такой вершины нет в графе!")
	bfs(graph, start)


if __name__ == '__main__':
	main()