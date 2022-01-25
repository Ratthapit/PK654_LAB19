#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}


void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
	
	char *f;
	for(int i = 0; i < filename.size();i++) *(f+i) = filename[i];
	*(f+filename.size()) = 0;
	
	ifstream source;
	source.open(f);
	string textline;
	
	while(getline(source,textline)){
		const char* text_to_char = textline.c_str();
		int s1,s2,s3,sum=0;
		char getname[100];
		char format[]= "%[^:]:%d,%d,%d";
	    sscanf(text_to_char,format,getname,&s1,&s2,&s3);
	    names.push_back(getname);
		
		sum=s1+s2+s3;
		scores.push_back(sum);
		
		grades.push_back(score2grade(sum));
	}
}

void getCommand(string &command,string &key){
	cout<<"Please input your command: ";
	cin>>command;
	cin.get();
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
	int count=0;
	for(int i=0;i<names.size();i++){
		if(names[i]==key){
			cout<<names<<"'s score = "<<scores<<"\n";
			cout<<names<<"'s grade = "<<grades<<"\n";
			break;
		}
		else	count++;
	}
	if(count==names.size())	cout << "Cannot found.\n";
	
	cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
	for(int i=0;i<names.size();i++){
		if(grades[i]==key){
			cout<<names<<"("<<scores<<")\n";
		}
	}
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    for(int i=0;i<names.size();i++) cout<<names[i]<<" "<<scores[i]<<" "<<grades[i]<<"\n";
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
