#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

typedef struct
{
	string duration;
	string protocol_type;
	string service;
	string flag;
	string src_bytes;
	string dst_bytes;
	string land;
	string wrong_fragment;
	string urgent;
	string hot;
	string num_failed_logins;
	string logged_in;
	string num_compromised;
	string root_shell;
	string su_attempted;
	string num_root;
	string num_file_creations;
	string num_shells;
	string num_access_files;
	string num_outbound_cmds;
	string is_host_login;
	string is_guest_login;
	string count;
	string srv_count;
	string serror_rate;
	string srv_serror_rate;
	string rerror_rate;
	string srv_rerror_rate;
	string same_srv_rate;
	string diff_srv_rate;
	string srv_diff_host_rate;
	string dst_host_count;
	string dst_host_srv_count;
	string dst_host_same_srv_rate;
	string dst_host_diff_srv_rate;
	string dst_host_same_src_port_rate;
	string dst_host_srv_diff_host_rate;
	string dst_host_serror_rate;
	string dst_host_srv_serror_rate;
	string dst_host_rerror_rate;
	string dst_host_srv_rerror_rate;
	string label;				// Labeled data, does NOT have a value for unlabeled data set.
} features;

typedef vector < string > vs;
typedef vector < vs > vvs;
typedef vector < int > vi;
typedef map < string, int > msi;
typedef map < string, string > mss;
typedef vector < double > vd;
typedef vector< vd > vvd;
typedef pair<int,int> pp;
//typedef map<int , int> mii;

// const string TRAIN_FILE = "kddcup.data_10_percent.txt";
// const string TEST_FILE = "testdata_unlabeled_50000.txt";

// node of the decision tree
struct node
{
	string splitOn;
	string label;
	bool isLeaf;
	  vector < string > childrenValues;
	  vector < node * >children;
};

vd getColSD(vvs &);
void printCov(vvd &);
pp getMaxCov(vvs &);
vd getRowMean(vvs &);
vvd getRowPointMul(vvs &);
vvd computeCov(vvs &);
string deCalssLabelMap(string/*, mss &*/);
string getProcessFlag (string/*, mss &*/);
string getProcessLabel (string/*, mss &*/);
string getProcessProtocol (string/*, mss &*/);
string getProcessService (string/*, mss &*/);

// //get data attributes num
// long long get_col_num(ifstream &infile,bool flag);
// //get total records num
// long long get_row_num(ifstream &infile);

void encode(vvs &);
void preProcessRate(vvs &);

//pre-process data
void preDiscretization (vvs & /*,vvs& */ );

//get the spilit value by computing entropy
string getSplitValue (int, vvs & /*, vvs& */ );

// //generate sub-table contains relevant column and the class label column
// vvs genEntropySubTable(int,vvs&,vvs&);

// parses a single line from the input file and stores the info into a matrix
void getData (string &, vvs &);

// print data table
void printAttributeTable (vvs &);

//get the sub-table
vvs pruneTable (vvs &, string &, string);

// build the decision tree
node *buildDecisionTree (vvs &, node *, vvs &);

// returns true if all instances in a subtable at a node have the same label
bool isSameClass (vvs &);

// return the counts of all the various values of an attribute/column
vi countDistinct (vvs &, int);

// return the spilit attribute                          
string decideSplittingColumn (vvs &);

// return the index of a column in a subtable
int returnColumnIndex (string &, vvs &);

// return true if a subtable is empty
bool tableIsEmpty (vvs &);

// recursively print the decision tree
void printDecisionTree (node *);

//test the test dataset
string testDataOnDecisionTree (vs &, node *, vvs &, string);

// return the index of a string in a vector of strings  
int returnIndexOfVector (vs &, string);

// output the predictions to file and returns the accuracy of the classification
double printPredictionsAndCalculateAccuracy (vs &, vs &);

// generate information about the table in a vector of vector of strings        
vvs generateTableInfo (vvs & dataTable);

// return the most frequent class from the training data. This class is used as the default class during the testing phase
string returnMostFrequentClass (vvs & dataTable);
