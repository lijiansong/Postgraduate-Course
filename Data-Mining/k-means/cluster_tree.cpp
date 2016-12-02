#include "cluster_tree.h"

string intToString(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}

//calculate the distance to centroid
float ClusterNode::CalCenterDistance(feature* pRecord)
{
	double fDist;
	fDist = 0;
	/*
	fDist += pow((pRecord->fProtocolType - fCenter[0]), 2);
	fDist += pow((pRecord->fService - fCenter[1]), 2);
	fDist += pow((pRecord->fStatusFlag - fCenter[2]), 2);
	*/
	fDist += pow((pRecord->fSrcBytes - fCenter[3]), 2);
	fDist += pow((pRecord->fDestBytes - fCenter[4]), 2);
	fDist += pow((pRecord->fFailedLogins - fCenter[5]), 2);
	fDist += pow((pRecord->fNumofRoot - fCenter[6]), 2);
	fDist += pow((pRecord->fCount - fCenter[7]), 2);
	fDist += pow((pRecord->fSrvCount - fCenter[8]), 2);
	fDist += pow((pRecord->fRerrorRate - fCenter[9]), 2);
	fDist += pow((pRecord->fSameSrvRate - fCenter[10]), 2);
	fDist += pow((pRecord->fDiffSrvRate - fCenter[11]), 2);
	fDist += pow((pRecord->fDstHostSrvCount - fCenter[12]), 2);
	fDist += pow((pRecord->fDstHostSameSrvRate - fCenter[13]), 2);
	fDist += pow((pRecord->fDstHostDiffSrvRate - fCenter[14]), 2);
	fDist += pow((pRecord->fDstHostSameSrcPortRate - fCenter[15]), 2);
	fDist += pow((pRecord->fDstHostSrvDiffHostRate - fCenter[16]), 2);
	fDist += pow((pRecord->fDstHostSrvSerrorRate - fCenter[17]), 2);

	return float(fDist);	
}

ClusterNode* ClusterNode::GetChildNode(int i)
{
	return pChildNode[i];
}

int ClusterNode::GetClusterNodeLabel()
{
	return int(fCenter[18]);
}

ClusterNode* ClusterNode::GetNearestCluster(feature* pRecord)
{
	//cout<<"In the GetNearestCluster"<<endl;
	//cout<<"Path = "<<strPath<<endl;
	//outfile<<"Path = "<<strPath<<endl;
	int i;
	float MinDistance,TmpDistance;
	ClusterNode* pNearestNode;
	ClusterNode* pTmpNode;
	if(IsLeaf > 0)
	{
		pNearestNode = this;
    }
	else
	{
		pNearestNode = this;
		MinDistance = CalCenterDistance(pRecord);
		for(i=0;i<MAXLABEL;i++)
		{
			if(pChildNode[i] != NULL)
			{
				pTmpNode = pChildNode[i]->GetNearestCluster(pRecord);
			}
			TmpDistance = pTmpNode->CalCenterDistance(pRecord);
			if(TmpDistance < MinDistance)
			{
				pNearestNode = pTmpNode;
				MinDistance = TmpDistance;
			}
		}
    }
	return pNearestNode;
}

void ClusterNode::Print()
{
	int i;
	
	cout<<"Cluster "<<strPath<<endl;
	/*
	cout<<"fProtocolType = "<<fCenter[0]<<endl;
	cout<<"fService = "<<fCenter[1]<<endl;
	cout<<"fStatusFlag = "<<fCenter[2]<<endl;
	*/
	cout<<"------------------ Center Information -----------------"<<endl;
	cout<<"fSrcBytes = "<<fCenter[3]<<endl;
	cout<<"fDestBytes = "<<fCenter[4]<<endl;
	cout<<"fFailedLogins = "<<fCenter[5]<<endl;
	cout<<"fNumofRoot = "<<fCenter[6]<<endl;
	cout<<"fCount = "<<fCenter[7]<<endl;
	cout<<"fSrvCount = "<<fCenter[8]<<endl;
	cout<<"fRerrorRate = "<<fCenter[9]<<endl;
	cout<<"fSameSrvRate = "<<fCenter[10]<<endl;
	cout<<"fDiffSrvRate = "<<fCenter[11]<<endl;
	cout<<"fDstHostSrvCount = "<<fCenter[12]<<endl; 
	cout<<"fDstHostSameSrvRate = "<<fCenter[13]<<endl;
	cout<<"fDstHostDiffSrvRate = "<<fCenter[14]<<endl;
	cout<<"fDstHostSameSrcPortRate = "<<fCenter[15]<<endl;
	cout<<"fDstHostSrvDiffHostRate = "<<fCenter[16]<<endl;
	cout<<"fDstHostSrvSerrorRate = "<<fCenter[17]<<endl;
	cout<<"iLabel = "<<fCenter[18]<<endl;
	cout<<"--------------------- Cluster Param ---------------------"<<endl;
	cout<<"IsClusterOK = "<<IsClusterOK<<endl;
	cout<<"IsLeaf = "<<IsLeaf<<endl;
	cout<<"ClusterResult = "<<ClusterResult<<endl;
	cout<<"---------------------- Label Number ---------------------"<<endl;
	cout<<"normal = "<<iLabelNum[0]<<endl;
	cout<<"dos = "<<iLabelNum[2]<<endl;
	cout<<"probe = "<<iLabelNum[1]<<endl;
	cout<<"u2r = "<<iLabelNum[3]<<endl;
	cout<<"r2l = "<<iLabelNum[4]<<endl;
	cout<<"============================================================"<<endl;	
	
	for(i=0;i<MAXLABEL;i++)
	{
		if(pChildNode[i] != NULL)
		{
			pChildNode[i]->Print();
		}
	}
}

void ClusterNode::PrintLog()
{
	int i;
	
	outfile<<"Cluster "<<strPath<<endl;
	/*
	outfile<<"fProtocolType = "<<fCenter[0]<<endl;
	outfile<<"fService = "<<fCenter[1]<<endl;
	outfile<<"fStatusFlag = "<<fCenter[2]<<endl;
	*/
	outfile<<"------------------ Center Information -----------------"<<endl;
	outfile<<"fSrcBytes = "<<fCenter[3]<<endl;
	outfile<<"fDestBytes = "<<fCenter[4]<<endl;
	outfile<<"fFailedLogins = "<<fCenter[5]<<endl;
	outfile<<"fNumofRoot = "<<fCenter[6]<<endl;
	outfile<<"fCount = "<<fCenter[7]<<endl;
	outfile<<"fSrvCount = "<<fCenter[8]<<endl;
	outfile<<"fRerrorRate = "<<fCenter[9]<<endl;
	outfile<<"fSameSrvRate = "<<fCenter[10]<<endl;
	outfile<<"fDiffSrvRate = "<<fCenter[11]<<endl;
	outfile<<"fDstHostSrvCount = "<<fCenter[12]<<endl; 
	outfile<<"fDstHostSameSrvRate = "<<fCenter[13]<<endl;
	outfile<<"fDstHostDiffSrvRate = "<<fCenter[14]<<endl;
	outfile<<"fDstHostSameSrcPortRate = "<<fCenter[15]<<endl;
	outfile<<"fDstHostSrvDiffHostRate = "<<fCenter[16]<<endl;
	outfile<<"fDstHostSrvSerrorRate = "<<fCenter[17]<<endl;
	outfile<<"iLabel = "<<fCenter[18]<<endl;
	outfile<<"IsClusterOK = "<<IsClusterOK<<endl;
	outfile<<"IsLeaf = "<<IsLeaf<<endl;
	outfile<<"---------------------- Label Number ---------------------"<<endl;
	outfile<<"normal = "<<iLabelNum[0]<<endl;
	outfile<<"dos = "<<iLabelNum[2]<<endl;
	outfile<<"probe = "<<iLabelNum[1]<<endl;
	outfile<<"u2r = "<<iLabelNum[3]<<endl;
	outfile<<"r2l = "<<iLabelNum[4]<<endl;
	outfile<<"============================================================"<<endl;	
	
	for(i=0;i<MAXLABEL;i++)
	{
		if(pChildNode[i] != NULL)
		{
			pChildNode[i]->PrintLog();
		}
	}
}

ClusterNode* ClusterTree::GetRootNode()
{
	return pRootNode;
}

void ClusterTree::InsertNode(ClusterNode* pParent,ClusterNode* pNode,int i)
{
	string strTmp1, strTmp2;
	pNode->pParentNode = pParent;
	pParent->pChildNode[i] = pNode;
	strTmp1 = pParent->strPath;
	strTmp2 = intToString(i);
	strTmp1 += ".";
	strTmp1 += strTmp2;
	pNode->strPath = strTmp1;
}

ClusterNode* ClusterTree::FindNearestCluster(feature* pRecord)
{
	ClusterNode* pNearestNode;
  pNearestNode = pRootNode->GetNearestCluster(pRecord);
	return pNearestNode;
}

void ClusterTree::Print()
{
	cout<<"Start printing ClusterTree ..."<<endl;
	outfile<<"Start printing ClusterTree ..."<<endl;
	pRootNode->Print();
	cout<<"Printing ClusterTree finished !"<<endl;
	outfile<<"Printing ClusterTree finished !"<<endl;
}

void ClusterTree::PrintLog()
{
	cout<<"Start printing ClusterTree in Log ..."<<endl;
	outfile<<"Start printing ClusterTree in Log ..."<<endl;
	pRootNode->PrintLog();
	cout<<"Printing ClusterTree in Log finished !"<<endl;
	outfile<<"Printing ClusterTree in Log finished !"<<endl;
}
