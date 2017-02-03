#include<string>
using namespace std;
typedef string ItemType;

class QueueType
{
public:
	QueueType(); /*Constructor with no params*/
	QueueType(int max); /*Constructor with params*/

	~QueueType();

	void Clear();
	bool IsEmpty();
	bool IsFull();
	void Insert(ItemType item);
	ItemType Delete();
	int Size();
	int GetLength();

private:
	ItemType* items;
	int front, rear, length;
	int MaxQueue;
};

//----------------------------------------------------------------------
QueueType::~QueueType()
{
	delete[] items;
}

//----------------------------------------------------------------------
QueueType::QueueType(int max)
{
	MaxQueue = max + 1;
	front = MaxQueue - 1;
	rear = MaxQueue - 1;
	length = 0;
	items = new ItemType[MaxQueue];
}
//----------------------------------------------------------------------
QueueType::QueueType() :QueueType(5)
{
	MaxQueue = 5 + 1;
	front = MaxQueue - 1;
	rear = MaxQueue - 1;
	length = 0;
	items = new ItemType[MaxQueue];
}
//----------------------------------------------------------------------
void QueueType::Clear()
{
	front = MaxQueue - 1;
	rear = MaxQueue - 1;
	length = 0;
}
//----------------------------------------------------------------------
bool QueueType::IsEmpty()
{
	return (rear == front);
}
//----------------------------------------------------------------------
bool QueueType::IsFull()
{
	return ((rear + 1) % MaxQueue == front);
}
//----------------------------------------------------------------------
void QueueType::Insert(ItemType item)
{
	if (IsFull())
		throw "Queue is full";

	rear = (rear + 1) % MaxQueue;
	items[rear] = item;
	length++;
}
//----------------------------------------------------------------------
ItemType QueueType::Delete()
{
	if (IsEmpty())
		throw "Queue is empty";

	front = (front + 1) % MaxQueue;

	length--;
	return items[front];
}

int QueueType::Size()
{
	return MaxQueue - 1;
}

int QueueType::GetLength()
{
	return length;
}