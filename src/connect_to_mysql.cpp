#include <iostream>
#include <Windows.h>
#include <string>

#include "connect_to_mysql.h"


using namespace std;

Mysql::Mysql() {
	ifconnect = false;
	result = NULL;
	fd = NULL;
}


Mysql::~Mysql() {

}


bool Mysql::ConnectToMysql() {
	const char user[] = "tzz";            //username  
	const char pswd[] = "123456";         //password  
	const char host[] = "localhost";      //or"127.0.0.1"  
	const char table[] = "weather";  //database  
	unsigned int port = 3306;             //server port          

	mysql_init(&myCont);
	//mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0);
	ifconnect = mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0);
	//设置字符
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

bool Mysql::CheckConnection(){
	if (ifconnect)
		return true;
	else
		return false;
}

void Mysql::InsertWeatherInfo() {
	string insert_str;
	string sample_id, pub_num, pub_stat, temperature, humidity, wind_speed, direction;

	sample_id = "2";
	pub_num = "2";
	pub_stat = "2";
	temperature = "2";
	humidity = "2";
	wind_speed = "2";
	direction = "2";

	insert_str = "INSERT INTO weather_info VALUES('" +
		sample_id + "', '" +
		pub_num + "', '" +
		pub_stat + "', '" +
		temperature + "', '" +
		humidity + "', '" +
		wind_speed + "', '" +
		direction + "');";

	if (mysql_query(&myCont, insert_str.c_str()) == 0)
		cout << "weatherinfo插入成功" << endl;
	else
		cout << "weatherinfo插入失败" << endl;

}

void Mysql::InsertWeatherInfo2(struct WeatherInfo arg) {
	string insert_str;

	insert_str = "INSERT INTO weather_info VALUES('" +
		arg.sample_id + "', '" +
		arg.pub_num + "', '" +
		arg.pub_stat + "', '" +
		arg.temperature + "', '" +
		arg.humidity + "', '" +
		arg.wind_speed + "', '" +
		arg.direction + "');";

	if (mysql_query(&myCont, insert_str.c_str()) == 0)
		cout << "weatherinfo插入成功" << endl;
	else
		cout << "weatherinfo插入失败" << endl;
}


void Mysql::CheckWeatherInfo() {
	string insert_str;
	string sample_id = "2";
	insert_str = "SELECT * FROM weather_info WHERE sample_id='" + sample_id + "'";

	res = mysql_query(&myCont, insert_str.c_str());
	if (!res) {
		result = mysql_store_result(&myCont);
		if (result) {
			sql_row = mysql_fetch_row(result);
		}
	}

	cout << "sample id = " << sql_row[0] << endl;
	cout << "pub num = " << sql_row[1] << endl;
	cout << "pub stat = " << sql_row[2] << endl;
	cout << "temperature = " << sql_row[3] << endl;
	cout << "humidity = " << sql_row[4] << endl;
	cout << "wind speed = " << sql_row[5] << endl;
	cout << "direction = " << sql_row[6] << endl;

	if (result != NULL)
		mysql_free_result(result);
}

void Mysql::CheckWeatherInfo2(std::string sample_id) {
	string insert_str;
	insert_str = "SELECT * FROM weather_info WHERE sample_id='" + sample_id + "'";

	res = mysql_query(&myCont, insert_str.c_str());
	if (!res) {
		result = mysql_store_result(&myCont);
		if (result) {
			sql_row = mysql_fetch_row(result);
		}
	}

	if (sql_row == NULL) {
		cout << "no such sample id." << endl;
		return;
	}

	cout << "====================" << endl;
	cout << "sample id = " << sql_row[0] << endl;
	cout << "pub num = " << sql_row[1] << endl;
	cout << "pub stat = " << sql_row[2] << endl;
	cout << "temperature = " << sql_row[3] << endl;
	cout << "humidity = " << sql_row[4] << endl;
	cout << "wind speed = " << sql_row[5] << endl;
	cout << "direction = " << sql_row[6] << endl;

	if (result != NULL)
		mysql_free_result(result);
}

bool Mysql::HaveSqlRowData() {
	if (sql_row != NULL)
		return true;
	else
		return false;
}

struct WeatherInfo Mysql::GetSqlRowData() {
	struct WeatherInfo info;

	info.sample_id = sql_row[0];
	info.pub_num = sql_row[1];
	info.pub_stat = sql_row[2];
	info.temperature = sql_row[3];
	info.humidity = sql_row[4];
	info.wind_speed = sql_row[5];
	info.direction = sql_row[6];

	return info;
}
