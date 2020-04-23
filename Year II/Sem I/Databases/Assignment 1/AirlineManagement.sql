create database Airline
go
use Airline
go

create table Country(
CountryID int primary key identity(1,1),
Name varchar(50))

create table Passenger(
PassengerID int primary key identity(1,1),
Name varchar(50),
Phone varchar(15),
Email varchar(50))

create table Airport(
AirportID int primary key identity(1,1),
CountryID int foreign key references Country(CountryID),
City varchar(20))

create table Aircraft(
AircraftID int primary key identity(1,1),
Model varchar(50),
Capacity int default 250)

create table Pilot(
PilotID int primary key identity(1,1),
Name varchar(50))

create table Crew(
CrewID int primary key)

create table Runway(
RunwayID int primary key identity(1,1),
Track int,
Tower int)

create table Flight(
FlightID int primary key,
DepartureAirportID int foreign key references Airport(AirportID),
ArrivalAirportID int foreign key references Airport(AirportID),
DepartureDate date not null,
DepartureTime time(0) not null,
ArrivalDate date not null,
ArrivalTime time(0) not null,
Gate int,
PilotID int foreign key references Pilot(PilotID),
CrewID int foreign key references Crew(CrewID),
RunwayID int foreign key references Runway(RunwayID),
AircraftID int foreign key references Aircraft(AircraftID))

create table Booking(
BookingID int primary key identity(1,1),
PassengerID int foreign key references Passenger(PassengerID),
FlightID int foreign key references Flight(FlightID),
Price int)

create table Payment(
PaymentID int foreign key references Booking(BookingID),
constraint pk_Payment primary key(PaymentID),
Amount int,
PaymentStatus varchar(10) default 'Pending')