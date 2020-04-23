create database RaceManagement2
go
use RaceManagement2
go

--- 1. Create tables

create table Pilots(
PID int primary key identity(1,1),
FName varchar(50),
LName varchar(50),
DoB date)

create table Cars(
CID int primary key identity(1,1),
PID int foreign key references Pilots(PID),
Brand varchar(50),
Color varchar(50))

create table RaceType(
RTID int primary key identity(1,1),
Name varchar(50) unique,
Description varchar(50),
AvgBudget int)

create table Race(
RID int primary key identity(1,1),
RTID int foreign key references RaceType(RTID) on delete cascade,
Name varchar(50),
Location varchar(50),
RDate date)

create table RaceCar(
RID int foreign key references Race(RID) on delete cascade,
--PID int foreign key references Pilots(PID),
CID int foreign key references Cars(CID)
constraint pk_racepilot primary key (RID, CID),
Ranking int)

/*
drop table RaceCar
drop table Race
drop table RaceType
drop table Cars
drop table Pilots
*/

go

insert into Pilots values ('Ion','Ionescu', '1999-01-01'),('Vasile','Vasilescu','1999-01-01'),('Gheorghe','Gheorghescu', '1999-01-01')
insert into Cars values (1,'Ford','Red'),(1,'Toyota','Blue'),(2,'Tesla','Black'),(2,'Hyundai','Green'),(3,'VW','Silver')
insert into RaceType values ('Sports','2 laps',2000),('Endurance','4 laps',4000),('RaceToDelete','smth',5000)
insert into Race values (1,'Race','Location','2020-01-01'), (2,'Race2','London','2020-01-02'), (3,'Race3','Sydney','2020-01-03')
insert into RaceCar values (1,1,2),(1,3,1),(1,5,3),(2,2,1),(2,4,2) 

select * from Pilots
select * from Cars
select * from RaceType
select * from Race
select * from RaceCar

go

--- 2. Create procedure
create or alter procedure deleteRaceType @RTName varchar(50) as
begin
	declare @RTID int
	set @RTID = (select RTID from RaceType where Name = @RTName)
	---delete from Race where RTID = @RTID
	delete from RaceType where Name = @RTName
end


exec deleteRaceType 'RaceToDelete'

go

--- 3. Create view
create or alter view view_Pilots as
select FName, LName
from Pilots
where PID IN
			(select PID
			from RaceCar RC INNER JOIN Cars C ON RC.CID = C.CID
			group by PID
			having count(RID) = (select count(*) from Race))
go

select * from view_Pilots

go

--- 4. Create function

create function f_maxRace ()
RETURNS TABLE
AS
	RETURN
	SELECT Name
	FROM Race
	WHERE RID IN (
		SELECT RID
		FROM RaceCar
		GROUP BY RID
		HAVING COUNT(CID) = (
			SELECT MAX(NoCars)
			FROM (SELECT Count(CID) as NoCars FROM RaceCar GROUP BY RID) AS T))
GO

select * from f_maxRace()