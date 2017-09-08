#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

void read_file(bool flag, bool ctr);
void select_attributes();

int main() 
{
	srand(time(NULL));
	//map <int,bool> M;
	bool flag = 0;
	bool ctr = false;
	read_file(flag,ctr);
	//read_file(flag,M);
	flag = 1;
	//map <int,bool> M1;
	ctr = true;
	read_file(flag,ctr);
	select_attributes();
	return 0;
}

void read_file(bool flag, bool ctr)
{
	ifstream fil_in;
	fstream fil_out;
	if(!flag)
	{
		fil_in.open("../aclImdb/train/labeledBow.feat");
	}
	else
	{
		fil_in.open("../aclImdb/test/labeledBow.feat");
	}
	if(!ctr)
	{
		fil_out.open("label.feat",ios::out);
	}
	else
	{
		fil_out.open("label.feat",ios::app);
	}	
	//map <int,int> M;
	int M[25000] = {0};
	int range = 12500;
	int low = 0;
	int count = 0;
	int num;
	while(count < 500)
	{
		num = low + (rand()%range);
		if(M[num] == 0)
		{
			M[num] = 1;
			count++;
		}
	}
	low = 12500;
	count = 0;
	while(count < 500)
	{
		num = low + (rand()%range);
		if(M[num] == 0)
		{
			M[num] = 1;
			count++;
		}
	}
	count = 0;
	string line;
	while(getline(fil_in,line))
	{
		if(M[count] == 1)
		{
			fil_out<<line<<endl;
		}
		count++;
	}
	if(!flag)
	{
		//fil_out<<"********* VALIDATION SET ********************"<<endl;
		low = 0;
		count = 0;
		while(count < 500)
		{
			num = low + (rand()%range);
			if(M[num] == 0)
			{
				M[num] = 2;
				count++;
			}
		}
		low = 12500;
		count = 0;
		while(count < 500)
		{
			num = low + (rand()%range);
			if(M[num] == 0)
			{
				M[num] = 2;
				count++;
			}
		}
		count = 0;
		ifstream fin;
		fin.open("../aclImdb/train/labeledBow.feat");
		while(getline(fin,line))
		{
			if(M[count] == 2)
			{
				fil_out<<line<<endl;
			}
			count++;
		}
		//fil_out<<"********* VALIDATION SET ENDS ********************"<<endl;	
	}
}

void select_attributes()
{
	ifstream fin;
	fin.open("../aclImdb/imdbEr.txt");
	vector < pair <float,int> > V;
	float x;
	fin>>x;
	int count = 0;
	while(!fin.eof())
	{
		V.push_back(make_pair(x,count));
		fin>>x;
		count++;
	}
	//sort(V.begin(), V.end());
	ofstream fout;
	fout.open("selected-features-indices.txt");
	
	
	bool A[89000];
	int range = 89000;
	/*
	for(int idx=0;idx<5000;idx++)
	{
		/*
		int num = rand()%range;
		if(A[num] == false)
		{
			fout<<num<<endl;
			A[num] = true;
			idx++;
		}
			
		fout<<V[idx].second<<endl;

	}
	*/
	
	int idx = V.size() - 1;
	count = 0;
	while(count < 2500)
	{
		fout<<V[idx].second<<endl;
		count++;
		idx--;
	}
	count = 0;
	idx = 0;
	while(count < 2500)
	{
		fout<<V[idx].second<<endl;
		count++;
		idx++;
	}
	
}