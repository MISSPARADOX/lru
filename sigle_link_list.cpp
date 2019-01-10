struct Node
{
	int num;
    int key;
	Node* next=NULL;
	Node(int num=0,int key=-1):num(num),key(key){}
	
};
class LRUCache {
public:

	Node* head = NULL; //链表
	Node* pre=NULL;
	int cap = 0;
	int len = 0;
	LRUCache(int capacity) {
		cap = capacity;
		pre = new Node;
		Node* cur = pre;
		for (int i = 0; i<capacity; ++i) //创建链表结构，节点个数固定
		{
			Node* tmp = new Node;
			cur->next = tmp;
			cur = tmp;
		}
		head = pre->next;
	}

~LRUCache()
{
    while(pre) //释放链表内存
    {
        Node* cur=pre->next; 
        delete pre;
        pre=cur;
    }
    pre=NULL;
    head=NULL;
}
	int get(int key) {
		Node* cur = head; //dummy节点，辅助作用。
		Node* last = pre;
		while (cur)
		{
			if (key == cur->key)
			{
				if (cur!= head) //若不是第一个节点
				{
					last->next = cur->next;
					cur->next = head;
					pre->next = cur;
					head = pre->next;
				}
				return cur->num;

			}
			last = last->next;
			cur = cur->next;
		}
		return -1;

	}

	void put(int key, int value) {
		Node* cur=head;
		Node* last=pre;
		while(cur&&cur->next)
		{
		    if(key==cur->key)
		    {
                if(cur!=head)  //找到关键字，若对应节点不是头节点，移动到头
                {
                    last->next=cur->next;
		            cur->next=head;
		            pre->next=cur;
		            head = pre->next;
                }
		   
		      cur->num=value;
                return;
    
		    }
		    last=last->next;
		    cur=cur->next;
		}
		cur->key = key; //此时，cur指向最后一个节点。将其值赋为key，且移动到最前端
        cur->num=value;
        if(cur!=head)//若list不为空
        {
            last->next=cur->next;
	    	cur->next = head;
		    pre->next = cur;
		    head = pre->next;
        }
		return;
	}
};
