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
	void InsertWeatherInfo2(struct WeatherInfo arg);
	void CheckWeatherInfo();
	void CheckWeatherInfo2(std::string sample_id);
	bool HaveSqlRowData();
	struct WeatherInfo GetSqlRowData();
	
	void InsertWeatherInfoWithInstance(HelloWorld* instance);
};

struct WeatherInfo {
	std::string sample_id;
	std::string pub_num;
	std::string pub_stat;
	std::string temperature;
	std::string humidity;
	std::string wind_speed;
	std::string direction;
};