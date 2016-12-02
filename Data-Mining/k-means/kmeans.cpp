/*
Reference:
https://github.com/serpheroth/k-means
*/

#include "kmeans.h"

bool ReadTestFile(feature_list* pRecordList)
{
	FILE *pInFile;
	int iTestCount;
	char szBuf[MAX_BUF_SIZE];
	feature* pRecord;

	string strTemp;
	char szSeps[] = ",\r\n";
	
	cout<<"Start reading records from test file!"<<endl;
	outfile<<"Start reading records from test file!"<<endl;	
	
	if ((pInFile = fopen("corrected_preprocessing", "r")) == NULL)
	{
		cout<<"Open Test file faied !"<<endl;
		return false;
	}
	else
	{
		iTestCount = 0;
		while (fgets(szBuf, MAX_BUF_SIZE, pInFile) != NULL)
		{
			if(++iTestCount%10000 == 0)
				cout<<setiosflags(ios::left)<<setw(8)<<iTestCount<<"  lines have been read ..."<<endl;

			pRecord = new feature;

			strTemp = strtok(szBuf, szSeps);
			pRecord->fProtocolType = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fService = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fStatusFlag = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fSrcBytes = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDestBytes = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fFailedLogins = (float)atof(strTemp.c_str());
			strtok(NULL, szSeps);
			strTemp = strtok(NULL, szSeps);
			pRecord->fNumofRoot = (float)atof(strTemp.c_str());
			strtok(NULL, szSeps);
			strTemp = strtok(NULL, szSeps);
			pRecord->fCount = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fSrvCount = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fRerrorRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fSameSrvRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDiffSrvRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSrvCount = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSameSrvRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostDiffSrvRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSameSrcPortRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSrvDiffHostRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSrvSerrorRate = (float)atof(strTemp.c_str());
			strTemp = strtok(NULL, szSeps);
			pRecord->iLabel = atoi(strTemp.c_str());
			
		    pRecordList->push_back(pRecord);
		}
		
		cout<<iTestCount<<" Records have been read from test file!"<<endl;			
		outfile<<iTestCount<<" Records have been read from test file!"<<endl;		
		return true;
	}
}

string LabelInttoStr(int i)
{
	string strLabel;
	switch(i)
	{
	case 0:
		strLabel = "normal";
		break;
	case 2:
		strLabel = "dos";
		break;
	case 1:
		strLabel = "probe";
		break;
	case 3:
		strLabel = "ur2";
		break;
	case 4:
		strLabel = "r2l";
		break;
	// default:
	// 	strLabel = "!!ERROR!!";
	// 	break;
	}
    return strLabel;	
}

int main()
{
	int Kvalue;
	int iRightRcdNum;
	int TestRcdNum;
	string strTrueLabel,strPreLabel;
	
	feature* pRecord;
	feature_list* pTestRcdList;
	feature_list::iterator TestListIter;

	ClusterNode* pClusterNode;
	ClusterTree* pClusterTree;
	clock_t start,finish;
	double duration;
	outfile<<"Start K-means clustering proccess ..."<<endl;
	pClusterTree = new ClusterTree();
	CKMeans m_CKMeans(pClusterTree,++KmeansID,1,19);
	if(!m_CKMeans.ReadTrainingRecords())
	{
		cout<<"Open training file failed !"<<endl;
		outfile<<"Open training file failed !"<<endl;
		exit(0);
	}
	else
	{
		cout<<"----------------------------------------------"<<endl;
		cout<<"Read training file successfully !"<<endl;
		outfile<<"--------------------------------------"<<endl;
		outfile<<"Read training file successfully !"<<endl;
		// Kvalue is 5
		Kvalue = MAXLABEL;	  
	    outfile<<"Init K-value ="<<Kvalue<<endl;
	    start=clock();
		m_CKMeans.RunKMeans(Kvalue);
		finish=clock();
		duration=((double)(finish-start))/CLOCKS_PER_SEC;
		cout<<"****************** Cluster Time for the training data-set: "<<duration<<" seconds"<<endl;
		outfile<<"****************** Cluster Time for the training data-set: "<<duration<<" seconds"<<endl;
	    cout<<"****************** Total Clustering process finished ! *******************"<<endl;
	    outfile<<"****************** Total Clustering process finished ! *******************"<<endl;

		pClusterTree->Print();
		pClusterTree->PrintLog();
    }
  
	cout<<"************* Start classify the test records **************"<<endl;
	outfile<<"************* Start classify the test records **************"<<endl;

	pTestRcdList = new feature_list;
	if(!ReadTestFile(pTestRcdList))
	{
		cout<<"Open Test file failed !"<<endl;
		outfile<<"Open Test file failed !"<<endl;
		exit(0);  	
	}
	else
	{
		cout<<"*****************************************************************"<<endl;
		cout<<"Start classifying test records ... "<<endl;
		outfile<<"*****************************************************************"<<endl;
		outfile<<"Start classifying test records ... "<<endl;
		Rstfile<<"********************** Classification Result **************************"<<endl;
		ConfuseMatrix m_CfsMatrix;
		iRightRcdNum = 0;
		TestRcdNum = 0;
		start =clock();
		for(TestListIter = pTestRcdList->begin();TestListIter != pTestRcdList->end();TestListIter++)
		{
			pRecord = (*TestListIter);
			pClusterNode = pClusterTree->FindNearestCluster(pRecord);
			
			if(pRecord->iLabel == pClusterNode->GetClusterNodeLabel())
			{
				iRightRcdNum++;
			}
			
			m_CfsMatrix.UpdateValue(pRecord->iLabel,pClusterNode->GetClusterNodeLabel());
			
			strTrueLabel = LabelInttoStr(pRecord->iLabel);
			strPreLabel = LabelInttoStr(pClusterNode->GetClusterNodeLabel());
			//Rstfile<<setiosflags(ios::left)<<"True Label = "<<setw(8)<<strTrueLabel<<" Pre Label = "<<setw(8)<<strPreLabel<<" Cluster Path = "<<pClusterNode->strPath<<endl;

		  if((++TestRcdNum)%10000 == 0)
		  {
		  	// cout<<TestRcdNum<<" records have been done ..."<<endl;
		  	// outfile<<TestRcdNum<<" records have been done ..."<<endl;
		  }
		}
		finish=clock();
		duration=((double)(finish-start))/CLOCKS_PER_SEC;
		cout<<"****************** Cluster Time for the test data-set: "<<duration<<" seconds"<<endl;
		outfile<<"****************** Cluster Time for the test data-set: "<<duration<<" seconds"<<endl;
    
	    cout<<"****** The process of classifying test records  finished ! ******"<<endl;
	    outfile<<"****** The process of classifying test records  finished ! ******"<<endl;

	    cout<<"================================== Classify Result ===================================="<<endl;
	    Rstfile<<"================================== Classify Result ===================================="<<endl;
	    cout<<"Total Test Records = "<<TestRcdNum<<"  Right_Label Records = "<<iRightRcdNum<<" Right Rate = "<<(float)(iRightRcdNum)/TestRcdNum<<endl;
	    Rstfile<<"Total Test Records = "<<TestRcdNum<<"  Right_Label Records = "<<iRightRcdNum<<" Right Rate = "<<(float)(iRightRcdNum)/TestRcdNum<<endl;
	    
	    m_CfsMatrix.PrintMatrix();
	    m_CfsMatrix.PrintMatrixToLog();
	}
}