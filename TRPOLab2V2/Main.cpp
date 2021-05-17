#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <windows.h>

/// <summary>
/// Класс Singleton логирования
/// </summary>
class Singleton
{
private:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
public:
    static Singleton& Instance()
    {
        static Singleton instance;
        return instance;
    }
    static void AppendToLog(std::string Message)
    {
        //Объект класса для записи в лог файл
        std::ofstream logFile;
        //Текущие дата и время
        std::time_t now;
        std::tm* local;

        logFile.open("log.txt", std::ios_base::app);
        now = std::time(0);
        local = std::localtime(&now);
        //Запись в лог файл в формате "%Y-%m-%d %H:%M:%S Message" 
        logFile << std::put_time(local, "%F ")
            << std::put_time(local, "%T ") << Message << "\n";
    }
};

/// <summary>
/// Класс игрок
/// </summary>
class Player {
public:
    Singleton& log = Singleton::Instance();
    Player()
    {
        name.clear();
        std::string logString("Создан игрок ");
        log.AppendToLog(logString);
    }
    Player(std::string _name)
    {
        name.clear();
        std::string logString("Создан игрок ");
        log.AppendToLog(logString);
        this->setPlayerName(_name);
    }
    void setPlayerName(std::string _name)
    {
        name = _name;
        //Запись в лог файл
        std::string logString("Назначено имя игрока ");
        logString.append(_name);
        log.AppendToLog(logString);
    };
    std::string getPlayerName()
    {
        //Запись в лог файл
        std::string logString("Получено имя игрока ");
        logString.append(name);
        log.AppendToLog(logString);
        return name;
    };
    void inputPlayerName()
    {
        std::string logString("Запрос имени игрока");
        log.AppendToLog(logString);
        std::cout << "Как тебя зовут, герой?" << "\n";
        std::string _name;
        _name.clear();
        std::cin >> _name;
        this->setPlayerName(_name);
    }
private:
    std::string name;
};


//Абстрактный класс враг, из которого будут 3 подкласса прототипов врагов
class Enemy {
public:
    virtual ~Enemy() {};
    virtual Enemy* clone() const = 0; //необходимость переопределения метода в каждом из подклассов
    Singleton& log = Singleton::Instance();
};

//Подкласс врага: Орк
class Ork : public Enemy {
public:
    //  Ork(const Ork&) {};
    Ork()
    {
        std::string logString("Создание прототипа орка ");
        log.AppendToLog(logString);
    }
    Ork* clone() const
    {
        std::string logString("Клонирование орка ");
        log.AppendToLog(logString);
        return new Ork(*this);
    }
};

//Подкласс врага: Тролль
class Troll : public Enemy {
public:
    Troll()
    {
        std::string logString("Создание прототипа тролля ");
        log.AppendToLog(logString);
    }
    Troll* clone() const
    {
        std::string logString("Клонирование тролля ");
        log.AppendToLog(logString);
        return new Troll(*this);
    }
};

//Подкласс врага: Гоблин
class Goblin : public Enemy {
public:
    Goblin()
    {
        std::string logString("Создание прототипа гоблина ");
        log.AppendToLog(logString);
    }
    Goblin* clone() const
    {
        std::string logString("Клонирование гоблина ");
        log.AppendToLog(logString);
        return new Goblin(*this);
    }
};


//Класс, клонирующий прототипы
class EnemySpawner
{
private:
    Enemy* prototype;
    unsigned int count;
public:
    Singleton& log = Singleton::Instance();
    EnemySpawner(Enemy* _prototype) :prototype(_prototype)
    {
        count = 0;
        std::string logString("Создание клонирующего объекта ");
        log.AppendToLog(logString);
    }
    Enemy* spawnEnemy()
    {
        count++;
        return prototype->clone();

    }
    //   void killEnemy() { count--; }
    //   void killAll() { count = 0; }
    int getSpawnedCount()
    {
        std::string logString("Возвращение количества созданных клонов ");
        log.AppendToLog(logString);
        return count;
    }
};

class QuestGiver
{
private:
    std::string playerName;
    Singleton& log = Singleton::Instance();
    int orksToKill = 0, trollsToKill = 0, goblinsToKill = 0;
public:
    QuestGiver()
    {
        std::string logString("Создание КвестГивера ");
        log.AppendToLog(logString);
    }
    QuestGiver(std::string _playerName, int _orksToKill, int _trollsToKill, int _goblinsToKill)
    {
        std::string logString("Создание КвестГивера с инициализацией ");
        log.AppendToLog(logString);
        initialize(_playerName, _orksToKill, _trollsToKill, _goblinsToKill);

    }
    void initialize(std::string _playerName, int _orksToKill, int _trollsToKill, int _goblinsToKill)
    {
        playerName = _playerName;
        orksToKill = _orksToKill;
        trollsToKill = _trollsToKill;
        goblinsToKill = _goblinsToKill;
        std::string logString("Инициализация КвестГивера ");
        log.AppendToLog(logString);
    }
    void giveQuest()
    {
        std::string logString("Выдача задания");
        log.AppendToLog(logString);
        std::cout << "Доблестный герой " << playerName << " ! Я вижу честь и бесстрашие в тебе! Помоги мне, и я не останусь в долгу. "
            << "\nРазведчики сообщают, что неподалеку бесчинствуют ";
        if (orksToKill > 0) std::cout << orksToKill << " орков ";
        if (trollsToKill > 0) std::cout << trollsToKill << " троллей ";
        if (goblinsToKill > 0) std::cout << goblinsToKill << " гоблинов ";
        std::cout << "!\nРасправся с ними! " << std::endl;
    }
    ~QuestGiver() {}

};

class Facade
{
public:
    Singleton& log = Singleton::Instance();
    Player* player;
    Ork* orkPrototype;
    Troll* trollPrototype;
    Goblin* goblinPrototype;
    EnemySpawner* orkSpawner;
    EnemySpawner* trollSpawner;
    EnemySpawner* goblinSpawner;
    QuestGiver* questGiver;
    Facade()
    {
        std::string logString("Создание Фасада ");
        log.AppendToLog(logString);
        player = new Player();
        orkPrototype = new Ork();
        trollPrototype = new Troll();
        goblinPrototype = new Goblin();
        orkSpawner = new EnemySpawner(orkPrototype);
        trollSpawner = new EnemySpawner(trollPrototype);
        goblinSpawner = new EnemySpawner(goblinPrototype);
        questGiver = new QuestGiver();

    }
    void makeQuest()
    {
        std::string logString("Создание задания");
        log.AppendToLog(logString);
        player->inputPlayerName();
        for (int i = 1; i <= rand() % 5 + 1; i++)
        {
            orkSpawner->spawnEnemy();
        }
        for (int i = 1; i <= rand() % 3 + 1; i++)
        {
            trollSpawner->spawnEnemy();
        }
        for (int i = 1; i <= rand() % 10 + 1; i++)
        {
            goblinSpawner->spawnEnemy();
        }
        questGiver->initialize(player->getPlayerName(), orkSpawner->getSpawnedCount(), trollSpawner->getSpawnedCount(), goblinSpawner->getSpawnedCount());
        questGiver->giveQuest();
    }
};


int main()
{
    Singleton& log = Singleton::Instance();
    std::string logString("Старт приложения ");
    log.AppendToLog(logString);

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Facade* facade = new Facade;
    facade->makeQuest();

    logString.clear();
    logString.append("Завершение работы приложения");
    log.AppendToLog(logString);
}
