CREATE OR ALTER PROCEDURE AddFlight_Recovery 
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
		DECLARE @fail INT
		SET @fail = 0
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

				INSERT INTO Pilot (Name, Age) VALUES (@pilotName, @age)

				DECLARE @pid INT
				SET @pid = (SELECT IDENT_CURRENT('Pilot'))

				SAVE TRAN Pilot_Point
				print 'Saved Pilot'
			END TRY

			BEGIN CATCH
				print ERROR_MESSAGE()
				print 'Could not save Pilot'
				SET @fail = 1
			END CATCH

			BEGIN TRY
				IF(dbo.validateManufacturer(@manufacturer)<>1)
					BEGIN
					RAISERROR('Manufacturer should be Boeing, Airbus or Bombardier',14,1)
					END
				IF(dbo.validateAircraftCapacity(@aircraftCapacity)<>1)
					BEGIN
					RAISERROR('Capacity must be between 5 and 900',14,1)
					END

				INSERT INTO Aircraft (Manufacturer, Capacity) VALUES (@manufacturer, @aircraftCapacity)

				DECLARE @aid INT
				SET @aid = (SELECT IDENT_CURRENT('Aircraft'))

				SAVE TRAN Aircraft_Point
				print 'Saved Aircraft'
			END TRY

			BEGIN CATCH
				print ERROR_MESSAGE()
				print 'Could not save Aircraft'
				ROLLBACK TRAN Pilot_Point
				SET @fail = 1
			END CATCH
		
		IF (@fail = 0)
			BEGIN
				BEGIN TRY
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
				
					INSERT INTO Flight(DepartureAirport, ArrivalAirport, DepartureDate, ArrivalDate, Gate, PilotID, AircraftID) VALUES (@depAirport, @arrAirport, @depTime, @arrTime, @gate, @pid, @aid)
					COMMIT TRAN
					print 'Saved Flight'
					print 'Fully saved instances'
				END TRY

				BEGIN CATCH
					print ERROR_MESSAGE()
					ROLLBACK TRAN Aircraft_Point
					print 'Transaction rollbacked for Flight'
					COMMIT TRAN
				END CATCH
			END

		ELSE
			BEGIN
				print 'Flight could not be saved'
				COMMIT TRAN
			END

	END

-- nice case
EXEC AddFlight_Recovery 'Teddy Constantin', 20, 200, 'Airbus', 'Henri Coanda', 'Luton', '2020-11-11 13:23:44', '2020-12-11 11:23:44', 6

-- bad case
-- (pilot fails)
EXEC AddFlight_Recovery 'Alina Radacina', 5, 400, 'Boeing', 'Quebec', 'Heathrow', '2020-11-11 10:23:44', '2020-11-11 11:23:44', 3
-- (aircraft fails)
EXEC AddFlight_Recovery 'Alina Radacina', 25, 200, 'Covor zburator', 'Quebec', 'Heathrow', '2020-11-11 10:23:44', '2020-11-11 11:23:44', 3
-- (flight fails)
EXEC AddFlight_Recovery 'Leo Mihalcea', 25, 200, 'Boeing', 'Quebec', 'Heathrow', '2020-12-11 10:23:44', '2020-11-11 11:23:44', 3


SELECT * FROM Aircraft
SELECT * FROM Flight
SELECT * FROM Pilot