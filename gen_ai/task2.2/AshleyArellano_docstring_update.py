def check_file():
    """
    Continuously prompts the user to enter a valid file name until an accessible file is provided.
    
    Returns:
        str: The valid file name entered by the user.
    """
    while True:
        try:
            fname = input("Enter the file name: \n")  # Prompt the user for a file name
            with open(fname, 'r') as _:  # Attempt to open the file in read mode
                print("File accepted. Loading...")
                return fname  # Return the valid file name
        except IOError:
            print("File not accessible. Try again.\n")  # Inform user of an invalid file

def read_file(fname):
    """
    Reads a file line by line, processes each line as a DNA sequence,
    and prints its reverse complement.
    
    Args:
        fname (str): The name of the file to read.
    """
    with open(fname, 'r') as file:
        for line in file:
            revc_line = reverse_complement(line.strip())  # Remove whitespace and process sequence
            print(revc_line)  # Output the reverse complement

def reverse_complement(dna_sequence):
    """
    Computes the reverse complement of a given DNA sequence.
    
    Args:
        dna_sequence (str): The DNA sequence consisting of characters A, T, G, and C.
    
    Returns:
        str: The reverse complement of the input DNA sequence.
    """
    complement_map = str.maketrans("ATGC", "TACG")  # Mapping of nucleotides to their complements
    return dna_sequence.translate(complement_map)[::-1]  # Translate the sequence and reverse it

# Main execution
fname = check_file()  # Get a valid file name from the user
read_file(fname)  # Read and process the file
