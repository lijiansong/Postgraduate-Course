#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
//output the result to file, a is A matrix,b is b matrix,c is c matrix, opt is the objective function value,numVars is the number of varibles
void output(vector<vector<double> > *a, vector<double> *b, vector<double> *c, double opt, int numVars)
{
	ofstream outfile;
	outfile.open("out.txt");
	if (outfile.is_open())
	{
		// output the final simplex table
		outfile << "Final Table:" << endl;
		for (int i=0; i<(*a).size(); i++)
		{
			for (int j=0; j<(*a)[0].size(); j++)
			{
				// output the A matrix
				outfile << (*a)[i][j] << " ";
			}
			// output the b matrix
			outfile << "| " << (*b)[i] << endl;
		}
		// output the c matrix
		for (int i=0; i<(*c).size(); i++)
		{
			outfile << (*c)[i] << " ";
		}
		// output the optimal value
		outfile << "| " << opt << endl;
		outfile << endl;

		outfile << "z* = " << opt << endl;

		// get x* from the matrix
		vector<double> x;
		// for each column
		for (int i=0; i<numVars; i++)
		{
			// check if x_i is basic
			bool basic = true;
			int basic_i = 0;
			for (int j=0; j<(*a).size(); j++)
			{
				// not 0 or 1, not basic
				if ((*a)[j][i] != 0 && (*a)[j][i] != 1)
				{
					basic = false;
				}
				// get the basic index
				if ((*a)[j][i] == 1)
					basic_i = j;
			}

			// basic x, get the b value
			if (basic)
			x.push_back((*b)[basic_i]);
			// nonbasic, 0
			else
			x.push_back(0.0);
		}

		// output the optimal x
		outfile << "x* = (";
		for (int i=0; i<x.size(); i++)
		{
			if (i == x.size()-1)
			outfile << x[i] << ")" << endl;
			else
			outfile << x[i] << ", ";
		}

		outfile.close();
	}
	else
	{
		cout << "Could not open output file." << endl;
	}
}
//output an unbounded solution to file, minimize is true if min,false if max
void outputUnbounded(vector<vector<double> > *a, vector<double> *b, vector<double> *c, bool minimize)
{
	ofstream outfile;
	outfile.open("out.txt");
	if (outfile.is_open())
	{
		// output the final simplex table
		outfile << "Final Tableau:" << endl;
		for (int i=0; i<(*a).size(); i++)
		{
			for (int j=0; j<(*a)[0].size(); j++)
			{
				// output the A matrix
				outfile << (*a)[i][j] << " ";
			}
			// output the b matrix
			outfile << "| " << (*b)[i] << endl;
		}
		// output the c matrix
		for (int i=0; i<(*c).size(); i++)
		{
			outfile << (*c)[i] << " ";
		}
		outfile << endl;

		// optimal is unbounded
		if (minimize)
			outfile << "z* = -infinity" << endl;
		else
			outfile << "z* = infinity" << endl;
		outfile << "This linear programming is unbounded." << endl;

		outfile.close();
	}
	else
	{
		cout << "Could not open output file." << endl;
	}
}

//outputs an infeasible solution to file
void outputInfeasible(vector<vector<double> > *a, vector<double> *b, vector<double> *c)
{
	ofstream outfile;
	outfile.open("out.txt");
	if (outfile.is_open())
	{
		// output the final simplex table
		outfile << "Final Tableau:" << endl;
		for (int i=0; i<(*a).size(); i++)
		{
			for (int j=0; j<(*a)[0].size(); j++)
			{
				// output the A matrix
				outfile << (*a)[i][j] << " ";
			}
			// output the b matrix
			outfile << "| " << (*b)[i] << endl;
		}
		// output the c matrix
		for (int i=0; i<(*c).size(); i++)
		{
			outfile << (*c)[i] << " ";
		}
		outfile << endl;
		outfile << "This linear programming is infeasible." << endl;
		outfile.close();
	}
	else
		cout << "Could not open output file." << endl;
}
//perform row operations to pivot on an element and reduce a simplex table
//opt the objective function value in the current simplex table
//row is the pivot row, col is the pivot column
void reduce(vector<vector<double> > *a, vector<double> *b, vector<double> *c, double *opt, int row, int col)
{
	// get the value needed to make the pivot element 1
	double pivdiv = 1 / (*a)[row][col];
	// reduce the pivot row with this value
	for (int i=0; i<(*a)[0].size(); i++)
	{
		(*a)[row][i] = (*a)[row][i] * pivdiv;
	}
	(*b)[row] = (*b)[row] * pivdiv;

	// for every other row
	for (int i=0; i<(*a).size(); i++)
	{
		if (i == row)
		continue;

		// get the value needed to make the pivot column element 0
		double coeff = (*a)[i][col] * (*a)[row][col];
		// reduce the row with this value
		for (int j=0; j<(*a)[0].size(); j++)
		{
			(*a)[i][j] = (*a)[i][j] - ((*a)[row][j] * coeff);
		}
		(*b)[i] = (*b)[i] - ((*b)[row] * coeff);
	}
	// get the value needed to make the c element 0 in the pivot column
	double coeff = (*c)[col] * (*a)[row][col];
	// reduce the c row with this value
	for (int i=0; i<(*c).size(); i++)
	{
		(*c)[i] = (*c)[i] - ((*a)[row][i] * coeff);
	}
	(*opt) = (*opt) - ((*b)[row] * coeff);
}

//perform row operations to make c elements in basic columns 0
//opt is the optimal value in the current simplex table
void reduceC(vector<vector<double> > *a, vector<double> *b, vector<double> *c, double *opt)
{
	// for each row
	for (int i=0; i<(*a).size(); i++)
	{
		// default the row operation coefficient to 1
		double coeff = 1;
		for (int j=0; j<(*a)[0].size(); j++)
		{
			// found a 1, check for a basic column
			if ((*a)[i][j] == 1)
			{
				bool basic = true;
				for (int k=0; k<(*a).size(); k++)
				{
					// not 0 or 1, not basic
					if ((*a)[k][j] != 0 && k != i)
					basic = false;
				}
				// basic, make sure the c element becomes 0
				if (basic)
					coeff = (*c)[j] * (*a)[i][j];
			}
			// reduce the c element in this column
			(*c)[j] = (*c)[j] - ((*a)[i][j] * coeff);
		}
		// apply the reduction to the optimal value
		(*opt) = (*opt) - ((*b)[i] * coeff);
	}
}

//simplex algorithm
void simplex(vector<vector<double> > *a,vector<double> *b,vector<double> *c, double initialOpt,int var_num, int phase, bool minimize)
{
	if(phase==1)
	{
		vector<double> plc;
		//initilize by 0
		for(int i=0;i<(*a)[0].size();++i)
		{
			plc.push_back(0.0);
		}

		for(int i=0;i<(*a).size();++i)
		{
			plc.push_back(1.0);
			// add an identity matrix to A
			for(int j=0;j<(*a).size();++j)
			{
				if(j==i)
					(*a)[i].push_back(1.0);
				else
					(*a)[i].push_back(0.0);
			}
		}
		//initilize the objective function value by 0
		double opt=0.0;
		//reduce the new c row so basic variables have 0 cost
		reduceC(a, b, &plc, &opt);

		bool stop=false;
		while(!stop)
		{
			// get the pivot column
			double min_r=0;
			int pivot_col=0;
			for(int i=0;i<plc.size();++i)
			{
				if( plc[i]<min_r )
				{
					min_r=plc[i];
					pivot_col=i;
				}
			}
			// no c < 0, done
			if(min_r>=0)
			{
				stop=true;
				continue;
			}

			//get the pivot row
			double min_ratio=0;
			int pivot_row=0;
			//for each row
			for(int i=0;i<(*a).size();++i)
			{
				// check for the smallest positive ratio b[i] / a[i][pivot_column]
		        if ((*a)[i][pivot_col] > 0 && ((*b)[i] / (*a)[i][pivot_col] < min_ratio || min_ratio == 0))
		        {
					min_ratio = (*b)[i] / (*a)[i][pivot_col];
					pivot_row = i;
		        }
			}
			// no positive ratios, stop
			if(min_ratio<=0)
			{
				stop=true;
				continue;
			}
			//reduce the table on the pivot row and the pivot column
			reduce(a,b,&plc,&opt,pivot_row,pivot_col);
			// return to step 1 of the Simplex algorithm
		}
		// phase 1 done, cut off the added variables
		for(int i=0;i<(*a).size();++i)
		{
			(*a)[i].resize(var_num);
		}
		// reset optimal value to 0
		opt=0;
		// reduce the new c row so basic variables have 0 cost
		reduceC(a,b,c,&opt);
		//go to phase 2
		simplex(a,b,c,opt,var_num,2,minimize);
	}
	//phase 2
	else
	{
		double opt = initialOpt;
		bool stop = false;
		while(!stop)
		{
			// get the pivot column
			double min_r=0;
			int pivot_col=0;
			for(int i=0;i<(*c).size();++i)
			{
				// check for the smallest c < 0
				if((*c)[i]<min_r)
				{
					min_r=(*c)[i];
					pivot_col=i;
				}
			}

			// no c < 0, done
			if(min_r >= 0)
			{
				stop=true;
				// check for infeasibility
				bool infeasible=true;
				for(int i=0;i<(*c).size();++i)
				{
					//if any c > 0, the problem is feasible
					if((*c)[i] > 0)
					{
						infeasible=false;
						break;
					}
				}
				if(infeasible)
				{
					outputInfeasible(a,b,c);
					continue;
				}
				if(minimize)
				{
					output(a,b,c,-1*opt,var_num);
				}
				else
				{
					output(a,b,c,opt,var_num);
				}
				continue;

			}

			//get the pivot row
			double min_ratio=0;
			int pivot_row=0;
			for(int i=0;i<(*a).size();++i)
			{
				if ((*a)[i][pivot_col] > 0 && ((*b)[i] / (*a)[i][pivot_col] < min_ratio || min_ratio == 0))
		        {
					min_ratio = (*b)[i] / (*a)[i][pivot_col];
					pivot_row = i;
		        }
			}
			// no positive ratios, problem is unbounded
			if(min_ratio<=0)
			{
				stop=true;
				outputUnbounded(a,b,c,minimize);
				continue;
			}
			// reduce the tableau on the pivot row and column
			reduce(a,b,c,&opt,pivot_row,pivot_col);
		}
	}
}

int main(int argc,char *argv[])
{
	//get the input file by cmd input
	if(argc==2)
	{
		string line;
		ifstream infile;
		infile.open(argv[1]);
		//get one line from the input
		if(infile.is_open())
		{
			//get the var nums and contraint nums
			int variable_num,constraint_num;
			if(getline(infile,line))
			{
				size_t offset=line.find(" ");
				if(offset!=string::npos)
				{
					string var_num_str=line.substr(0,offset);
					variable_num=atoi(var_num_str.c_str());
					string cons_num_str=line.substr(offset);
					constraint_num=atoi(cons_num_str.c_str());
				}
			}

			//minimize is true if min,else false
			bool minimize;
			if(getline(infile,line))
			{
				if(line.compare(0,3,"min")==0)
				{
					minimize=true;
				}
				else
				{
					minimize=false;
				}
			}

			//c_original is the c matrix
			int c_original[variable_num];
			if(getline(infile,line))
			{
				// int count=0;
				// size_t index=line.find(" ");
				// c_original[0]=atoi((line.substr(0,index)).c_str());
				// if(!minimize)
				// {
				// 	c_original[0] = -1*c_original[0];
				// }
				// string sub_line=line.substr(index);
				// ++count;
				// while(index != string::npos)
				// {
				// 	index=sub_line.find(" ");
				// 	c_original[count]=atoi((sub_line.substr(0,index)).c_str());
				// 	if(!minimize)
				// 	{
				// 		c_original[count] = -1*c_original[count];
				// 	}
				// 	sub_line=sub_line.substr(index);
				// 	++count;
				// }
				char *token = strtok((char *)line.c_str(), " ");
				int count=0;
				while(token)
				{
					c_original[count]=atoi(token);
					if(!minimize)
					{
						c_original[count]=-1*c_original[count];
					}
					++count;
					token=strtok(NULL," ");
				}
			}

			//A matrix
			vector<vector<double> > vec_a(constraint_num);
			//b matrix
			vector<double> vec_b;
			int row_index=0;
			//nums of LE constraints
			int num_LT=0;
			while(getline(infile,line))
			{
				bool flag=false;
				char *token = strtok((char *)line.c_str(), " ");
				while(token)
				{
					if(!strcmp(token,"="))
					{
						flag=true;
					}
					else if(!strcmp(token,"<="))
					{
						for(int i=0;i<constraint_num;++i)
						{
							if(row_index==i)
								vec_a[row_index].push_back(1.0);
							else
								vec_a[row_index].push_back(0.0);
						}
						flag=true;
						++num_LT;
					}
					else if(!strcmp(token,">="))
					{
						for(int i=0;i<constraint_num;++i)
						{
							if(row_index==i)
								vec_a[row_index].push_back(-1.0);
							else
								vec_a[row_index].push_back(0.0);
						}
						flag=true;
					}
					else
					{
						if(flag)
							vec_b.push_back(atof(token));
						else
							vec_a[row_index].push_back(atof(token));
					}
					token = strtok(NULL, " ");
				}
				++row_index;
			}
			infile.close();

			//c matrix
			vector<double> vec_c;
			for(int i=0;i<vec_a[0].size();++i)
			{
				if( i<( sizeof(c_original)/sizeof(c_original[0]) ) )
					vec_c.push_back(c_original[i]);
				else
					vec_c.push_back(0.0);
			}

			// cout<<variable_num<<endl<<constraint_num<<endl;
			// for(int i=0;i<vec_c.size();++i)
			// 	cout<<vec_c[i]<<" ";
			// cout<<endl;
			// for(int i=0;i<constraint_num;++i)
			// {
			// 	for(int j=0;j<vec_a[0].size();++j)
			// 	{
			// 		cout<<vec_a[i][j]<<" ";
			// 	}
			// 	cout<<endl;
			// }
			// for(int i=0;i<vec_b.size();++i)
			// 	cout<<vec_b[i]<<" ";
			// cout<<endl;

			int phase=1;
			if(num_LT==constraint_num)
				phase=2;

			clock_t start=clock();
			simplex(&vec_a,&vec_b,&vec_c,0,variable_num,phase,minimize);
			clock_t finish=clock();
			double duration=((double)(finish-start))/CLOCKS_PER_SEC;
			cout<<"Time used "<<duration<<" seconds"<<endl;

		}
		else
		{
			cout<<"Error: connot open "<<argv[1]<<endl;
		}
	}
	return 0;
}