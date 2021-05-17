use weather;



create table weather_info (
	
sample_id char(10) not null primary key,
    
pub_num char(10),
    
pub_stat char(5),
    
temperature char(20),
    
humidity char(20),
    
wind_speed char(20),
    
direction char(5)

)

ENGINE = InnoDB

DEFAULT CHARACTER SET = utf8;


INSERT INTO weather_info 
VALUES
(
	1,
    1,
    1,
    1,
    1,
    1,
    1
)