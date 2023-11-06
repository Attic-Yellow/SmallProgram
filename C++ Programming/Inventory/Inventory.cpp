#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

#define LEFT    75
#define RIGHT   77
#define UP      72
#define DOWN    80

using namespace std;

enum class PlayerLevel
{
    LEVEL_1 = 3,
    LEVEL_2 = 4,
    LEVEL_3 = 5,
    LEVEL_4 = 6
};

enum class Item
{
    ITEM_0 = 0,
    ITEM_1 = 1,
    ITEM_2 = 2,
    ITEM_3 = 3,
    ITEM_4 = 4,
    ITEM_5 = 5
};

enum class MenuOption
{
    OPTION_ITEM_PUT = 1,
    OPTION_BACK = 2,
    OPTION_SELECT = 3,
    OPTION_INFO = 4,
    OPTION_SWITCH_POSITION = 5
};

class GameDisplay
{
protected:
    void setCursorPosition(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    COORD getConsoleSize()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        COORD size = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
        return size;
    }

    int getDisplayLength(const std::string& str) {
        int length = 0;
        for (char c : str) {
            if ((c & 0x80) == 0)
                length += 1;
            else if ((c & 0xE0) == 0xC0)
                length += 2;
            else if ((c & 0xF0) == 0xE0)
                length += 2;
        }
        return length;
    }

public:
    static string getPlayerChoice(PlayerLevel playerLevel);
    static string getItemChoice(Item item);
};

class Player
{
private:
    vector<PlayerLevel> playerChoice;

public:
    Player();
    void print(int row);
    PlayerLevel getSelectedPlayerType(int row);
};

class Inventory : public GameDisplay
{
private:
    vector<vector<Item>> inven;

public:
    void setItem(int row, int col, Item item);
    Item getItem(int row, int col);
    bool isEmpty(int row, int col);
    Inventory(int num);
    void print(int row, int col);
    void printMenu(vector<MenuOption>& menuOptions, int& selectedIndex);
    vector<MenuOption> getMenuOptions(bool emptySlot);
};

class ItemSelector : GameDisplay
{
private:
    vector<Item> items;
    int selectedIndex;

public:
    ItemSelector(const vector<Item>& items);
    ItemSelector();
    Item chooseItem();
    void printItems();
    vector<Item> getItemSelector() const;
};

class Menu : public GameDisplay
{
private:
    vector<MenuOption> options;
    int selectedIndex;

public:
    Menu(const vector<MenuOption>& options);
    std::pair<bool, Item> navigateMenu();
    void printMenu();
    MenuOption getSelectedOption() const;
};

class Game
{
public:
    static int pressKey();
    static void Ineventory(int num);
};

void initializePlayer(vector<PlayerLevel>& player);
void initializeInven(vector<vector<Item>>& inven);

int main()
{
    Player player;
    PlayerLevel selectedPlayerType = PlayerLevel::LEVEL_1;
    int inventorySize = 0;
    int row = 0;
    int col = 1;

    while (1)
    {
        player.print(row);
        int key = Game::pressKey();

        switch (key)
        {
        case DOWN:
            if (row < 3)
                row++;
            else
                row = 0;
            break;
        case UP:
            if (row > 0)
                row--;
            else
                row = 3;
            break;
        case 'z':
            selectedPlayerType = player.getSelectedPlayerType(row);
            inventorySize = static_cast<int>(selectedPlayerType);
            row = inventorySize - 1;
            col = inventorySize - 1;
            Game::Ineventory(inventorySize);
            return EXIT_SUCCESS;
        default:
            continue;
        }
    }
    return 0;
}

string GameDisplay::getPlayerChoice(PlayerLevel playerLevel)
{
    switch (playerLevel)
    {
    case PlayerLevel::LEVEL_1:
        return "\t3 x 3 공간";
    case PlayerLevel::LEVEL_2:
        return "\t4 x 4 공간";
    case PlayerLevel::LEVEL_3:
        return "\t5 x 5 공간";
    case PlayerLevel::LEVEL_4:
        return "\t6 x 6 공간";
    default:
        return "\t비어있는 공간";
    }
}

string GameDisplay::getItemChoice(Item item)
{
    switch (item)
    {
    case Item::ITEM_0:
        return "검";
    case Item::ITEM_1:
        return "방패";
    case Item::ITEM_2:
        return "지팡이";
    case Item::ITEM_3:
        return "활";
    case Item::ITEM_4:
        return "뒤로 가기";
    case Item::ITEM_5:
        return "비어 있음";
    default:
        return "알 수 없음";
    }
}

Player::Player()
{
    initializePlayer(playerChoice);
}


void Player::print(int row)
{
    system("cls");
    cout << "\n\n" << "\t\t 공간 크기 설정" << "\n\n";
    for (int i = 0; i < playerChoice.size(); i++)
    {
        cout << "\t" << GameDisplay::getPlayerChoice(playerChoice[i]) << (i == row ? "\t◀" : "") << "\n\n";
    }
    cout << "\n\t\t>> 방향키( ↓, ↑ ) 또는 'z'( 선택 )를 눌러주세요!!\n";
}

PlayerLevel Player::getSelectedPlayerType(int row)
{
    return playerChoice[row];
}

Inventory::Inventory(int num)
{
    inven.resize(num, vector<Item>(num));
    initializeInven(inven);
}

void Inventory::print(int row, int col)
{
    system("cls");

    int cellWidth = 25;
    int invenSize = inven.size();
    int totalWidth = invenSize * cellWidth + invenSize - 4;

    COORD consoleSize = getConsoleSize();
    int startX = (consoleSize.X - totalWidth) / 2;
    int startY = (consoleSize.Y - (invenSize * 2)) / 2;

    setCursorPosition(startX, startY);

    cout << "+" << string(totalWidth, '-') << "+" << endl;
    startY++;
    setCursorPosition(startX, startY);

    for (int i = 0; i < invenSize; i++)
    {
        for (int j = 0; j < invenSize; j++)
        {
            string itemText = GameDisplay::getItemChoice(inven[i][j]);
            string paddingLeft((cellWidth - itemText.size() - 2) / 2, ' ');
            string paddingRight = paddingLeft;

            if (itemText.size() % 2 == 1)
                paddingLeft.pop_back();

            if (i == row && j == col)
            {
                cout << "|" + paddingLeft + itemText + paddingRight + "◀";
            }
            else
            {
                cout << "|" + paddingLeft + " " + itemText + paddingRight + " ";
            }
        }
        cout << "|" << endl;

        if (i != invenSize - 1)
        {
            setCursorPosition(startX, startY + i * 2 + 1);
            for (int j = 0; j < invenSize; j++)
            {
                cout << "+" << string(cellWidth - 1, '-');
            }
            cout << "+" << endl;
            setCursorPosition(startX, startY + i * 2 + 2);
        }
    }

    setCursorPosition(startX, startY + invenSize * 2 - 1);
    cout << "+" << string(totalWidth, '-') << "+";
}

Menu::Menu(const vector<MenuOption>& options) : options(options), selectedIndex(0) {}

void Menu::printMenu()
{
    system("cls");

    int cellWidth = 25;
    int menuHeight = options.size() * 2 + 3;
    COORD consoleSize = getConsoleSize();
    int startX = (consoleSize.X - cellWidth) / 2;
    int startY = (consoleSize.Y - menuHeight) / 2;

    setCursorPosition((consoleSize.X - 7) / 2, startY);
    cout << "메뉴 선택" << endl;

    startY++;

    setCursorPosition(startX, startY);
    cout << "+" << string(cellWidth, '-') << "+";
    startY++;

    for (int i = 0; i < options.size(); i++)
    {
        setCursorPosition(startX, startY + i * 2);
        string menuText;
        switch (options[i])
        {
        case MenuOption::OPTION_ITEM_PUT: menuText = "아이템 넣기"; break;
        case MenuOption::OPTION_BACK: menuText = "뒤로 가기"; break;
        case MenuOption::OPTION_SELECT: menuText = "정보 보기"; break;
        case MenuOption::OPTION_INFO: menuText = "사용 하기"; break;
        case MenuOption::OPTION_SWITCH_POSITION: menuText = "조합 하기"; break;
        }

        int paddingSize = (cellWidth - menuText.size()) / 2;
        string paddingLeft(paddingSize, ' ');
        string paddingRight(paddingSize, ' ');

        if (menuText.size() % 2 == 1)
            paddingLeft.pop_back();

        if (i == selectedIndex)
        {
            cout << "|" + paddingLeft + menuText + paddingLeft + "◀";
        }
        else
        {
            cout << "|" + paddingLeft + " " + menuText + paddingRight;
        }

        cout << "|" << endl;

        if (i != options.size() - 1)
        {
            setCursorPosition(startX, startY + i * 2 + 1);
            cout << "+" << string(cellWidth, '-') << "+";
        }
    }

    setCursorPosition(startX, startY + menuHeight - 4);
    cout << "+" << string(cellWidth, '-') << "+";
    setCursorPosition(startX, startY + menuHeight - 2);
    cout << ">> 방향키( ↓, ↑ ) 또는 'z'( 선택 )를 눌러주세요!!";
}

pair<bool, Item> Menu::navigateMenu()
{
    while (true)
    {
        printMenu();
        int key = Game::pressKey();

        switch (key)
        {
        case UP:
            if (selectedIndex > 0) selectedIndex--;
            else selectedIndex = options.size() - 1;
            break;
        case DOWN:
            if (selectedIndex < options.size() - 1) selectedIndex++;
            else selectedIndex = 0;
            break;
        case 'z':
            switch (options[selectedIndex])
            {
            case MenuOption::OPTION_BACK:
                return { false, Item::ITEM_0 };
            case MenuOption::OPTION_ITEM_PUT:
            {
                ItemSelector itemSelector;
                Item chosenItem = itemSelector.chooseItem();
                return { true, chosenItem };
            }

            }
            break;
        default:
            continue;
        }
    }
}

vector<MenuOption> Inventory::getMenuOptions(bool emptySlot)
{
    if (emptySlot)
    {
        return { MenuOption::OPTION_ITEM_PUT, MenuOption::OPTION_BACK };
    }
    else
    {
        return { MenuOption::OPTION_SELECT, MenuOption::OPTION_INFO, MenuOption::OPTION_SWITCH_POSITION, MenuOption::OPTION_BACK };
    }
}

MenuOption Menu::getSelectedOption() const
{
    return options[selectedIndex];
}

ItemSelector::ItemSelector(const vector<Item>& items) : items(items), selectedIndex(0) {}

void ItemSelector::printItems()
{
    system("cls");

    int cellWidth = 25;
    int menuHeight = items.size() * 2 + 3;
    COORD consoleSize = getConsoleSize();
    int startX = (consoleSize.X - cellWidth) / 2;
    int startY = (consoleSize.Y - menuHeight) / 2;

    setCursorPosition((consoleSize.X - 9) / 2, startY);
    cout << "아이템 선택" << endl;

    startY++;

    setCursorPosition(startX, startY);
    cout << "+" << string(cellWidth, '-') << "+";
    startY++;

    for (int i = 0; i < items.size(); i++)
    {
        setCursorPosition(startX, startY + i * 2);
        string itemText;

        switch (items[i])
        {
        case Item::ITEM_0: itemText = "검"; break;
        case Item::ITEM_1: itemText = "방패"; break;
        case Item::ITEM_2: itemText = "지팡이"; break;
        case Item::ITEM_3: itemText = "활"; break;
        case Item::ITEM_4: itemText = "뒤로 가기"; break;
        case Item::ITEM_5: itemText = "비어 있음"; break;
        default: itemText = "알 수 없음";
        }
        int paddingSize = (cellWidth - itemText.size()) / 2;
        string paddingLeft(paddingSize, ' ');
        string paddingRight(paddingSize - 1, ' ');

        if (itemText.size() % 2 == 1)
            paddingLeft.pop_back();

        if (i == selectedIndex)
        {
            cout << "|" + paddingLeft + itemText + paddingRight + "◀";
        }
        else
        {
            cout << "|" + paddingLeft + " " + itemText + paddingRight + " ";
        }

        cout << "|" << endl;

        if (i != items.size() - 1)
        {
            setCursorPosition(startX, startY + i * 2 + 1);
            cout << "+" << string(cellWidth, '-') << "+";
        }
    }

    setCursorPosition(startX, startY + menuHeight - 4);
    cout << "+" << string(cellWidth, '-') << "+";
    setCursorPosition(startX, startY + menuHeight - 2);
    cout << ">> 방향키( ↓, ↑ ) 또는 'z'( 선택 )를 눌러주세요!!";
}

void Inventory::setItem(int row, int col, Item item)
{
    inven[row][col] = item;
}

Item Inventory::getItem(int row, int col)
{
    return inven[row][col];
}

ItemSelector::ItemSelector() : selectedIndex(0)
{
    items.push_back(Item::ITEM_0);
    for (int i = static_cast<int>(Item::ITEM_1); i < static_cast<int>(Item::ITEM_5); ++i)
    {
        items.push_back(static_cast<Item>(i));
    }
}

Item ItemSelector::chooseItem()
{
    while (true)
    {
        printItems();
        int key = Game::pressKey();

        switch (key)
        {
        case UP:
            if (selectedIndex > 0) selectedIndex--;
            else selectedIndex = items.size() - 1;
            break;
        case DOWN:
            if (selectedIndex < items.size() - 1) selectedIndex++;
            else selectedIndex = 0;
            break;
        case 'z':
            return items[selectedIndex];
        default:
            continue;
        }
    }
}

bool Inventory::isEmpty(int row, int col)
{
    return inven[row][col] == Item::ITEM_5;
}

int Game::pressKey()
{
    int key = _getch();
    if (key == 224)
    {
        return _getch();
    }
    return key;
}

void Game::Ineventory(int num)
{
    Inventory inven(num);
    int row = num - 1;
    int col = num - 1;

    while (1)
    {
        inven.print(row, col);
        cout << "\n\t\t>> 방향키( ←, ↓, ↑, → ) 또는 'z'( 선택 )를 눌러주세요!!\n";
        int key = pressKey();

        switch (key)
        {
        case LEFT:
            if (col > 0)
                col--;
            break;
        case RIGHT:
            if (col < num - 1)
                col++;
            break;
        case DOWN:
            if (row < num - 1)
                row++;
            break;
        case UP:
            if (row > 0)
                row--;
            break;
        case 'z':
        {
            vector<MenuOption> menuOptions = inven.getMenuOptions(inven.isEmpty(row, col));
            Menu menu(menuOptions);
            auto menuResult = menu.navigateMenu();
            if (!menuResult.first)
                continue;
            if (menuResult.second == Item::ITEM_4)
                continue;
            inven.setItem(row, col, menuResult.second);
            break;
        }
        default:
            continue;
        }
    }
}

void initializePlayer(vector<PlayerLevel>& player)
{
    player.clear();
    player.push_back(PlayerLevel::LEVEL_1);
    player.push_back(PlayerLevel::LEVEL_2);
    player.push_back(PlayerLevel::LEVEL_3);
    player.push_back(PlayerLevel::LEVEL_4);
}

void initializeInven(vector<vector<Item>>& inven)
{
    for (int i = 0; i < inven.size(); i++)
    {
        for (int j = 0; j < inven[i].size(); j++)
        {
            inven[i][j] = Item::ITEM_5;
        }
    }
}
