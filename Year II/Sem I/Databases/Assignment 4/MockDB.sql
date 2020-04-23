create database TestAirline
go
use TestAirline
go

create table Pilot(
PilotID int primary key,
Name varchar(50))

create table Flight(
FlightID int primary key,
PilotID int foreign key references Pilot(PilotID),
DepartureAirport varchar(20),
ArrivalAirport varchar(20))

create table Booking(
PassengerID int,
FlightID int foreign key references Flight(FlightID),
CONSTRAINT PK_Booking PRIMARY KEY (PassengerID, FlightID),
Price int)