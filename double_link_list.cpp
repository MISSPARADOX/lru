struct Node
{
	int num;
    int key;
	Node* next;
	Node* pre;
	Node(int i=-1)
	{
	    	num = i;
        key =i;
		next = NULL;
		pre = NULL;
	}
};
class DoubleListNode {
public:
	Node * head;
	Node * tail;
	DoubleListNode()
	{
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->pre = head;	
	}
	void remove(Node* item);
	void sethead(Node* item);
	~DoubleListNode();
	
};
DoubleListNode::~DoubleListNode()
{
	
		//free(head);
		//free(tail);
        delete head;
        delete tail;
}
void DoubleListNode::remove(Node* item) //从链表中移除
{
	Node* preNode = item->pre;
	Node* nextNode = item->next;
	if(preNode)
	preNode->next = nextNode;
	if(nextNode)
	nextNode->pre = preNode;
	return;
}
void DoubleListNode::sethead(Node* item) //将节点放置到头
{
	//Node* preNode = item->pre;
	//if (item->pre != head)//加了判断后，当移除的item是第一个时，再调用  sethead就不会执行下面的语句，会出问题（只从链表中移除，没有添加）。
	//{
		item->next = head->next;
		item->pre = head;
		head->next->pre = item;
		head->next = item;
	//}
	return;
}
void DoubleListNode::dump()
{
	Node* index = head->next;
	printf("\n");
	while (index&&index!=tail)
	{
		printf("%d ", index->num);
		index = index->next;
	}
	printf("\n");
}
class LRUCache {
public:
	map<int, Node*>m_map; //存放key和对应Node
	DoubleListNode list;
	Node* head = NULL;
	Node* pre;
	int cap = 0;
	int cnt = 0;
	int len = 0;
	LRUCache(int capacity) {
		cap = capacity;
	
	}

	int get(int key) {
		
		if (m_map.find(key)!= m_map.end())
		{
			Node* ret = m_map[key];
			list.remove(ret);
			list.sethead(ret);
			return ret->num;
		}
		return -1;
	}

	void put(int key, int value) {
		
		if (m_map.find(key) != m_map.end())
		{
			Node* ret = m_map[key];
			list.remove(ret);
			//delete ret;
			//Node* item = new Node;
			ret->num = value;
           // item->key=key;
			list.sethead(ret);
			//m_map[key] = item;
			return;
		}
		if (cnt >= cap)
		{
            Node* p=list.tail->pre;
			list.remove(p);
            m_map.erase(p->key);
            delete p;
		}
		Node* item = new Node;
		item->num = value;
        item->key=key;
		list.sethead(item);
		m_map[key] = item;
		cnt++;
		return;
	}
};
