//
// Author info:
// Created by Hao Liang on 2022/7/22.
//
/*
设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：val 和 next。val 是当前节点的值，next 是指向下一个节点的指针/引用。如果要使用双向链表，则还需要一个属性 prev 以指示链表中的上一个节点。假设链表中的所有节点都是 0-index 的。

在链表类中实现这些功能：

get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。
*/
/**
 * @brief
 * @_size 节点个数
 * @dummyNode 虚拟头节点
 * @tailNode 尾节点
 * */
class MyLinkedList_707 {
private:
    class ListNode{
    public:
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr){}
        ListNode(int val) : val(val), next(nullptr){}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    int _size = 0;
    ListNode *dummyNode = nullptr;
    ListNode *tailNode = nullptr;

public:
    MyLinkedList_707() : dummyNode(new ListNode()){
    }
//获取指定位置的值
//判定index是否合法
//遍历index + 1 次到指定的位置
//取出并返回节点值
    int get(int index) {
        if(index >= _size || index < 0){
            return -1;
        }
        ListNode *loopNode = dummyNode;
        for (int i = 0; i <= index; ++i) {
           loopNode = loopNode->next;
        }
        int i = loopNode->val;
        return i;
    }

//头插法
//如果是空表，初始化尾节点的值
    void addAtHead(int val) {
        ListNode *tmp = new ListNode(val);
        tmp->next = dummyNode->next;
        dummyNode->next = tmp;
        if (_size == 0) {
            tailNode = tmp;
        }
        ++_size;
    }

//尾插法，如果空表，则初始化尾节点；否则直接向尾节点后插入
    void addAtTail(int val) {
        ListNode *tmp = new ListNode(val);
        if(_size == 0){
            dummyNode->next = tmp;
        }
        else{
            tailNode->next = tmp;
        }
        tailNode = tmp;
        ++_size;
    }
//index 等于 表长，则尾插；index小于或者等于0，则头插
//其他情况，则循环index次，到要插入的位置之前的节点
    void addAtIndex(int index, int val) {
        if (index == _size) {
            addAtTail(val);
        }
        else if(index <= 0){
            addAtHead(val);
        }
        else if (index > 0 && index < _size) {
            ListNode *tmp = new ListNode(val);
            ListNode *loopNode = dummyNode;
            for (int i = 0; i < index; ++i) {
                loopNode = loopNode->next;
            }
            tmp->next = loopNode->next;
            loopNode->next = tmp;
            ++_size;
        }
    }

//删除指定位置的节点
//如果index合法，则定位到要删除节点的前一个位置。
//如果要删除尾节点，则更新尾节点

    void deleteAtIndex(int index) {
        if (index < _size && index > -1) {
            ListNode *loopNode = dummyNode;
            //定位到要删除的前面一个节点
            for (int i = 0; i < index; ++i) {
                loopNode = loopNode->next;
            }
            if (index == _size -1) {
                tailNode = loopNode;
            }
            ListNode *tmp = loopNode->next;
            loopNode->next = loopNode->next->next;
            delete tmp;
            --_size;
        }
    }
};

/**
 * Your MyLinkedList_707 object will be instantiated and called as such:
 * MyLinkedList_707* obj = new MyLinkedList_707();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */