#ifndef BST_H
#define BST_H

#include "candidate.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// BST Node structure
struct BSTNode {
    Candidate data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const Candidate& candidate) 
        : data(candidate), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Class for Candidates
class CandidateBST {
private:
    BSTNode* root;
    int totalCandidates;
    
    // Helper function for insertion
    BSTNode* insertHelper(BSTNode* node, const Candidate& candidate, bool& success) {
        if (node == nullptr) {
            success = true;
            totalCandidates++;
            return new BSTNode(candidate);
        }
        
        if (candidate.id < node->data.id) {
            node->left = insertHelper(node->left, candidate, success);
        } else if (candidate.id > node->data.id) {
            node->right = insertHelper(node->right, candidate, success);
        } else {
            success = false; // Duplicate ID
        }
        
        return node;
    }
    
    // Helper function for search
    BSTNode* searchHelper(BSTNode* node, int id) {
        if (node == nullptr || node->data.id == id) {
            return node;
        }
        
        if (id < node->data.id) {
            return searchHelper(node->left, id);
        } else {
            return searchHelper(node->right, id);
        }
    }
    
    // Helper function for in-order traversal
    void inOrderHelper(BSTNode* node) {
        if (node != nullptr) {
            inOrderHelper(node->left);
            node->data.display();
            inOrderHelper(node->right);
        }
    }
    
    // Helper function for pre-order traversal
    void preOrderHelper(BSTNode* node) {
        if (node != nullptr) {
            node->data.display();
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }
    
    // Helper function for post-order traversal
    void postOrderHelper(BSTNode* node) {
        if (node != nullptr) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            node->data.display();
        }
    }
    
    // Helper function to find minimum node
    BSTNode* findMinHelper(BSTNode* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function to find maximum node
    BSTNode* findMaxHelper(BSTNode* node) {
        while (node && node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    
    // Helper function for deletion
    BSTNode* deleteHelper(BSTNode* node, int id, bool& success) {
        if (node == nullptr) {
            success = false;
            return nullptr;
        }
        
        if (id < node->data.id) {
            node->left = deleteHelper(node->left, id, success);
        } else if (id > node->data.id) {
            node->right = deleteHelper(node->right, id, success);
        } else {
            success = true;
            totalCandidates--;
            
            // Node with only one child or no child
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            
            // Node with two children
            BSTNode* temp = findMinHelper(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data.id, success);
        }
        
        return node;
    }
    
    // Helper function to count nodes
    int countNodesHelper(BSTNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
    }
    
    // Helper function to calculate height
    int heightHelper(BSTNode* node) {
        if (node == nullptr) {
            return -1;
        }
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }
    
    // Helper function to calculate total votes
    int totalVotesHelper(BSTNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->data.votes + totalVotesHelper(node->left) + totalVotesHelper(node->right);
    }
    
    // Helper function to find winner
    void findWinnerHelper(BSTNode* node, BSTNode*& winner, int& maxVotes, bool& tie) {
        if (node == nullptr) {
            return;
        }
        
        findWinnerHelper(node->left, winner, maxVotes, tie);
        
        if (node->data.votes > maxVotes) {
            maxVotes = node->data.votes;
            winner = node;
            tie = false;
        } else if (node->data.votes == maxVotes && maxVotes > 0) {
            tie = true;
        }
        
        findWinnerHelper(node->right, winner, maxVotes, tie);
    }
    
    // Helper function to display results
    void displayResultsHelper(BSTNode* node, int totalVotes) {
        if (node != nullptr) {
            displayResultsHelper(node->left, totalVotes);
            node->data.displayWithPercentage(totalVotes);
            displayResultsHelper(node->right, totalVotes);
        }
    }
    
    // Helper function to display tied candidates
    void displayTiedHelper(BSTNode* node, int maxVotes) {
        if (node != nullptr) {
            displayTiedHelper(node->left, maxVotes);
            if (node->data.votes == maxVotes) {
                cout << "- " << node->data.name << " (" << node->data.party << ")\n";
            }
            displayTiedHelper(node->right, maxVotes);
        }
    }
    
    // Helper function to destroy tree
    void destroyTree(BSTNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
public:
    CandidateBST() : root(nullptr), totalCandidates(0) {}
    
    // Destructor
    ~CandidateBST() {
        destroyTree(root);
    }
    
    // Insert a new candidate
    bool insert(int id, const string& name, const string& party) {
        Candidate candidate(id, name, party);
        bool success = false;
        root = insertHelper(root, candidate, success);
        
        if (!success) {
            cout << "Error: Candidate with ID " << id << " already exists!\n";
        }
        
        return success;
    }
    
    // Search for a candidate
    void searchCandidate(int id) {
        BSTNode* result = searchHelper(root, id);
        
        if (result == nullptr) {
            cout << "\nCandidate with ID " << id << " not found!\n";
        } else {
            cout << "\n" << string(60, '=') << "\n";
            cout << "Candidate Found:\n";
            cout << string(60, '=') << "\n";
            result->data.display();
            cout << string(60, '=') << "\n";
        }
    }
    
    // Cast a vote
    bool castVote(int id) {
        BSTNode* candidate = searchHelper(root, id);
        
        if (candidate == nullptr) {
            cout << "Error: Candidate with ID " << id << " not found!\n";
            return false;
        }
        
        candidate->data.votes++;
        return true;
    }
    
    // Delete a candidate
    bool deleteCandidate(int id) {
        bool success = false;
        root = deleteHelper(root, id, success);
        return success;
    }
    
    // Display candidates in-order (sorted by ID)
    void displayInOrder() {
        if (root == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        inOrderHelper(root);
        cout << string(80, '=') << "\n";
        cout << "Total Candidates: " << totalCandidates << "\n";
    }
    
    // Display candidates pre-order
    void displayPreOrder() {
        if (root == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        preOrderHelper(root);
        cout << string(80, '=') << "\n";
    }
    
    // Display candidates post-order
    void displayPostOrder() {
        if (root == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        postOrderHelper(root);
        cout << string(80, '=') << "\n";
    }
    
    // Display results
    void displayResults() {
        if (root == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        int totalVotes = totalVotesHelper(root);
        
        cout << "\n" << string(90, '=') << "\n";
        cout << "                         VOTING RESULTS\n";
        cout << string(90, '=') << "\n";
        displayResultsHelper(root, totalVotes);
        cout << string(90, '=') << "\n";
        cout << "Total Votes Cast: " << totalVotes << "\n";
        cout << string(90, '=') << "\n";
    }
    
    // Find winner
    void findWinner() {
        if (root == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        BSTNode* winner = nullptr;
        int maxVotes = -1;
        bool tie = false;
        
        findWinnerHelper(root, winner, maxVotes, tie);
        
        if (maxVotes == 0) {
            cout << "\nNo votes have been cast yet.\n";
            return;
        }
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "                    WINNER ANNOUNCEMENT\n";
        cout << string(60, '=') << "\n";
        
        if (tie) {
            cout << "There is a TIE with " << maxVotes << " votes!\n";
            cout << "Tied candidates:\n\n";
            displayTiedHelper(root, maxVotes);
        } else {
            cout << "Winner: " << winner->data.name << "\n";
            cout << "Party: " << winner->data.party << "\n";
            cout << "Total Votes: " << winner->data.votes << "\n";
        }
        cout << string(60, '=') << "\n";
    }
    
    // Find minimum ID candidate
    void findMinimum() {
        if (root == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        BSTNode* minNode = findMinHelper(root);
        cout << "\n" << string(60, '=') << "\n";
        cout << "Candidate with Minimum ID:\n";
        cout << string(60, '=') << "\n";
        minNode->data.display();
        cout << string(60, '=') << "\n";
    }
    
    // Find maximum ID candidate
    void findMaximum() {
        if (root == nullptr) {
            cout << "\nNo candidates registered yet.\n";
            return;
        }
        
        BSTNode* maxNode = findMaxHelper(root);
        cout << "\n" << string(60, '=') << "\n";
        cout << "Candidate with Maximum ID:\n";
        cout << string(60, '=') << "\n";
        maxNode->data.display();
        cout << string(60, '=') << "\n";
    }
    
    // Count total nodes
    int countNodes() {
        return countNodesHelper(root);
    }
    
    // Get tree height
    int getHeight() {
        return heightHelper(root);
    }
    
    // Check if tree is empty
    bool isEmpty() {
        return root == nullptr;
    }
};

#endif // BST_H
