# Ashley Arellano
#This is the new refactored code to a short python script
#that reads files and get the reverse complement of a DNA strand
def check_file():
    while True:
        try:
            fname = input("Enter the file name: \n")
            with open(fname, 'r') as _:
                print("File accepted. Loading...")
                return fname
        except IOError:
            print("File not accessible. Try again.\n")


def read_file(fname):
    with open(fname, 'r') as file:
        for line in file:
            revc_line = reverse_complement(line.strip())  # Remove unnecessary whitespace
            print(revc_line)


def reverse_complement(dna_sequence):
    complement_map = str.maketrans("ATGC", "TACG")
    return dna_sequence.translate(complement_map)[::-1]  # Translate and reverse in one step


# Main Function
fname = check_file()
read_file(fname)
