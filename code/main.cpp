#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

struct Node {
	int data;
	double value;
	int maj_elem;
	Node *left, *right;
	bool isleaf;
};
Node *root = NULL;
Node *root1 = NULL;

void make_attributes(map <int,int> &M);
void make_table(map <int,int> &M, char *str);
Node* getNewNode(int x, double y);
Node* ID3(vector <int> Examples, vector <int> Attributes, double stopping_parameter);
int findBestAtt(vector <int> Examples, vector <int> Attributes, double &avg);
void inorder(Node *r);
double check_percentage(Node *r, map<int,int> &M, int flag, char *str);
int height(Node *r);
void get_freq(Node *r, vector <pair <int,int> > &freq);
int find(vector <pair <int,int> > freq, int data);

void addNoise(double percent);
int Node_count(Node *r);
int Leaf_count(Node *r);

void prune(Node *r, double &max_acc, map <int,int> &M, char *str);
void DecisionForest(vector <int> Examples, map <int,int> &M, int K, int N, char *str);
double check_percentage2(Node *Forest[], int N, map <int,int> &M, int flag, char *str);


int Attributes[5000];
int **Table = new int*[1000];


int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		cout<<"usage - "<<argv[0]<<" <filename> <Expt No>\n";
	}
	else
	{
		srand(time(NULL));
		for(int i=0;i<1000;++i)
	    {
	    	Table[i] = new int[5001];
		}
		memset(Attributes,0,sizeof(Attributes));
		map <int, int> M;
		make_attributes(M);
		int flag = 1; // flag = 1 for making table for training data
		make_table(M, argv[1]);
		vector <int> Examples;
		for(int i=0;i<1000;i++)
		{
			Examples.push_back(i);
		}
		vector <int> Att;
		for(int i=1;i<=5000;i++)
		{
			Att.push_back(i);
		}
		if(*argv[2] == '2')
		{
			vector <pair <int,int> > most_freq_att;
			
			cout<<"Constructing Decision Tree by varying stopping parameter as the probability of positive/negative values in a leaf node"<<endl<<endl;
			double stopping_parameter = 1;
			flag = 1;
			cout<<"Pure Decision Tree without any Stopping Parameter - "<<endl;
			root = ID3(Examples, Att, stopping_parameter);
			
			get_freq(root, most_freq_att);

			cout<<"Prediction Accuracy on Training Dataset = ";
			double ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			stopping_parameter = 0.9;
			flag = 1;
			cout<<endl<<"Decision Tree with Stopping Parameter Probability = 0.9 - "<<endl;
			root = ID3(Examples, Att, stopping_parameter);
			
			get_freq(root, most_freq_att);

			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			stopping_parameter = 0.8;
			flag = 1;
			cout<<endl<<"Decision Tree with Stopping Parameter Probability = 0.8 - "<<endl;
			root = ID3(Examples, Att, stopping_parameter);
			
			get_freq(root, most_freq_att);

			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			stopping_parameter = 0.7;
			flag = 1;
			cout<<endl<<"Decision Tree with Stopping Parameter Probability = 0.7 - "<<endl;
			root = ID3(Examples, Att, stopping_parameter);
			
			get_freq(root, most_freq_att);

			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			sort(most_freq_att.begin(), most_freq_att.end());
			cout<<endl<<"Most Frequently Used Attributes for splitting -"<<endl<<endl;
			for(int i=most_freq_att.size()-1;i>=0;i--)
			{
				if(most_freq_att[i].first >= 4)
					cout<<"Attribute - "<<Attributes[most_freq_att[i].second-1]<<" Frequency - "<<most_freq_att[i].first<<endl;
			}
		}
		else if(*argv[2] == '3')
		{
			cout<<"Decision Tree Performance without adding noise - "<<endl<<endl;
			double stopping_parameter = 1;
			flag = 1;
			root = ID3(Examples, Att, stopping_parameter);
			
			cout<<"Prediction Accuracy on Training Dataset = ";
			double ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			cout<<endl<<"Decision Tree Performance with 0.1% Noise - "<<endl<<endl;
			double noise = 0.1;
			addNoise(noise);
			flag = 1;
			root = ID3(Examples, Att, stopping_parameter);
			
			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			cout<<endl<<"Decision Tree Performance with 1% Noise - "<<endl<<endl;
			noise = 1;
			addNoise(noise);
			flag = 1;
			root = ID3(Examples, Att, stopping_parameter);
			
			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			cout<<endl<<"Decision Tree Performance with 5% Noise - "<<endl<<endl;
			noise = 5;
			addNoise(noise);
			flag = 1;
			root = ID3(Examples, Att, stopping_parameter);
			
			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			cout<<endl<<"Decision Tree Performance with 10% Noise - "<<endl<<endl;
			noise = 10;
			addNoise(noise);
			flag = 1;
			root = ID3(Examples, Att, stopping_parameter);
			
			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;
		}
		else if(*argv[2] == '4')
		{
			cout<<"Decision Tree Performance before Prunning - "<<endl<<endl;
			double stopping_parameter = 1;
			flag = 1;
			root = ID3(Examples, Att, stopping_parameter);
			
			cout<<"Prediction Accuracy on Training Dataset = ";
			double ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;

			double max_acc = 0;
			cout<<endl<<"Decision Tree Performance after Prunning - "<<endl<<endl;
			prune(root,max_acc,M,argv[1]);

			cout<<"Prediction Accuracy on Training Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 2;
			cout<<"Prediction Accuracy on Validation Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			flag = 3;
			cout<<"Prediction Accuracy on Test Dataset = ";
			ans = check_percentage(root,M,flag,argv[1]);
			cout<<ans<<"%"<<endl;
			
			cout<<"Height of Decision Tree = "<<height(root)<<endl;
			cout<<"Number of nodes in Decision Tree = "<<Node_count(root)<<endl;
			cout<<"Number of Terminal nodes in Decision Tree = "<<Leaf_count(root)<<endl;		
		}
		else if(*argv[2] == '5')
		{
			cout<<"Decision Forest Analysis by selecting any 500 features at random - "<<endl<<endl;
			int K = 500;
			int N = 40;
			cout<<"Number of Trees = "<<N<<endl;
			DecisionForest(Examples,M,K,N, argv[1]);
			N = 60;
			cout<<endl<<"Number of Trees = "<<N<<endl;
			DecisionForest(Examples,M,K,N, argv[1]);
			N = 80;
			cout<<endl<<"Number of Trees = "<<N<<endl;
			DecisionForest(Examples,M,K,N, argv[1]);
			N = 100;
			cout<<endl<<"Number of Trees = "<<N<<endl;
			DecisionForest(Examples,M,K,N, argv[1]);
			N = 120;
			cout<<endl<<"Number of Trees = "<<N<<endl;
			DecisionForest(Examples,M,K,N, argv[1]);
		}
	}
	return 0;
}

void make_attributes(map <int,int> &M)
{
	ifstream fil;
	fil.open("selected-features-indices.txt");
	int x;
	fil>>x;
	int idx = 0;
	while(!fil.eof())
	{
		Attributes[idx++] = x;
		if(M.find(x) == M.end())
		{
			M.insert(make_pair(x,idx));
		}
		fil>>x;
	}
}

void make_table(map <int, int> &M, char *str)
{
	ifstream fil;
	fil.open(str);
	string line;
	int row = 0;
	int col = 0;
	while(row < 1000)
	{
		getline(fil,line);
		int idx = 0;
		string s = "";
		while(line[idx] != ' ')
		{
			s += line[idx];
			idx++;
		}
		int temp;
		stringstream g(s);
		g >> temp;
		if(temp >= 7)
		{
			Table[row][0] = 1;
		}
		else
		{
			Table[row][0] = -1;
		}
		idx++;
		string t = "";
		int x,y;
		while(idx < line.length())
		{
			if(line[idx] != ' ' && line[idx] != ':')
			{
				t += line[idx];
			}
			else if(line[idx] == ':')
			{
				stringstream g(t);
    			g >> x;
    			t = "";
			}
			else if(line[idx] == ' ')
			{
				if(M[x] != 0)
				{
					col = M[x];
					stringstream g(t);
    				g >> y;
					Table[row][col] = y;		
				}	
				t = "";
			}
			idx++;
		}
		row++;	
	}
}

struct Node *getNewNode(int x, double y)
{
	Node *T = new Node;
	T->data = x;
	T->value = y;
	T->maj_elem = 0;
	T->left = NULL;
	T->right = NULL;
	T->isleaf = false;
	return T;
}

struct Node * ID3(vector <int> Examples, vector <int> Att, double stopping_parameter)
{
	double count_pos = 0;
	double count_neg = 0;
	for(int i=0;i<Examples.size();i++)
	{
		if(Table[Examples[i]][0] == 1)
		{
			count_pos++;
		}
		else
		{
			count_neg++;
		}
	}
	if(count_pos == 0 || count_neg == 0)
	{
		Node *r;
		if(count_pos == 0)
		{
			r = getNewNode(-1,0);
		}
		else
		{
			r = getNewNode(1,0);
		}
		r->isleaf = true;
		return r;
	}
	if(Att.size() == 0)
	{
		Node *r;
		if(count_pos >= count_neg)
		{
			r = getNewNode(1,0);
		}
		else
		{
			r = getNewNode(-1,0);
		}
		r->isleaf = true;
		return r;	
	}
	
	if(count_pos > stopping_parameter * Examples.size())
	{
		Node *r = getNewNode(1,0);
		r->isleaf = true;
		return r;
	}
	if(count_neg > stopping_parameter * Examples.size())
	{
		Node *r = getNewNode(-1,0);
		r->isleaf = true;
		return r;
	}
	
	double avg = 0;
	int best_att = findBestAtt(Examples, Att, avg);
	Node *r = getNewNode(best_att,avg);
	if(count_pos >= count_neg)
	{
		r->maj_elem = 1;
	}
	else
	{
		r->maj_elem = -1;
	}
	vector <int> eg1;
	vector <int> eg2;
	for(int i=0;i<Examples.size();i++)
	{
		if(Table[Examples[i]][best_att] > r->value)
		{
			eg1.push_back(Examples[i]);
		}
		else
		{
			eg2.push_back(Examples[i]);
		}
	}
	Att.erase(std::remove(Att.begin(), Att.end(), best_att), Att.end());
	if(!eg1.empty())
	{
		r->left = ID3(eg1,Att,stopping_parameter);
	}
	else
	{
		if(count_pos >= count_neg)
		{
			r->left = getNewNode(1,0);
		}
		else
		{
			r->left = getNewNode(-1,0);
		}
		r->left->isleaf = true;
	}
	if(!eg2.empty())
	{
		r->right = ID3(eg2,Att,stopping_parameter);
	}
	else
	{
		if(count_pos >= count_neg)
		{
			r->right = getNewNode(1,0);
		}
		else
		{
			r->right = getNewNode(-1,0);
		}
		r->right->isleaf = true;
	}
	return r;
}

int findBestAtt(vector <int> Examples, vector <int> Att, double &avg)
{
	double num_of_eg = Examples.size();
	double minimum = 100000;
	double best_att = Att[0];
	double count_pos = 0;
	double count_neg = 0;
	for(int j=0;j<Examples.size();j++)
	{
		if(Table[Examples[j]][0] == 1)
		{
			count_pos++;
		}
		else
		{
			count_neg++; 
		}
	}
	for(int i=0;i<Att.size();i++)
	{
		double count1 = 0, count2 = 0;
		double count_pos1 = 0, count_neg1 = 0;
		double count_pos2 = 0, count_neg2 = 0;
		double average = 0;
		for(int j=0;j<Examples.size();j++)
		{
			average += Table[Examples[j]][Att[i]];
		}
		average /= Examples.size();
		for(int j=0;j<Examples.size();j++)
		{
			if(Table[Examples[j]][Att[i]] > average)
			{
				count1++;
				if(Table[Examples[j]][0] == 1)
				{
					count_pos1++;
				}
				else
				{
					count_neg1++;
				}
			}
			else
			{
				count2++;
				if(Table[Examples[j]][0] == 1)
				{
					count_pos2++;
				}
				else
				{
					count_neg2++;
				}
			}
		}
		double p1_1 = count_pos1/count1;
		double p1_2 = count_neg1/count1;
		double X;
		if(p1_1 != 0 && p1_2 != 0)
		{
			X = (count1/num_of_eg) * -1 * (p1_1*log2(p1_1) + p1_2*log2(p1_2));
		}	
		else if(p1_1 == 0 && p1_2 != 0)
		{
			X = (count1/num_of_eg) * -1 * p1_2*log2(p1_2);
		}
		else if(p1_1 != 0 && p1_2 == 0)
		{
			X = (count1/num_of_eg) * -1 * p1_1*log2(p1_1);	
		}
		else
		{
			X = 0;
		}
		double p2_1 = count_pos2/count2;
		double p2_2 = count_neg2/count2;
		if(p2_1 != 0 && p2_2 != 0)
		{
			X += (count2/num_of_eg) * -1 * (p2_1*log2(p2_1) + p2_2*log2(p2_2));
		}	
		else if(p2_1 == 0 && p2_2 != 0)
		{
			X += (count2/num_of_eg) * -1 * p2_2*log2(p2_2);
		}
		else if(p2_1 != 0 && p2_2 == 0)
		{
			X += (count2/num_of_eg) * -1 * p2_1*log2(p2_1);	
		}
		else
		{
			X += 0;
		}
		
		if(X < minimum)
		{
			minimum = X;
			best_att = Att[i];
			avg = average;
		}
	}
	return best_att;
}

void get_freq(Node *r, vector <pair <int,int> > &freq)
{
	if(r == NULL || r->isleaf == true)
	{
		return;
	}
	get_freq(r->left, freq);
	int ans = find(freq, r->data);
	if(ans == -1)
	{
		freq.push_back(make_pair(1,r->data));
	}
	else
	{
		freq[ans].first = freq[ans].first + 1;
	}
	get_freq(r->right, freq);
}

int find(vector < pair<int,int> > freq, int data)
{
	int ans = -1;
	for(int i=0;i<freq.size();i++)
	{
		if(freq[i].second == data)
		{
			ans = i;
			break;
		}
	}
	return ans;
}

void inorder(Node *r)
{
	if(r == NULL)
	{
		return;
	}
	inorder(r->left);
	cout<<r->data<<" "<<r->value<<" "<<r->maj_elem<<endl;
	inorder(r->right);
}	

double check_percentage(Node *r, map<int,int> &M, int flag, char *str)
{
	double correct = 0;
	ifstream fil;
	fil.open(str);
	int row = 0, col = 0;
	string line;
	int count = 1;
	int low = 0;
	int high = 0;
	if(flag == 1)
	{
		low = 1;
		high = 1000;
	}
	else if(flag == 2)
	{
		low = 1001;
		high = 2000;
	}
	else
	{
		low = 2001;
		high = 3000;
	}
	while(getline(fil,line))
	{
		if(count >= low && count <= high)
		{
			int A[5001] = {0};
			int idx = 0;
			string s = "";
			while(line[idx] != ' ')
			{
				s += line[idx];
				idx++;
			}
			int temp1;
			stringstream g(s);
			g >> temp1;
			if(temp1 >= 7)
			{
				A[0] = 1;
			}
			else
			{
				A[0] = -1;
			}
			idx++;
			string t = "";
			int x,y;
			while(idx < line.length())
			{
				if(line[idx] != ' ' && line[idx] != ':')
				{
					t += line[idx];
				}
				else if(line[idx] == ':')
				{
					stringstream g(t);
	    			g >> x;
	    			t = "";
				}
				else if(line[idx] == ' ')
				{
					if(M[x] != 0)
					{
						col = M[x];
						stringstream g(t);
	    				g >> y;
						A[col] = y;		
					}	
					t = "";
				}
				idx++;
			}
			Node *temp = root;
			while(temp->isleaf == false && temp != NULL)
			{
				if(A[temp->data] > temp->value)
				{
					temp = temp->left;
				}
				else 
				{
					temp = temp->right;
				}
			}
			if(temp)
			{
				if(temp->data == A[0])
				{
					correct++;
				}
			}
			row++;
		}
		count++;
	}
	return correct/10;
}	

int height (Node *r)
{
	if(r->isleaf == true)
	{
		return 0;
	}
	else
	{
		return 1 + max(height(r->left),height(r->right));
	}
}

void addNoise(double percent)
{
	int num = percent * 10;
	int range = 1000;
	bool A[1000] = {false};
	while(num)
	{
		int x = rand()%range;
		if(A[x] == false)
		{
			// Switching Label
			if(Table[x][0] == 1)
			{
				Table[x][0] = -1;
			}
			else
			{
				Table[x][0] = 1;
			}
			A[x] = true;
			num--;
		}
	}
}

int Node_count(Node *r)
{
	if(r == NULL)
	{
		return 0;
	}
	return 1 + Node_count(r->left) + Node_count(r->right);
}

int Leaf_count(Node *r)
{
	if(r == NULL)
	{
		return 0;
	}
	if(r->isleaf == true)
	{
		return 1 + Leaf_count(r->left) + Leaf_count(r->right);
	}
	else
	{
		return Leaf_count(r->left) + Leaf_count(r->right);	
	}
}

void prune(Node *r, double &max_acc, map<int,int> &M, char *str)
{
	if(r == NULL || r->isleaf == true)
	{
		return;
	}
	prune(r->left, max_acc, M, str);
	prune(r->right, max_acc, M, str);
	Node *temp = new Node;
	temp->data = r->data;
	temp->value = r->value;
	temp->maj_elem = r->maj_elem;
	temp->left = r->left;
	temp->right = r->right;
    temp->isleaf = false;

	r->data = r->maj_elem;
	r->value = 0;
	r->maj_elem = 0;
	r->left = NULL;
	r->right = NULL;
	r->isleaf = true;
	
	double acc = check_percentage(root,M,2,str);
	if(acc > max_acc)
	{
		max_acc = acc;
	}
	else
	{
		r->data = temp->data;
		r->value = temp->value;
		r->maj_elem = temp->maj_elem;
		r->left = temp->left;
		r->right = temp->right;
	    r->isleaf = false;
	}
}

void DecisionForest(vector <int> Examples,map <int,int> &M, int K, int N, char *str)
{
	Node *Forest[N];
	bool A[5000];
	for(int i=0;i<N;i++)
	{
		vector <int> Att;
		memset(A,false,sizeof(A));
		int range = 5000;
		int count = 0;
		while(count < K)
		{
			int x = 1 + (rand()%range);
			if(A[x-1] == false)
			{
				A[x-1] = true;
				Att.push_back(x);
				count++;
			}
		}
		Forest[i] = ID3(Examples,Att,0.8);
	}
	int flag = 1;
	cout<<"Decision Forest Accuracy on Training Set = ";
	double ans = check_percentage2(Forest, N, M, flag, str);
	cout<<ans<<endl;
	flag = 2;
	cout<<"Decision Forest Accuracy on Validation Set = ";
	ans = check_percentage2(Forest, N, M, flag, str);
	cout<<ans<<endl;
	flag = 3;
	cout<<"Decision Forest Accuracy on Test Set = ";
	ans = check_percentage2(Forest, N, M, flag, str);
	cout<<ans<<endl;
}

double check_percentage2(Node *Forest[], int N, map <int,int> &M, int flag, char *str)
{
	double correct = 0;
	ifstream fil;
	fil.open(str);
	int row = 0, col = 0;
	string line;
	int count = 1;
	int low = 0; 
	int high = 0;
	if(flag == 1)
	{
		low = 1;
		high = 1000;
	}
	else if(flag == 2)
	{
		low = 1001;
		high = 2000;
	}
	else
	{
		low = 2001;
		high = 3000;
	}
	while(getline(fil,line))
	{
		if(count >= low && count <= high)
		{
			int *A; 
			A = new int[5001]; 
			memset(A,0,sizeof(A));
			int idx = 0;
			string s = "";
			while(line[idx] != ' ')
			{
				s += line[idx];
				idx++;
			}
			int temp1;
			stringstream g(s);
			g >> temp1;
			if(temp1 >= 7)
			{
				A[0] = 1;
			}
			else
			{
				A[0] = -1;
			}
			idx++;
			string t = "";
			int x,y;
			while(idx < line.length())
			{
				if(line[idx] != ' ' && line[idx] != ':')
				{
					t += line[idx];
				}
				else if(line[idx] == ':')
				{
					stringstream g(t);
	    			g >> x;
	    			t = "";
				}
				else if(line[idx] == ' ')
				{
					if(M[x] != 0)
					{
						col = M[x];
						stringstream g(t);
	    				g >> y;
						A[col] = y;		
					}	
					t = "";
				}
				idx++;
			}
			int pos_count = 0;
			int neg_count = 0;
			int label;
			for(int i=0;i<N;i++)
			{
				Node *temp = Forest[i];
				while(temp->isleaf == false && temp != NULL)
				{
					if(A[temp->data] > temp->value)
					{
						temp = temp->left;
					}
					else 
					{
						temp = temp->right;
					}
				}
				int ans = 0;
				if(temp)
					ans = temp->data;
				if(ans == 1)
				{
					pos_count++;
				}
				else
				{
					neg_count++;
				}
			}
			if(pos_count >= neg_count)
			{
				label = 1;
			}
			else
			{
				label = -1;
			}
			if(label == A[0])
			{
				correct++;
			}
		}
		count++;
	}
	return correct/10;
}

int Classify(int A[], Node *r)
{
	Node *temp = r;
	while(temp->isleaf == false)
	{
		if(A[temp->data] > temp->value)
		{
			temp = temp->left;
		}
		else 
		{
			temp = temp->right;
		}
	}
	return temp->data;
}
/*
void DecisionForest(vector <int> Examples,map <int,int> &M, int K, int N)
{
	Node *Forest[N];
	for(int i=0;i<N;i++)
	{
		Node *temp = new Node;
		Forest.push_back(temp);
		vector <int> Att;
		//generate_random_att(Att, K);
		bool A[5000] = {false};
		int range = 5000;
		int count = 0;
		while(count < K)
		{
			int x = 1 + (rand()%range);
			if(A[x] == false)
			{
				A[x] = true;
				Att.push_back(x);
				count++;
			}
		}
		//Forest[i] = ID3(Examples,Att);
	}
	/*
	for(int i=0;i<N;i++)
	{
		cout<<Forest[i]->data<<" ";
		//cout<<"Height = "<<height(Forest[i])<<endl;
	}
	
	cout<<endl;
	double ans = check_percentage2(Forest, M);
	cout<<"Decision Forest Accuracy = "<<ans<<endl;
}
*/
void generate_random_att(vector <int> &Att, int K)
{
	bool A[5000] = {false};
	int range = 5000;
	int count = 0;
	while(count < K)
	{
		int x = 1 + (rand()%range);
		if(A[x] == false)
		{
			A[x] = true;
			Att.push_back(x);
			count++;
		}
	}
}
