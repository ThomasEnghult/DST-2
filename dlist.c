// dlist.c fånig changeeeee

#include "dlist.h"

list * create_list()
{
	list * mylist = (list *)calloc(1, sizeof(list));
	if (mylist == NULL) {
		return NULL;
	}

	mylist->pHead = (listobj *)calloc(1, sizeof(listobj));
	if (mylist->pHead == NULL) {
		free(mylist);
		return NULL;
	}

	mylist->pTail = (listobj *)calloc(1, sizeof(listobj));
	if (mylist->pTail == NULL) {
		free(mylist->pHead);
		free(mylist);
		return NULL;
	}
	mylist->pHead->pPrevious = mylist->pHead;
	mylist->pHead->pNext = mylist->pTail;
	mylist->pTail->pPrevious = mylist->pHead;
	mylist->pTail->pNext = mylist->pTail;
	return mylist;
}


listobj * create_listobj(int num)
{
	listobj * myobj = (listobj *)calloc(1, sizeof(listobj));
	if (myobj == NULL)
	{
		return NULL;
	}
	myobj->nTCnt = num;
	return (myobj);
}

void insert(list * mylist, listobj * pObj)
{
	// insert first in list
	listobj *pMarker;
	pMarker = mylist->pHead;

	/* Position found, insert element */
	pObj->pNext = pMarker->pNext;
	pObj->pPrevious = pMarker;
	pMarker->pNext = pObj;
	pObj->pNext->pPrevious = pObj;
}

void insertWait(list * mylist, listobj * pObj)
{
	// insert first in list
	listobj *pMarker;
	pMarker = mylist->pHead;
	
	if((pObj->pTask != NULL)&&(pMarker->pTask != NULL)){
		printf("true \n");
		while(pObj->pTask->DeadLine >= pMarker->pTask->DeadLine){
		pMarker = pMarker->pNext;
		}
	}
	/* Position found, insert element */
	pObj->pNext = pMarker->pNext;
	pObj->pPrevious = pMarker;
	pMarker->pNext = pObj;
	pObj->pNext->pPrevious = pObj;
}

void timerSort(list* mylist,listobj* prObj){
    listobj* pMarker = mylist->pHead;
    printf(" Head  %u ", mylist->pHead->nTCnt);;
    if(mylist->pHead==mylist->pTail){
        mylist->pHead->nTCnt=prObj->nTCnt;
        return;
    }
    else if((pMarker->nTCnt) >= (prObj->nTCnt)){
            prObj->pNext = pMarker->pNext;
            prObj->pPrevious = pMarker;
            pMarker->pNext = prObj;
            prObj->pNext->pPrevious = prObj;
    }
    else{
        while(pMarker->pNext != mylist->pTail && pMarker->pNext->nTCnt < prObj->nTCnt){
            pMarker=pMarker->pNext;
        }
        prObj->pNext=pMarker->pNext;
        if(pMarker->pNext!=mylist->pTail){
            prObj->pNext->pPrevious=prObj;
        }
        pMarker->pNext=prObj;
        prObj->pPrevious=pMarker;   
    }
}

listobj * extract(listobj *pObj)
{
	pObj->pPrevious->pNext = pObj->pNext;
	pObj->pNext->pPrevious = pObj->pPrevious;
	pObj->pNext = pObj->pPrevious = NULL;
	return (pObj);
}

int main(void){
		// My own test
	list * testList1 = create_list();
	list * testList2 = create_list();
	listobj * testObj1 = create_listobj(10);
	listobj * testObj3 = create_listobj(11);
	listobj * testObj2 = create_listobj(9);
 	TCB * mytask = (TCB *)calloc(1, sizeof(TCB));
	mytask->DeadLine = 1;
	testObj1->pTask = mytask;
	testObj2->pTask = mytask;
	testObj3->pTask = mytask;
	//testObj1->pTask.DeadLine = 100;
	insertWait(testList1,testObj1);
	printf("%d \n", 1);
	insertWait(testList1,testObj2);
	printf("%d \n", 2);
	insertWait(testList1,testObj3);
	printf("%d \n", 3);
	//insertWait(testList2,testObj2);
	uint x = testList1->pTail->pTask->DeadLine;
	return 0;
}
