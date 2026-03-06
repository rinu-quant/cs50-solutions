import csv
import sys


def main():

    # TODO: Check for command-line usage
    if ( len(sys.argv) != 3 ):
      exit(0)

    # TODO: Read database file into a variable

    file = open ( sys.argv[1] , "r" )
    data1 = file.readlines()
    header = [h.strip() for h in data1[0].strip().split(",")]
    content = [line.strip().split(",") for line in data1[1:]]
    record1 = []
    for row in content :
      person = {}
      for i in range(len(header)):
        key = header[i]
        value = row[i].strip()
        if key != "name" :
          value = int(value)
        person[key] = value
      record1.append(person)
    file.close()

    # TODO: Read DNA sequence file into a variable

    file = open ( sys.argv[2] , "r" )
    data2 = file.read()
    file.close()

    # TODO: Find longest match of each STR in DNA sequence

    counts = []
    patterns = header[1:]
    for pattern in patterns[:] :
      count1 = 0
      for i in range ( len(data2) ) :
        count2 = 0
        while data2.startswith(pattern,i+count2*len(pattern)) :
          count2 += 1
        count1 = max ( count1 , count2 )
      counts.append(count1)
    record2 = dict(zip(patterns,counts))

    # TODO: Check database for matching profiles

    for person1 in record1 :
      match = True
      for pattern in record2 :
        if person1[pattern] != record2[pattern] :
          match = False
          break
      if match :
       print (person1["name"])
       break
    else :
       print ("No Match")
    return

def longest_match(sequence, subsequence):
    """Returnsg length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_ggrun = 0
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
