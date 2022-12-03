#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct TodoItem
{
    string name;
    string description;
    int priority = 0;
    bool doneStatus = false;
};

enum SortType
{
    None,
    Asc,
    Desc
};

using TodoList = vector<TodoItem>;

TodoItem editItem(TodoItem &item)
{
    cout << "Enter name: ";
    cin >> item.name;
    cout << "Enter description: ";
    cin >> item.description;
    cout << "Enter priority: ";
    cin >> item.priority;
    cout << "Enter status: ";
    cin >> item.doneStatus;
    return item;
}

TodoItem createItem()
{
    TodoItem item;
    editItem(item);
    return item;
}

void addNewItem(TodoList &list)
{
    TodoItem item = createItem();
    list.push_back(item);
}

void viewItem(const TodoItem &item)
{
    cout << "Name: " << item.name << endl;
    cout << "Description: " << item.description << endl;
    cout << "Priority: " << item.priority << endl;
    cout << "Status: " << item.doneStatus << endl;
}

bool compareAsc(const TodoItem &l, const TodoItem &r)
{
    return l.name < r.name;
}

bool compareDesc(const TodoItem &l, const TodoItem &r)
{
    return l.name > r.name;
}

void smartViewList(const TodoList &list, string *nameFilter = 0, string *descriptionFilter = 0, bool *statusFilter = 0, SortType sortType = SortType::None)
{
    cout << "*** Begin list *** " << endl;
    TodoList viewList;
    size_t i;
    for (i = 0; i < list.size(); i++)
    {
        const TodoItem &item = list[i];
        const bool isName = (nameFilter == 0 || item.name == *nameFilter);
        const bool isDescription = (descriptionFilter == 0 || item.description == *descriptionFilter);
        const bool isStatus = (statusFilter == 0 || item.doneStatus == *statusFilter);

        if (isName && isDescription && isStatus)
        {
            viewList.push_back(list[i]);
        }
    }

    if (sortType == SortType::Asc)
    {
        sort(viewList.begin(), viewList.end(), compareAsc);
    }
    else if (sortType == SortType::Desc)
    {
        sort(viewList.begin(), viewList.end(), compareDesc);
    }

    for (i = 0; i < viewList.size(); i++)
    {
        cout << "Item " << i << "." << endl;
        viewItem(viewList[i]);
        cout << endl;
    }
    cout << "*** End list *** " << endl;
}

void viewList(const TodoList &list)
{
    cout << "You want to sort items by: " << endl;
    cout << "1. Asc " << endl;
    cout << "2. Desc " << endl;
    cout << "3. No sort " << endl;
    cout << "Please select number: ";

    int command;
    cin >> command;

    cout << endl;

    switch (command)
    {
    case 1:
        smartViewList(list, 0, 0, 0, SortType::Asc);
        break;
    case 2:
        smartViewList(list, 0, 0, 0, SortType::Desc);
        break;
    case 3:
        smartViewList(list, 0, 0, 0, SortType::None);
        break;
    default:
        cout << "You have entered invalid index." << endl;
        break;
    }
}

void deleteItem(TodoList &list)
{
    cout << "Please enter index: " << endl;
    size_t index;
    cin >> index;

    if (index >= 0 && index < list.size())
    {
        list.erase(list.begin() + index);
    }
    else
    {
        cout << "You have entered invalid index." << endl;
    }
}

void editItem(TodoList &list)
{
    cout << "Please enter index: " << endl;
    size_t index;
    cin >> index;

    if (index >= 0 && index < list.size())
    {
        TodoItem &item = *(list.begin() + index);
        editItem(item);
    }
    else
    {
        cout << "You have entered invalid index." << endl;
    }
}

void findItems(const TodoList &list)
{
    cout << "You want to find items by: " << endl;
    cout << "1. Name " << endl;
    cout << "2. Description " << endl;
    cout << "3. Status " << endl;
    cout << "Please select number: ";

    int command;
    cin >> command;

    switch (command)
    {
    case 1:
    {
        string name;
        cout << "Please enter name: ";
        cin >> name;
        smartViewList(list, &name);
    }
    break;
    case 2:
    {
        string description;
        cout << "Please enter description: ";
        cin >> description;
        smartViewList(list, 0, &description);
    }
    break;
    case 3:
    {
        bool status;
        cout << "Please enter status: ";
        cin >> status;
        smartViewList(list, 0, 0, &status);
    }
    break;
    default:
        cout << "You have entered invalid index." << endl;
        break;
    }
}

int main()
{
    vector<TodoItem> list;

    cout << "Hello. This is todo list !" << endl;

    bool doing = true;
    while (doing)
    {
        int command = 0;

        cout << "************************************" << endl;
        cout << "1. View the list" << endl;
        cout << "2. Add item to the list" << endl;
        cout << "3. Remove item from list" << endl;
        cout << "4. Edit item in list" << endl;
        cout << "5. Find items in list" << endl;
        cout << "6. Exit" << endl;

        cout << "Please select number: ";
        cin >> command;
        cout << "************************************" << endl;

        switch (command)
        {
        case 1:
            cout << "View the list: " << endl;
            viewList(list);
            break;
        case 2:
            cout << "Add item to the list: " << endl;
            addNewItem(list);
            break;
        case 3:
            cout << "Delete item from the list: " << endl;
            deleteItem(list);
            break;
        case 4:
            cout << "Edit item in list: " << endl;
            editItem(list);
            break;
        case 5:
            cout << "Find items in list: " << endl;
            findItems(list);
            break;
        case 6:
            doing = false;
            break;

        default:
            cout << "You have entered invalid command. Please try again." << endl;
            break;
        }

        cout << endl;
    }

    cout << "Goodbye!" << endl;
}
