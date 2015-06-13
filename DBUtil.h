#include <string>
#include "cocos2d.h"
#include "sqlite3.h"
using namespace std;
using namespace cocos2d;
class DBUtil{

    
public:
    
    static void initDB(const char *db);
    
    static bool tableIsExist(string name);
    
    static void createTable(string sql,string name);
    
    static void deleteTable(string sql,string name);

    static void insertData(string sql);
    
    static void deleteData(string sql);

    static void updateData(string sql);
    
    static int getDataCount(string sql);
    
    static void getDataInfo(string sql,void *pSend);
    
    static void closeDB();

	int atoi(char   *s);
};
class UserVO
{
public:
	UserVO(){};
	~UserVO(){};
	int mId;
	string name;
	int lastscore;
	int bestscore;
    int lastkm;
    int bestkm;
    int jifen;
};
