#include "DoublyLinkedList.h"
DoublyLinkedList::Node::Node(const ValueType &value, DoublyLinkedList::Node *next, DoublyLinkedList::Node *previous)
{
    this->value = value;
    this->next = next;
    this->previous = previous;
}

DoublyLinkedList::Node::~Node()
{

}

void DoublyLinkedList::Node::insertNext(const ValueType &value)
{
    Node* newNode = new Node(value, this->next, this);
    this->next->previous = newNode;
    this->next = newNode;
}
void DoublyLinkedList::Node::removeNext()
{
    Node* newNext = this->next->next;
    newNext->previous = this;
    delete this->next;
    this->next = newNext;
}

DoublyLinkedList::DoublyLinkedList()
{
    _size = 0;
    _firstNode = nullptr;
    _lastNode = nullptr;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0) {
        this->_lastNode = nullptr;
        this->_firstNode = nullptr;
        return;
    }

    this->_firstNode = new Node(copyList._firstNode->value);

    Node* currentNode = this->_firstNode;
    Node* currentCopyNode = copyList._firstNode;

    while (currentCopyNode->next) {
        currentNode->next = new Node(currentCopyNode->next->value);
        currentNode->next->previous = currentNode;
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
    this->_lastNode = currentNode;
}
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& copyList)
{
    if (this == &copyList)
    {
        return *this;
    }
    this->_size = copyList._size;
    this->_lastNode = copyList._lastNode;
    this->_firstNode = copyList._firstNode;
    return *this;
}
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_lastNode= moveList._lastNode;
    this->_firstNode = moveList._firstNode;

    moveList._size = 0;
    moveList._firstNode = nullptr;
    moveList._lastNode = nullptr;
}
DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    this->_size = moveList._size;
    this->_lastNode = moveList._lastNode;
    this->_firstNode = moveList._firstNode;

    moveList._size = 0;
    moveList._lastNode= nullptr;
    moveList._firstNode = nullptr;

    return *this;
}
DoublyLinkedList::~DoublyLinkedList()
{
    forceNodeDelete(_firstNode);
}

ValueType& DoublyLinkedList::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}
DoublyLinkedList::Node* DoublyLinkedList::getNode(const size_t pos) const
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos >= this->_size) {
        assert(pos >= this->_size);
    }

    Node* bufNode = this->_firstNode;
    for (int i = 0; i < pos; ++i) {
        bufNode = bufNode->next;
    }

    return bufNode;
}
void DoublyLinkedList::insert(const size_t pos, const ValueType& value)
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos > this->_size) {
        assert(pos > this->_size);
    }

    if (pos == 0)
    {
        pushFront(value);
    }
    else
        {
        Node* bufNode = this->_firstNode;
        for (size_t i = 0; i < pos-1; ++i) {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        ++_size;
    }
}
void DoublyLinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    this->_size++;
}
void DoublyLinkedList::pushBack(const ValueType& value)
{
    this->_size++;
    if (this->_size == 1)
    {
        _firstNode = new Node(value, nullptr, nullptr);
        _lastNode = _firstNode;

    }
    else
    {
        Node* newLastNode = new Node(value, nullptr, _lastNode);
        _lastNode->next = newLastNode;
        _lastNode = newLastNode;
    }
}
void DoublyLinkedList::pushFront(const ValueType& value)
{
    ++_size;
    if (this->_size == 1)
    {
        _firstNode = new Node(value, _firstNode, nullptr);
    }
    else
    {
        Node* newFirst = new Node(value, _firstNode, nullptr);
        _firstNode->previous = newFirst;
        _firstNode = newFirst;
    }
}
void DoublyLinkedList::remove(const size_t pos)// Посмотреть
{
    if (pos < 0)
    {
        assert(pos < 0);
    }
    else if (pos > this->_size)
    {
        assert(pos > this->_size);
    }
    if (pos == 0)
    {
        this->removeFront();
    }
    else if (pos == this->size() - 1)
    {
        this->removeBack();
    }
    else
    {
        Node* currentNode = _firstNode;

        for (int i = 0; i < pos - 1; i++)
        {
            currentNode = currentNode->next;
        }

        Node* erasedNode = currentNode->next;
        currentNode->next = erasedNode->next;
        erasedNode->next->previous = currentNode;
        delete erasedNode;
        this->_size--;
    }

}

size_t DoublyLinkedList::size() const
{
    return this->_size;
}

void DoublyLinkedList::removeNextNode(DoublyLinkedList::Node *node)
{
    Node* erasedNode = node->next;
    erasedNode->next->previous = node;
    node->next = erasedNode->next;
    delete erasedNode;
}

void DoublyLinkedList::removeFront()
{
    this->_firstNode = this->_firstNode->next;
    delete _firstNode->previous;
    this->_firstNode->previous = nullptr;
    this->_size--;
}

void DoublyLinkedList::removeBack()
{
    this->_lastNode = this->_lastNode->previous;
    delete _lastNode->next;
    this->_lastNode->next = nullptr;
    this->_size--;
}

long long int DoublyLinkedList::findIndex(const ValueType &value) const {
    long long int i = 0;
    Node *currentNode = _firstNode;
    while (i < _size)
    {
        if (currentNode->value == value)
            return i;
    }
    std:: cout << "No Node" << std :: endl;
    return -1;
}
DoublyLinkedList::Node* DoublyLinkedList::findNode(const ValueType& value) const
{
    long long int i = 0;
    Node *currentNode = _firstNode;
    while (i < _size)
    {
        if (currentNode->value == value)
            return currentNode;
    }
    std:: cout << "No Node" << std :: endl;
    return nullptr;
}
void DoublyLinkedList::reverse()
{
    Node* currentNode = this->_firstNode;
    Node* buf = nullptr;
    for (int i = 0; i < this->_size; i++)
    {
        currentNode->previous = currentNode->next;
        currentNode->next = buf;
        buf = currentNode;
        currentNode = currentNode->previous;
    }
    buf = _firstNode;
    _firstNode = _lastNode;
    _lastNode = buf;
}

DoublyLinkedList DoublyLinkedList::reverse() const
{
    DoublyLinkedList reversedList = *this;
    reversedList.reverse();
    return reversedList;
}

DoublyLinkedList DoublyLinkedList::getReverseList() const
{
    DoublyLinkedList reversedList = *this;
    reversedList.reverse();
    return reversedList;
}

void DoublyLinkedList::forceNodeDelete(DoublyLinkedList::Node *node)
{

    if (node == nullptr)
    {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}

void DoublyLinkedList::print() {
    Node node = *_firstNode;
    while(node.next != nullptr)
    {
        std:: cout << node.value << std::endl;
        node = *node.next;
    }
    std:: cout << node.value << std::endl;
}
void DoublyLinkedList::printBackwards()
{
    Node node = *_lastNode;
    while(node.previous != nullptr)
    {
        std:: cout << node.value << std:: endl;
        node = *node.previous;
    }
    std:: cout << node.value << std:: endl;
}

void DoublyLinkedList::Swap(DoublyLinkedList::Node *a, DoublyLinkedList::Node *b)
{
    if (!a || !b || a == b)
        exit;
    Node* bufnode = a;
    b = bufnode;
    a = b;

}
