/*
@desc This is a class about the head node in adjacency-List representation
@writer quantumman
*/
#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST
#include<vector>
#include<iostream>
#include<fstream>
#include<limits>
using std::vector;

class EdgeNode//the node linked by a vector
{
public:
	int adjacentVertex;//the number of node
	double length;
	EdgeNode *next;//pointer to next
	EdgeNode();//constructor;
};
EdgeNode::EdgeNode(){//the number of node is set to -1
	adjacentVertex = -1;
	length=0.0;
	next = NULL;
};

class VertexNode{//the node considered to be the head of a list
public:
	VertexNode();
	int numberOfNode;  //节点在系统中的编号
	int distance2S;//节点相对于s的距离,除s外，初始化为-1
	int nodeState;//用来标记节点状态值:1- -1未连接时的初始态；0-连接后初始态；1- -1连接后的故障态；
	EdgeNode *firstEdge; //指向第一个边节点
	vector<int> pathFromS;
	//float degreeIn;  //节点度
	//float degreeOut;
	bool insert(EdgeNode& i);
};

VertexNode::VertexNode(){
	numberOfNode = -1;  //节点编号
	distance2S = INT_MAX;//节点相对于s的距离,除s外，初始化为-1
	nodeState = OUT;//用来标记节点状态值
	firstEdge = NULL; //指向第一个边节点
	//degreeIn=0;
	//degreeOut=0;
	
};

bool VertexNode::insert(EdgeNode& neededInsert){
	if(firstEdge==NULL){//give the firstEdge the address of a new edgenode i
		firstEdge=&neededInsert;
	}
	else{
		neededInsert.next=firstEdge;//give the value of firstedge to the new edgenode
		firstEdge=&neededInsert;//give the the address of a new edgenode i to the firstedge
	}
	return 0;
}
#endif
