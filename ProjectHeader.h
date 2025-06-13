#ifndef PROJECT_H
#define PROJECT_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define WHITE 0
#define GRAY  1
#define BLACK 2

// --- Data Structures ---
typedef struct {
    int neighbor;
    int cost;
} Edge;

typedef struct edge_node {
    Edge e;
    struct edge_node* next;
} EdgeNode;

typedef struct {
    EdgeNode* head;
    EdgeNode* tail;
} EdgeList;

typedef struct {
    int computer;
    int min;
} Candidate;

typedef struct candidate_node {
    Candidate c;
    struct candidate_node* next;
    struct candidate_node* prev;
} CandidateNode;

typedef struct {
    CandidateNode* head;
    CandidateNode* tail;
} CandidateList;

// --- Utility Functions ---
void checkAllocation(void* ptr);
void error_and_exit(void);
void Check_n(int n);
void Check_first_and_last(int first, int last, int n);

// --- Network Functions ---
void insertEdgeSorted(EdgeList* lst, EdgeNode* node);
void appendEdge(EdgeList* lst, int neighbor, int cost);
EdgeList* build_net(int n);

// --- Prim Functions ---
CandidateList buildPriorityAndLocation(int numComputers, CandidateNode*** outLocation);
int DeleteMin(CandidateList* q);
void decreaseKey(CandidateNode* node, int newMin);
int* build_prim_tree(EdgeList net[], int n);

// --- Path Functions ---
EdgeList* build_paths(int Prim[], int n);
void find_and_print_path(EdgeList PrimPath[], int n, int first, int last);

// --- Path Helpers ---
static void FindPath(int u, int last, EdgeList PrimPath[], int Color[], int Parent[]);
static void PrintPath(int v, int first, int Parent[]);

#endif 
