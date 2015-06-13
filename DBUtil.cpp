#include "DBUtil.h"
sqlite3 *pDB = NULL;
char * errMsg = NULL;
std::string sqlstr;
int result;

void DBUtil::initDB(const char *db )
{
    result = sqlite3_open(db, &pDB);
    if( result != SQLITE_OK )
        CCLOG( "Fail to open the database, error code:%d, error cause:%s\n" , result, errMsg );
}

int isExisted( void * para, int n_column, char ** column_value, char ** column_name )
{
    bool *isExisted_=(bool*)para;
    *isExisted_=(**column_value)!='0';
    return 0;
}


bool DBUtil::tableIsExist( string name )
{
    if (pDB!=NULL)
    {
        bool tableIsExisted;
        sqlstr = "select count(type) from sqlite_master where type='table' and name ='"+name+"'";
        result =sqlite3_exec(pDB,sqlstr.c_str(),isExisted,&tableIsExisted,&errMsg);
        return tableIsExisted;
    }
    return false;
}


void DBUtil::createTable( string sql,string name )
{
    if (!tableIsExist(name))
    {
        result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
        if( result != SQLITE_OK )
            CCLOG( "Fail to create  a table, error code:%d, error cause:%s\n" , result, errMsg );
    }
    
}

void DBUtil::deleteTable( string sql,string name )
{
    if (tableIsExist(name))
    {
        result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
        if( result != SQLITE_OK )
            CCLOG( "Fail to create  a table, error code:%d, error cause:%s\n" , result, errMsg );
    }
}

void DBUtil::insertData( string sql ){
    result = sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLOG( "Fail to insert  a record, error code:%d, error cause:%s\n" , result, errMsg );
}


void DBUtil::deleteData( string sql )
{
    result=sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLOG( "Fail to insert  a record, error code:%d, error cause:%s\n" , result, errMsg );
}

void DBUtil::updateData( string sql )
{
    result = sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        CCLOG( "Fail to insert  a record, error code:%d, error cause:%s\n" , result, errMsg );
}


//getDataCount的回调函数
int loadRecordCount( void * para, int n_column, char ** column_value, char ** column_name )
{
    int *count=(int*)para;
    *count=n_column;
    return 0;
}
int DBUtil::getDataCount( string sql )
{
    int count=0;
    sqlite3_exec( pDB, sql.c_str() , loadRecordCount, &count, &errMsg );
    return count;
}


int loadRecord( void * para, int n_column, char ** column_value, char ** column_name )
{
    CCLOG("n_column:%d",n_column);
    // mId name lastscore  bestscore
    UserVO* userVO = (UserVO*)para;
    
	userVO->mId = atoi(column_value[0]);
	userVO->name = column_value[1];
	userVO->lastscore = atoi(column_value[2]);
	userVO->bestscore = atoi(column_value[3]);
    userVO->lastkm = atoi(column_value[4]);
    userVO->bestkm = atoi(column_value[5]);
    userVO->jifen = atoi(column_value[6]);
    return 0;
}
void DBUtil::getDataInfo( string sql,void *pSend )
{
    sqlite3_exec( pDB, sql.c_str() , loadRecord, pSend, &errMsg );
}

void DBUtil::closeDB()
{
    sqlite3_close(pDB);
}
int DBUtil::atoi(char   *s)
{
	char   *p  =  s;
	char   c;
	int   i   =   0;
	while(c = *p++)
	{
		if(c>='0'   &&   c<='9')
		{
			i   =   i*10   +   (c-'0');
		}
		else
			return   -1;                   
	}
	return   i;
} 