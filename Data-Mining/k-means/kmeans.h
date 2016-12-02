#include "cluster_tree.h"
#include "utils.h"

ofstream outfile("Log.txt");
ofstream Rstfile("Result.txt");

int KmeansID = 0;

//cluster
struct Cluster 
{
	float Center[MAXDIMENSION];
	//record list
	feature_list MemberList;
	//record num
	int iNumMembers;
};

class CKMeans  
{
public:

	CKMeans(ClusterTree* pTree,int KmeansID,int Level,int NumDimensions)
	{
		cout<<"********** Creat a new Kmeans, ID = "<<KmeansID<<" **********"<<endl;
		outfile<<"********** Creat a new Kmeans, ID = "<<KmeansID<<" **********"<<endl;
		
		pClusterTree = pTree;
		pSelfClusterNode = pClusterTree->GetRootNode();
		
		m_iNumDimensions = NumDimensions;
		m_ClusterLevel = Level;
		m_KmeansID = KmeansID;
		m_iNumRecords = 0;
		m_iNumClusters = 0;
	};
	
	CKMeans(ClusterNode* pSelf,ClusterTree* pTree,int KmeansID,int Level,int NumDimensions,feature_list* pDataList)
	{
		cout<<"********** Creat a new Kmeans, ID = "<<KmeansID<<" **********"<<endl;
		outfile<<"********** Creat a new Kmeans, ID = "<<KmeansID<<" **********"<<endl;
		
		pClusterTree = pTree;
		pSelfClusterNode = pSelf;
		m_iNumDimensions = NumDimensions;
		m_ClusterLevel = Level;
		m_KmeansID = KmeansID;
		m_iNumRecords = 0;
		m_iNumClusters = 0;
		m_RecordsList = (*pDataList);
	};
	
	//read the training file
	bool ReadTrainingRecords();

	//random choose k records as cluster center
	void InitClusters(unsigned int NumClusters);	

	//update the cluster by distance
	void DistributeSamples();
	//update new cluster center
	bool CalcNewClustCenters();
	//calculate distance
	float CalcEucNorm(feature *pRecord, int id);

	//find closest cluster
	int  FindClosestCluster(feature *pRecord);
	//print cluster center
	void PrintClusters();
	
	void RunKMeans(int Kvalue);

	void GetClustersLabel();
	//check whether classfier is right 
	bool IsClusterOK(int i);
	
	feature_list* GetClusterList(int i);

	void PrintClusterLabel(int i);

	int GetDiffLabelofCluster(int i);
	
	bool IsStopRecursion(int i);

	void CreatClusterTreeNode(ClusterNode* pParent);
	
private:

	bool IsSameAsCluster(int i,feature* pRecord);
	//assignment value for center i
	void EvaluateCluster(int i,feature* pRecord);

private:	
	FILE *pInFile;
	feature_list m_RecordsList;
	unsigned int  m_iNumClusters;
	int m_iNumRecords;
	int m_iNumDimensions;
	Cluster m_Cluster[MAXCLUSTER];
	int m_ClusterLevel;
	int m_KmeansID;
	ClusterTree* pClusterTree;
	ClusterNode* pClusterNode[MAXLABEL];
	ClusterNode* pSelfClusterNode;
};

class ConfuseMatrix
{
public:
  ConfuseMatrix()
  {
  	int i,j;
  	for(i=0;i<MAXLABEL;i++)
  	{
  		for(j=0;j<MAXLABEL;j++)
  		{
  			CfusMatrix[i][j] = 0;
  		}
  	}  	
  };
  
	void UpdateValue(int iTrueLabel,int iPreLabel)
	{
		CfusMatrix[iTrueLabel][iPreLabel]++;
	};
  
	void PrintMatrix()
	{
		int i,j;
		cout<<"=================================  Confusion Matrix  =================================="<<endl;
		//first line
		cout<<setiosflags(ios::left)<<setw(5)<<"T/P";
		for(i=0;i<MAXLABEL;i++)
		{
			cout<<setiosflags(ios::left)<<setw(7)<<i;
		}
		cout<<endl;

		for(i=0;i<MAXLABEL;i++)
		{
			cout<<setiosflags(ios::left)<<setw(5)<<i;
			for(j=0;j<MAXLABEL;j++)
			{
				cout<<setiosflags(ios::left)<<setw(7)<<CfusMatrix[i][j];
			}
			cout<<endl;
		}    	
	};
  
	void PrintMatrixToLog()
	{
		int i,j;
		Rstfile<<"=================================  Confusion Matrix  =================================="<<endl;
		Rstfile<<setiosflags(ios::left)<<setw(5)<<"T/P";
		for(i=0;i<MAXLABEL;i++)
		{
			Rstfile<<setiosflags(ios::left)<<setw(7)<<i;
		}
		Rstfile<<endl;
		for(i=0;i<MAXLABEL;i++)
		{
			Rstfile<<setiosflags(ios::left)<<setw(5)<<i;
			for(j=0;j<MAXLABEL;j++)
			{
				Rstfile<<setiosflags(ios::left)<<setw(7)<<CfusMatrix[i][j];
			}
			Rstfile<<endl;
		}    	
	};

private:
	int CfusMatrix[MAXLABEL][MAXLABEL];
};

bool CKMeans::ReadTrainingRecords()
{
	int iCount;
	
	char szBuf[MAX_BUF_SIZE];
	char szSeps[] = ",\r\n";
	string strTemp;
	feature* pRecord;
	cout<<"Start reading Records from training file ..."<<endl;

	if ((pInFile = fopen("kddcup.data_10_percent.txt_preprocessing", "r")) == NULL)
	{
		cout<<"fail to open training dataset !"<<endl;
		return false;
	}
	else
	{
		iCount = 0;
		while (fgets(szBuf, MAX_BUF_SIZE, pInFile) != NULL)
		{
			if(++iCount%100000 == 0)
				cout<<"========== "<<iCount<<"  lines have been read =========="<<endl;
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
		    m_RecordsList.push_back(pRecord);
		}

		m_iNumRecords = iCount;
		cout<<iCount<<" Record have been read from training file!"<<endl;	
		return true;
	}
}

//whether is the same as the cluster center
bool CKMeans::IsSameAsCluster(int i,feature* pRecord)
{
	int j;
	bool Sameflag= false;
	for(j = 0;j < i;j++)
	{
		if(m_Cluster[j].Center[18] == pRecord->iLabel && j < m_iNumClusters)
		{
			Sameflag = true;
			break;
		}
		else if(m_Cluster[j].Center[0] != pRecord->fProtocolType)
		{
			continue;
		}
		else if(m_Cluster[j].Center[1] != pRecord->fService)
		{
			continue;
		}
		else if(m_Cluster[j].Center[2] != pRecord->fStatusFlag)
		{
			continue;
		}			
		else if(m_Cluster[j].Center[3] != pRecord->fSrcBytes)
		{
			continue;
		}
		else if(m_Cluster[j].Center[4] != pRecord->fDestBytes)
		{
			continue;
		}
		else if(m_Cluster[j].Center[5] != pRecord->fFailedLogins)
		{
			continue;
		}
		else if(m_Cluster[j].Center[6] != pRecord->fNumofRoot)
		{
			continue;
		}
		else if(m_Cluster[j].Center[7] != pRecord->fCount)
		{
			continue;
		}
		else if(m_Cluster[j].Center[8] != pRecord->fSrvCount)
		{
			continue;
		}
		else if(m_Cluster[j].Center[9] != pRecord->fRerrorRate)
		{
			continue;
		}
		else if(m_Cluster[j].Center[10] != pRecord->fSameSrvRate)
		{
			continue;
		}
		else if(m_Cluster[j].Center[11] != pRecord->fDiffSrvRate)
		{
			continue;
		}
		else if(m_Cluster[j].Center[12] != pRecord->fDstHostSrvCount)
		{
			continue;
		}
		else if(m_Cluster[j].Center[13] != pRecord->fDstHostSameSrvRate)
		{
			continue;
		}
		else if(m_Cluster[j].Center[14] != pRecord->fDstHostDiffSrvRate)
		{
			continue;
		}
		else if(m_Cluster[j].Center[15] != pRecord->fDstHostSameSrcPortRate)
		{
			continue;
		}
		else if(m_Cluster[j].Center[16] != pRecord->fDstHostSrvDiffHostRate)
		{
			continue;
		}
		else if(m_Cluster[j].Center[17] != pRecord->fDstHostSrvSerrorRate)
		{
			continue;
		}
		else
		{
			Sameflag = true;
			break;
		}
	}	
	return Sameflag;
}

void CKMeans::EvaluateCluster(int j,feature* pRecord)
{
	m_Cluster[j].Center[0] = pRecord->fProtocolType;
	m_Cluster[j].Center[1] = pRecord->fService;
	m_Cluster[j].Center[2] = pRecord->fStatusFlag;		
	m_Cluster[j].Center[3] = pRecord->fSrcBytes;
    m_Cluster[j].Center[4] = pRecord->fDestBytes;
	m_Cluster[j].Center[5] = pRecord->fFailedLogins;
	m_Cluster[j].Center[6] = pRecord->fNumofRoot;
	m_Cluster[j].Center[7] = pRecord->fCount;
	m_Cluster[j].Center[8] = pRecord->fSrvCount;
	m_Cluster[j].Center[9] = pRecord->fRerrorRate;
	m_Cluster[j].Center[10]= pRecord->fSameSrvRate;
	m_Cluster[j].Center[11]= pRecord->fDiffSrvRate;
	m_Cluster[j].Center[12]= pRecord->fDstHostSrvCount;
	m_Cluster[j].Center[13]= pRecord->fDstHostSameSrvRate;
    m_Cluster[j].Center[14]= pRecord->fDstHostDiffSrvRate;
    m_Cluster[j].Center[15]= pRecord->fDstHostSameSrcPortRate;
    m_Cluster[j].Center[16]= pRecord->fDstHostSrvDiffHostRate;
    m_Cluster[j].Center[17]= pRecord->fDstHostSrvSerrorRate;
    m_Cluster[j].Center[18]= pRecord->iLabel;
}

void CKMeans::InitClusters(unsigned int NumClusters)
{	
	//cout<<"In function InitClusters"<<endl;
	int i;
	feature* pRecord;
	feature_list::iterator RecdListIter;
	
	m_iNumClusters = NumClusters;
	RecdListIter = m_RecordsList.begin();
	
	for(i=0; i < m_iNumClusters; i++)
	{
		pRecord = (*RecdListIter);
	    while(IsSameAsCluster(i,pRecord))
	    {
	    	RecdListIter++;
	    	pRecord = (*RecdListIter);
	    }
	    m_Cluster[i].MemberList.push_back(pRecord);
		m_Cluster[i].iNumMembers = 1;
	    EvaluateCluster(i,pRecord);
	}
}

void CKMeans::PrintClusters()
{
	int i;
	outfile<<"================================================"<<endl;
	outfile<<"There are totally "<<m_iNumClusters<<" Clusters."<<endl;
	for(i=0; i < m_iNumClusters; i++)
	{
		outfile<<"+++++++++++++ Cluster Center "<<i<<" +++++++++++++"<<endl;
		
		outfile<<"fProtocolType = "<<m_Cluster[i].Center[0]<<endl;
		outfile<<"fService = "<<m_Cluster[i].Center[1]<<endl;
		outfile<<"fStatusFlag = "<<m_Cluster[i].Center[2]<<endl;
		outfile<<"fSrcBytes = "<<m_Cluster[i].Center[3]<<endl;
		outfile<<"fDestBytes = "<<m_Cluster[i].Center[4]<<endl;
		outfile<<"fFailedLogins = "<<m_Cluster[i].Center[5]<<endl;
		outfile<<"fNumofRoot = "<<m_Cluster[i].Center[6]<<endl;
		outfile<<"fCount = "<<m_Cluster[i].Center[7]<<endl;
		outfile<<"fSrvCount = "<<m_Cluster[i].Center[8]<<endl;
		outfile<<"fRerrorRate = "<<m_Cluster[i].Center[9]<<endl;
		outfile<<"fSameSrvRate = "<<m_Cluster[i].Center[10]<<endl;
		outfile<<"fDiffSrvRate = "<<m_Cluster[i].Center[11]<<endl;
		outfile<<"fDstHostSrvCount = "<<m_Cluster[i].Center[12]<<endl; 
		outfile<<"fDstHostSameSrvRate = "<<m_Cluster[i].Center[13]<<endl;
		outfile<<"fDstHostDiffSrvRate = "<<m_Cluster[i].Center[14]<<endl;
		outfile<<"fDstHostSameSrcPortRate = "<<m_Cluster[i].Center[15]<<endl;
		outfile<<"fDstHostSrvDiffHostRate = "<<m_Cluster[i].Center[16]<<endl;
		outfile<<"fDstHostSrvSerrorRate = "<<m_Cluster[i].Center[17]<<endl;
		outfile<<"iLabel = "<<m_Cluster[i].Center[18]<<endl;
		
		outfile<<"----------------------------------------------------"<<endl;
		outfile<<"Number of members in Cluster "<<i<<" = "<<m_Cluster[i].MemberList.size()<<endl;	
		outfile<<"iNumMembers = "<<m_Cluster[i].iNumMembers<<endl;
	}
}

float CKMeans::CalcEucNorm(feature *pRecord, int id)
{
	double fDist;
	fDist = 0;
	/*
	fDist += pow((pRecord->fProtocolType - m_Cluster[id].Center[0]), 2);
	fDist += pow((pRecord->fService - m_Cluster[id].Center[1]), 2);
	fDist += pow((pRecord->fStatusFlag - m_Cluster[id].Center[2]), 2);
	*/
	fDist += pow((pRecord->fSrcBytes - m_Cluster[id].Center[3]), 2);
	fDist += pow((pRecord->fDestBytes - m_Cluster[id].Center[4]), 2);
	fDist += pow((pRecord->fFailedLogins - m_Cluster[id].Center[5]), 2);
	fDist += pow((pRecord->fNumofRoot - m_Cluster[id].Center[6]), 2);
	fDist += pow((pRecord->fCount - m_Cluster[id].Center[7]), 2);
	fDist += pow((pRecord->fSrvCount - m_Cluster[id].Center[8]), 2);
	fDist += pow((pRecord->fRerrorRate - m_Cluster[id].Center[9]), 2);
	fDist += pow((pRecord->fSameSrvRate - m_Cluster[id].Center[10]), 2);
	fDist += pow((pRecord->fDiffSrvRate - m_Cluster[id].Center[11]), 2);
	fDist += pow((pRecord->fDstHostSrvCount - m_Cluster[id].Center[12]), 2);
	fDist += pow((pRecord->fDstHostSameSrvRate - m_Cluster[id].Center[13]), 2);
	fDist += pow((pRecord->fDstHostDiffSrvRate - m_Cluster[id].Center[14]), 2);
	fDist += pow((pRecord->fDstHostSameSrcPortRate - m_Cluster[id].Center[15]), 2);
	fDist += pow((pRecord->fDstHostSrvDiffHostRate - m_Cluster[id].Center[16]), 2);
	fDist += pow((pRecord->fDstHostSrvSerrorRate - m_Cluster[id].Center[17]), 2);

	return float(fDist);
}

int CKMeans::FindClosestCluster(feature *pRecord)
{
	int iClusterId;
	float fMinDist, temp;

	fMinDist = CalcEucNorm(pRecord, 0);
	iClusterId = 0;

	for(int i=1; i < m_iNumClusters; i++)
	{
		temp = CalcEucNorm(pRecord, i);
		if(temp < fMinDist)
		{
			fMinDist = temp;
			iClusterId = i;
		}
	}
	return iClusterId;	
}

void CKMeans::DistributeSamples()
{
	int iClusterId,i;
	for (i=0; i < m_iNumClusters; ++i)
	{
		m_Cluster[i].MemberList.clear();
		m_Cluster[i].iNumMembers=0;
	}
	feature* pRecord;
	feature_list::iterator RecdListIter,recdie;
	for (RecdListIter = m_RecordsList.begin(),recdie=m_RecordsList.end(); RecdListIter != recdie; ++RecdListIter)
	{
		pRecord = (*RecdListIter);
		iClusterId = FindClosestCluster(pRecord);
		m_Cluster[iClusterId].MemberList.push_back(pRecord);
		++m_Cluster[iClusterId].iNumMembers;
	}
}

bool CKMeans::CalcNewClustCenters()
{
	bool  IsNewRound;
	int i,j;
	float TempCenter[MAXDIMENSION];
	feature* pRecord;
	feature_list::iterator ClusterListIter;
	IsNewRound = true;

	for(i=0; i < m_iNumClusters; i++)
	{
		for(j=0; j<m_iNumDimensions; j++)
		{
			TempCenter[j] = 0.0;
		}
	    for(ClusterListIter = m_Cluster[i].MemberList.begin(); ClusterListIter != m_Cluster[i].MemberList.end(); ++ClusterListIter)
		{
		  	pRecord = (*ClusterListIter);
			TempCenter[0] += pRecord->fProtocolType;
			TempCenter[1] += pRecord->fService;
			TempCenter[2] += pRecord->fStatusFlag;		
			TempCenter[3] += pRecord->fSrcBytes;
			TempCenter[4] += pRecord->fDestBytes;
			TempCenter[5] += pRecord->fFailedLogins;
			TempCenter[6] += pRecord->fNumofRoot;
			TempCenter[7] += pRecord->fCount;
			TempCenter[8] += pRecord->fSrvCount;
			TempCenter[9] += pRecord->fRerrorRate;
			TempCenter[10]+= pRecord->fSameSrvRate;
			TempCenter[11]+= pRecord->fDiffSrvRate;
			TempCenter[12]+= pRecord->fDstHostSrvCount;
			TempCenter[13]+= pRecord->fDstHostSameSrvRate;
			TempCenter[14]+= pRecord->fDstHostDiffSrvRate;
			TempCenter[15]+= pRecord->fDstHostSameSrcPortRate;
			TempCenter[16]+= pRecord->fDstHostSrvDiffHostRate;
			TempCenter[17]+= pRecord->fDstHostSrvSerrorRate;	
        }

		for(j=3; j<(m_iNumDimensions-1); j++)
		{
			TempCenter[j] = TempCenter[j]/m_Cluster[i].iNumMembers;
			if(TempCenter[j] != m_Cluster[i].Center[j])
			{
				IsNewRound = false;
			}
			m_Cluster[i].Center[j] = TempCenter[j];
		}
	}
	return IsNewRound;	
}

void CKMeans::GetClustersLabel()
{
	int i,k,max;
	int LabelCount[5];
	feature* pRecord;
	feature_list::iterator ClusterListIter;
	

	cout<<"************** Cluster Level "<<m_ClusterLevel<<" **************"<<endl;
	outfile<<"************** Cluster Level "<<m_ClusterLevel<<" **************"<<endl;
	
	for(i=0; i < m_iNumClusters; ++i)
	{
		for(k=0;k < 5;++k)
		{
			LabelCount[k] = 0;
		}
		
		cout<<"------------- Kmeans"<<m_KmeansID<<" Cluster"<<i<<" -------------"<<endl;
		outfile<<"------------- Kmeans"<<m_KmeansID<<" Cluster"<<i<<" -------------"<<endl;
		
		for(ClusterListIter = m_Cluster[i].MemberList.begin(); ClusterListIter != m_Cluster[i].MemberList.end(); ++ClusterListIter)
		{
			 pRecord = (*ClusterListIter);
			 switch(pRecord->iLabel)
			 {
			 	 case 0:
			 	 	LabelCount[0]++;
			 	 	break;
			 	 case 1:
			 	 	LabelCount[1]++;
			 	 	break;
			 	 case 2:
			 	 	LabelCount[2]++;
			 	 	break;
			 	 case 3:
			 	 	LabelCount[3]++;
			 	 	break;
			 	 case 4:
			 	 	LabelCount[4]++;
			 	 	break;
			 	 default:
			 	 	break;
			 }
		}

	    for(k=0;k < 5;k++)
		{
			pClusterNode[i]->iLabelNum[k] = LabelCount[k];
		}
		
		for(k=0,max=0;k < 5;k++)
	    {
		  	if(LabelCount[max] < LabelCount[k])
		  	{
		  		max = k;
		  	}
		}
		//make the maximum of class label as the cluster label
		pClusterNode[i]->fCenter[18] = max;
		cout<<"normal = "<<LabelCount[0]<<endl;
		cout<<"dos = "<<LabelCount[2]<<endl;
		cout<<"probe = "<<LabelCount[1]<<endl;
		cout<<"u2r = "<<LabelCount[3]<<endl;
		cout<<"r2l = "<<LabelCount[4]<<endl;

		outfile<<"normal = "<<LabelCount[0]<<endl;
		outfile<<"dos = "<<LabelCount[2]<<endl;
		outfile<<"probe = "<<LabelCount[1]<<endl;
		outfile<<"u2r = "<<LabelCount[3]<<endl;
		outfile<<"r2l = "<<LabelCount[4]<<endl;
	}
	cout<<"********************************************"<<endl;
	outfile<<"*******************************************"<<endl;
}

bool CKMeans::IsClusterOK(int i)
{
	int j,k,sum,max;
	int LabelCount[5];
	float Result;
	feature* pRecord;
	feature_list::iterator ClusterListIter;   
	  
	for(k=0;k < 5;k++)
	{
		LabelCount[k] = 0;
	}

	for(ClusterListIter = m_Cluster[i].MemberList.begin(); ClusterListIter != m_Cluster[i].MemberList.end(); ClusterListIter++)
	{
		 pRecord = (*ClusterListIter);
		 switch(pRecord->iLabel)
		 {
		 	 case 0:
		 	 	LabelCount[0]++;
		 	 	break;
		 	 case 1:
		 	 	LabelCount[1]++;
		 	 	break;
		 	 case 2:
		 	 	LabelCount[2]++;
		 	 	break;
		 	 case 3:
		 	 	LabelCount[3]++;
		 	 	break;
		 	 case 4:
		 	 	LabelCount[4]++;
		 	 	break;
		 	 default:
		 	 	break;
		 }
	}

	for(k=0,max=0;k < 5;k++)
	{
		if(LabelCount[max] < LabelCount[k])
		{
			max = k;
		}
	}
	for(k=0,sum=0;k < 5;k++)
	{
		if(k != max)
			sum += LabelCount[k];
	}
		
	Result = float(sum)/float(LabelCount[max]);	
	pClusterNode[i]->ClusterResult = Result;
				

    if(m_ClusterLevel <= INTERLEVEL)//m_ClusterLevel <= 3
    {
    	if(sum >100)
    	{
    		cout<<sum<<" > 100"<<endl;
    		outfile<<sum<<" > 100"<<endl;
    		return false;
    	}
    	else
    	{
	    	if(Result < CLUSTER_PRECISION)
	    	{
				cout<<0<<" <= "<<Result<<" < "<<CLUSTER_PRECISION<<endl;
				outfile<<0<<" <= "<<Result<<" < "<<CLUSTER_PRECISION<<endl;
				pClusterNode[i]->IsClusterOK = true;
				pClusterNode[i]->IsLeaf = 1;
	    		return true;
	    	}
	    	else
	    	{
				cout<<Result<<" > "<<CLUSTER_PRECISION<<endl;
				outfile<<Result<<" > "<<CLUSTER_PRECISION<<endl;
				pClusterNode[i]->IsClusterOK = false;
	    		return false;
	    	}
        }
    }
    else//m_ClusterLevel > 3
    { 
    	if(sum >500)
    	{
    		cout<<sum<<" > 500"<<endl;
    		outfile<<sum<<" > 500"<<endl;
    		return false;
    	}
    	else
	    {
	    	if(Result < (m_ClusterLevel-INTERLEVEL)*CLUSTER_PRECISION)
	    	{
	    		for(k=1;k <= (m_ClusterLevel-INTERLEVEL);k++)
	    		{
	    			if(Result < k*CLUSTER_PRECISION)
	    			{
						cout<<((k-1)*CLUSTER_PRECISION)<<" <= "<<Result<<" < "<<(k*CLUSTER_PRECISION)<<endl;
						outfile<<((k-1)*CLUSTER_PRECISION)<<" <= "<<Result<<" < "<<(k*CLUSTER_PRECISION)<<endl;
						pClusterNode[i]->IsLeaf = 1;
						pClusterNode[i]->IsClusterOK = true;
				    	return true;   			 	
	    			}
	    		}
	    	}
	    	else
	    	{
			 	cout<<Result<<" > "<<(m_ClusterLevel-INTERLEVEL)*CLUSTER_PRECISION<<endl;
				outfile<<Result<<" > "<<(m_ClusterLevel-INTERLEVEL)*CLUSTER_PRECISION<<endl;
				pClusterNode[i]->IsClusterOK = false;
	    		return false;
	    	}
        }
    }
}

feature_list* CKMeans::GetClusterList(int i)
{
	feature_list* pClustList;
	pClustList = &(m_Cluster[i].MemberList);
	return pClustList;
}

void CKMeans::PrintClusterLabel(int i)
{
	int k;
	int LabelCount[5];
	feature* pRecord;
	feature_list::iterator ClusterListIter;
	cout<<"Cluster "<<m_ClusterLevel<<"."<<i<<endl;
	for(k=0;k < 5;k++)
	{
		LabelCount[k] = 0;
	}

	for(ClusterListIter = m_Cluster[i].MemberList.begin(); ClusterListIter != m_Cluster[i].MemberList.end(); ++ClusterListIter)
	{
		pRecord = (*ClusterListIter);
		switch(pRecord->iLabel)
		{
			case 0:
			 	LabelCount[0]++;
			 	break;
			case 1:
			 	LabelCount[1]++;
			 	break;
			case 2:
			 	LabelCount[2]++;
			 	break;
			case 3:
			 	LabelCount[3]++;
			 	break;
			case 4:
			 	LabelCount[4]++;
			 	break;
			default:
			 	break;
		}
	}
	cout<<"------------------------------"<<endl;
	cout<<"normal = "<<LabelCount[0]<<endl;
	cout<<"dos = "<<LabelCount[2]<<endl;
	cout<<"probe = "<<LabelCount[1]<<endl;
	cout<<"u2r = "<<LabelCount[3]<<endl;
	cout<<"r2l = "<<LabelCount[4]<<endl;	
	
	outfile<<"------------------------------"<<endl;
	outfile<<"normal = "<<LabelCount[0]<<endl;
	outfile<<"dos = "<<LabelCount[2]<<endl;
	outfile<<"probe = "<<LabelCount[1]<<endl;
	outfile<<"u2r = "<<LabelCount[3]<<endl;
	outfile<<"r2l = "<<LabelCount[4]<<endl;
}

int CKMeans::GetDiffLabelofCluster(int i)
{
	int k,DiffLabel;
	int LabelCount[5];
	feature* pRecord;
	feature_list::iterator ClusterListIter;
		
	for(k=0;k < 5;k++)
	{
		LabelCount[k] = 0;
	}
	for(ClusterListIter = m_Cluster[i].MemberList.begin(); ClusterListIter != m_Cluster[i].MemberList.end(); ClusterListIter++)
	{
		pRecord = (*ClusterListIter);
		switch(pRecord->iLabel)
		{
			case 0:
			 	LabelCount[0]++;
			 	break;
			case 1:
			 	LabelCount[1]++;
			 	break;
			case 2:
			 	LabelCount[2]++;
			 	break;
			case 3:
			 	LabelCount[3]++;
			 	break;
			case 4:
			 	LabelCount[4]++;
			 	break;
			default:
			 	break;
		}
	}
	for(k=0,DiffLabel=0;k<5;++k)
	{
		if(LabelCount[k] > 0)
			++DiffLabel;
	}
  return DiffLabel;	
}

bool CKMeans::IsStopRecursion(int i)
{
	int k,DiffLabel,NextLevel,sum,max;
	int LabelCount[5];
	float Result;
	feature* pRecord;
	feature_list::iterator ClusterListIter;
	
	NextLevel = m_ClusterLevel+1;

	if(NextLevel <= INTERLEVEL)//NextLevel <= 3
	{
		pSelfClusterNode->IsLeaf = 0;//not leaf
		return false;
	}
	else//NextLevel > 3
	{
		if(NextLevel <= MAXLEVEL)//NextLevel <= 8
		{
			for(k=0;k < 5;k++)
			{
				LabelCount[k] = 0;
			}
			for(ClusterListIter = m_Cluster[i].MemberList.begin(); ClusterListIter != m_Cluster[i].MemberList.end(); ++ClusterListIter)
			{
				pRecord = (*ClusterListIter);
				switch(pRecord->iLabel)
				{
					case 0:
					 	++LabelCount[0];
					 	break;
					case 1:
					 	++LabelCount[1];
					 	break;
					case 2:
					 	++LabelCount[2];
					 	break;
					case 3:
					 	++LabelCount[3];
					 	break;
					case 4:
					 	++LabelCount[4];
					 	break;
					default:
					 	break;
					}
			}			
			//find the maximum of label
			for(k=0,max=0;k < 5;++k)
		    {
			  	if(LabelCount[max] < LabelCount[k])
			  	{
			  		max = k;
			  	}
			}
			for(k=0,sum=0;k < 5;++k)
			{
				if(k != max)
					sum += LabelCount[k];
			}
			Result = float(sum)/float(LabelCount[max]);

		    if(LabelCount[max] > 200) 
		    {
				pSelfClusterNode->IsLeaf = 0;
				return false;
		    }
			else if(LabelCount[max] > 100 && LabelCount[max] <= 200 && Result > 0.33)
			{
				cout<<"100 < Max Label <=200 and Result = "<<Result<<" > 0.33"<<endl;
				outfile<<"100 < Max Label <=200 and Result = "<<Result<<" > 0.33"<<endl;
				pSelfClusterNode->IsLeaf = 0;
				return false;
			}
			else if(LabelCount[max] > 0 && LabelCount[max] <= 100 && Result > 0.5)
			{
				cout<<"0 < Max Label <=200 and Result = "<<Result<<" > 0.5"<<endl;
				outfile<<"0 < Max Label <=200 and Result = "<<Result<<" > 0.5"<<endl;
				pSelfClusterNode->IsLeaf = 0;
				return false;
			}	
			else
			{
				pSelfClusterNode->IsLeaf = 2;
				return true;
			}
		}
		else
		{
			pSelfClusterNode->IsLeaf = 2;
			return true;
		}	
	}
}

void CKMeans::CreatClusterTreeNode(ClusterNode* pParent)
{
	int i,k;
	for(i=0; i < m_iNumClusters; i++)
	{
		pClusterNode[i] = new ClusterNode();
		for(k=3; k<(m_iNumDimensions-1); k++)
		{
			pClusterNode[i]->fCenter[k] = m_Cluster[i].Center[k];
	    }
		pClusterTree->InsertNode(pParent,pClusterNode[i],i);
  }	
}

//k-means algorithm
void CKMeans::RunKMeans(int Kvalue)
{
	int i;
	int NextKvalue;
	int CircleNum;
	bool IsFinish;
	int NextLevel;
	feature_list* pTmpClustList;
	
	IsFinish = false;
	CircleNum = 0;

	InitClusters(Kvalue);
	//PrintClusters();
	cout<<"Start clustering proccess !"<<endl;
	outfile<<"Start clustering proccess !"<<endl;
	while(!IsFinish)
	{
		++CircleNum;
		//cout<<setiosflags(ios::left)<<"----------- Cirle "<<setw(2)<<CircleNum<<" ------------"<<endl; 
		//outfile<<setiosflags(ios::left)<<"----------- Cirle "<<setw(2)<<CircleNum<<" ------------"<<endl;
		DistributeSamples();
		IsFinish = CalcNewClustCenters();
	}
	cout<<"The Proccess of clustering is finished !"<<endl;
	outfile<<"The Proccess of clustering is finished !"<<endl;
	//PrintClusters();
	cout<<"Print clustering result ...."<<endl;
	outfile<<"Print clustering result ...."<<endl;	
	CreatClusterTreeNode(pSelfClusterNode);
	GetClustersLabel();

	//whether the cluster result is ok
	for(i=0;i < Kvalue;i++)
	{
		cout<<"Check Kmeans"<<m_KmeansID<<" Cluster"<<i<<endl;
		outfile<<"Check Kmeans"<<m_KmeansID<<" Cluster"<<i<<endl;
		
		if(IsClusterOK(i))
		{
			cout<<"Level"<<m_ClusterLevel<<" Kmeans"<<m_KmeansID<<" Cluster"<<i<<" OK !"<<endl;
			cout<<"------------------------------"<<endl;
			
			outfile<<"Level"<<m_ClusterLevel<<" Kmeans"<<m_KmeansID<<" Cluster"<<i<<" OK !"<<endl;
			outfile<<"------------------------------"<<endl;			
		}
		else
		{
			cout<<"Level"<<m_ClusterLevel<<" Kmeans"<<m_KmeansID<<" Cluster"<<i<<" need go on !"<<endl;
			outfile<<"Level"<<m_ClusterLevel<<" Kmeans"<<m_KmeansID<<" Cluster"<<i<<" need go on !"<<endl;			
			PrintClusterLabel(i);
			NextKvalue = GetDiffLabelofCluster(i);
			cout<<"------------------------------"<<endl;	
			cout<<"Set K = "<<NextKvalue<<endl;
			outfile<<"------------------------------"<<endl;	
			outfile<<"Set K = "<<NextKvalue<<endl;

			if(!IsStopRecursion(i))     
			{
				pTmpClustList = GetClusterList(i);
				NextLevel = m_ClusterLevel+1;
				CKMeans* pKMeans;
				pKMeans = new CKMeans(pClusterNode[i],pClusterTree,++KmeansID,NextLevel,19,pTmpClustList);
				pKMeans->RunKMeans(NextKvalue);		
			}
			else
			{
				cout<<"------------------------------"<<endl;	
				cout<<"Stop Recursion! Go back !"<<endl;
				outfile<<"------------------------------"<<endl;
				outfile<<"Stop Recursion! Go back !"<<endl;
			}
		}
	}
}
