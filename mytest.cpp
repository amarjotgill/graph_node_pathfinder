//
//  mytest.cpp
//  Project 1 
//
//  Created by Amarjot Gill 9/28/2021
// test program for testing edge, error cases, and assignment opertator for graph class

#include "graph.h"
const string TESTFILE = "testdata.txt";

class Tester{ // Tester class to implement test functions
    public:
    bool testAssignment(Graph& rhs, Graph& cGraph);
};

int main(){
    Tester testObj;
    Graph aGraph(TESTFILE);
    cout << "TESTING A NORMAL CASE" << endl;
    try{
        aGraph.findPath(1,15);
        cout << "Finding the path from node 1 to node 15: " << endl;
        aGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }
    cout << endl;
     cout << "TESTING A CASE WHERE START NODE DOES NOT EXIST" << endl;
    try{
        aGraph.findPath(20,15);
        cout << "Finding the path from node 20 to node 15: " << endl;
        aGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }

    cout << endl;
     cout << "TESTING A CASE END NODE DOES NOT EXIST" << endl;
    try{
        aGraph.findPath(1,20);
        cout << "Finding the path from node 1 to node 15: " << endl;
        aGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }

    cout << endl;
    cout << "TESTING A CASE FOR FINDING NODE TO ITSELF" << endl;
    try{
        aGraph.findPath(2,2);
        cout << "Finding the path from node 2 to itself: " << endl;
        aGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }
    
    cout << endl;
    cout << "TESTING CASE WHERE PATH DOES NOT EXIST" << endl;
    try{
        aGraph.findPath(3,0);
        cout << "Finding the path from node 3 to node 0: " << endl;
        aGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }
    
    cout << endl;
    Graph bGraph;
    cout << "TESTING CASE OF TRYING TO FIND PATH IN EMPTY GRAPH" << endl;
    cout << "Finding the path from node 0 to node 12 in an empty Graph object: " << endl;
    try{
        bGraph.findPath(1,14);
        bGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }

    cout << endl;
    cout << "BUILDING EMPTY GRAPH USING BUILDGRAPH FUNCTION AND TRYING TO FIND PATH" << endl;
    bGraph.buildGraph(TESTFILE);
    try{
        cout << "Finding the path from node 0 to node 12 in new Graph" << endl;
        bGraph.findPath(0,12);
        bGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }
    cout << endl;
    Graph cGraph;
    
    cout << "TESTING ASSIGNMENT OPERATOR FUNCTION" << endl;
    try{
        if(testObj.testAssignment(bGraph,cGraph)){
        cout << "Assignment passed deep copy made!" << endl;
         }else{
            cout << "Assignment failed!" << endl;
        }
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }
    cout << endl;
    
    cout << "TESTING SELF ASSIGNMENT IN ASSIGNMENT OPERATOR FUNCTION" << endl;
    try{
        if(testObj.testAssignment(cGraph,cGraph)){
        cout << "Assignment passed deep copy made!" << endl;
         }else{
            cout << "Assignment failed!" << endl;
        }
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }

    cout << endl;

    cout << "FINDING PATH FROM 0 to 12 IN NEW ASSIGNED GRAPH" << endl;
     try{
        cout << "Finding the path from node 0 to node 12 in new Graph" << endl;
        cGraph.findPath(0,12);
        cGraph.dump();
    }catch(std::out_of_range const &e){
        cout << e.what() << endl;
    }
    cout << endl;


    return 0;
}

bool Tester::testAssignment(Graph& rhs, Graph& cGraph){
    cGraph = rhs;
    rhs.clearGraph();
    if(cGraph.empty()){
        return false;
    }else{
        return true;
    }
}