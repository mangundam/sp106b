#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<stdlib.h>
#include<string.h> 
using namespace std;
string dexbinary(int);
string intstring(int &);
string aStonumber(string);
int charlength(char*);
string jump(string);
string dest(string);
string comp(string);
string aEng[30000]={"@R0","@R1","@R2","@R3","@R4","@R5","@R6","@R7","@R8","@R9","@R10","@R11",
					 "@R12","@R13","@R14","@R15","@SCREEN","@KBD","@SP","@LCL","@ARG","@THIS","@THAT"};
int aNum[30000]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16384,24576,0,1,2,3,4};
int tempbuffer,rowcount=0,extracount=23;
char tempcomp[50],tempdest[50],tempjump[50];

int main(){
	cout<<"start!"<<endl;
	fstream file;
	fstream file2;
	char filename[50]="";
	char filename2[50]="";
	char buffer[50];
	char buffer2[50];
	char temprow[50];
	int extraAt=16;
	int filelen;
	char tempbuffer2[50];
	cin>>filename;
	filelen = charlength(filename);
	filename[filelen]='.';
	filename[filelen+1]='a';
	filename[filelen+2]='s';
	filename[filelen+3]='m';
	for(int x=0;x<filelen;x++){
		filename2[x]=filename[x];
	}
	filename2[filelen]='.';
	filename2[filelen+1]='h';
	filename2[filelen+2]='a';
	filename2[filelen+3]='c';
	filename2[filelen+4]='k';
	file.open(filename,ios::in);
	file2.open(filename2,ios::out);
		do{
		file.getline(buffer,sizeof(buffer));
		rowcount++;
		int c=0;
		if (buffer[0]=='('){
					do{
						if(buffer[c]==')'){
							buffer[0]='@';
							buffer[c]='\0';
							aEng[extracount]=buffer;
							aNum[extracount]=rowcount;
							aEng[extracount+1]="no"; 
							break;
						}
						c++;
					}while(buffer[c-1]!=')');
					extracount++;
			}
		}while(!file.eof());
	file.close();

	file.open(filename,ios::in);
	do{
		file.getline(buffer,sizeof(buffer));
		//cout<<buffer<<endl;//逐行處理區
		if(buffer[0]=='@'){
			if(buffer[1]>47&&buffer[1]<58){
				for(int i=0;i<50;i++){
				buffer[i]=buffer[i+1];
				}
				tempbuffer=atoi(buffer);
			 	cout<<dexbinary(tempbuffer)<<endl;
			 	file2<<dexbinary(tempbuffer)<<endl;
			 }
			 else if(aStonumber(buffer)!="0"){
			 	cout<<aStonumber(buffer)<<endl;
			 	file2<<aStonumber(buffer)<<endl;
			 }
			 else if(aStonumber(buffer)=="0"){
			 	cout<<dexbinary(extraAt)<<endl;
			 	file2<<dexbinary(extraAt)<<endl;
			 	extraAt++;
			 }
		}
		else if(buffer[0]=='('){
		}
		else{
			for(int i=0;i<50;i++){
				tempcomp[i]='\0';
				tempdest[i]='\0';
				tempjump[i]='\0';
			}
		for(int i=0;i<50;i++){
			if(buffer[i]==';'){
				int k=0;
				for(int j=0;j<i;j++){
					tempcomp[j]=buffer[j];
				}
				
				for(int j=i+1;j<i+5;j++){
					tempjump[k]=buffer[j];
					k++;
				}
				file2<<"111"<<comp(tempcomp)<<"000"<<jump(tempjump)<<endl;
				cout<<"111"<<comp(tempcomp)<<"000"<<jump(tempjump)<<endl;
				break;
			}
			else if(buffer[i]=='='){
				int k=0;
				for(int j=0;j<i;j++){
					tempdest[j]=buffer[j];
				}
				for(int j=i+1;j<i+5;j++){
					tempcomp[k]=buffer[j];
					k++;
				}
				file2<<"111"<<comp(tempcomp)<<dest(tempdest)<<"000"<<endl;
				cout<<"111"<<comp(tempcomp)<<dest(tempdest)<<"000"<<endl;
				break;
			}
		}
	}
	}while(!file.eof());
	file2.close();
}

string dexbinary(int a){
	string number;
	for(int i=0;i<16;i++){
		int b = a%2;
		number+=intstring(b);
		a=a/2;
	}
	reverse(number.begin(),number.end());
	return number; 
}

string intstring(int &i){
	string s;
	stringstream ss(s);
	ss<<i;
	return ss.str();
}

string aStonumber(string a){
	int i=0;
	do{ 
		if(a==aEng[i]){
			return dexbinary(aNum[i]);
			break;
		}
		i++;
	}while(aEng[i]!="no");
	return "0";
}
string dest(string a){
	string dest[8]={"","M","D","MD","A","AM","AD","AMD"};
	string destnum[8]={"000","001","010","011","100","101","110","111"};
	for(int i=0;i<8;i++){
		if(a==dest[i]){
			return destnum[i];
		}
	}
	return "Wrong";
}
string comp(string a){
	string comp[28]={"0","1","-1","D","A",
					 "!D","!A","-D","-A","D+1",
					 "A+1","D-1","A-1","D+A","D-A",
					 "A-D","D&A","D|A","M","!M",
					 "-M","M+1","M-1","D+M","D-M",
					 "M-D","D&M","D|M"};
	string compnum[28]={"0101010","0111111","0111010","0001100","0110000",
						"0001101","0110001","0001111","0110011","0011111",
						"0110111","0001110","0110010","0000010","0010011",
						"0000111","0000000","0010101","1110000","1110001",
						"1110011","1110111","1110010","1000010","1010011",
						"1000111","1000000","1010101"};
	for(int i=0;i<28;i++){
		if(a==comp[i]){
			return compnum[i];
		}
	}
	return "Wrong";
}
string jump(string a){
	string jump[8]={"","JGT","JEQ","JGE","JLT","JNE","JLE","JMP"};
	string jumpnum[8]={"000","001","010","011","100","101","110","111"};
	for(int i=0;i<8;i++){
		if(a==jump[i]){
			return jumpnum[i];
		}
	}
	return "Wrong";
	
}

int charlength(char* a){
	int i=0;
	do{
		i++;
	}while(a[i]!='\0');
	return i;
}
