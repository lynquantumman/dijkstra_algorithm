/*Dijkstra algorithm
@desc This algorithm uses Dijkstra algorithm to search the shortest path from a known source to a known end.
@input directed graph written in Topology_net_input.txt and the left column is the source of a vector and
 the right column is the end of a vector;
@writer Quantumman*/
#include<iostream>
#include<memory>
#include<vector>
#include<fstream>
#include<limits>
using std::vector;
const int NUMNODE=6;//the start node number in the graph
const int OUT=0;
const int IN=1;


#include"AdjacencyList.cpp"//I use the Adjacency List to deal with the graph.
using namespace std;
//==================================================================
int min(const vector<VertexNode>& headOfList){
	int i=0, j, smallest;
	while(headOfList[i].nodeState==IN){//first we select a node with OUT nodeState
		i++;
	}
	smallest=i;
	i++;//compare that node with the next one
	for(;i!=NUMNODE;i++){
		if(headOfList[i].nodeState==OUT){
		smallest=headOfList[smallest].distance2S<headOfList[i].distance2S?smallest:i;
		}
	}
	return smallest;
}
//=======================================================================

int main(){
	ifstream loadNet("Topology_net_input.txt");
	vector<VertexNode> headOfList(NUMNODE);//This is the head of the list
	int col_1, col_2,col_3;//used below as the num
	while(loadNet>>col_1){//This is a directed graph with the first column points to the second column
		//===the code below uses smart pointer to insert the right column 
		//to the the headOfList specified by the first 
		loadNet>>col_2;
		loadNet>>col_3;
		headOfList[col_1].numberOfNode=col_1;
		//shared_ptr<EdgeNode> toEdgeNode=make_shared<EdgeNode>();//when while-part finishes, the newly applied memory will be destructed.
		EdgeNode* toEdgeNode=new EdgeNode;//This needs to be destructed.
		toEdgeNode->adjacentVertex=col_2;
		toEdgeNode->length=col_3;
		headOfList[col_1].insert(*toEdgeNode);

		//===============================================
	}
/*===this part is test code.
	cout<<"Here is the numberOfNode of vertex"<<headOfList[2].numberOfNode<<endl;//test code
	EdgeNode* next=headOfList[2].firstEdge;
	cout<<"here is the AdjacencyList of vertex"<<endl;
	while(next){
		cout<<next->adjacentVertex<<endl;
		next=next->next;
	}
*/

	//the code above is the construction of a graph in Adjacency List.
	//the code below uses the Dijkstra algorithm to search the shortest path to certain end.

	//====There are 2 ways to update the distance2S
	//if the vertex belongs to the searched set, the distance2S is itself
	//else the distance2S = the distance2S of the new member of that set + the distance between the new member
	//and that vertex which is gonna be in the searched set.
	//choose the shortest edgenode to be in the searched set.
	unsigned source,end;
	cout<<"Please input the source vertex."<<endl;
	cin>>source;//people input the source node here.
	cout<<"Please input the end vertex."<<endl;
	cin>>end;
	headOfList[source].nodeState=IN;
	headOfList[source].pathFromS.push_back(source);
	EdgeNode* next;
	next=headOfList[source].firstEdge;
	while(next){
		headOfList[next->adjacentVertex].distance2S=next->length;//每一个这个产生的时候，都应该有一个path
		headOfList[next->adjacentVertex].pathFromS=headOfList[source].pathFromS;//copy the path of source to adjvertex
		headOfList[next->adjacentVertex].pathFromS.push_back(next->adjacentVertex);
		next=next->next;
	}//set the source and set the neighbors of source distance2S;
	while(headOfList[end].nodeState==OUT){
		int i;
		int minNode;
		minNode=min(headOfList);
		headOfList[minNode].nodeState=IN;//choose the one with the smallest distance2S in the set in which the nodeState=OUT

		next=headOfList[minNode].firstEdge;
		while(next){
			//code in if block is when the newly-being-in node brings the shorter distance2S 
			if(headOfList[next->adjacentVertex].distance2S>(headOfList[minNode].distance2S+next->length)){
				//the update of the distance2S
				headOfList[next->adjacentVertex].distance2S=headOfList[minNode].distance2S+next->length;
				//the update of the pathFromS
				headOfList[next->adjacentVertex].pathFromS=headOfList[minNode].pathFromS;
				headOfList[next->adjacentVertex].pathFromS.push_back(next->adjacentVertex);
			}//===the update of the distance2S and pathFromS must be done simultaneously.
			next=next->next;
		}
	}
		//change the nodeState and the pathFromS
	
	for(auto i:(headOfList[end].pathFromS)){
		cout<<i<<" ";
	}
	

	for(auto& i:headOfList){//the destruction of the graph
		EdgeNode* next;
		next=i.firstEdge;
		while(next){
			EdgeNode* temp;
			temp=next->next;
			delete next;
			next=temp;
		}
	}

	system("pause");
}
