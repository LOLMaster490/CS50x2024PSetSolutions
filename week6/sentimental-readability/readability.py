import cs50

input = cs50.get_string("Text: ")


words = 1 + input.count(" ")
sentences = input.count(".") + input.count("!") + input.count("?")
letters = len([i for i in input if i.isalpha()])
complexity = (0.0588 * (letters / words * 100)) - (0.296 * (sentences / words * 100)) - 15.8

if (complexity < 1):
    print("Before Grade 1")
elif (complexity >= 1 and complexity <= 16):
    print(f"Grade {int(round(complexity, 0))}")
else:
    print("Grade 16+")
