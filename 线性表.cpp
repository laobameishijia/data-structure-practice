// 线性表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
# define LIST_INIT_SIZE 100 // 线性表存储空间的初始分配量
# define LISTINCREMENT 10//线性表存储空间的分配增量
typedef struct {
    int* elem; //存储空间基址
    int length;//当前长度
    int listsize;//当前分配的存储容量(以sizeof(int)为单位)
}SqList;

/*
    初始化创建
*/
bool InitList_Sq(SqList &L) {
    L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
    memset(L.elem, 0, LIST_INIT_SIZE * sizeof(int));
    if (!L.elem) return false;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return true;
}
/*
    按顺序打印
*/
void ListPrint_Sq(SqList& L) {
    if (L.length == 0) { printf_s("该顺序表为空"); exit(0); }
    for (int i = 0; i <= L.length - 1; i++) {
        printf_s("%d->", *(L.elem + i));
    }
    printf_s("\n");
}
/*
    在固定位置插入元素
*/
bool ListInsert_Sq(SqList& L, int i, int e) {
    //在顺序线性表L中第i个位置之前插入新的元素e
    //i的合法值
    if (i<1 || i>L.length + 1) return false;
    if (L.length > L.listsize) {//当前存储空间已满，增加分配
        int* newbase = (int*)realloc(L.elem, ((L.listsize + LISTINCREMENT)*sizeof(int)));
        if (!newbase) exit(OVERFLOW);
        L.elem = newbase;//新基址
        L.listsize  = L.listsize + LISTINCREMENT;
    }
    int* q = &(L.elem[i - 1]); //q为插入位置
    for (int* p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p + 1) = *p;//插入位置的元素后移
    *q = e;
    ++L.length;
    return true;
}
/*
    删除固定位置的元素
*/
bool ListDelete_Sq(SqList& L, int i, int& e) {
    //在顺序线性表L中删除第i个元素，并用e返回值
    if (i<1 || i>L.length + 1)return false;
    int* p = &(L.elem[i - 1]);//被删除元素的位置
    e = *p;
    int*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  q = L.elem + L.length - 1;
    for (++p; p <= q; ++p) *(p - 1) = *p;//被删除元素之后的元素左移
    --L.length;
    return false;
}
/*
    删除顺序表中最小的元素 √
*/
bool ListDeleteMin_Sq(SqList& L, int& e) {
    if (!(L.elem) || L.length == 0) { printf_s("长度为零"); exit(-1); }
    int* q = L.elem + L.length - 1;
    int* p = L.elem;
    int* tag = L.elem;
    for (; p <= q; p++) {
        if (*p < *tag) tag = p;
    }
    e = *tag;
    *tag = *q;
    return true;
}
/*
    顺序表逆置 √
*/
bool ListReverse_Sq(SqList& L) {
    if (L.length == 0) return false;
    int* temp,*p,*q;
    // C++不允许空指针，定义只是定义int*,定义了并没有实际的指向。习惯上一定要进行初始指针的初始化操作。
    temp =(int*)malloc(1*sizeof(int));
    //也或者在这里直接用int类型的test即可。
    int test;
    for (int i = 0; i <= L.length/ 2-1; i++) {
        p = L.elem + i;
        q = L.elem + L.length - 1 - i;
        test = *p;
        *p = *q;
        *q = test;
    }
    return true;
}
/*
    删除顺序表中所有值为x的元素 √
     ----无论是有序表还是无序表用这个都行，有序表可以先找到所有的元素，然后一起移动，但是从时间复杂度上面来讲是一样的
    从逻辑上讲，2这个值的确被删除了
    但是从存储的结构上讲，2这个值还在存储空间里，只不过在逻辑上，这个位置已经是不合法的了。(改变了顺序表的长度)
*/
bool ListDeleValue(SqList& L, int e) {
    int k = 0;
    if (L.length == 0) return false;
    for (int i = 0; i < L.length; i++) {
        if (*(L.elem + i) != e) {
            k++;
            *(L.elem + k - 1) = *(L.elem + i);
        }
    }
    L.length = k;
    return true;
}
/*
    删除值在s和t之间的节点 √
    跟上面的方法很像了
*/
bool ListDeleValueBetween(SqList& L, int s, int t) {
    if (s > t) {
        printf_s("请检查参数设置\n"); 
        return false;
    }
    int k = 0;
    if (L.length == 0)return false;
    for (int i = 0; i < L.length; i++) {
        if (*(L.elem + i) <s || *(L.elem + i) > t) {
            k++;
            *(L.elem + k - 1) = *(L.elem + i);
        }
    }
    L.length = k;
    return true;
}
/*
    删除有序线性表中所有的重复值 √
*/
bool ListDeleteDuplicateValueInOrder(SqList& L) {
    if (L.length == 0 || L.length == 1)return false;
    int k=0;
    for (int i = 0; i < L.length; i++) {
        if (*(L.elem + i) != *(L.elem + i + 1)) {
            k++;
            *(L.elem + k - 1) = *(L.elem + i);
        }
    }
    L.length = k;
    return true;
}
/*
    将两个有序表---假设是由小到大  合成为一个有序表 √
*/
SqList ListMergeOrder(SqList L1,SqList L2) {
    int* p, * q,*p_last,*q_last;
    p = L1.elem;
    p_last = L1.elem + L1.length - 1;//可以采用这种方式在循环中进行限制，q==NULL这种是没办法限制的。一旦它有了初值，q++下去，永远也不会为NULL了
    q = L2.elem;
    q_last = L2.elem + L2.length - 1;

    //像这种，考试的时候，一般是要把merge作为参数传进来的
    //要判断一下,merge分配的空间是否大于L1+L2的总和
    SqList merge;
    merge.elem= (int*)malloc((L1.length+L2.length)* sizeof(int));
    merge.length = 0;
    merge.listsize = L1.length + L2.length;
    if (!merge.elem) exit(-1);

    int i = 0;
    for (; p<=p_last && q <= q_last;i++) {
        if (*p <= *q) {
            *(merge.elem + i) = *p;
            p++;
        }
        else if (*p > * q) {
            *(merge.elem + i) = *q;
            q++;
        }
    }
    while (p <= p_last)
    {
        *(merge.elem + i) = *p;
        i++;
        p++;
    }
    while (q <= q_last)
    {
        *(merge.elem + i) = *q;
        i++;
        q++;
    }
    merge.length = i;
    return merge;
}
/*
    将A[m+n]中的a1.....an,b1...bn--->b1.....bn,a1.....an √
*/
void Reverse(int A[], int left, int right, int arrySize) {
    if (left >= right || right >= arrySize) return;
    int mid = (left + right) / 2;
    int temp;
    for (int i = left; i <= mid; i++) {//如果这里没有 = ，那么是无法置换长度为偶数的数组的。
        temp = A[i];
        A[i] = A[left + right - i];
        A[left + right - i] = temp;
    }
}
void Exchange(int A[], int m, int n) {
    int arrySize = m + n;
    Reverse(A, 0, m + n - 1, arrySize);
    Reverse(A, 0, n - 1, arrySize);
    Reverse(A, n, m + n - 1, arrySize);
}

/*
    从有序表---中获取数值为x的元素，找到之后跟其后续元素互换，找不到，将其插入表中,并使表中元素依然有序

    返回的是从0开始的坐标--返回的是最后一个与元素值相等的节点
*/
int FindNodeInOrder(SqList& L, int left, int right,int e) {
    int i = (left + right) / 2;
    if (left != right||left<right) {
        if (e < *(L.elem + i)) {
            return FindNodeInOrder(L, 0, i-1, e);//这里一定要是i-1,否则找到的值就变成了第一个大于e的节点了
        }
        if (e >= * (L.elem + i)) {
            return FindNodeInOrder(L, i + 1, right, e);
        }
    }
    else if (left == right) {
        return i;
    }
}
bool InsertOrReverse(SqList& L, int e) {
    int t = FindNodeInOrder(L, 0, L.length-1, e);
    if (*(L.elem + t) == e && t < L.length) {
        int temp;
        temp = *(L.elem + t);
        *(L.elem + t) = *(L.elem + t + 1);
        *(L.elem + t + 1) = temp;
    }
    if (t == L.length) return false;
    if(*(L.elem + t) > e){
        ListInsert_Sq(L, t + 1, e);//插入的函数是从1开始的，返回的t是从0开始的
    }
    if(*(L.elem + t) < e){
        ListInsert_Sq(L, t + 2, e);
    }
    return true;
}
/*
测试代码
*/
int main()
{
    
    SqList test;
    InitList_Sq(test);
    ListInsert_Sq(test, 1, 2);
    ListInsert_Sq(test, 2, 2);
    ListInsert_Sq(test, 3, 2);
    ListInsert_Sq(test, 4, 3);
    ListInsert_Sq(test, 5, 4);
    ListInsert_Sq(test, 6, 5);
    ListInsert_Sq(test, 7, 5);
    ListInsert_Sq(test, 8, 6);

    SqList test2;
    InitList_Sq(test2);
    ListInsert_Sq(test2, 1, 2);
    ListInsert_Sq(test2, 2, 3);
    ListInsert_Sq(test2, 3, 4);
    ListInsert_Sq(test2, 4, 5);
    ListInsert_Sq(test2, 5, 6);
    ListInsert_Sq(test2, 6, 7);
    ListInsert_Sq(test2, 7, 8);
    ListInsert_Sq(test2, 8, 9);

    //测试删除最小的元素
    //int tag;
    //ListDeleteMin_Sq(test, tag);
    //printf_s("%d", tag);

    //测试元素逆序
    //ListReverse_Sq(test);
    //ListPrint_Sq(test);

    //测试删除所有值为x的元素
    //ListDeleValue(test, 2);
    //ListPrint_Sq(test);

    //测试删除区间内的值
    //ListDeleValueBetween(test,2, 5);
    //ListPrint_Sq(test);

    //测试删除有序表中的重复值
    //ListDeleteDuplicateValueInOrder(test);
    //ListPrint_Sq(test);
    
    //测试合并
    //SqList test3;
    //test3 = ListMergeOrder(test, test2);
    //ListPrint_Sq(test3);

    //测试反转
    //int A[5];
    //A[0] = 3;
    //A[1] = 2;
    //A[2] = 1;
    //A[3] = 5;
    //A[4] = 4;
    //Exchange(A, 3, 2);
    //printf_s("test");

    //测试在有序表中找到元素
    //InsertOrReverse(test, 1);//√
    InsertOrReverse(test, 2);//√
    //InsertOrReverse(test, 7);
    ListPrint_Sq(test);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
