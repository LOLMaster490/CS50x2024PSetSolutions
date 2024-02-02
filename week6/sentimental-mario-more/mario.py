import cs50

while True:
    height = cs50.get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(height):
    print(f" " * (height - i - 1), end="")
    print(f"#" * (i + 1), end="")
    print(" " * 2, end="")
    print(f"#" * (i + 1), end="")
    print("")
