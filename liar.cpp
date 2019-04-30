#include <iostream>
#include <string>
using namespace std;

char matrix[70][70];
string answers[70];
char info[70];
int liars[70];


// set the number of liars that student i claims to be if and only if student i could possibly be a truthteller
//     if not, set the number to -1
int numLiars(int i, int numStudents){
	if(info[i] == 'L'){
		return -1;
	}else{
		for(int j=0; j < numStudents; ++j){
			bool noLies = true;
			for (int k = 0; k < numStudents; ++k){
				if(matrix[i][j] == 'T'){
					if(matrix[j][k] != matrix[i][k]){
						return -1;
					}
					noLies = false;
				}else{
					if(matrix[j][k] != matrix[i][k]){
						noLies = false;
					}
				}
			}
			if(noLies){
				return -1;
			}
		}
		int count = 0;
		for (int j = 0; j < numStudents; ++j){
			if(matrix[i][j] == 'L'){
				count++;
			}
		}
		return count;
	}
}


// predetermine some students who are obviously liars to liars status (aids in efficiency)
// if can't be sure, set number of liars according to function numLiars
// A few observations: if a student A claims B is a truthteller, their replies have to be identical.
//                          otherwise student A is a liar
//                     if a student claims to be a liar, he is definitively a liar
void findLiars(int numStudents){
	for(int i = 0; i < numStudents; ++i){
		for (int j = 0; j < numStudents; ++j){
			if(matrix[i][j] == 'T'){
				if(answers[i] != answers[j]){
					info[i] = 'L';
				}
			}else if(matrix[i][i] == 'L'){
				info[i] = 'L';
			}
		}
		liars[i] = numLiars(i, numStudents);
	}
}


// checks if all students can be liars by defintion
bool allFalse(int numStudents){
	for(int i = 0; i <numStudents; ++i){
		int count = 0;
		for (int j = 0; j < numStudents; ++j){
			if(matrix[i][j] == 'T'){
				count++;
			}
		}
		if(count == 0){
			return false;
		}
	}
	return true;
}

// checks, after the preprocessing, if there are no students who can be a truthteller
bool noTruth(int numStudents){
	bool acc = true;
	for (int i = 0; i < numStudents; ++i){
		if(liars[i] != -1){
			acc = false;
		}
	}
	return acc;
}


// find the minimum number of liars: if there is a truthteller possible, the smallest valid claimed number
//                                    otherwise, the number of students
int findMinLiars(int numStudents){
	int result = numStudents;
	for (int i = 0; i < numStudents; ++i){
		int claimedLiars = liars[i];
		if(claimedLiars != -1){
			if(claimedLiars < result){
				result = claimedLiars;
			}
		}
	}
	return result;
}


// find the maximum number of liars: if there is no truthtellers, the number of students
//                                      otherwise, the biggest number of valid claimed liars (as there has to be one truth teller)
int findMaxLiars(int numStudents){
	if(allFalse(numStudents)){
		return numStudents;
	}
	int result = 0;
	for(int i = 0; i < numStudents; ++i){
		int claimedLiars = liars[i];
		if(claimedLiars > result){
			result = claimedLiars;
		}
	}
	return result;
}

int main() {
	int numTests;
	int numStudents;
	string reply;
	int numUnknown;
	int numTruthSayer;
	int numLiar;


	// Finding the number of tests
	cin >> numTests;
	// Test loop
	for(int i = 0; i < numTests; ++i){
		// Test Case Input and Setup
		cin >> numStudents;
		cin.ignore();
		//setup: each corresponding reply is assigned to its position 
		//       all status of all student is set to ?, which symbolize unknown
		for(int j = 0; j < numStudents; ++j){
			getline(cin, reply);
			answers[j] = reply;
			info[j] = '?';
			liars[j] = -1;
			for(int k = 0; k < numStudents; ++k){
				matrix[j][k] = reply[k];
			}
		}
		findLiars(numStudents);
		cout << "Class Room#" << (i+1);
		if((!allFalse(numStudents)) && noTruth(numStudents)){
			cout << " is paradoxical" << endl;
		}else{
			cout << " contains atleast " << findMinLiars(numStudents) << " and atmost " << findMaxLiars(numStudents) << " liars" << endl;
		}
	}
	// loved this question
	return 0;
}