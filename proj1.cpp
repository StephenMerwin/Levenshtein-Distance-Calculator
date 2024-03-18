/*
Use the Makefile to compile using 'make' in Terminal.
Then run with ./proj1 and follow the prompts to enter your inputs.
Please limit words to 24 chars or less in length.
*/
#include "proj1.h"

int main()
{
	//declare string variables for both words
	string str1, str2;

	//Get input words
	cout << "Enter two words for the edit distance:" << endl;
	cout << "Enter word #1: ";
	cin >> str1;
	cout << "Enter word #2: ";
	cin >> str2;

	//declare 2D array to store the value matrix
	int matrix[25][25];

	//initializing matrix
	 for (size_t i = 0; i < str1.length() + 1; i++)
		matrix[i][0] = i;
	 for (size_t j = 0; j < str2.length() + 1; j++)
		matrix[0][j] = j;

	//fill out matrix with proper values
	 for (size_t i = 1; i <= str1.length(); i++){
		 for (size_t j = 1; j <= str2.length(); j++){
			if (str1[i-1] == str2[j-1])
				matrix[i][j] = matrix[i - 1][j - 1];
			else
				matrix[i][j] = 1 + min(matrix[i-1][j-1], min(matrix[i][j-1], matrix[i-1][j]));
		}
	}

	//display the matrix
	cout << "The matrix is: " <<endl;
	 for (size_t i = 0; i <= str1.length(); i++){
		 for (size_t j = 0; j <= str2.length(); j++){
			cout << matrix[i][j] << "|";
		}
		cout << endl ;
		 for (size_t k = 0; k <= str2.length(); k++)
			cout << "_|"; 
		cout << endl;
	}

	//display the edit distance
	cout << "The edit distance is: " << matrix[str1.length()][str2.length()] << endl;

	//create another matrix for arrows
	char arrow[25][25];
	int go_diag, go_up, go_left;

	//calculate the direction
	 for (size_t i = 1; i <= str1.length();i++){
		 for (size_t j = 1; j <= str2.length(); j++){
			if (i == 1){
				matrix[i][j] = j;
				arrow[i][j] = 'L'; //left
			} else if (j == 1){
				matrix[i][j] = i;
				arrow[i][j] = 'U'; //up
			}
			if (str1[i-1] == str2[j-1]){
				matrix[i][j] = matrix[i - 1][j - 1];
				arrow[i][j] = 'D'; //diag
			}else{
				go_diag = matrix[i - 1][j - 1];
				go_up = matrix[i - 1][j];
				go_left = matrix[i][j - 1]; 
				matrix[i][j] = 1 + min(go_diag, min(go_left, go_up));//choose min

				if (min(go_diag, min(go_left, go_up)) == go_diag){
					arrow[i][j] = 'D';
				}else if (min(go_diag, min(go_left, go_up)) == go_left){
					arrow[i][j] = 'L';
				}else if (min(go_diag, min(go_left, go_up)) == go_up){
					arrow[i][j] = 'U';
				}
			}
		}
	}

	//declare stack that will store trace path	
	stack<char> tracer;
	
	int length1 = str1.length();
	int length2 = str2.length();
	while (length1 > 0 && length2 > 0){
		tracer.push(arrow[length1][length2]);
		if (arrow[length1][length2] == 'D'){
			length1 --;
			length2 --;
		}
		else if (arrow[length1][length2] == 'L'){
			length2 --;
		}
		else if (arrow[length1][length2] == 'U'){
			length1 --;
		}
	}

	string align1 = " ";
	int count1 = 0;
	string align2 = " ";
	int count2 = 0;
	char chr;
	
	//display the alignment
	cout << "Alignment is:" << endl;

	while (!tracer.empty()){
		chr = tracer.top();
		tracer.pop();
		if (chr == 'U'){
			align1 += str1[count1];
			align2 += '_';
			count1 ++;
		} else if (chr == 'L'){
			align2 += str2[count2];
			align1 += '_';
			count2 ++;
		} else if (chr == 'D'){
			align1 += str1[count1];
			align2 += str2[count2];
			count1 ++;
			count2 ++;
		}
	}
	cout << align1 << endl; 
	cout << align2 << endl; 
	
return 0;
}
