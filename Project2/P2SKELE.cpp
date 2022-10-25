#include <vector>
#include <iostream>
#include <string> 
#include <algorithm> //for transform
#include <queue> 
using namespace std;

class PQueueNode {
public:
    //flight properties
    int id;
    bool emergency;
    int time_arrival;
    int priority;
    bool takeoff; // if takeoff then true, if landing then false;

    //AVL tree node properties
    int height;
    int balanceFactor;

    PQueueNode* left;
    PQueueNode* right;
    PQueueNode* parent; // you are not required to update parent nodes but you may use them if you want

    //no default constructor!
    PQueueNode(int fid, bool fe, int ft, int fp, bool tk) {
        //initializing flight properties
        id = fid; 
        emergency = fe; 
        time_arrival = ft; 
        priority = fp; 
        takeoff = tk;
        //initializing avl node properties
        height = 0; 
        balanceFactor = 0; 
    }

    //comparison between the "this" pnode with another pnode, note: there is no "equal" relationship between two pnodes!
    bool biggerThan(PQueueNode* p) {

    }
};


class PQueue {
private:
    PQueueNode* root;
    int size;

    PQueueNode* search(PQueueNode* sub_tree_root, PQueueNode* target) {
    };

    PQueueNode* minimum(PQueueNode* sub_tree_root, PQueueNode* target) {
    };
    PQueueNode* maximum(PQueueNode* sub_tree_root, PQueueNode* target) {
    };

    PQueueNode* insertValue(PQueueNode* sub_tree_root, PQueueNode* target);
    PQueueNode* deleteValue(PQueueNode* sub_tree_root, PQueueNode* target);

    PQueueNode* rebalance(PQueueNode* ynode);
    PQueueNode* rotateLeft(PQueueNode* ynode);
    PQueueNode* rotateRight(PQueueNode* ynode);
    PQueueNode* rotateLeftRight(PQueueNode* ynode);
    PQueueNode* rotateRightLeft(PQueueNode* ynode);
public:
    PQueue() {
        root = nullptr;
        size = 0;
    }

    PQueueNode* getRoot() {
        return root;
    }

    int getSize() {
        return size;
    }

    PQueueNode* search(PQueueNode* target);

    PQueueNode* minimum();
    PQueueNode* maximum();  
    PQueueNode* emergency();  //return the first/highest priority emergency node; 
    void timeorder(int timestep); // update emergency value based on timestep; 
    void insertValue(PQueueNode* target);
    void deleteValue(PQueueNode * target);

    void preOrder(PQueueNode*, vector<PQueueNode*>&);
    void inOrder(PQueueNode*, vector<PQueueNode*>&);
    void postOrder(PQueueNode*, vector<PQueueNode*>&);
};

class minHeap {

};
int main() {
    //step 1: build two PQueues, one for takeoff, one for landing
    //step 2: populate the two PQueues with inputs 
    //step 3: schedule runways to flights and output results
    PQueue takeoff;
    PQueue landing;
    queue<PQueueNode*> tqueue; // simple queue in order of arrival time
    int numplanes;
    int count = 0;
    //temp node variables and pointer to pass to insert()/push();  
    int tid;
    bool temergency;
    int ttime_arrival;
    int tpriority;
    string DorA; //departing or arriving, converts to ttakeoff via if
    bool ttakeoff;
    PQueueNode* tnode;

    cin >> numplanes;
    //enter values and insert for numplanes
    while (count < numplanes)
    {
        cin >> ttime_arrival >> tid >> DorA >> temergency >> tpriority;
        transform(DorA.begin(), DorA.end(), DorA.begin(), ::tolower);
        if (DorA == "departing") { ttakeoff = true; }
        else { ttakeoff = false; }
        tnode = new PQueueNode(tid, temergency, ttime_arrival, tpriority, ttakeoff);
        tqueue.push(tnode); 
        tnode = NULL; 
        count++;
    }

    int timestep = 0; 
    minHeap EQueue; // fill with emergency flights in the order that they become emergencies, most likely will be min heap; 
    
    PQueueNode* tempNode; 
    // announce arriving planes from tqueue, place them into appropriate pqueue
    while (numplanes != 0)  // exit when no more planes, will likely replace with a counter; 
    {
        while (tqueue.front()->time_arrival == timestep)
        {
            tqueue.front() = tempNode; 
            tqueue.pop(); 
            cout << tempNode->time_arrival << " " << tempNode->id << " ";
            if (tempNode->takeoff == true)
            {
                cout << "departing "; 
            }
            else {
                cout << "arriving ";
            }
            cout << tempNode->priority << endl; 
            if (tempNode->emergency)
            {
                EQueue.insertValue(tempNode);
            }
            else if (tempNode->takeoff)
            {
                takeoff.insertValue(tempNode);
            }
            else {
                landing.insertValue(tempNode);
            }
            tempNode = NULL; 
        }
    // check and update timestamps for emergencies, delete from PQueue and insert to minheap;
    // runway A fill from emergency
    // runway B fill from emergency
    // if empty, A fills priority takeoff;
    // b then fills priority landing; 
    // if a still not filled, fill from priority landing; 
    // if b still not filled, fill from priority takeoff;  
    // output A
    // output B
    }



    return 0;
}
