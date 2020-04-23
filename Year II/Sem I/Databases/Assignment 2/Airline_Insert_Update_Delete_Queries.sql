USE Airline
GO

-- INSERT INTO TABLES

INSERT INTO Country(CountryID,Name) VALUES 
(1,'Romania'),
(2,'UK'),
(3,'France'),
(4,'Italy'),
(5,'Spain')

INSERT INTO Airport(AirportID, CountryID, AirportName`) VALUES
(1, 1, 'Otopeni'),
(2, 1, 'Avram Iancu'),
(3, 2, 'Heathrow'),
(4, 2, 'Luton'),
(5, 3, 'Charles de Gaulle'),
(6, 3, 'Saint Exupery'),
(7, 4, 'Fiumicino'),
(8, 4, 'Palermo'),
(9, 5, 'Madrid-Barajas'),
(10, 5, 'Valencia')

INSERT INTO Runway(RunwayID, Track, Tower) VALUES
(1,1,1),
(2,2,2),
(3,3,3),
(4,19,4),
(5,20,5),
(6,21,6)

INSERT INTO Aircraft(AircraftID, Model, Capacity) VALUES
(1,'Boeing 707', 200),
(2,'Airbus A320', 220),
(3,'Boeing 777', 450),
(4,'Boeing 757', 150),
(5,'Boeing 727', 100)

INSERT INTO Pilot(PilotID,Name) VALUES
(1,'Eva Marseille'),
(2,'Maria Petterson'),
(3,'Linda Kats'),
(4,'John Larson')

INSERT INTO Crew(CrewID) VALUES
(1),
(2),
(3),
(4),
(5),
(6)

INSERT INTO Flight(FlightID,DepartureAirportID,ArrivalAirportID,DepartureDate,ArrivalDate,DepartureTime,ArrivalTime,Gate,PilotID,CrewID,RunwayID,AircraftID) VALUES
(1,1,2,'2019-11-10','2019-11-10','08:45:00','10:00:00',2,1,1,1,2),
(2,1,3,'2019-11-10','2019-12-10','23:15:00','00:35:00',3,2,2,1,3),
(3,2,7,'2019-11-10','2019-11-10','12:30:00','14:45:00',1,1,3,4,2),
(4,1,7,'2019-11-10','2019-11-10','14:00:00','15:45:00',8,3,5,3,1)

INSERT INTO Passenger(PassengerID, Name, Phone, Email) VALUES
(1,'Oana N','0749066933','o@scs.ubbcluj.ro'),
(2,'Georgiana M','0749177044','g@scs.ubbcluj.ro'),
(3,'Mara C','0749288155','m@scs.ubbcluj.ro'),
(4,'Vasi M','0749399266','v@scs.ubbcluj.ro'),
(5,'Lorena M','0749400377','l@scs.ubbcluj.ro')

INSERT INTO Booking(BookingID, FlightID, PassengerID, Price) VALUES
(1, 1, 1, 100),
(2, 1, 2, 100),
(3, 1, 4, 150),
(4, 1, 5, 100),
(5, 3, 3, 200)

INSERT INTO Payment(PaymentID) VALUES
(1),
(2),
(3),
(4),
(5)

-- Violates referential integrity: there is no flight 0
INSERT INTO Booking(BookingID, FlightID, PassengerID, Price) VALUES
(6,0,1,300)



-- UPDATE VALUES
UPDATE Booking
SET Price = Price + 100
WHERE FlightID = 1 AND Price < 150

UPDATE Payment
SET PaymentStatus = 'Completed'
WHERE (PaymentID IN (SELECT BookingID FROM Booking B WHERE (B.Price BETWEEN 100 AND 150) AND (B.FlightID = 1))) AND (NOT PaymentStatus = 'Completed')

UPDATE Passenger
SET Name = 'Oana Nourescu'
WHERE PassengerID = 1



-- DELETE ROWS
DELETE FROM Aircraft WHERE Capacity < 200

DELETE FROM Airport WHERE CountryID = 5