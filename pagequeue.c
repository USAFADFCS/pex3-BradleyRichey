/** pagequeue.c
 * ===========================================================
 * Name: Bradley Richey
 * Section: CS483 / M3
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {


    PageQueue* pageQueue = malloc(sizeof(PageQueue));

    if(pageQueue == NULL){
        printf("malloc failed");
        return NULL;
    }

    pageQueue->head = NULL;
    pageQueue->tail = NULL;
    pageQueue->size = 0;
    pageQueue->maxSize = maxSize;
    
    return pageQueue;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {

    int d = 0;

    if(pq == NULL){
        return -1;
    }

    PqNode *currentNode = pq->tail;


    while(currentNode != NULL && currentNode->pageNum != pageNum){
        currentNode = currentNode -> prev;
        d++;
    }

    if(currentNode == NULL){

        PqNode* newNode = (PqNode*)malloc(sizeof(PqNode));

        newNode->pageNum = pageNum;
        newNode->next = NULL;
        newNode->prev = pq->tail;

        if(pq->tail == NULL){
            pq->head = newNode;
            pq->tail = newNode;
        }
        else{
            pq->tail->next = newNode;
            pq->tail = newNode;
        }

        pq->size++;
        return -1;
        
    }

    if(currentNode == pq->tail){
        return d;
    }

    if(currentNode->prev != NULL){
        currentNode->prev->next = currentNode->next;
    }
    else{
        pq->head = currentNode->next;
    }

    if(currentNode->next != NULL){
        currentNode->next->prev = currentNode->prev;
    }
    else{
        pq->tail = currentNode->prev;
    }

    currentNode->next = NULL;
    currentNode->prev = pq->tail;

    if(pq->tail != NULL){
        pq->tail->next = currentNode;
    }
    else{
        pq->head = currentNode;
    }
    
    pq->tail = currentNode;

    return d;

}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    
    while(pq->head != NULL){
        PqNode* delNode = (PqNode*)malloc(sizeof(PqNode));

        delNode = pq->head;
        
        pq->head = delNode->next;
        free(delNode);
    }
    free(pq);
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
}
