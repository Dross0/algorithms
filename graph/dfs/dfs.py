from stack import Stack

def dfs(graph, visited, node):
	visited[node] = True
	print(node)
	for child in graph[node]:
		if not visited[child]:
			dfs(graph, visited, child)

def dfs_with_stack(graph, node):
	visited = {}
	in_stack = {}
	for k in graph:
		visited[k] = False
		in_stack[k] = False
	s = Stack()
	s.push(node)
	in_stack[node] = True		
	while not s.is_empty():
		graph_node = s.pop()
		in_stack[graph_node] = False
		print(graph_node)
		visited[graph_node] = True
		for child in graph[graph_node]:
			if not visited[child] and not in_stack[child]:
				s.push(child)
				in_stack[child] = True


def main():
	graph = {}
	visited = {}
	n = int(input("Количество вершин: "))
	for _ in range(n):
		graph_node = input("Вершина: ")
		graph[graph_node] = list(input('Связанные вершины с' + graph_node + ': ').split())
		visited[graph_node] = False
	start = input("Вершина для начала обхода: ")
	if start not in graph:
		print("Такой вершины нет в графе!")
	print("DFS:")
	dfs(graph, visited, start)
	print("DFS with stack:")
	dfs_with_stack(graph, start)


if __name__ == "__main__":
	main()