/*
    name: yasin küyük
    id: 150170059
*/

#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct prevData{ //inherited datas
    int vertical;
    int horizontal;
    int diagonal;
};

struct maxScores{
    int i; //i index of the max data in matrix
    int j; //j index of the max data in the matrix
    int max;
};

int findMax(prevData data){ 
    int max = data.vertical;
    if(max < data.horizontal){
        max = data.horizontal;
    }

    if(max<data.diagonal){
        max = data.diagonal;
    }

    return max;
}

void SmithWatermanAlgorithm(string first, string second){
    prevData data;

    int firstLength = first.length();
    int secondLength = second.length();
    int match = 1;
    int mismatch = -5;
    int penalty = -5;

    //matrix definition
    int** matrix = new int* [secondLength +1];
    for(int i=0; i<secondLength+1; i++){
        matrix[i] = new int[firstLength+1];
    } 

    //initilization
    for(int i=0; i<firstLength+1;i++){
        matrix[0][i] = 0;
    }

    for(int i=0; i<secondLength+1;i++){
        matrix[i][0]=0;
    }

    //matrix filling
    for(int i=1; i<secondLength+1; i++){
        for(int j=1; j<firstLength+1; j++){
            data.horizontal = matrix[i][j-1] + penalty;
            data.vertical = matrix[i-1][j] + penalty;
            if(first[j-1]==second[i-1]){
                data.diagonal = matrix[i-1][j-1] + match;
            }
            else{
                data.diagonal = matrix[i-1][j-1] + mismatch;
            }
            int x = findMax(data);
            if(x<0){
                x  = 0;
            }
            matrix[i][j]  = x;
        }
    }

    vector<maxScores> maximums; //to store all maximum score in 2 sequence
    maxScores temp;
    int max = 1;

    for(int i=0; i<secondLength+1; i++){
        for(int j=0; j<firstLength+1; j++){
            if(matrix[i][j] >= max){
                temp.i = i-1;
                temp.j = j-1;
                temp.max = matrix[i][j];
                if(matrix[i][j]>max){
                    max = matrix[i][j];
                    maximums.clear();
                }

                bool isNotInVector = true;
                for(auto iter: maximums){
                    if(second.substr(iter.i, iter.max) == second.substr(temp.i,temp.max)){
                        isNotInVector = false;
                    }
                }
            
                if(isNotInVector){
                    maximums.push_back(temp);
                }
            }
        }
    }

    //output formatting
    cout<<first<<" - "<<second<<endl;
    int flag = 0;
    if(maximums.empty()){
        cout<<"Score: 0 Sequence(s): ";
    }
    else{
        vector<string> pairedSequences; //sorted format
        for(auto iter: maximums){
            if(flag==0){
                cout<<"Score: "<<iter.max<<" Sequence(s): ";
            }
            string temporary = second.substr(iter.i + 1 - iter.max, iter.max);
            pairedSequences.push_back(temporary);
            flag++;
        }

        sort(pairedSequences.begin(), pairedSequences.end());
        for(string iter: pairedSequences){
            cout<<'"'<<iter<<'"'<<" ";
        }
    }
    cout<<endl;
}

int main(){
    string filename = "strings.txt";
    vector <string> strings; //to store strings file in vector
    ifstream file;
    file.open(filename);
    string line;

    //taking lines from file as input and pushing them into string vector
    while(!(file.eof())){
        getline(file,line,'\n');
        strings.push_back(line);
    }

    //sorting them in ascending order
    sort(strings.begin(), strings.end());
    
    time_t start, end;
    time(&start);
    for(unsigned int i=0; i<strings.size(); i++){
        for(unsigned int j=i+1; j<strings.size(); j++){
            SmithWatermanAlgorithm(strings[i], strings[j]);
        }
    }
    time(&end);
    //double time_taken = double(end - start);
    /* 
    RUNNING TIME
    cout << "Running Time" << fixed << time_taken << " sec"<<endl;
    */

    return EXIT_SUCCESS;
}