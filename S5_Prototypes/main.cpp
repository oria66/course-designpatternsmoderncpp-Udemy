#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

enum ALARM_TYPE{
    SOFT,
    HARD
};

class Alarm
{
public:
    explicit Alarm(const int newCode, const string newDescription): code(newCode), description(newDescription) {}
    virtual ~Alarm() {}
    virtual unique_ptr<Alarm> clone() = 0;

    int getCode() const
    {
        return code;
    }

protected:
    int code{};
    string description{};
};

class SoftAlarm : public Alarm
{
public:
    explicit SoftAlarm(const int code, const string descrip, const int newRemainingSecs) :
        Alarm(code, descrip), remainingSecs(newRemainingSecs){}

    unique_ptr<Alarm> clone(){
        return make_unique<SoftAlarm>(*this);
    }

    int getRemainingSecs() const
    {
        return remainingSecs;
    }

private:
    int remainingSecs{};
};

class HardAlarm : public Alarm
{
public:
    explicit HardAlarm(const int code, const string descrip, const bool newRecognized) :
        Alarm(code, descrip), recognized(newRecognized){}

    unique_ptr<Alarm> clone(){
        return make_unique<HardAlarm>(*this);
    }

    bool getRecognized() const
    {
        return recognized;
    }

private:
    bool recognized{};
};

class AlarmFactory
{
public:
    AlarmFactory(){
        map[SOFT] = make_unique<SoftAlarm>(2, "This is a soft alarm", 10);
        map[HARD] = make_unique<HardAlarm>(1, "This is a hard alarm", false);
    }

    ~AlarmFactory(){
        map[SOFT].release();
        map[HARD].release();
    }

    unique_ptr<Alarm> create(ALARM_TYPE type)
    {
        return map[type]->clone();
    }

private:
    unordered_map<ALARM_TYPE, unique_ptr<Alarm>> map;
};

int main()
{
    AlarmFactory factory;

    auto hardAlarm = factory.create(HARD);
    auto softAlarm = factory.create(SOFT);

    cout << hardAlarm->getCode() << endl;
    cout << softAlarm->getCode() << endl;

    hardAlarm.release();
    softAlarm.release();

    return 0;
}






