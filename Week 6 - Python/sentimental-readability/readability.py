from cs50 import get_string
import math

text = get_string("Text: ")

wordCount = 0
letterCount = 0
sentenceCount = 0
inWord = False
for letter in text:
    if letter.upper() >= "A" and letter.upper() <= "Z":
        letterCount += 1
        inWord = True
    if letter in [" "]:
        if inWord:
            wordCount += 1
            inWord = False
    if letter in [".", "!", "?"]:
        if inWord:
            wordCount += 1
            sentenceCount += 1
            inWord = False

averageLetters = (letterCount / wordCount) * 100
averageSentences = (sentenceCount / wordCount) * 100
index = (0.0588 * averageLetters) - (0.296 * averageSentences) - 15.8


if int(index) >= 16:
    print("Grade 16+")
elif int(index) < 1:
    print("Before Grade 1")
else:
    print("Grade ", round(index))
