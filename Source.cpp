#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>


/*	
	This function cycles the digit from the digits vector indicated by digit counter (argument) through all possible positions, on each cycle it calls itself but with the next digit
	Also, the vector which stores the already used positions of the permutation is updated, that way the next recursion knows which indexes are already occupied
	If the recursion is cycling the last digit of the digits vector, once it places it on the remaining free position on the current intermediate permutation vector, it saves this last
		one on the vector which stores all possible permutations
	Once each execution of the function as cycled its digit through all possible positions, we end the function and go back to the previous execution (and the previous digit)
*/
void Permutate(std::vector<int>& digitsVector, std::vector<std::vector<int>>& permutationsVector, std::vector<int> &intermediatePermutationVector, std::vector<int> &occupiedPositions, int&digitCounter)
{

	int positionCyclingIndex{ 0 };
	while (positionCyclingIndex < digitsVector.size())
	{
		if (std::none_of(occupiedPositions.begin(), occupiedPositions.end(), [positionCyclingIndex](int position) { return position == positionCyclingIndex; }))
		{
			intermediatePermutationVector[positionCyclingIndex] = digitsVector[digitCounter];
			occupiedPositions.push_back(positionCyclingIndex);
			if (digitCounter  == digitsVector.size() -1)
			{
				permutationsVector.push_back(intermediatePermutationVector);

			}

			else
			{
				digitCounter += 1;
				Permutate(digitsVector, permutationsVector, intermediatePermutationVector, occupiedPositions, digitCounter);

			}

			occupiedPositions.pop_back();

		}

		else {}

		positionCyclingIndex++;

	}
	
	digitCounter--;

}


/*	
	Here we have the definition of the wrapper function, which will instantiate the variables shared across recursions and make the initial call to the calculation function 
*/
void CalculatePermutations( std::vector<int>& digitsVector ,std::vector<std::vector<int>>& permutationsVector ) 
{	
	std::vector<int> intermediatePermutationVector(digitsVector.size(),0);
	intermediatePermutationVector.reserve(digitsVector.size());
	std::vector<int> occupiedPositions;
	occupiedPositions.reserve(digitsVector.size());
	
	int digitCounter{0};
	Permutate(digitsVector, permutationsVector, intermediatePermutationVector, occupiedPositions, digitCounter);

}

/*
	We check if the permutations in the permutations vector configure a valid 24 hour format time, 
	if a permutation does, it is pushed into the valid hours vector
*/
void GetValidHours(std::vector<std::vector<int>>& permutationsVector, std::vector<std::vector<int>>& validHoursVector)
{
	for (auto& permutation : permutationsVector)
	{
		if ((((permutation[0] * 10 + permutation[1]) < 24) && ((permutation[2] * 10 + permutation[3]) < 60)) && (std::none_of(validHoursVector.begin(), validHoursVector.end(), [permutation](std::vector<int> validHour) { return permutation == validHour; })))
		{

			validHoursVector.push_back(permutation);

		}

	}
}


void PrintHours(std::vector< std::vector<int> >& validHoursVector)
{
	for (auto hour : validHoursVector)
	{

		for (int digit : hour)
		{

			std::cout << digit;

		}

		std::cout << "\n";
	}

	std::cout << "\n";
}


int main(int argc, char* argv[])
{
	std::vector<int> digitsVector;
	digitsVector.reserve(argc - 1);
	std::vector< std::vector<int> > permutationsVector;
	std::vector< std::vector<int> > validHoursVector; 
	
	if (argc > 1)
	{

		int i = 0;
		std::stringstream CLArgument;
		int intArgument{};
		while ((i+1) <= (argc-1))
		{
			CLArgument.clear();
			CLArgument.str(argv[i + 1]);
			
			if (!(CLArgument >> intArgument))
			{
				std::cout << "Invalid argument " << argv[i + 1] << "\n";
				return 1;

			}

			else
			{
				if ((intArgument < 10) && (intArgument > -1))
				{
					digitsVector.push_back(intArgument);

				}

				else
				{
					std::cout << "Invalid (greater than 10 or less than 0) integer argument\n";
					return 1;

				}

			}
			
			i += 1;

		}

	}
	
	else
	{
		std::cout << "No valid integer arguments\n";
		return 1;

	}
	CalculatePermutations(digitsVector,permutationsVector);
	GetValidHours(permutationsVector, validHoursVector);
	
	std::cout << "Valid hours: " << validHoursVector.size() << "\n";
	PrintHours(validHoursVector);

	return 0;
}
