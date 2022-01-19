
// Created by Amarjot Gill 10/1/2021
#include "graph.h"
const int NEGATIVE_ONE = -1;
const int ZERO = 0;

// O(1)
Graph::Graph(){
    m_head = nullptr;
    m_numNodes = ZERO;
    m_dataFile = "";
}

// O(1)
Graph::Graph(string dataFile){
    m_head = nullptr;
    m_numNodes = ZERO;
    m_dataFile = dataFile;
    loadData();
}

// O(N)
Graph::~Graph(){
    // case if graph is empty cant delete anything
    if(m_head == nullptr){
        return;
    }
    Node* current = m_head;
    while(current -> getNext() != nullptr){
        current = current -> getNext();
        // deletes the node
        delete m_head;
        m_head = current;
    }
    delete m_head;
    m_head = nullptr;
}

//O(N)
void Graph::loadData(){
    int numNodes;
    int node, n, e, s, w; 
    ifstream dataFile;
    dataFile.open(m_dataFile);
    if (dataFile.is_open()) {
        dataFile >> numNodes;
        m_numNodes = numNodes;
        for (int i = 0; i < numNodes; i++) {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open
        //please note: not all platforms are providing the same message
        cerr << "Error: " << strerror(errno) << endl;
}

// O(N^2)
void Graph::insert(int node, int n, int e, int s, int w){
    // This is for the case of the graph being empty and this is the first value being added to the graph
    if(m_head == nullptr){
        m_numNodes++;
        Node *newNode = new Node(node);
        m_head = newNode;
        if(n > NEGATIVE_ONE){
            // since head was nullptr for this case none of these 
            //nodes were created so all within this case will be created
            Node *newNode = new Node(n);
            m_head -> setNorth(newNode);
            m_head -> setNext(newNode);
            m_numNodes++;
        }if(e > NEGATIVE_ONE){
            Node *newNode = new Node(e);
            m_head -> setEast(newNode);
            insertAtHead(newNode);
        }if(s > NEGATIVE_ONE){
            Node *newNode = new Node(s);
            m_head -> setSouth(newNode);
            insertAtHead(newNode);
        }if(w > NEGATIVE_ONE){
            Node *newNode = new Node(w);
            m_head -> setWest(newNode);
            insertAtHead(newNode);
        }
    }else{
        // bool to keep track if a node is already created or not
        bool inList = false;
        Node* temp = m_head;
        // while loop to check if node is created already or not
        while(temp -> getNext() != nullptr){
            temp = temp -> getNext();
            if(temp -> getValue() == node){
                inList = true;
            }
        }
        // if node wasnt found it is created and added to end of linked list
        if(inList == false){
            Node* newNode = new Node(node);
            temp -> setNext(newNode);
            m_numNodes++;
        }
        // checking for > -1 bc -1 is case of no connection
        if(n > NEGATIVE_ONE){
            inList = false;
            Node* temp = m_head;
            Node* insertedNode;
            // first while loop to check if node with value n is already made
            while(temp -> getNext() != nullptr){
                temp = temp -> getNext();
                if(temp -> getValue() == node){
                    // creates a second temp to search through too see if node with value n is in list
                    Node* secTemp = m_head;
                    while(secTemp != nullptr){
                        if(secTemp -> getValue() == n){
                            // if it is found sets Node's north to node with value n
                            temp -> setNorth(secTemp); 
                            inList = true;
                        }
                        secTemp = secTemp -> getNext();
                    }
                    // if node with value n isnt in list then creates and sets main Node north to it
                    if(inList == false){
                        Node* newNode = new Node(n);
                        temp -> setNorth(newNode);
                        insertedNode = newNode;
                    }
                }
            }
            // if node N wasnt in list then it gets added to the end of the linked list
            if(inList == false){
                temp -> setNext(insertedNode);
                m_numNodes++;
            }
        // Other 3 connections work exactly the same as North
        }if(e > NEGATIVE_ONE){
            inList = false;
            Node* temp = m_head;
            Node* insertedNode;
            while(temp -> getNext() != nullptr){
                temp = temp -> getNext();
                if(temp -> getValue() == node){
                    Node* secTemp = m_head;
                    
                    while(secTemp  != nullptr){
                        if(secTemp -> getValue() == e){
                            temp -> setEast(secTemp); 
                            inList = true;
                        }
                        secTemp = secTemp -> getNext();
                        
                    }
                    if(inList == false){
                        Node* newNode = new Node(e);
                        temp -> setEast(newNode);
                        insertedNode = newNode;
                    }
                }
            }
            if(inList == false){
                temp -> setNext(insertedNode);
                m_numNodes++;
            }

        }if(s > NEGATIVE_ONE){
           inList = false;
            Node* temp = m_head;
            Node* insertedNode;
            while(temp -> getNext() != nullptr){
                temp = temp -> getNext();
                if(temp -> getValue() == node){
                    Node* secTemp = m_head;
                    while(secTemp != nullptr){
                        if(secTemp -> getValue() == s){
                            temp -> setSouth(secTemp); 
                            inList = true;
                        }
                        secTemp = secTemp -> getNext();
                    }
                    if(inList == false){
                        Node* newNode = new Node(s);
                        temp -> setSouth(newNode);
                        insertedNode = newNode;
                    }
                }
            }
            if(inList == false){
                temp -> setNext(insertedNode);
                m_numNodes++;
            }

        }if(w > NEGATIVE_ONE){
            inList = false;
            Node* temp = m_head;
            Node* insertedNode;
            while(temp -> getNext() != nullptr){
                temp = temp -> getNext();
                if(temp -> getValue() == node){
                    Node* secTemp = m_head;
                    while(secTemp != nullptr){
                        if(secTemp -> getValue() == w){
                            temp -> setWest(secTemp); 
                            inList = true;
                        }
                        secTemp = secTemp -> getNext();
                    }
                    if(inList == false){
                        Node* newNode = new Node(w);
                        temp -> setWest(newNode);
                        insertedNode = newNode;
                    }
                }
            }
            if(inList == false){
                if(temp -> getValue() != insertedNode -> getValue()){
                    temp -> setNext(insertedNode);
                    m_numNodes++;
                }
            }
        }
    }
}

// O(N)
void Graph::insertAtHead(Node * aNode){
    if(m_head == nullptr){
        m_head = aNode;
    }else{
        Node* temp = m_head;
            while(temp -> getNext() != nullptr){
                temp = temp -> getNext();
            }
            // sets last node to node to be inserted
            temp -> setNext(aNode);
            m_numNodes++;
    } 
}

// O(N)
Node * Graph::findNode(int nodeValue){
    if(empty()){
        return m_head;
    }else{
        Node* temp = m_head;
        while(temp != nullptr){
            // once node with value is found its returned
            if(temp -> getValue() == nodeValue){
                return temp;
            }
            temp = temp -> getNext();
        }
    }
    return nullptr;
}

//O(M + N)
bool Graph::findPath(int start, int end){
    Node* temp = findNode(start);
    Node* secTemp = findNode(end);
    // error case, start or end node are not in graph
    if(temp == nullptr || secTemp == nullptr){
        throw std::out_of_range("Out of range error!");
        return false;
    }
    // error case start or end node are negative
    if(start < ZERO || end < ZERO){
        throw std::out_of_range("Out of range error!");
        return false;
    }
    // error case list is empty
    if(empty()){
        throw std::out_of_range("Graph is empty");
        return false;
    }
    // case if you are searching for path to itself
    if(start == end){
        m_path.push(end);
        return true;
    }else{
        Node* temp = m_head;
        while(temp != nullptr){
            if (temp -> getValue() == start){
                    // clears results and visted for obj before finding a new path
                    clearResult();
                    clearVisited();
                    return findPath(temp, end);
            }else{
                temp = temp -> getNext();
            }
        }
    }
    return false;
}

//O(M + N)
bool Graph::findPath(Node* aNode, int end){
    // if first time visiting pushes node to stack and sets visited
    if(aNode -> getVisited() == false){
         m_path.push(aNode -> getValue());
        aNode -> setVisited(true);
    }
    if(aNode -> getValue() == end){
        return true;
    // calling a depth first search starting from north and ending at west to find value
    }else if(aNode -> getNorth() != nullptr && aNode -> getNorth() -> getVisited() == false){
        return findPath(aNode -> getNorth(), end);
    }else if(aNode -> getEast() != nullptr && aNode -> getEast() -> getVisited() == false){
       return findPath(aNode -> getEast(),end);
    }else if(aNode -> getSouth() != nullptr && aNode -> getSouth() -> getVisited() == false){
       return findPath(aNode -> getSouth(), end);
    }else if(aNode -> getWest() != nullptr && aNode -> getWest() -> getVisited() == false){
       return findPath(aNode -> getWest(), end);
    }if (m_path.empty()){
        return false;
    }else{
        m_path.pop();
        // prevents a seg fault and infinite loop
       if(m_path.empty()){
           return false;
       }
       // backtracking if reached node with no connections
        Node* temp = findNode(m_path.top());
        return findPath(temp, end);
    }
    return false;
}

//O(N)
void Graph::dump(){
    if(m_head == nullptr){
        cout << "END" << endl;
        return;
    }
    // printing in a first in first out style needs a temp stack
    stack<int> temp;
    while(!m_path.empty()){
        temp.push(m_path.top());
        m_path.pop();
    }

    while(!temp.empty()){
        cout<< temp.top() << " => ";
        temp.pop();
    }
    cout<<"END "<< endl;
}

//O(N)
void Graph::clearResult(){
    // popping stack to clear it
    while(!m_path.empty()) {
        m_path.pop();
    }
    
}

//O(N)
void Graph::clearVisited(){
    // setting all node's visited in list to false
    if(m_head == nullptr){
        return;
    }else{
        Node *temp = m_head;
        temp -> setVisited(false);
        while(temp -> getNext() != nullptr){
            temp = temp -> getNext();
            temp -> setVisited(false);
        }
    }
    
}

//O(N)
void Graph::buildGraph(string file){
    // if the graph is populated clear it
    if(m_head != nullptr){
        clearVisited();
        clearResult();
        clearGraph();
    }
    int numNodes;
    int node, n, e, s, w; 
    ifstream dataFile;
    dataFile.open(file);
    if (dataFile.is_open()) {
        dataFile >> numNodes;
        m_numNodes = numNodes;
        for (int i = 0; i < numNodes; i++) {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open
        //please note: not all platforms are providing the same message
        cerr << "Error: " << strerror(errno) << endl;
    
}

//O(N)
void Graph::clearGraph(){
    // Works same way as destructor
    if(m_head == nullptr){
        return;
    }
    Node* current = m_head;
    while(current -> getNext() != nullptr){
        current = current -> getNext();
        // deletes the node
        delete m_head;
        m_head = current;
    }
    delete m_head;
    m_head = nullptr;
    m_numNodes = ZERO;
    m_dataFile = "";
}

//O(N)
const Graph & Graph::operator=(const Graph & rhs){
    // if given an empty Graph to assign
    if(rhs.m_head == nullptr){
        throw std::out_of_range("Can not assign an empty graph");
        return *this;
    }
    // clear current Graph if its populated
    // protects against self assignment
    if(m_head != rhs.m_head){
        if(m_head != nullptr){
            clearResult();
            clearVisited();
            clearGraph();
        }
        Node *temp = rhs.m_head;
        // Checks if currect node has connections and then calls insert function to insert them
        while(temp != nullptr){
            int n = NEGATIVE_ONE;
            int e = NEGATIVE_ONE;
            int w = NEGATIVE_ONE;
            int s = NEGATIVE_ONE;
            if(temp -> getNorth() != nullptr){
                n = temp -> getNorth() -> getValue();
            }if(temp -> getEast() != nullptr){
                e = temp -> getEast() -> getValue();
            }if(temp -> getSouth() != nullptr){
                s = temp -> getSouth() -> getValue();
            }if(temp -> getWest() != nullptr){
                w = temp -> getWest() -> getValue();
            }
            insert(temp -> getValue(),n,e,s,w);
            temp = temp -> getNext();
        }
    }else{
       throw std::out_of_range("Self Assignment dectected");
    }
     return *this; 
}

//O(1)
bool Graph::empty() const		// is the list empty?
    { return m_head == nullptr; }
