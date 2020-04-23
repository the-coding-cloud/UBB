#include<stdio.h>


//This is a data structure used for easier representation and parsing of our initial sequence
//It contains an array of integer values + the length of the sequence
typedef struct {
	int elements[200];
	int length;
}Vector;

int is_prime(int number)
	/*
	Function that checks whether a number is prime or not.
	Input: number
	Output: the function returns 1 if the number is prime and 0 otherwise
	Precondition: number - natural number
	Postcondition: the returned value is 0 or 1
	*/
{
	if (number == 0 || number == 1)
		return 0;

	if (number == 2)
		return 1;

	for (int divisor = 2; divisor*divisor <= number; divisor = divisor + 1)
		if (number%divisor == 0)
			return 0;

	return 1;
}

void find_subsequence(Vector sequence, int *start, int *end)
	/*
	Function that computes the start and the end of the longest subsequence in which the difference between two consecutive numbers is a prme number.
	Input: sequence, *start, *end
	Output: start, end will be modified accordingly
	Precondition: 
		sequence - Vector,
		*start - the address of the memory location where we store the starting index of the requested subsequence,
		*end - the address of the memory location where we store the ending index of the requested subsequence
	Postcondition:
		start - contains the value of the starting index
		end - contains the value of the ending index
	*/
{
	int current_length = 1, maximum_length = 1, current_end = 0;
	*start = 0;

	for (int index = 0; index < sequence.length - 1; index = index + 1)
	{
		if (is_prime(sequence.elements[index + 1] - sequence.elements[index]))
		{
			current_length++;
			current_end = index + 1;
		}

		else
		{
			if (maximum_length < current_length)
			{
				maximum_length = current_length;
				*end = current_end;
			}

			current_length = 1;
			
		}
	}

	if (maximum_length < current_length)
	{
		maximum_length = current_length;
		*end = current_end;
	}

	*start = *end - maximum_length + 1;
}

void print_subsequence(Vector sequence, int start, int end)
	/*
	Function that prints a subsequence of a sequence of numbers, given its starting and ending indexes
	Input: sequence, start, end
	Output: prints the values of the subsequence, separated by a space
	Preconditions:
		sequence - Vector
		start - natural number ranging from 0 to the length of the sequence
		end - natural number ranging from 0 to the length of the sequence
	*/
{
	for (int index = start; index <= end; index = index + 1)
		printf("%d ", sequence.elements[index]);
}

int read_number()
	/*
	Function that reads from the console until a number is entered and returns it.
	Output: number
	Postcondition: number - base 10 integer
	*/
{
	char string[100];
	int number = 0;
	printf("Write a number:");
	scanf("%s", string);
	while (!sscanf(string, "%d", &number))
	{
		printf("Write a number:");
		scanf("%s", string);
	}
	return number;
}

Vector read_vector()
	/*
	Function that reads a sequence of numbers until the value 0 is encountered and returns a Vector type.
	Output: sequence
	Postcondition: sequence - Vector
	*/
{

	Vector sequence;
	sequence.length = 0;
	int number = read_number();
	while (number != 0)
	{
		sequence.elements[sequence.length] = number;
		sequence.length += 1;
		number = read_number();
	}
	return sequence;
}

int main()
{
	Vector sequence;
	int start = 0, end = 0;

 	sequence = read_vector();
	find_subsequence(sequence, &start, &end);
	print_subsequence(sequence, start, end);

	system("Pause");
	return 0;
}