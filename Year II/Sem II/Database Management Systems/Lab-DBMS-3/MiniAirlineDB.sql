create database MiniAirline
go

use MiniAirline
go

create table Aircraft(
AircraftID int primary key identity(1,1),
Producer varchar(50),
Capacity int default 250)

create table Pilot(
PilotID int primary key identity(1,1),
Name varchar(50),
Age int)

create table Flight(
FlightID int primary key identity(1,1),
DepartureAirport varchar(50),
ArrivalAirport varchar(50),
DepartureDate datetime not null,
ArrivalDate datetime not null,
Gate int,
PilotID int foreign key references Pilot(PilotID),
AircraftID int foreign key references Aircraft(AircraftID))
