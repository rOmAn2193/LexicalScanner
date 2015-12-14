//
//  main.cpp
//  Final Project
//
//  Created by Roman Puzey on 5/11/13.
//  Copyright (c) 2013 Roman Puzey. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


const int maxp=100;
const int maxt=30;

enum statetype{newtoken, reswrd, variable, integer, real, delimiter, laststate};
enum chartype{letter, digit, period, delimit, blank, pod, eoln, illegal, lastchar};


statetype stringtostate(string s)
{	
	statetype answer;
	if (s == "newtoken")
		answer = newtoken;
	else if (s == "reswrd")
		answer = reswrd;
	else if (s == "variable")
		answer = variable;
	else if (s == "integer")
		answer = integer;
	else if (s == "real")
		answer = real;
	else if (s == "delimiter")
		answer=delimiter;
	else 
		answer=laststate;
	return answer;
}

string statetostring(statetype f)
{	
	string answer;
	if (f == newtoken)
		answer = "newtoken";
	else if (f == reswrd)
		answer = "reswrd";
	else if (f == variable)
		answer = "variable";
	else if (f == integer)
		answer = "integer";
	else if (f == real)
		answer = "real";
	else if (f == delimiter)
		answer = "delimiter";
	else 
		answer="Invalid";
	return answer;
}

chartype stringtochar(string f)
{	
	chartype answer;
	if(f == "letter")
		answer=letter;
	else if(f == "digit")
		answer=digit;
	else if(f == "period")
		answer=period;
	else if(f == "delimit")
		answer=delimit;
	else if(f == "blank")
		answer=blank;
	else if(f == "pod")
		answer=pod;
	else if(f == "eoln")
		answer=eoln;
	else if(f == "illegal")
		answer=illegal;
	else 
		answer= lastchar;
	return answer;
}

string chartostring(int a)
{	
	string answer;
	if(a==letter)
		answer="letter";
	else if(a==digit)
		answer="digit";
	else if(a==period)
		answer="period";
	else if(a==delimit)
		answer="delimit";
	else if(a==blank)
		answer="blank";
	else if(a==pod)
		answer="pod";
	else if(a==eoln)
		answer="eoln";
	else if(a==illegal)
		answer="illegal";
	else 
		answer= "Illegal";
	return answer;
}

void readresve(string reserve[maxt], int &num)
{	
	int i=0;
	ifstream res("reserve.dat");
	for(i=0;i<maxt;i++)
	{	
		res >> reserve[i];
		i++;
	}
	num=i;
}

void readstate(statetype state[laststate][lastchar])
{	
	ifstream inf("state.dat");
	int i,j;
	string t;
	for(i=newtoken;i<laststate;i++)
		for(j=letter;j<lastchar;j++)
		{	
			inf >> t;
			state[i][j] = stringtostate(t);
		}	
}

void readaction(int action[laststate][lastchar])
{	
	ifstream act("action.dat");
	int i,j;
	for(i=newtoken;i<laststate;i++)
			for(j=letter;j<lastchar;j++)
				act>>action[i][j];
}

void readexpl(string explain[maxp], int &num)
{	
	ifstream exp("explain.dat");
	string line;
	int i=0;
	while(!exp.eof())
	{	
		getline(exp,explain[i],'|');
		i++;
	}
	num=i;
}

void printresve(string reserve[maxt],int num,ofstream &outf)
{
	int i;
	outf << "Reserved Words" << endl;
	for(i=0; i<maxt-1; i++)
		outf << reserve[i] << " ";
		outf << endl << endl;
}

void printstate(statetype state[laststate][lastchar],ofstream &outf)
{
    int i,j;
	outf << "State Table: " << endl;
	for(i=0;i<111;i++)
		outf << '*';
		outf << endl;
		outf << setw(5) << " ";
	for(j=letter;j<lastchar;j++)
		outf << right << setw(13) << chartostring(chartype(j));
		outf << endl;
	for(i=0;i<111;i++)
		outf << '-';
		outf << endl;
	for(i=newtoken;i<laststate;i++)
	{	
		outf << left << setw(10) << statetostring(statetype(i));
		outf << left << setw(2) << " ";
		for(j=letter;j<lastchar;j++)
			outf << left << setw(13) << statetostring(state[i][j]);
		    outf << endl;
	}
	for(i=0;i<111;i++)
		outf << '*';
		outf << endl << endl << endl;
}

void printaction(int action[laststate][lastchar],ofstream &outf)
{	
	int i,j;
	outf << "Action Table: " << endl;
	for(i=0;i<86;i++)
		outf << '*';
		outf << endl;
		outf << setw(6) << " ";

	for(j=letter;j<lastchar;j++)
		outf << right << setw(10) << chartostring(chartype(j));
		outf << endl;

	for(i=newtoken;i<laststate;i++)
	{	
		outf << left << setw(10) << statetostring(statetype(i));
		outf << left << setw(3) << " ";
		for(j=letter;j<lastchar;j++)
			outf << left << setw(10) << action[i][j];
			outf << endl;
	}
	for(i=0;i<86;i++)
		outf << '*';
		outf << endl << endl << endl;
}

void printexpl(string explain[maxp],ofstream &outf)
{
	int i;
	outf << "Explanations of Action Table Entries: " << endl;
	for(i=0;i<92;i++)
		outf << '*';
		outf << endl;
	for(i=0; i<maxp;i++)
		outf << explain[i];
		outf << endl << endl;
}

chartype getchar(char ch)
{
	chartype answer;
	if(ch>='a' && ch<='z')
		answer=letter;
	else if(ch>='0' && ch<='9')
		answer=digit;
	else if(ch==' ')
		answer=blank;
	else if(ch=='.')
		answer=period;
	else if(ch=='|')
		answer=eoln;
	else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='"'||ch=='^'||ch=='='||ch=='<'||ch=='>'|| ch=='('||ch==')'||ch=='&'||ch==',')
		answer=delimit;
	else if(ch=='%' || ch=='$')
		answer=pod;
	else	
		answer=illegal;
	return answer;
}

void doaction(string &token, statetype &s, chartype  ct, statetype state[laststate][lastchar], string reserve[maxt], int num, int todoaction, char ch, ofstream &outf)
{
	int i;
	switch(todoaction)
	{
	case 1:
		token+=ch;
		break;
	case 2:
		s=variable;
		for(i=0;i<num;i++)
		{
			if(reserve[i]==token)s=reswrd;
		}
		outf << setw(10) << token;
		outf << setw(10) << statetostring(s) << endl;
		token="";
		break;
	case 3:
		outf << setw(10) << token;
		outf << setw(10) << statetostring(s) << endl;
		token="";
		break;
	case 4:
		outf << setw(10) << token;
		outf << setw(10) << ch << " Incorrect usage " << endl;
		token="";
		break;
	case 5:
		outf << ch << " Incorrect usage" << endl;
		break;
	case 6:
		break;
	case 7:
		outf << ch << " Illegal Symbol " << endl;
		break;
	case 8:
		s=variable;
		for(i=0;i<num;i++)
		{
			if(reserve[i]==token)s=reswrd;
		}
		outf << setw(10) << token;
		outf << setw(10) << statetostring(s) << endl;
		token="";
		token+=ch;
		break;
	case 9:
		outf << setw(10) << token;
		outf << setw(10) << statetostring(s) << endl;
		token="";
		token+=ch;
		break;
	case 10:
		token+=ch;
		s=variable;
		outf << setw(10) << token;
		outf << setw(10) << statetostring(s) << endl;
		token="";
		break;
	case 11:
		s=variable;
		for(i=0;i<num;i++)
		{
			if(reserve[i]==token)s=reswrd;
		}
		outf << token;
		outf << ch << " Illegal Symbol" << endl;
		break;
	case 12:
		token+=ch;
		outf << setw(10) << token;
		outf << setw(10) << statetostring(s) << endl;
		token="";
		break;
	case 13:
		outf << setw(10) << token;
		outf << ch <<" Illegal Symbol" << endl;
		token="";
		break;
	}
}

void scan(int action[laststate][lastchar], statetype state[laststate][lastchar], string reserve[maxt],int num,ofstream &outf)
{
	string line,token;
	chartype cct;
	statetype fsm;
	char ch;
	int len,i,actiontodo;
	ifstream inf("prog1.bas");
	outf << "Scanner: "<< endl << endl;
	outf << setw(10) << "Token" << "Token Type" << endl;
	for(i=0;i<30;i++)
		outf << '-';
		outf << endl;

	while(!inf.eof())
	{
		getline(inf,line);
		token="";
		line+='|';
		len=line.length();
		fsm=newtoken;
		for(i=0;i<len;i++)
		{
			ch=line[i];
			cct=getchar(ch);
			actiontodo=action[fsm][cct];
			doaction(token,fsm,cct,state,reserve,num,actiontodo,ch,outf);
			fsm=state[fsm][cct];
		
		}
	}
}

void main()
{	
	ofstream outf("scanner.out");
	int num,action[laststate][lastchar];
	string explain[maxp], reserve[maxt];
	statetype state[laststate][lastchar];
	readaction(action);
	readexpl(explain,num);
	readresve(reserve,num);
	readstate(state);
	printresve(reserve,num,outf);
	printstate(state,outf);
	printaction(action,outf);
	printexpl(explain,outf);
	scan(action,state,reserve,num,outf);
}
