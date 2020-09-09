use MiniAirline
go

CREATE OR ALTER FUNCTION validatePilotAge (@age int) RETURNS INT AS
BEGIN
DECLARE @return INT
SET @return = 0
IF(@age > 17 AND @age < 65)
	SET @return = 1
RETURN @return
END

go

CREATE OR ALTER FUNCTION validateAircraftCapacity (@capacity int) RETURNS INT AS
BEGIN
DECLARE @return INT
SET @return = 0
IF(@capacity > 5 AND @capacity < 900)
	SET @return = 1
RETURN @return
END

go

CREATE OR ALTER FUNCTION validateManufacturer (@manufacturer varchar(100)) RETURNS INT AS
BEGIN
DECLARE @return INT
SET @return = 0
IF(@manufacturer IN ('Boeing', 'Airbus', 'Bombardier'))
SET @return = 1
RETURN @return
END

go

CREATE OR ALTER FUNCTION validateAirportName (@airport varchar(100)) RETURNS INT AS
BEGIN
DECLARE @return INT
SET @return = 0
IF(NOT @airport LIKE '%[^a-Z ''-]%')
SET @return = 1
RETURN @return
END

go

CREATE OR ALTER FUNCTION validatePilotName (@pilotName varchar(100)) RETURNS INT AS
BEGIN
DECLARE @return INT
SET @return = 0
IF(NOT @pilotName LIKE '%[^a-Z ''-]%')
SET @return = 1
RETURN @return
END

go

CREATE OR ALTER FUNCTION validateFlightTimes (@depTime datetime, @arrTime datetime) RETURNS INT AS
BEGIN
DECLARE @return INT
SET @return = 0
IF(getdate() < @depTime AND @depTime < @arrTime)
SET @return = 1
RETURN @return
END

go

CREATE OR ALTER FUNCTION validateGate (@gate int) RETURNS INT AS
BEGIN
DECLARE @return INT
SET @return = 0
IF(@gate > 0)
SET @return = 1
RETURN @return
END

go

SELECT dbo.validatePilotAge(20)
SELECT dbo.validateAirportName('Avram Iancu Cluj')
SELECT dbo.validateFlightTimes('2020-11-11 13:23:44', '2020-11-11 12:23:44')