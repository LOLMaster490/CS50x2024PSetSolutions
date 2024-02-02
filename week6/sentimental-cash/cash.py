import cs50

while True:
    change = cs50.get_float("Input change: ")
    if change > 0:
        break
count = 0

while (change > 0):
    while (change >= 0.25):
        change -= 0.25
        change = round(change, 2)
        count += 1
    while (change >= 0.1):
        change -= 0.1
        change = round(change, 2)
        count += 1
    while (change >= 0.05):
        change -= 0.05
        change = round(change, 2)
        count += 1
    while (change > 0):
        change -= 0.01
        change = round(change, 2)
        count += 1

print(count)
