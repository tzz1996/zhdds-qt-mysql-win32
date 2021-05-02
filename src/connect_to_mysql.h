#pragma once
#include <iostream>
#include <mysql.h>



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
	void CheckConnection();
	bool DisconnectToMysql();
	void InsertMember();
	void DropMember();
	void InputManey();
	void CheckMember();
	void CheckInformation();
};