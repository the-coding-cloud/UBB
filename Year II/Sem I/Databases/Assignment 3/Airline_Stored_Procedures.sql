USE Airline
GO

--- a) Modify the type of a column
CREATE PROCEDURE ModifyPlaneCapacityType
AS
BEGIN
	ALTER TABLE Aircraft
	ALTER COLUMN Capacity smallint not null

	UPDATE CurrentVersion
	SET version = 1
END
GO 

EXEC ModifyPlaneCapacityType

CREATE PROCEDURE RevertPlaneCapacityType
AS
BEGIN
	ALTER TABLE Aircraft
	ALTER COLUMN Capacity int

	UPDATE CurrentVersion
	SET version = 0
END
GO

EXEC RevertPlaneCapacityType

---b) Add/Remove a column

CREATE PROCEDURE AddCrewName
AS
BEGIN
	ALTER TABLE Crew
	ADD CrewName varchar(20)

	UPDATE CurrentVersion
	SET version = 2
END
GO

EXEC AddCrewName
	
CREATE PROCEDURE RemoveCrewName
AS
BEGIN
	ALTER TABLE Crew
	DROP COLUMN CrewName

	UPDATE CurrentVersion
	SET version = 1
END
GO

EXEC RemoveCrewName

--- c) Add/Remove default constraint

CREATE PROCEDURE AddCapacityDefault
AS
BEGIN
	ALTER TABLE Aircraft
	ADD CONSTRAINT DF_PlaneCap DEFAULT 150 FOR Capacity

	UPDATE CurrentVersion
	SET version = 3
END
GO

EXEC AddCapacityDefault

CREATE PROCEDURE RemoveCapacityDefault
AS 
BEGIN
	ALTER TABLE Aircraft
	DROP CONSTRAINT DF_PlaneCap

	UPDATE CurrentVersion
	SET version = 2
END
GO

EXEC RemoveCapacityDefault

--- d) Add/Remove primary key

CREATE PROCEDURE AddPKFlightAttendant
AS
BEGIN
	CREATE TABLE FlightAttendant(
	AttendantID INT,
	Name VARCHAR(50),
	CONSTRAINT PK__FlightAtt PRIMARY KEY(AttendantID)
	)

	UPDATE CurrentVersion
	SET version = 4
END
GO

EXEC AddPKFlightAttendant

CREATE PROCEDURE RemovePKFlightAttendant
AS
BEGIN
	ALTER TABLE FlightAttendant
	DROP CONSTRAINT PK__FlightAtt
	DROP TABLE FlightAttendant

	UPDATE CurrentVersion
	SET version = 3
END
GO

EXEC RemovePKFlightAttendant

--- e) Add/Remove candidate key

CREATE PROCEDURE AddUniqueTower
AS
BEGIN
	ALTER TABLE Runway
	ADD CONSTRAINT UK__Tower UNIQUE(Tower)

	UPDATE CurrentVersion
	SET version = 5
END
GO 

EXEC AddUniqueTower

CREATE PROCEDURE RemoveUniqueTower
AS
BEGIN
	ALTER TABLE Runway
	DROP CONSTRAINT UK__Tower

	UPDATE CurrentVersion
	SET version = 4
END
GO

EXEC RemoveUniqueTower

--- f) Add/Remove foreign key

CREATE PROCEDURE RemoveFKAirport
AS
BEGIN
	ALTER TABLE Airport
	DROP CONSTRAINT FK__Airport_CountryID

	UPDATE CurrentVersion
	SET version = 6
END
GO

EXEC RemoveFKAirport

CREATE PROCEDURE AddFKAirport
AS
BEGIN
	ALTER TABLE Airport
	ADD CONSTRAINT FK__Airport_CountryID FOREIGN KEY(CountryID) REFERENCES Country(CountryID)

	UPDATE CurrentVersion
	SET version = 5
END
GO

EXEC AddFKAirport

--- g) Create/Remove table

CREATE PROCEDURE AddOffices
AS
BEGIN
	CREATE TABLE Office(
	OfficeID INT NOT NULL PRIMARY KEY,
	CountryID INT FOREIGN KEY REFERENCES Country(CountryID))

	UPDATE CurrentVersion
	SET version = 7
END
GO

EXEC AddOffices

CREATE PROCEDURE RemoveOffices
AS
BEGIN
	DROP TABLE Office
	
	UPDATE CurrentVersion
	SET version = 6

END
GO

EXEC RemoveOffices


--Create a new table that holds the current version of the database schema. For simplicity, the version is assumed to be an integer number.

CREATE TABLE CurrentVersion(
version INT PRIMARY KEY)

INSERT INTO CurrentVersion values (0);


--Write another stored procedure that receives as a parameter a version number and brings the database to that version.

CREATE TABLE AllVersions(
version INT PRIMARY KEY,
do VARCHAR(50),
undo VARCHAR(50))

INSERT INTO AllVersions(version, do, undo)
VALUES (0, null, null),
(1, 'ModifyPlaneCapacityType', 'RevertPlaneCapacityType'),
(2, 'AddCrewName', 'RemoveCrewName'),
(3, 'AddCapacityDefault', 'RemoveCapacityDefault'),
(4, 'AddPKFlightAttendant', 'RemovePKFlightAttendant'),
(5, 'AddUniqueTower', 'RemoveUniqueTower'),
(6, 'RemoveFKAirport', 'AddFKAirport'),
(7, 'AddOffices', 'RemoveOffices')

SELECT*
FROM AllVersions