
def point_cover(dots, len_of_section = 1):
	sections = []
	while dots:
		min_dot = min(dots)
		dots.remove(min_dot)
		section = (min_dot, min_dot + len_of_section)
		sections.append(section)
		for dot in dots:
			if (dot >= section[0] and dot <= section[1]):
				dots.remove(dot)
	return sections

def fast_point_cover(dots, len_of_section=1):
	dots.sort()
	sections = []
	i = 0
	while i < len(dots):
		dot = dots[i]
		section = (dot, dot + len_of_section)
		sections.append(section)
		while i < len(dots) and dots[i] <= section[1]:
			i += 1
	return sections

def main():
	dots = list(map(float, input("Введите точки: ").split()))
	len_of_section = float(input("Введите длину единичного отрезка: "))
	sec1 = fast_point_cover(dots, len_of_section)
	sec2 = point_cover(dots.copy(), len_of_section)
	print(sec1, sec2)

if __name__ == '__main__':
	main()

