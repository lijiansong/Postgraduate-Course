#include "utils.h"

extern ofstream outfile;

//cluster node
class ClusterNode
{
public:
	ClusterNode()
	{
		int i;
		pParentNode = NULL;
		for(i=0;i < MAXLABEL;i++)
		{
			pChildNode[i] = NULL;
			iLabelNum[i] = 0;
		}
		for(i=0;i<MAXDIMENSION;i++)
		{
			fCenter[i] = 0;
		}
		ClusterResult = 0;
		IsClusterOK = false;//not ok
		IsLeaf = 0;//not a leaf
	};
	
	float CalCenterDistance(feature* pRecord);
	ClusterNode* GetChildNode(int i);
	int GetClusterNodeLabel();
	ClusterNode* GetNearestCluster(feature* pRecord);

	//output
	void Print();
	void PrintLog();

public:
	//cluster center
	float fCenter[MAXDIMENSION];
	//cluster path
	string strPath;
	ClusterNode* pParentNode;
	ClusterNode* pChildNode[MAXLABEL];
	float ClusterResult;
	bool IsClusterOK;
	//is leaf node or not and normally finished
	//0:not a leaf node; 1:leaf node and normally exit; 2:leaf node and exit normally
	int IsLeaf;
	int iLabelNum[MAXLABEL];
};

class ClusterTree
{
public:
	ClusterTree()
	{
		pRootNode = new ClusterNode();
		pRootNode->strPath = "0";
	}
	//insert node
	void InsertNode(ClusterNode* pParent,ClusterNode* pNode,int i);
	//find nearest cluster to pRecord
	ClusterNode* FindNearestCluster(feature* pRecord);
	ClusterNode* GetRootNode();	

	//output
	void Print();
	void PrintLog();
	
private:
	ClusterNode* pRootNode;
};
