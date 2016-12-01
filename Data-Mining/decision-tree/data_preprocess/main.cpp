#include "pre_process.h"

int main(int argc, char *argv[])
{
	FILE *pInFile, *pOutFile;
	
	if (argc != 2)
	{
		cout << "params error !" << endl;
		return -1;
	}
	char *inputFileName;
	inputFileName = new char[30];
	strcpy (inputFileName, argv[1]);

	//kddcup.data_10_percent.txt
	if ((pInFile = fopen (inputFileName, "r")) == NULL)	
	{
		cout << "fail to open training dataset file!" << endl;
		return -1;
	}

	cout << "start reading records from " << argv[1] << "..." << endl;
	feature_list data=getData(pInFile);

	const char *outfname = "_preprocessing";
	char *outputFileName;
	outputFileName = strcat (inputFileName, outfname);
	if ((pOutFile = fopen (outputFileName, "w")) == NULL)	//kddcup99.data_10000_datatreat
	{
		fclose (pInFile);
		cout << "fail to create _preprocessing file!" << endl;
		return -1;
	}

	cout << "Start writing records into " << outputFileName<< " ..." << endl;
	writeToFile(pOutFile,data);

	//fclose(pInFile);
	//fclose(pOutFile);
	return 0;
}