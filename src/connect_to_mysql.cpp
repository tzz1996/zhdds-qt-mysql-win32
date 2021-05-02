#include <iostream>
#include <Windows.h>
#include <string>

#include "connect_to_mysql.h"


using namespace std;

Mysql::Mysql() {

}


Mysql::~Mysql() {

}


bool Mysql::ConnectToMysql() {
	const char user[] = "tzz";            //username  
	const char pswd[] = "123456";         //password  
	const char host[] = "localhost";      //or"127.0.0.1"  
	const char table[] = "kechengsheji";  //database  
	unsigned int port = 3306;             //server port          

	mysql_init(&myCont);
	//mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0);
	ifconnect = mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0);
	//ÉèÖÃ×Ö·û
	mysql_query(&myCont, "set names gbk");
	if (ifconnect)
		return TRUE;
	else 
		return FALSE;
}


bool Mysql::DisconnectToMysql() {
	if (ifconnect) {
		mysql_close(&myCont);
		ifconnect = FALSE;
	}
	if (ifconnect)
		return FALSE;
	else
		return TRUE;
}


