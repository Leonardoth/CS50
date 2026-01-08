import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) < 3:
        return print("ERROR: Wrong number of arguments!")

    dnaMap = {}
    database = []
    # TODO: Read database file into a variable
    with open(f"{sys.argv[1]}") as db:
        reader = csv.DictReader(db)
        for fieldname in reader.fieldnames:
            if fieldname != "name":
                dnaMap[fieldname] = 0
        for row in reader:
            database.append(row)

    sequence = []
    # TODO: Read DNA sequence file into a variable
    with open(f"{sys.argv[2]}") as dnaSequence:
        reader = csv.reader(dnaSequence)
        for row in reader:
            sequence = row

    # TODO: Find longest match of each STR in DNA sequence
    for subsequence in dnaMap:
        longest = longest_match(sequence[0], subsequence)
        dnaMap[subsequence] = longest

    # TODO: Check database for matching profiles
    matches = []
    for person in database:
        possible = True
        for subsequence in dnaMap:
            if dnaMap[subsequence] != int(person[subsequence]):
                possible = False
                break
        if possible:
            matches.append(person["name"])


    if len(matches):
        print(matches[0])
    else:
        print("No Match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
