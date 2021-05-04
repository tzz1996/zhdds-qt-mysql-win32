#pragma once
#include <iostream>
#include <mysql.h>

#include "HelloWorld.h"



class Mysql {
private:
	MYSQL* ifconnect;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	MYSQL_FIELD *fd;
	int res;

public:
	Mysql();
	~Mysql();
	bool ConnectToMysql();
	bool CheckConnection();
	bool DisconnectToMysql();
	void InsertWeatherInfo();
	void CheckWeatherInfo();
	
	void InsertWeatherInfoWithInstance(HelloWorld* instance);
};