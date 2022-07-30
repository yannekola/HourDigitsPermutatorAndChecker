#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>



void calculatePermutations(std::vector<int>& digitsVector, std::vector<std::vector<int>>& permutationsVector, std::vector<int> &intermediateVector, std::vector<int> &occupiedPositions, int&digitCounter)
{

	int i{ 0 };
	while (i < digitsVector.size())
	{
	
		if (std::none_of(occupiedPositions.begin(), occupiedPositions.end(), [i](int position) { return position == i; }))
		{

			intermediateVector[i] = digitsVector[digitCounter];
			occupiedPositions.push_back(i);
			if (digitCounter  == digitsVector.size() -1)
			{
				permutationsVector.push_back(intermediateVector);

			}

			else
			{
				digitCounter += 1;
				calculatePermutations(digitsVector, permutationsVector, intermediateVector, occupiedPositions, digitCounter);

			}

			occupiedPositions.pop_back();

		}

		else {}

		i++;

	}
	
	digitCounter--;

}


void calculatePermutationsWrapper( std::vector<int>& digitsVector ,std::vector<std::vector<int>>& permutationsVector )
{

	std::vector<int> intermediateVector(digitsVector.size(), 0);
	std::vector<int> occupiedPositions;
	intermediateVector.reserve(digitsVector.size());
	occupiedPositions.reserve(digitsVector.size());
	int digitCounter{0};
	calculatePermutations(digitsVector, permutationsVector, intermediateVector, occupiedPositions, digitCounter);

}



int main()
{
	
	std::vector<int> digitsVector{2,1,2,4};
	std::vector< std::vector<int> > permutationsVector;
	std::vector< std::vector<int> > validHoursVector;
	calculatePermutationsWrapper(digitsVector,permutationsVector);
	int validHoursCounter = 0;
	for (auto &permutation : permutationsVector)
	{
		
		if (((permutation[0] * 10 + permutation[1]) < 24) && ((permutation[2] * 10 + permutation[3]) < 60))
		{
			
			validHoursVector.push_back(permutation);
			validHoursCounter++;
		
		}
		
		else
		{

		}
	}
	
	std::cout << "Valid hours: " << validHoursCounter << "\n";
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
