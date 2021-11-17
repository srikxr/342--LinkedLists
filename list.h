#ifndef LIST_
#define LIST_
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/*
------------------------List342 Class-----------------------------------------------------------
*/
template <class T>
class List342 
{
public:
    List342();
    List342(const List342 &a);
    ~List342(); //destructor

    bool BuildList(string file_name);
    bool Insert(T *obj);
    bool Remove(T target, T &result);
    bool Peek(T target, T &result) const;
    bool isEmpty() const;
    void DeleteList();
    bool Merge(List342 &list1);

    List342 operator+(const List342 &rhs) const;
    List342& operator+=(const List342 &rhs);

    bool operator==(const List342 &rhs) const;
    bool operator!=(const List342 &rhs) const;

    List342& operator=(const List342 &rhs);

    template <class type> 
    friend ostream& operator<<(ostream& stream, const List342<type> &rhs);

private:
    struct Node 
    {
        T *data;
        Node *next;
    };
    Node *head;
};
#endif

/*
------------------------List342 Implementation-----------------------------------------------------------
*/

template <class T>
List342<T>::List342()
{
    head = nullptr;
}

template <class T>
List342<T>::List342(const List342<T> &a)
{
    head = nullptr;
    *this = a;
}

template <class T>
List342<T>::~List342()
{
    DeleteList();
}


template <class T>
bool List342<T>::BuildList(string file_name)
{
    ifstream inFile;
    inFile.open(file_name);

    if (!inFile)
    {
        cout << "The file can't be opened. Please try again." << endl;
        return false;
    } 

    T item;
    while (inFile.eof())
    {
        inFile >> item;
        Insert(&item);
    }

    inFile.close();
    return true;
}

template <class T>
bool List342<T>::Insert(T *obj)
{
    if (obj == nullptr)
    {
        return false;
    }

    if (Peek(*obj, *obj))
    {
        return false;
    }
    
    Node *new_node_insert = new Node;
    T *new_data_insert;

    new_data_insert = new T;
    *new_data_insert = *obj;

    new_node_insert->data = new_data_insert;
    new_node_insert->next = nullptr;

    if ( head == nullptr)
    {
        head = new_node_insert;
        return true;
    }
    else if (*(new_node_insert->data) < *( head->data))
    {
        new_node_insert->next =  head;
        head = new_node_insert;

        return true;
    }
    else
    {
        Node *trackingPtr;
        trackingPtr =  head;

        while ((trackingPtr->next != nullptr) && (*(new_node_insert->data) > *(trackingPtr->next->data))) 
        {
            trackingPtr = trackingPtr->next;
        }

        new_node_insert->next = trackingPtr->next;
        trackingPtr->next = new_node_insert;
    }
    return true;
}

template <class T>
bool List342<T>::Remove(T target, T &result) 
{
    if ( head == nullptr)
    {
        return false;
    }

    Node *current_pointer;
    current_pointer =  head;
    
    if (*( head->data) == target)
    {
        head =  head->next;
        result = *(current_pointer->data);
        delete current_pointer->data;  

        current_pointer->data = nullptr;
        current_pointer->next = nullptr;
        delete current_pointer;

        current_pointer = nullptr;

        return true;
    }

    current_pointer =  head;
    Node *trackingPtr;

    while (current_pointer->next != nullptr && *(current_pointer->next->data) != target) 
    {
        current_pointer = current_pointer->next;
    }

    if (current_pointer->next == nullptr)
    {
        return false;
    }
    else
    {
        trackingPtr = current_pointer->next;
        result = *(trackingPtr->data);

        current_pointer->next = current_pointer->next->next;
        delete trackingPtr->data;    

        trackingPtr->data = nullptr;   
        delete trackingPtr;        

        trackingPtr = nullptr;          
        return true;
    }
}

template <class T>
bool List342<T>::Peek(T target, T &result) const
{
    if ( head == nullptr)
    {
        return false;
    }

    Node *current_pointer;
    current_pointer =  head;

    while (current_pointer != nullptr)
    {
        if (*(current_pointer->data) == target) 
        {
            result = *(current_pointer->data);                 
            return true;
        }
        else
        {
            current_pointer = current_pointer->next;
        }
    }
    return false;
}

template <class T>
bool List342<T>::isEmpty() const 
{
    return ( head == nullptr);
}

template <class T>
void List342<T>::DeleteList()
{
    Node *temp;
    while ( head != nullptr)
    {
        temp =  head;
        head =  head->next;

        delete temp->data;
        delete temp;
    }
    head = nullptr;
}

template <class T>
bool List342<T>::Merge(List342<T> &list1) 
{
    if (this == &list1 || list1. head == nullptr) 
    {
        return false;
    }

    if ( head == nullptr)
    {
        head = list1. head;
        list1. head = nullptr;

        return true;
    }

    Node *second_tracking_node;
    second_tracking_node = list1. head;

    if ((* head->data) >= *(second_tracking_node->data))
    {
        list1. head = list1. head->next;

        if (* head->data == *(second_tracking_node->data))
        {       
            delete (second_tracking_node->data);
            delete second_tracking_node;
        }
        else
        {
            second_tracking_node->next =  head;
            head = second_tracking_node;
        }
    }     

    Node *trackingNode;
    trackingNode =  head;
  
    while (list1. head != nullptr)
    {
        if (trackingNode->next != nullptr)
        {
            second_tracking_node = list1. head;

            if (*(second_tracking_node->data) < *(trackingNode->next->data))
            {
                list1. head = list1. head->next;

                second_tracking_node->next = trackingNode->next;
                trackingNode->next = second_tracking_node;

                trackingNode = second_tracking_node;
                second_tracking_node = nullptr;
            }
            else if (*(second_tracking_node->data) == *(trackingNode->next->data))
            {
                list1. head = list1. head->next;

                delete second_tracking_node->data;
                delete second_tracking_node;

                second_tracking_node = nullptr;
            }
            else
            {
                trackingNode = trackingNode->next;
            }
        }
        else
        {
            trackingNode->next = second_tracking_node;
            list1. head = nullptr;

            return true;
        }
    }

    return true;
}

template <class T>
List342<T> List342<T>::operator+(const List342<T> &rhs) const
{
    List342<T> tempList;

    tempList = *this;
    tempList += rhs; 
    
    return tempList;
}

template <class T>
List342<T>& List342<T>::operator+=(const List342<T> &rhs)
{
    if (rhs. head == nullptr)
    {
        return *this;
    }

    if ( head == nullptr)
    {
        *this = rhs;
        return *this;
    }

    Node *new_node_insert = rhs. head;

    while (new_node_insert != nullptr)
    {
        Insert(new_node_insert->data);
        new_node_insert = new_node_insert->next;
    }
    return *this;
}

template <class T>
bool List342<T>::operator==(const List342<T> &rhs) const
{
    if ((( head == nullptr) && (rhs. head != nullptr)) || (( head != nullptr) && (rhs. head == nullptr)))
    {
        return false;
    }

    Node *tracker1, *tracker2;
    
    tracker1 =  head;
    tracker2 = rhs.head;
    
    while (tracker1 != nullptr && tracker2 != nullptr)
    {
        if (*(tracker1->data) == *(tracker2->data))
        {
            tracker1 = tracker1->next;
            tracker2 = tracker2->next;
        }
        else
        {
            return false;
        }
    }

    if (((tracker1 == nullptr) && (tracker2 == nullptr)) || ((tracker1 != nullptr) && (tracker2 != nullptr)))
    {
        return true;
    }
    return false;
}

template <class T>
bool List342<T>::operator!=(const List342<T> &rhs) const
{
    return !(*this == rhs);
}

template <class T>
List342<T>& List342<T>::operator=(const List342<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    DeleteList();

    if (rhs.isEmpty())
    {
        return *this;
    }

    Node *assigned_node = new Node;
    T *assigned_item = new T;
    Node *tracker, *current;

    *assigned_item = *(rhs. head->data);

    assigned_node->data = assigned_item;
    assigned_node->next = nullptr;  

    head = assigned_node;

    tracker =  head;
    current = rhs. head->next;

    while (current != nullptr)
    {
        assigned_node = new Node;
        assigned_item = new T;

        *(assigned_item) = *(current->data);
        
        assigned_node->data = assigned_item;
        assigned_node->next = nullptr;   
        
        tracker->next = assigned_node;
        
        tracker = tracker->next;
        current = current->next;
    }
    return *this;
}

template <class T>
ostream& operator<<(ostream& stream, const List342<T> &rhs)
{
    if (rhs.isEmpty())
    {
        stream << "List is Empty" << endl;
        return stream;
    }

    typename List342<T>::Node* current_pointer;
    current_pointer = rhs.head;

    while (current_pointer != nullptr)
    {
        stream << *(current_pointer->data);
        current_pointer = current_pointer->next;
    }
    return stream;
}

/*
------------------------(Optional)Child Class-----------------------------------------------------------
*/

class Child 
{
public:
    Child();
    Child(string first_name, string last_name, int age);
    virtual ~Child(); //destructor

    string get_last_name() const;
    string get_first_name() const;
        
    int get_age() const;

    void set_last_name(const string &last_name);
    void set_first_name(const string &first_name);
    void set_age(const int &age);

    //Operator Overloads
    bool operator==(const Child &rhs) const;
    bool operator!=(const Child &rhs) const;

    bool operator>(const Child &rhs) const;
    bool operator>=(const Child &rhs) const;

    bool operator<(const Child &rhs) const;
    bool operator<=(const Child &rhs) const;
        
    Child& operator=(const Child &rhs);

    //Stream Overloads
    friend ostream& operator<<(ostream &stream, const Child &child);
    friend istream& operator>>(istream &stream, const Child &child);

private:
    string first_name_;
    string last_name_;
    int age_;
};

/*
------------------------(Optional)Child Implementation-----------------------------------------------------------
*/

Child::Child() : first_name_(""), last_name_(""), age_(0)
{
    //empty constructor
}

Child::Child(string the_first_name, string the_last_name, int the_age) : first_name_(the_first_name), last_name_(the_last_name), age_(the_age)
{

}

Child::~Child() 
{
    //empty destructor
}

string Child::get_last_name() const
{
    return last_name_;
}

string Child::get_first_name() const
{
    return first_name_;
}

int Child::get_age() const
{
    return age_;
}

void Child::set_last_name(const string &last_name)
{
    this->last_name_ = last_name;
}

void Child::set_first_name(const string &first_name)
{
    this->first_name_ = first_name;
}

void Child::set_age(const int &age)
{
    this->age_ = age;
}

bool Child::operator==(const Child &rhs) const
{
    if ((this->last_name_ == rhs.last_name_) && (this->first_name_ == rhs.first_name_) && (this->age_ == rhs.age_)) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Child::operator!=(const Child &rhs) const
{
    return !(*this == rhs);
}

bool Child::operator>(const Child &rhs) const
{
    if (last_name_ > rhs.last_name_)
    {
        return true;
    }

    if ((last_name_ == rhs.last_name_) && (first_name_ > rhs.first_name_))
    {
        return true;
    }

    if ((last_name_ == rhs.last_name_) && (first_name_ == rhs.first_name_) && (age_ > rhs.age_))
    {
        return true;
    }
    return false;
}

bool Child::operator>=(const Child &rhs) const
{
    return (*this > rhs || *this == rhs);
}

bool Child::operator<(const Child &rhs) const
{
    if (last_name_ < rhs.last_name_)
    {
        return true;
    }

    if ((last_name_ == rhs.last_name_) && (first_name_ < rhs.first_name_))
    {
        return true;
    }

    if ((last_name_ == rhs.last_name_) && (first_name_ == rhs.first_name_) && (age_ < rhs.age_))
    {
        return true;
    }

    return false;
}

bool Child::operator<=(const Child &rhs) const
{
    return (*this < rhs || *this == rhs);
}

Child& Child::operator=(const Child &rhs)
{
    last_name_ = rhs.last_name_;
    first_name_ = rhs.first_name_;
    age_ = rhs.age_;

    return *this;
}

ostream& operator<<(ostream &stream, const Child &child)
{
    stream << child.get_first_name() << child.get_last_name() << child.get_age();
    
    return stream;
}

istream& operator>>(istream &stream, Child &child)
{
    int age;
    string first_name, last_name;

    stream >> first_name >> last_name >> age;

    child.set_first_name(first_name);
    child.set_last_name(last_name);
    child.set_age(age);
    
    return stream;
}

