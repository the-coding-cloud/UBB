USE Airline
GO

-- A)
-- Display all the airports through which an aircraft will go (union between departure and arrival cities)
-- UNION
SELECT AirportName
FROM Airport
WHERE AirportID IN (SELECT DepartureAirportID FROM Flight WHERE AircraftID = 2)
UNION
SELECT AirportName
FROM Airport
WHERE AirportID IN (SELECT ArrivalAirportID FROM Flight WHERE AircraftID = 2)

-- Display all the incoming and departing flights for an airport
-- OR
SELECT FlightID
FROM Flight
WHERE ArrivalAirportID = 2 OR DepartureAirportID = 2


-- B)
-- Display the flights for a certain pilot leaving from a certain airport
-- INTERSECT
SELECT FlightID
FROM Flight
WHERE PilotID = 1
INTERSECT
SELECT FlightID
FROM Flight
WHERE DepartureAirportID = 1

-- Display the flights from a certain airport that depart from a range of gates
-- IN
SELECT FlightID
FROM Flight
WHERE DepartureAirportID = 1 AND (Gate IN (1,2,3))


-- C)
-- Display all bookings with a price of 200 and above, except the ones for flights that depart from a certain airport
-- EXCEPT
SELECT BookingID
FROM Booking
WHERE Price >= 200
EXCEPT
SELECT BookingID
FROM Booking
WHERE FlightID IN (SELECT FlightID FROM Flight WHERE DepartureAirportID = 2)

-- Display all the flights that don't arrive to Italy
-- NOT IN
SELECT FlightID
FROM Flight
WHERE ArrivalAirportID NOT IN (SELECT AirportID FROM Airport WHERE CountryID = 4)


-- D)
-- Display Details 
-- INNER JOIN
SELECT *
FROM Booking B INNER JOIN Flight F ON F.FlightID = B.FlightID INNER JOIN Passenger P ON B.PassengerID = P.PassengerID
 
-- Display all the countries to which a passenger will go
SELECT DISTINCT P.Name AS Passenger, C.Name AS Country
FROM Passenger P INNER JOIN  Booking B ON P.PassengerID = B.PassengerID INNER JOIN Flight F ON B.FlightID = F.FlightID INNER JOIN Airport A ON F.ArrivalAirportID = A.AirportID INNER JOIN Country C ON A.CountryID = C.CountryID

-- Display detailed information regarding the departure countries of the flights of this airline
-- LEFT JOIN (on 3 tables)
SELECT *
FROM Flight F LEFT JOIN Airport A ON F.DepartureAirportID = A.AirportID LEFT JOIN Country C ON A.CountryID = C.CountryID 

-- Display the information regarding all the flights done by all the pilots
-- RIGHT JOIN
SELECT * 
FROM Flight F RIGHT JOIN Pilot P ON P.PilotID = F.PilotID

-- FULL JOIN
SELECT *
FROM Passenger P FULL OUTER JOIN Booking B ON P.PassengerID = B.PassengerID FULL OUTER JOIN Flight F ON B.FlightID = F.FlightID

-- E)
-- Display all the flights for a certain passenger
SELECT FlightID
FROM Flight
WHERE FlightID IN (SELECT BookingID FROM Booking WHERE PassengerID = 1)

-- Display all the flights from bookings with a price of 200 and above, where the payment status is still pending
SELECT FlightID
FROM Flight
WHERE FlightID IN 
(SELECT FlightID FROM Booking WHERE Price >= 200 AND BookingID IN
(SELECT PaymentID FROM Payment WHERE PaymentStatus = 'Pending'))

                            
-- F)
-- Display all the flights that arrive to a certain country
SELECT FlightID
FROM Flight
WHERE EXISTS (SELECT AirportID FROM Airport WHERE AirportID = ArrivalAirportID AND CountryID = 4)

-- Display all the flights booked by a passenger
SELECT FlightID
FROM Flight F
WHERE EXISTS (SELECT BookingID FROM Booking B WHERE B.FlightID = F.FlightID AND PassengerID = 1)

-- G)
-- Display the passengers with bookings under the average price with 25
SELECT PassengerID
FROM (SELECT AVG(Price) AS AvgPrice FROM Booking) AS AveragePrice, Booking AS B
WHERE B.Price < AveragePrice.AvgPrice - 25

-- Display the cheapest flights
SELECT FlightID
FROM (SELECT MIN(Price) AS MinPrice FROM Booking) AS MinimumPrice, Booking AS B
WHERE B.Price = MinimumPrice.MinPrice

-- H)
-- Display the number of flights departing from an airport on each date
SELECT COUNT(FlightID) AS NumberOfFlights, DepartureDate
FROM Flight
WHERE DepartureAirportID = 1
GROUP BY DepartureDate

-- Display all the passengers with 2 or more bookings
SELECT COUNT(BookingID) AS NumberOfBookings, PassengerID
FROM Booking
GROUP BY PassengerID
HAVING COUNT(BookingID) >= 2

-- Display all the budget friendly flights
SELECT FlightID
FROM Booking
GROUP BY FlightID
HAVING MAX(Price)<=150


-- Display all the flights that have bookings with mininum price of 200
SELECT FlightID
FROM Booking
GROUP BY FlightID
HAVING MIN(Price)>=200 

-- Display the flights with more than 2 bookings
SELECT F.FlightID
FROM Flight F INNER JOIN Booking B ON F.FlightID = B.FlightID
GROUP BY F.FlightID
HAVING 2 <= (SELECT COUNT (*) FROM Booking B WHERE B.FlightID = F.FlightID)
 
-- I)
-- Display all the passengers that have a pending status to their payment (DISTINCT)
-- ANY
SELECT DISTINCT B.PassengerID
FROM Booking B
WHERE B.BookingID = ANY(SELECT B1.BookingID FROM Booking B1 INNER JOIN Payment P ON B1.BookingID = P.PaymentID WHERE P.PaymentStatus = 'Pending')

SELECT DISTINCT B.PassengerID
FROM Booking B
WHERE B.BookingID NOT IN (SELECT B.BookingID FROM Booking B INNER JOIN Payment P ON B.BookingID = P.PaymentID WHERE P.PaymentStatus = 'Completed')

-- Display the flights that are booked
-- ANY
SELECT DISTINCT F.FlightID
FROM Flight F
WHERE F.FlightID = ANY (SELECT B.FlightID FROM Booking B)

-- Check if all the passengers have bookings with a price of over 150
-- ALL
SELECT DISTINCT B.PassengerID
FROM Booking B
WHERE B.BookingID = ALL(SELECT B.BookingID FROM Booking B WHERE B.Price > 100)

-- Find the passengers that have paid all their bookings
-- ALL
SELECT B.PassengerID
FROM Booking B 
WHERE B.BookingID = ALL(SELECT B1.BookingID FROM Booking B1 INNER JOIN Payment P ON B1.BookingID = P.PaymentID WHERE P.PaymentStatus = 'Completed') 

SELECT B.PassengerID
FROM Booking B 
WHERE B.BookingID IN (SELECT B1.BookingID FROM Booking B1 INNER JOIN Payment P ON B1.BookingID = P.PaymentID WHERE P.PaymentStatus = 'Completed') 
