use MiniAirline
go

CREATE OR ALTER PROCEDURE AddFlight 
		@pilotName varchar(50), 
		@age int, 
		@aircraftCapacity int, 
		@manufacturer varchar(50),
		@depAirport varchar(50),
		@arrAirport varchar(50),
		@depTime datetime, 
		@arrTime datetime,
		@gate int
	AS
		BEGIN
		BEGIN TRAN
			BEGIN TRY
				IF(dbo.validatePilotName(@pilotName)<>1)
					BEGIN
					RAISERROR('Name must consist only of English letters and ''/- ',14,1)
					END
				IF(dbo.validatePilotAge(@age)<>1)
					BEGIN
					RAISERROR('Age must be between 18 and 60',14,1)
					END
				IF(dbo.validateManufacturer(@manufacturer)<>1)
					BEGIN
					RAISERROR('Manufacturer should be Boeing, Airbus or Bombardier',14,1)
					END
				IF(dbo.validateAircraftCapacity(@aircraftCapacity)<>1)
					BEGIN
					RAISERROR('Capacity must be between 5 and 900',14,1)
					END
				IF(dbo.validateAirportName(@depAirport)<>1)
					BEGIN
					RAISERROR('Name must consist only of English letters and ''/- ',14,1)
					END
				IF(dbo.validateAirportName(@arrAirport)<>1)
					BEGIN
					RAISERROR('Name must consist only of English letters and ''/- ',14,1)
					END
				IF(dbo.validateFlightTimes(@depTime, @arrTime)<>1)
					BEGIN
					RAISERROR('Invalid departure/arrival time',14,1)
					END
				IF(dbo.validateGate(@gate)<>1)
					BEGIN
					RAISERROR('Invalid gate',14,1)
					END

				INSERT INTO Aircraft (Manufacturer, Capacity) VALUES (@manufacturer, @aircraftCapacity)
				DECLARE @aid INT
				SET @aid = (SELECT IDENT_CURRENT('Aircraft'))

				INSERT INTO Pilot (Name, Age) VALUES (@pilotName, @age)
				DECLARE @pid INT
				SET @pid = (SELECT IDENT_CURRENT('Pilot'))
				
				INSERT INTO Flight(DepartureAirport, ArrivalAirport, DepartureDate, ArrivalDate, Gate, PilotID, AircraftID) VALUES (@depAirport, @arrAirport, @depTime, @arrTime, @gate, @pid, @aid)
				COMMIT TRAN
				print 'Transaction committed'
			END TRY

			BEGIN CATCH
				print ERROR_MESSAGE()
				print 'Transaction rollbacked'
				ROLLBACK TRAN
			END CATCH
	END

-- nice case
EXEC AddFlight 'Ruxi Constantin', 25, 200, 'Airbus', 'Otopeni', 'Luton', '2020-09-11 10:23:44', '2020-11-11 11:23:44', 6

-- bad case
-- (flight fails --- case of time travelling)
EXEC AddFlight 'Maria Muresan', 20, 200, 'Boeing', 'Lyon Saint-Exupery', 'Heathrow', '2020-12-11 13:23:44', '2020-11-11 11:23:44', 3


SELECT * FROM Aircraft
SELECT * FROM Flight
SELECT * FROM Pilot