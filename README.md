## Probabilistic inference

**Name and CSM ID of the student**

	Name: Deepak Rajasekhar Karishetti
	CWID: 


**What programming language is being used**

	-Programming language used: C++
	-Operating system: Linux - Ubuntu 16.04 LTS


**How the code is structured**

	-The program takes the observation argument if provided and parses it to obtain number of Ls and Cs. It then stores the values for what it knows about the world as defined in the problem.

	-It then calculates the probability of each bag given the observation Q using Baye's theorem.
	
	-Prediction for the probability of drawing C or L is calculated using the full joint distribution equation and stored in the file 'result.txt'.

**How to run the code**

-For running on Windows:

	-Open a terminal at the file path and type the following command.

	$ g++ -o compute_a_posteriori main.cpp

		-Executable is called compute_a_posteriori here.
		-There is only one arg to program or zero if no observation made.
		-Argument is a continuous string of chars of only Cs and Ls

	Example:
	
		$ ./compute_a_posteriori CLLCCLLLCCL

	
	-A result file is attached along.
