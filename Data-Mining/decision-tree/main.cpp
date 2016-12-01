#include "utils.h"
/*
Reference:
CSDN blog 决策树实现例子:
http://blog.csdn.net/zhoubl668/article/details/40828573

连续特征离散化和归一化（卡方检验和信息增益）：
http://www.cnblogs.com/zhizhan/p/5042935.html

卡方检验
http://www.cnblogs.com/emanlee/archive/2008/10/25/1319569.html

数据离散化的常用方法
http://wenku.baidu.com/view/d38264791711cc7931b71691.html

csdn blog连续属性的离散化
https://www.zybuluo.com/K1999/note/460870
*/

int main (int argc, const char *argv[])
{
	freopen ("stdout.txt", "w", stdout);
	ifstream inputFile;
	string singleLine;
	vvs dataTable;
	inputFile.open (argv[1]);
	if (!inputFile)
	{
		cerr << "Error: Training data file not found!" << endl;
		exit (-1);
	}

	while (getline (inputFile, singleLine)&& singleLine!="")
	{
		getData (singleLine, dataTable);
	}
	inputFile.close ();

	encode(dataTable);
	preProcessRate(dataTable);

	vvd cov=computeCov(dataTable);
	cout<<endl<<"##############"<<endl<<endl;
	printCov(cov);
	cout<<endl<<"##############"<<endl<<endl;

	vvs tableInfo = generateTableInfo (dataTable);
	cout << "table Info+++++++++++++++++++++++++++" << endl;
	printAttributeTable (tableInfo);

	cout << "Before preDiscretization------------------------------------------" << endl << endl << endl;;
	//printAttributeTable (dataTable);
	cout << "After preDiscretization------------------------------------------" << endl << endl << endl;
	//data discretization
	preDiscretization (dataTable /*,tableInfo */ );
	//printAttributeTable (dataTable);

	cout << "table Info+++++++++++++++++++++++++++" << endl;
	tableInfo = generateTableInfo (dataTable);
	printAttributeTable (tableInfo);


	// Declare and assign memory for the root node of the Decision Tree
	node *root = new node;
	// Recursively build and train decision tree
	root = buildDecisionTree (dataTable, root, tableInfo);

	cout<<"*********************************Decision Tree:***********"<<endl;
	printDecisionTree(root);

	// vote to store the most frequent class in the training data. This is used as the default class label
	string defaultClass = returnMostFrequentClass (dataTable);
	//cout<<"****************defaultClass "<<defaultClass<<endl;
	// clear dataTable of training data to store testing data
	dataTable.clear ();

	inputFile.clear ();
	inputFile.open (argv[2]);
	if (!inputFile)
	{
		cerr << "Error: Testing data file not found!" << endl;
		exit (-1);
	}
	while (getline (inputFile, singleLine)&& singleLine!="")
	{
		getData (singleLine, dataTable);
	}
	inputFile.close ();

	encode(dataTable);
	preProcessRate(dataTable);
	
	// vvs tableInfo = generateTableInfo(dataTable);
	// cout<<"table Info+++++++++++++++++++++++++++"<<endl;
	// printAttributeTable(tableInfo);

	// cout << "Before preDiscretization------------------------------------------" << endl << endl << endl;;
	// printAttributeTable (dataTable);
	// cout << "After preDiscretization------------------------------------------" << endl << endl << endl;
	//data discretization
	preDiscretization (dataTable /*,tableInfo */ );
	//printAttributeTable (dataTable);
	tableInfo = generateTableInfo (dataTable);
	cout<<"+++++++++++++++++++==test tableInfo"<<endl;
	printAttributeTable(tableInfo);
	vs predictedClassLabels;
	vs givenClassLabels;
	for (int i = 1; i < dataTable.size (); ++i)
	{
		string data = dataTable[i][dataTable[0].size () - 1];
		//cout<<"**********given class label "<<data<<endl;
		givenClassLabels.push_back (data);
	}

	clock_t start=clock();
	
	// Predict class labels based on the decision tree
	for (int i = 1; i < dataTable.size (); ++i)
	{
		string someString = testDataOnDecisionTree (dataTable[i], root, tableInfo, defaultClass);
		//cout<<"**********predicted class label "<<someString<<endl;
		predictedClassLabels.push_back (someString);
	}
	clock_t finish=clock();
	double duration=((double)(finish-start))/CLOCKS_PER_SEC;
	//cout<<"Time used "<<duration<<" seconds"<<endl;
	dataTable.clear ();

	/* Print output */
	ofstream outputFile;
	outputFile.open ("test_data_output.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
	// calculate accuracy of classification
	double accuracy = printPredictionsAndCalculateAccuracy (givenClassLabels, predictedClassLabels);
	// Print out accuracy to console
	outputFile << "Accuracy of decision tree = " << accuracy << "%"<<endl;
	outputFile<<"Time consumption: "<<duration/3600.0<<" hours"<<endl;
	outputFile.close ();
	fclose (stdout);
	return 0;
}
